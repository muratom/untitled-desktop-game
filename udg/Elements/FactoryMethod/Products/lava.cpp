#include "lava.h"

namespace Elements {
void Lava::Connect(Observer::IReceiver* rec) {
  receiver_list_.push_back(rec);
}

void Lava::Disconnect(Observer::IReceiver* rec) {
  receiver_list_.remove(rec);
}

void Lava::NotifyListeners() {
  for (auto& rec : receiver_list_) {
    rec->Update(*this);
  }
}
}
