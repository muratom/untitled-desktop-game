#ifndef COIN_H
#define COIN_H

#include "Elements/iusableelement.h"

#include <ostream>

namespace Elements {
// Инвариант:
// value == 1
class Coin : public IUsableElement {
public:
  Coin() = default;
  ~Coin() = default;

  uint8_t GetValue() const { return value_; }
  // void SetValue(uint8_t val);

  bool IsUsed() const override { return is_used_; }
  void SetIsUsed(bool val);

  bool GetIsPassable() override { return is_passable_; }

  void Connect(Observer::IReceiver* rec) override;
  void Disconnect(Observer::IReceiver* rec) override;
  void NotifyListeners() override;

private:
  void Print(std::ostream& os) const override { os << "Coin has been used\n"; }

  uint8_t value_ = 1;
  bool is_used_ = false;
  bool is_passable_ = true;
  std::list<Observer::IReceiver*> receiver_list_;
};
}

#endif // COIN_H
