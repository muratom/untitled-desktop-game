#include "coin.h"

void Elements::Coin::SetIsUsed(bool val) {
  if (is_used_)
    return;
  is_used_ = val;
  if (is_used_)
    NotifyListeners();
}

void Elements::Coin::Connect(Observer::IReceiver* rec) {
  receiver_list_.push_back(rec);
}

void Elements::Coin::Disconnect(Observer::IReceiver* rec) {
  receiver_list_.remove(rec);
}

void Elements::Coin::NotifyListeners() {
  for (auto& rec : receiver_list_) {
    rec->Update(*this);
  }
}
