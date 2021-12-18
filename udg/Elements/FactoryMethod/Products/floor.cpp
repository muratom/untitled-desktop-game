#include "floor.h"

namespace Elements {
void Floor::Connect(Observer::IReceiver* rec) {
  receiver_list_.push_back(rec);
}

void Floor::Disconnect(Observer::IReceiver* rec) {
  receiver_list_.remove(rec);
}

void Floor::NotifyListeners() {
  for (auto& rec : receiver_list_) {
    rec->Update(*this);
  }
}
}
