#include "coincreator.h"

namespace Elements {
std::shared_ptr<IElement> CoinCreator::CreateElement() {
  return std::shared_ptr<IElement>(new Coin());
}
}
