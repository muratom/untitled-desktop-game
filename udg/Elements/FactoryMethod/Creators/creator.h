#ifndef CREATOR_H
#define CREATOR_H

#include <memory>

#include "Elements/FactoryMethod/Products/ielement.h"

namespace Elements {
// Using "Factory method" design pattern
class Creator {
public:
  Creator() = default;
  virtual ~Creator() = default;

  virtual std::shared_ptr<IElement> CreateElement() = 0;
};
}

#endif // CREATOR_H
