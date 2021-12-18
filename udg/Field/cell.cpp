#include "cell.h"

namespace Field {
Cell::Cell(const std::shared_ptr<Elements::IElement>& element)
    : element_(element) {}

Elements::IElement& Cell::GetElement() const {
  return *element_;
}
}

