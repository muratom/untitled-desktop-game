#ifndef LAVA_H
#define LAVA_H

#include "Elements/FactoryMethod/Products/ielement.h"

#include <ostream>

namespace Elements {
// Инвариант:
// damage_ = 10
class Lava : public IElement {
public:
  Lava() = default;
  ~Lava() = default;

  uint8_t GetDamage() const { return damage_; }

  bool GetIsPassable() override { return is_passable_; }

  void Connect(Observer::IReceiver* rec) override;
  void Disconnect(Observer::IReceiver* rec) override;
  void NotifyListeners() override;

private:
  void Print(std::ostream& os) const override { os << "It is a lava.\n"; }

  uint8_t damage_ = 10;
  bool is_passable_ = false;

  std::list<Observer::IReceiver*> receiver_list_;
};
}

#endif // SPIKE_H
