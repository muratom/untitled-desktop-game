#ifndef FLOORCREATOR_H
#define FLOORCREATOR_H

#include <memory>
#include <exception>
#include <iostream>

#include "creator.h"
#include "Elements/FactoryMethod/Products/floor.h"

namespace Elements {
class FloorCreator : public Creator {
public:
  FloorCreator() = default;
  ~FloorCreator() = default;

  std::shared_ptr<IElement> CreateElement() override;
};
}

#endif // FLOORCREATOR_H
