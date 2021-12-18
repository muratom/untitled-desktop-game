#ifndef HEALTHSTRATEGY_H
#define HEALTHSTRATEGY_H

#include "Elements/Strategy/iinteractionstrategy.h"
#include "Elements/FactoryMethod/Products/health.h"
#include "Units/iunit.h"

#include <QDebug>

namespace Elements {
class HealthStrategy : public IInteractionStrategy {
public:
  HealthStrategy() = default;
  ~HealthStrategy() = default;

  void InteractWith(Units::IUnit& unit, IElement& elem) override;
};
}

#endif // HEALTHSTRATEGY_H
