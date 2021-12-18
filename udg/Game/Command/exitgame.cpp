#include "exitgame.h"

namespace Command {
ExitGame::ExitGame(ExitGame::GamePtr& game)
  : game_(game) {}

void ExitGame::Execute() const {
  game_->ExitGame();
}
}
