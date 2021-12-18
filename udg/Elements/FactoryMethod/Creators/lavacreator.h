#ifndef LAVACREATOR_H
#define LAVACREATOR_H

#include <memory>

#include "creator.h"
#include "Elements/FactoryMethod/Products/lava.h"

namespace Elements {
class LavaCreator : public Creator {
public:
  LavaCreator() = default;
  ~LavaCreator() = default;

  std::shared_ptr<IElement> CreateElement() override;
};
}

#endif // LAVACREATOR_H
