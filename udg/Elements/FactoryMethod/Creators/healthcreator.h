#ifndef HEALTHCREATOR_H
#define HEALTHCREATOR_H

#include <memory>

#include "creator.h"
#include "Elements/FactoryMethod/Products/health.h"

namespace Elements {
class HealthCreator : public Creator {
public:
  HealthCreator() = default;
  ~HealthCreator() = default;

  std::shared_ptr<IElement> CreateElement() override;
};
}

#endif // HEALTHCREATOR_H
