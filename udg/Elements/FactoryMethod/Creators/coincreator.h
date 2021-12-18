#ifndef COINCREATOR_H
#define COINCREATOR_H

#include <memory>
#include <exception>
#include <iostream>

#include "creator.h"
#include "Elements/FactoryMethod/Products/coin.h"

namespace Elements {
class CoinCreator : public Creator {
public:
  CoinCreator() = default;
  ~CoinCreator() = default;

  std::shared_ptr<IElement> CreateElement() override;
};
}

#endif // COINCREATOR_H
