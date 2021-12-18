#ifndef CELL_H
#define CELL_H

#include <exception>
#include <iostream>
#include <Elements/FactoryMethod/Products/ielement.h>

namespace Field {
using ElementPtr = std::shared_ptr<Elements::IElement>;

// Инвариант:
// element_ либо nullptr, либо указывает на элемент
class Cell {
public:
  Cell() = default;
  Cell(const ElementPtr& element);
  Cell(const Cell&) = default;
  Cell& operator=(const Cell&) = default;

  bool GetIsPassable() const { return element_->GetIsPassable(); }
  // void SetIsPassable(bool value) { is_passable_ = value; }

  Elements::IElement& GetElement() const;

private:
  // Пропускаемость заложена в элементе
  // bool is_passable_ = true;
  ElementPtr element_ = nullptr; // Если использовать ссылку, то при создании объекта её нужно сразу же инициализировать
};
}

#endif // CELL_H
