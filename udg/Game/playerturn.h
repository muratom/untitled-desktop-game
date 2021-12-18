#ifndef PLAYERTURN_H
#define PLAYERTURN_H

#include <memory>

#include "iturn.h"

namespace Game {
class Game;
}

namespace Turn {
// Инвариант:
// Чередование ходов между игроком и врагом
class PlayerTurn : public ITurn {
public:
  PlayerTurn(Game::Game& game);
  ~PlayerTurn() = default;

  void MakeMove() override;

private:
  Game::Game& game_;
};
}

#endif // PLAYERTURN_H
