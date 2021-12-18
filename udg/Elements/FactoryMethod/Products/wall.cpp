#include "wall.h"

namespace Elements {
void Wall::Connect(Observer::IReceiver* rec) {
  receiver_list_.push_back(rec);
}

void Wall::Disconnect(Observer::IReceiver* rec) {
  receiver_list_.remove(rec);
}

void Wall::NotifyListeners() {
  for (auto& rec : receiver_list_) {
    rec->Update(*this);
  }
}
}
