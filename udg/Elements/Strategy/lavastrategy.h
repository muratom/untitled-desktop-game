#ifndef LAVASTRATEGY_H
#define LAVASTRATEGY_H

#include "Elements/Strategy/iinteractionstrategy.h"
#include "Elements/FactoryMethod/Products/lava.h"
#include "Units/iunit.h"

#include <QDebug>

namespace Elements {
class LavaStrategy : public IInteractionStrategy {
public:
  LavaStrategy() = default;
  ~LavaStrategy() = default;

  void InteractWith(Units::IUnit& unit, IElement& elem) override;
};
}

#endif // LAVASTRATEGY_H
