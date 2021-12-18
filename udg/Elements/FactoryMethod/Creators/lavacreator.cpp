#include "lavacreator.h"

namespace Elements {
std::shared_ptr<IElement> LavaCreator::CreateElement() {
  return std::shared_ptr<IElement>(new Lava());
}
}
