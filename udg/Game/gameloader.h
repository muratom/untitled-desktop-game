#ifndef GAMELOADER_H
#define GAMELOADER_H

#include <exception>
#include <fstream>

#include "game.h"

namespace Game {

class LoadException : public std::exception {
public:
  LoadException(std::string info = "")
    : info_(info) {}
  const char* what() const noexcept { return info_.c_str(); }
private:
  std::string info_;
};

// Инвариант:
// 1) В случае неправильного формата файла или входных данных выбрасывается исключение
// 2) Файл закроется, когда уничтожается объект
class GameLoader {
  using PlayerPtr = std::shared_ptr<Units::Player>;
  using LogPtr = std::shared_ptr<Log::Log>;
  using CommandPtr = std::shared_ptr<Command::ICommand>;
  using TurnPtr = std::shared_ptr<Turn::ITurn>;
  using EnemyPtr = std::shared_ptr<Units::IEnemy>;
  using CreatorPtr = std::shared_ptr<Elements::Creator>;
  using Point2D = std::pair<int16_t, int16_t>;

  // Типы противников
  using HorizontalShooter = Units::Enemy<Units::MovementPolitic::HORIZONTAL, Units::AttackPolitic::DISTANT>;
  using VerticalShooter = Units::Enemy<Units::MovementPolitic::VERTICAL, Units::AttackPolitic::DISTANT>;
  using HorizontalFighter = Units::Enemy<Units::MovementPolitic::HORIZONTAL, Units::AttackPolitic::NEAR>;
  using VerticalFighter = Units::Enemy<Units::MovementPolitic::VERTICAL, Units::AttackPolitic::NEAR>;

public:
  GameLoader(Game& game, const std::string& file_name);
  ~GameLoader();

  void Load();

private:
  Game& game_;
  std::fstream load_file_;
};
}

#endif // GAMELOADER_H
