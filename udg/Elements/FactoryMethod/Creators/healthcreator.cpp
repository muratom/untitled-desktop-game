#include "healthcreator.h"

namespace Elements {
std::shared_ptr<IElement> HealthCreator::CreateElement() {
  return std::shared_ptr<IElement>(new Health());
}
}

