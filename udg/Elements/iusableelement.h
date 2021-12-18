#ifndef IUSABLEELEMENT_H
#define IUSABLEELEMENT_H

#include "Elements/FactoryMethod/Products/ielement.h"

#include <ostream>
#include <list>

namespace Elements {
class IUsableElement : public IElement {
public:
  virtual ~IUsableElement() = default;

  // Был ли использован элемент
  virtual bool IsUsed() const = 0;
};
}


#endif // IUSABLEELEMENT_H
