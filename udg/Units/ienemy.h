#ifndef IENEMY_H
#define IENEMY_H

#include "iunit.h"
// #include "player.h"

namespace Units {

class Player;

enum MovementPolitic : int16_t {
  HORIZONTAL, VERTICAL, RANDOM
};

enum AttackPolitic : int16_t {
  NEAR, DISTANT
};

struct BlasterBeam {
  using Point2D = std::pair<int16_t, int16_t>;
  BlasterBeam(Point2D crd, int16_t orient, int16_t damage)
    : crd(crd), orient(static_cast<Orientation>(orient)), damage(damage) {}
  Point2D crd;
  Orientation orient;
  int16_t damage;
};

class IEnemy : public IUnit {
public:
  IEnemy() = default;
  ~IEnemy() = default;

  virtual MovementPolitic GetMovePltc() const = 0;
  virtual AttackPolitic GetAttackPltc() const = 0;

  virtual IEnemy& operator-(Player& plr) = 0;
};

}

#endif // IENEMY_H
