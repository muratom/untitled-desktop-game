#ifndef HEALTH_H
#define HEALTH_H

#include "Elements/iusableelement.h"

#include <ostream>

namespace Elements {
// Инвариант:
// value_ == 10
class Health : public IUsableElement {
public:
  Health() = default;
  ~Health() = default;

  uint8_t GetValue() const { return value_; }
  // void SetValue(uint8_t val) { value_ = val; }

  bool IsUsed() const override { return is_used_; }
  void SetIsUsed(bool val);

  bool GetIsPassable() override { return is_passable_; }

  void Connect(Observer::IReceiver* rec) override;
  void Disconnect(Observer::IReceiver* rec) override;
  void NotifyListeners() override;

private:
  void Print(std::ostream& os) const override;

  uint8_t value_ = 10;
  bool is_used_ = false;
  bool is_passable_ = true;
  std::list<Observer::IReceiver*> receiver_list_;
};
}

#endif // HEALTH_H
