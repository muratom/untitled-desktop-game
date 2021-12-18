#include "wallcreator.h"

namespace Elements {
std::shared_ptr<IElement> WallCreator::CreateElement() {
  return std::shared_ptr<IElement>(new Wall());
}
}
