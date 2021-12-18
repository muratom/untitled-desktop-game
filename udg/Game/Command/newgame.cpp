#include "newgame.h"

namespace Command {
NewGame::NewGame(GamePtr& game, const std::string& input_file_name)
  : game_(game), input_file_name_(input_file_name) {}

void NewGame::Execute() const {
  game_->NewGame(input_file_name_);
}
}
