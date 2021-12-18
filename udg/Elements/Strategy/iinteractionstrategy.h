#ifndef IINTERACTIONSTRATEGY_H
#define IINTERACTIONSTRATEGY_H

#include "Elements/FactoryMethod/Products/ielement.h"

// Здесь нужен forward declaration, так как иначе все классы,
// реализующие интерфейс IInteractionStrategy будут абстрактными
namespace Units {
class IUnit;
}

namespace Elements {
// Interface "Strategy" in design pattern "Strategy"
class IInteractionStrategy {
public:
  virtual ~IInteractionStrategy() = default;
  virtual void InteractWith(Units::IUnit& unit, IElement& elem) = 0;
};
}

#endif // IINTERACTIONSTRATEGY_H
