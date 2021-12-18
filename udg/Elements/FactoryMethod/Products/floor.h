#ifndef FLOOR_H
#define FLOOR_H

#include "Elements/FactoryMethod/Products/ielement.h"

namespace Elements {
class Floor : public IElement {
public:
  Floor() = default;
  ~Floor() = default;

  bool GetIsPassable() override { return is_passable_; }

  void Connect(Observer::IReceiver* rec) override;
  void Disconnect(Observer::IReceiver* rec) override;
  void NotifyListeners() override;

private:
  void Print(std::ostream& os) const override { os << "Is is a floor\n"; }

  bool is_passable_ = true;

  std::list<Observer::IReceiver*> receiver_list_;
};
}


#endif // FLOOR_H
