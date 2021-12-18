#include "healthstrategy.h"

void Elements::HealthStrategy::InteractWith(Units::IUnit& unit, Elements::IElement& elem) {
  Health& health = static_cast<Health&>(elem);
  if (health.IsUsed())
    return;
  if (unit.GetHealth() == 100) {
    health.SetIsUsed(false);
    return;
  }
  unit.SetHealth(unit.GetHealth() + health.GetValue());
  health.SetIsUsed(true);
  qDebug() << "Interaction with health ended: unit.GetHealth() = " << unit.GetHealth();
}
