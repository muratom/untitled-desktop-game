#include "playerturn.h"
#include "game.h"
#include "enemyturn.h"
#include "Units/player.h"
#include "Units/enemy.h"

#include <QDebug>

namespace Turn {

PlayerTurn::PlayerTurn(Game::Game& game)
    : game_(game) {}

void PlayerTurn::MakeMove() {
  auto& player = game_.GetPlayer();
  Field::PlayingField* pf_ptr = game_.GetPF();

  // Проверяем жив ли игрок,
  // если он умирает, то игра завершается
  if (game_.IsPlayerAlive()) {
    game_.MoveUnit();
    game_.SetMoveCmd(nullptr);
    for (size_t i = 0; i < game_.GetEnemies().size(); ++i){
      if (pf_ptr->GetEnemiesCoord()[i] == pf_ptr->GetPlayerCoord()) {
        *game_.GetEnemies()[i] - *player;
      }
    }
  }
  // Смена хода
  game_.SetTurn(std::make_shared<Turn::EnemyTurn>(game_));

  // qDebug() << "Player's turn ended";
}

}
