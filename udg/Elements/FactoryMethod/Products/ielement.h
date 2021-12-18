#ifndef IELEMENT_H
#define IELEMENT_H

#include <memory>
#include <ostream>
#include <list>

#include "Log/Observer/iemitter.h"

namespace Elements {
// Using "Factory method" design patterns
class IElement : public Observer::IEmitter {
public:
  virtual ~IElement() = default;
  virtual bool GetIsPassable() = 0;
};
}

#endif // IELEMENT_H
