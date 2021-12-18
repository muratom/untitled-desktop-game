#include "health.h"

namespace Elements {
std::ostream& operator<<(std::ostream& os, const Health&) {
  os << "Health has been used\n";
  return os;
}

void Health::SetIsUsed(bool val) {
  if (is_used_)
    return;
  is_used_ = val;
  NotifyListeners();
}

void Health::Print(std::ostream& os) const {
  if (is_used_)
    os << "Health has been used\n";
  else
    os << "Unit has enough health\n";
}

void Health::Connect(Observer::IReceiver* rec) {
  receiver_list_.push_back(rec);
}

void Health::Disconnect(Observer::IReceiver* rec) {
  receiver_list_.remove(rec);
}

void Health::NotifyListeners() {
  for (auto& rec : receiver_list_) {
    rec->Update(*this);
  }
}
}
