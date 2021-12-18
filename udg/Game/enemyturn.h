#ifndef ENEMYTURN_H
#define ENEMYTURN_H

#include <memory>
#include <cstdlib>

#include "iturn.h"
// #include "game.h"

namespace Game {
class Game;
}

namespace Turn {
// Инвариант:
// Чередование ходов между игроком и врагом
class EnemyTurn : public ITurn {
public:
  EnemyTurn(Game::Game& game);
  ~EnemyTurn() = default;

  void MakeMove() override;

private:
  Game::Game& game_;
};
}

#endif // ENEMYTURN_H
