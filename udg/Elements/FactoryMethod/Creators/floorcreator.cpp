#include "floorcreator.h"

std::shared_ptr<Elements::IElement> Elements::FloorCreator::CreateElement() {
  return std::shared_ptr<IElement>(new Floor());
}
