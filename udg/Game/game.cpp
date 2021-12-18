#include "game.h"

#include "gameloader.h"
#include "gamesaver.h"

namespace Game {

Game::Game()
    : pf_ptr_(&Field::PlayingField::GetInstance()) {}

bool Game::NewGame(const std::string& input_file) {
  // Использование паттерна "Снимок"
  auto game_memento = SaveState();

  try {
    GameLoader gl(*this, input_file);
    gl.Load();

    // Теперь мы в игре
    in_game_ = true;
    NotifyListeners();

    // Игра инициализирована
    is_initialized_ = true;

    return true;
  } catch (std::exception& e) { // std::exception, так как может произойти bad_alloc
    std::cerr << e.what() << std::endl;

    RestoreState(game_memento);

    // Неудачная попытка загрузки игры
    return false;
  }
}

bool Game::SaveGame() {
  try {
    GameSaver gs(*this);
    gs.Save();

    // Сохранение игры прошло успешно
    return true;
  } catch (SaveException& se) {
    std::cerr << se.what() << std::endl;

    // Не удалось сохранить игру
    return false;
  }
}

bool Game::LoadGame(const std::string& input_file) {
  // Использование паттерна "Снимок"
  auto game_memento = SaveState();

  try {
    GameLoader gl(*this, input_file);
    gl.Load();

    // Уведомление подписчиков
    NotifyListeners();

    // Игра инициализирована
    is_initialized_ = true;

    // Загрузка игры прошла успешно
    return true;
  } catch (std::exception& e) { // std::exception, так как может произойти bad_alloc
    std::cerr << e.what() << std::endl;

    RestoreState(game_memento);

    // Неудачная попытка загрузки игры
    return false;
  }
}

void Game::ExitGame() {
  is_initialized_ = false;

  pf_ptr_->Clear();
  player_.reset();
  enemies_.clear();
  blaster_beams_.clear();
  turn_.reset();
  in_game_ = false;
  log_.reset();
  receiver_list_.clear();

  move_cmd_.reset();
  configure_log_cmd_.reset();
  new_game_cmd_.reset();
  exit_game_cmd_.reset();
}

void Game::SetTargetPoints(int16_t tp) {
  // Если значение целевых очков отрицательно,
  // то не выбрасываем исключение, а записываем 0
  if (tp < 0)
    target_points_ = 0;
  else
    target_points_ = tp;
}

void Game::MoveUnit() {
  if (move_cmd_ && in_game_)
    move_cmd_->Execute();
}

void Game::ConfigureLog() {
  // Это условие необходимо, так как объект класса Game не удаляется
  if (log_) {
    Disconnect(log_.get());
  }
  if (configure_log_cmd_)
    configure_log_cmd_->Execute();
  else // Если лог не нужен, то и объект нужно удалить
    log_ = nullptr;
}

void Game::ExecNewGameCmd() {
  if (new_game_cmd_)
    new_game_cmd_->Execute();
}

void Game::ExecExitGameCmd() {
  if (exit_game_cmd_) {
    exit_game_cmd_->Execute();
  }
}

bool Game::IsPlayerAlive() {
  if (player_->GetHealth() == 0) {
    in_game_ = false;
    NotifyListeners();
    return false;
  }
  return true;
}

bool Game::IsLevelComplete() {
  if (pf_ptr_->GetPlayerCoord() == pf_ptr_->GetExitCoord() &&
      player_->GetPoints() >= target_points_) {
    in_game_ = false;
    NotifyListeners();
    return true;
  }
  return false;
}

void Game::Connect(Observer::IReceiver* rec) {
  receiver_list_.push_back(rec);
}

void Game::Disconnect(Observer::IReceiver* rec) {
  receiver_list_.remove(rec);
}

void Game::NotifyListeners() {
  for (auto& rec : receiver_list_) {
    rec->Update(*this);
  }
}

Game::Memento Game::SaveState() const {
  return Memento(*this);
}

void Game::RestoreState(Game::Memento& m) {
  if (m.GetPfState())
    pf_ptr_->RestoreState(*m.GetPfState());
  else
    pf_ptr_ = nullptr;

  if (m.GetPlrState())
    player_->RestoreState(*m.GetPlrState());
  else
    player_ = nullptr;

  enemies_ = m.GetEnemies();
  blaster_beams_ = m.GetBlasterBeams();
  in_game_ = m.GetInGame();
  target_points_ = m.GetTP();
  log_ = m.GetLog();
  turn_ = m.GetTurn();
}

void Game::Print(std::ostream &os) const {
  if (in_game_) {
    os << "Game is on!\n";
  } else { // in_game_ == false
    if (player_->GetHealth() == 0) {
      os << "Game over!\n";
    } else if (pf_ptr_->GetPlayerCoord() == pf_ptr_->GetExitCoord() &&
               player_->GetPoints() >= target_points_) {
      os << "Level complete!\n";
    }
  }
}

Game::Memento::Memento(const Game& game)
    : enemies_(game.enemies_),
      blaster_beams_(game.blaster_beams_),
      in_game_(game.in_game_),
      target_points_(game.target_points_),
      turn_(game.turn_),
      log_(game.log_) {
  if (game.pf_ptr_) {
    pf_memento_ = std::make_shared<Field::PlayingField::Memento>(game.pf_ptr_->SaveState());
  } else {
    pf_memento_ = nullptr;
  }

  if (game.player_) {
    plr_memento_ = std::make_shared<Units::Player::Memento>(game.player_->SaveState());
  } else {
    plr_memento_ = nullptr;
  }
}
}
