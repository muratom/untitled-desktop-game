#include "lavastrategy.h"

void Elements::LavaStrategy::InteractWith(Units::IUnit& unit, Elements::IElement& elem) {
  Lava& lava = static_cast<Lava&>(elem);
  unit.SetHealth(unit.GetHealth() - lava.GetDamage());
  qDebug() << "Interaction with lava ended: unit.GetHealth() = " << unit.GetHealth();
}
