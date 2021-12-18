#ifndef WALLCREATOR_H
#define WALLCREATOR_H

#include <memory>

#include "creator.h"
#include "Elements/FactoryMethod/Products/wall.h"

namespace Elements {
class WallCreator : public Creator {
public:
  WallCreator() = default;
  ~WallCreator() = default;

  std::shared_ptr<IElement> CreateElement() override;
};
}

#endif // WALLCREATOR_H
