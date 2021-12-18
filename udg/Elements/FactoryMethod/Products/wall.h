#ifndef WALL_H
#define WALL_H

#include "Elements/FactoryMethod/Products/ielement.h"

namespace Elements {
class Wall : public IElement {
public:
  Wall() = default;
  ~Wall() = default;

  bool GetIsPassable() override { return is_passable_; }

  void Connect(Observer::IReceiver* rec) override;
  void Disconnect(Observer::IReceiver* rec) override;
  void NotifyListeners() override;

private:
  void Print(std::ostream& os) const override { os << "It is a wall\n"; }

  bool is_passable_ = false;

  std::list<Observer::IReceiver*> receiver_list_;
};
}

#endif // WALL_H
