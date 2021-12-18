#ifndef GAME_H
#define GAME_H

#include <QDebug>

#include <memory>
#include <vector>
#include <list>
#include <ctime>
#include <unistd.h>

#include "Log/log.h"
#include "Field/playingfield.h"
#include "Command/icommand.h"
#include "Command/configurelog.h"

#include "Elements/FactoryMethod/Creators/coincreator.h"
#include "Elements/FactoryMethod/Creators/floorcreator.h"
#include "Elements/FactoryMethod/Creators/healthcreator.h"
#include "Elements/FactoryMethod/Creators/lavacreator.h"
#include "Elements/FactoryMethod/Creators/wallcreator.h"

#include "iturn.h"
#include "playerturn.h"
#include "Units/iunit.h"
#include "Units/player.h"
#include "Units/enemy.h"

// constexpr double MS_PER_FRAME = 0.000016; // миллисекуды на один фрейм (при 16 мс. FPS = 60)

namespace Command {
class NewGame;
class Move;
}

namespace Game {
class GameLoader;

// Инварианты:
// 1) Все поля в валидном состоянии (достигается с помощью снимка)
// 2) target_points_ >= 0

class Game : public Observer::IEmitter {
  friend GameLoader;

  using PlayerPtr = std::shared_ptr<Units::Player>;
  using LogPtr = std::shared_ptr<Log::Log>;
  using CommandPtr = std::shared_ptr<Command::ICommand>;
  using TurnPtr = std::shared_ptr<Turn::ITurn>;
  using EnemyPtr = std::shared_ptr<Units::IEnemy>;

  // Типы противников
  using HorizontalShooter = Units::Enemy<Units::MovementPolitic::HORIZONTAL, Units::AttackPolitic::DISTANT>;
  using VerticalShooter = Units::Enemy<Units::MovementPolitic::VERTICAL, Units::AttackPolitic::DISTANT>;
  using HorizontalFighter = Units::Enemy<Units::MovementPolitic::HORIZONTAL, Units::AttackPolitic::NEAR>;
  using VerticalFighter = Units::Enemy<Units::MovementPolitic::VERTICAL, Units::AttackPolitic::NEAR>;

public:
  Game();
  ~Game() = default;

  // Возвращаемое значение означает успешность проведенного действия
  bool NewGame(const std::string& input_file);
  bool SaveGame();
  bool LoadGame(const std::string& input_file);
  void ExitGame();

  bool GetInGame() const { return in_game_; }
  void SetInGame(bool val) { in_game_ = val; }

  bool GetIsInitialized() { return is_initialized_; }
  Field::PlayingField* GetPF() { return pf_ptr_; }
  PlayerPtr& GetPlayer() { return player_; }
  std::vector<EnemyPtr>& GetEnemies() { return enemies_; }
  std::list<Units::BlasterBeam>& GetBlasterBeams() { return blaster_beams_; }
  LogPtr& GetLog() { return log_; }

  int16_t GetTargetPoints() const { return target_points_; }
  void SetTargetPoints(int16_t tp);

  bool IsPlayerAlive();
  bool IsLevelComplete();

  // Паттерн "Состояние"
  void SetTurn(TurnPtr t) { turn_ = t; }
  const TurnPtr& GetTurn() const { return turn_; }
  void MakeMove() { turn_->MakeMove(); }

  // Паттерн "Команда"
  void SetMoveCmd(const CommandPtr& move_cmd) { move_cmd_ = move_cmd; }
  void MoveUnit();

  void SetConfLogCmd(const CommandPtr& conf_log_cmd) { configure_log_cmd_ = conf_log_cmd; }
  void ConfigureLog();

  void SetNewGameCmd(const CommandPtr& ng_cmd) { new_game_cmd_ = ng_cmd; }
  void ExecNewGameCmd();

  void SetExitGameCmd(const CommandPtr& eg_cmd) { exit_game_cmd_ = eg_cmd; }
  void ExecExitGameCmd();

  // Паттерн "Наблюдатель"
  void Connect(Observer::IReceiver* rec) override;
  void Disconnect(Observer::IReceiver* rec) override;
  void NotifyListeners() override;

  // Паттерн "Снимок"
  class Memento {
  public:
    // Данные записываются в файл сразу после того, как будет сделан "снимок" состояния,
    // следовательно, нет необходимости создавать копии полей с выделением дополнительной памяти
    Memento(const Game& game);

    std::shared_ptr<Field::PlayingField::Memento> GetPfState() { return pf_memento_; }
    std::shared_ptr<Units::Player::Memento> GetPlrState() { return plr_memento_; }

    const std::vector<EnemyPtr>& GetEnemies() { return enemies_; }
    const std::list<Units::BlasterBeam>& GetBlasterBeams() { return blaster_beams_; }

    bool GetInGame() { return in_game_; }
    int16_t GetTP() { return target_points_; }

    const TurnPtr& GetTurn() { return turn_; }
    const LogPtr& GetLog() { return log_; }

  private:
    std::shared_ptr<Field::PlayingField::Memento> pf_memento_;
    std::shared_ptr<Units::Player::Memento> plr_memento_;

    // Нужно сохранить данные контейнеры, так как во время загрузки уровня они могут быть удалены (метод clear в GameLoader::Load())
    std::vector<EnemyPtr> enemies_;
    std::list<Units::BlasterBeam> blaster_beams_;

    bool in_game_;
    int16_t target_points_;

    const TurnPtr& turn_;
    const LogPtr& log_;
  };

  Memento SaveState() const;
  void RestoreState(Memento& m);

protected:
  // Часть паттерна "Наблюдатель"
  void Print(std::ostream& os) const override;

private:
  bool is_initialized_ = false;

  Field::PlayingField* pf_ptr_ = nullptr; // Поле находится в RW-сегменте памяти (очищение после завершения программы), нельзя использовать умные указатели
  PlayerPtr player_ = nullptr;
  std::vector<EnemyPtr> enemies_;
  // Лучи бластера, которые были выпущены врагами
  std::list<Units::BlasterBeam> blaster_beams_;

  bool in_game_ = false; // Состояние игры (в игре/игра окончена)
  int16_t target_points_ = 0; // Необходимое для прохождения уровня кол-во очков

  // Паттерн "Состояние"
  TurnPtr turn_ = std::make_shared<Turn::PlayerTurn>(*this);

  // Паттерн "Наблюдатель"
  LogPtr log_ = nullptr;
  std::list<Observer::IReceiver*> receiver_list_;

  // Паттерн "Команда"
  CommandPtr move_cmd_ = nullptr;
  CommandPtr configure_log_cmd_ = nullptr;
  CommandPtr new_game_cmd_ = nullptr;
  CommandPtr exit_game_cmd_ = nullptr;
};
}

#endif // GAME_H
