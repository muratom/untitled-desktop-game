#ifndef EXITGAME_H
#define EXITGAME_H

#include "icommand.h"
#include "Game/game.h"

namespace Command {
class ExitGame : public ICommand {
  using GamePtr = std::shared_ptr<Game::Game>;
public:
  explicit ExitGame(GamePtr& game);
  void Execute() const override;

private:
  GamePtr& game_;
};
}

#endif // EXITGAME_H
