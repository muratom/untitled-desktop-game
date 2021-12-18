#ifndef COINSTRATEGY_H
#define COINSTRATEGY_H

#include "Elements/Strategy/iinteractionstrategy.h"
#include "Elements/FactoryMethod/Products/coin.h"
#include "Units/iunit.h"

#include <QDebug>

namespace Elements {
// Инвариант
// С монетой может взаимодействовать только игрок
class CoinStrategy : public IInteractionStrategy {
public:
  CoinStrategy() = default;
  ~CoinStrategy() = default;

  void InteractWith(Units::IUnit& unit, IElement& elem) override;
};
}


#endif // COINSTRATEGY_H
