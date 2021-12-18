#ifndef MOVE_H
#define MOVE_H

#include "icommand.h"
#include "Units/iunit.h"
#include "Game/game.h"

namespace Command {

class Move : public ICommand {
  using GamePtr = std::shared_ptr<Game::Game>;
  using UnitPtr = std::shared_ptr<Units::IUnit>;
public:
  explicit Move(GamePtr& game, UnitPtr unit, Field::Point2D& unit_crd, Units::Orientation orient);
  void Execute() const override;

private:
  GamePtr& game_;
  UnitPtr unit_;
  // Ссылка нужна, чтобы изменять координаты в полях других классов
  Field::Point2D& unit_crd_;
  Units::Orientation orient_;
};
}

#endif // MOVE_H
