#include "playingfield.h"

/*
Идея для генерации уровней:
http://www.roguebasin.com/index.php?title=Grid_Based_Dungeon_Generator
*/

namespace Field {

PlayingField& PlayingField::GetInstance() {
  static PlayingField single_field;
  return single_field;
}

void PlayingField::CustomizeField(int16_t h, int16_t w, const FieldPtr& field, const Point2D& plr_crd,
                                  const std::vector<Point2D>& enemies_crd,
                                  const Point2D& entrance_crd, const Point2D& exit_crd) {

  // Проверка аргументов на валидность
  // ">=" и "<=", так как по краям поля всегда имеется стена
  if ((h <= 0) || (w <= 0)) {
    throw BadFieldException("Incorrect field parameters");
  }
  if (field == nullptr) { // Если нужно очистить поле, то следует вызвать метод Clear
    throw BadFieldException("Incorrect field pointer");
  }
  if ((plr_crd.first <= 0) || (plr_crd.second <= 0) ||
      (plr_crd.first >= h) || (plr_crd.second >= w)) {
    throw BadFieldException("Incorrect player's coordinates");
  }
  for (auto& p : enemies_crd) {
    if ((p.first <= 0) || (p.second <= 0) ||
        (p.first >= h) || (p.second >= w))
      throw BadFieldException("Incorrect enemies' coordinates");
  }
  if ((entrance_crd.first <= 0) || (entrance_crd.second <= 0) ||
      (exit_crd.first <= 0) || (exit_crd.second <= 0) ||
      (entrance_crd.first >= h) || (entrance_crd.second >= w) ||
      (exit_crd.first >= h) || (exit_crd.second >= w)) {
    throw BadFieldException("Incorrect entrance or exit coordinates");
  }


  field_ = field;
  height_ = h;
  width_ = w;
  entrance_ = entrance_crd;
  exit_ = exit_crd;

  player_coord_ = plr_crd;
  enemies_coord_ = enemies_crd;

  receiver_list_.clear(); // Все бывшие подписчики принудительно отписаны
}

void PlayingField::Clear() {
  field_.reset();
  enemies_coord_.clear();
  receiver_list_.clear();
}

void PlayingField::SetPlayerCoord(Point2D crd) {
  if ((crd.first <= 0) || (crd.second <= 0))
    throw BadFieldException("Incorrect coordinates");
  player_coord_ = crd;
  NotifyListeners();
}

void PlayingField::SetEnemyCoord(int16_t enemy_index, const Point2D& crd) {
  if ((crd.first <= 0) || (crd.second <= 0))
    throw BadFieldException("Incorrect coordinates");
  enemies_coord_[enemy_index] = crd;
}

void PlayingField::Connect(Observer::IReceiver* rec) {
  receiver_list_.push_back(rec);
}

void PlayingField::Disconnect(Observer::IReceiver* rec) {
  receiver_list_.remove(rec);
}

void PlayingField::NotifyListeners() {
  for (auto& rec : receiver_list_) {
    rec->Update(*this);
  }
}

PlayingField::Memento PlayingField::SaveState() {
  return Memento(*this);
}

void PlayingField::RestoreState(PlayingField::Memento& m) {
  field_ = m.GetField();
  player_coord_ = m.GetPlrCrd();
  enemies_coord_ = m.GetEnemiesCrd();
  entrance_ = m.GetEntrance();
  exit_ = m.GetExit();
  height_ = m.GetHeight();
  width_ = m.GetWidth();
  receiver_list_ = m.GetReceivers();
}

void PlayingField::Print(std::ostream& os) const {
  os << "Playing field: player's coordinates = (" << player_coord_.first << ", "
     << player_coord_.second << ")\n";
}

PlayingField::Iterator::Iterator(const PlayingField::Iterator& other)
    : pf_ptr_(other.pf_ptr_), current_coord_(other.current_coord_) {}

PlayingField::Iterator::Iterator(const PlayingField& pf, const Point2D& coord)
    : pf_ptr_(&pf), current_coord_(coord) {}

PlayingField::Iterator& PlayingField::Iterator::operator=(const PlayingField::Iterator& other) {
  if (this != &other) {
    pf_ptr_ = other.pf_ptr_;
    current_coord_ = other.current_coord_;
  }
  return *this;
}

PlayingField::Iterator& PlayingField::Iterator::operator++() {
  if (pf_ptr_ != nullptr) {
    ++current_coord_.second;
    if (current_coord_.second == pf_ptr_->width_)
      current_coord_ = { current_coord_.first + 1, 0 };
  }
  return *this;
}

PlayingField::Iterator PlayingField::Iterator::operator++(int) {
  Iterator temp(*this);
  if (pf_ptr_ != nullptr) ++(*this);
  return temp;
}

PlayingField::Iterator& PlayingField::Iterator::operator--() {
  if (pf_ptr_ != nullptr) {
    if (current_coord_.second == 0)
      current_coord_ = { current_coord_.first - 1, pf_ptr_->width_ - 1 };
    else
      current_coord_ = { current_coord_.first, current_coord_.second - 1 };
  }
  return *this;
}

PlayingField::Iterator PlayingField::Iterator::operator--(int) {
  Iterator temp(*this);
  if (pf_ptr_ != nullptr) --(*this);
  return temp;
}

bool PlayingField::Iterator::operator==(const PlayingField::Iterator& other) const {
  return current_coord_ == other.current_coord_;
}

bool PlayingField::Iterator::operator!=(const PlayingField::Iterator& other) const {
  return !(*this == other);
}

Cell& PlayingField::Iterator::operator*() const {
  return pf_ptr_->field_[current_coord_.first][current_coord_.second];
}

Cell* PlayingField::Iterator::operator->() const {
  return &(pf_ptr_->field_[current_coord_.first][current_coord_.second]);
}

PlayingField::Memento::Memento(const PlayingField& pf)
    : fld_(pf.field_),
      plr_crd_(pf.player_coord_),
      enemies_crd_(pf.enemies_coord_),
      entrance_(pf.entrance_),
      exit_(pf.exit_),
      height_(pf.height_),
      width_(pf.width_),
      receiver_list_(pf.receiver_list_) {}
}
