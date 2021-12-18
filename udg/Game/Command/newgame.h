#ifndef NEWGAME_H
#define NEWGAME_H

#include <QDebug>

#include <vector>

#include "icommand.h"
#include "Game/game.h"

namespace Command {
class NewGame : public ICommand {
  using GamePtr = std::shared_ptr<Game::Game>;
public:
  explicit NewGame(GamePtr& game, const std::string& input_file_name);
  void Execute() const override;

private:
  GamePtr& game_;
  std::string input_file_name_;
};
}

#endif // NEWGAME_H
