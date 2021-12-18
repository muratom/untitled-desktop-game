#include "move.h"

namespace Command {

Move::Move(GamePtr& game, UnitPtr unit, Field::Point2D& unit_crd, Units::Orientation orient)
  : game_(game),
    unit_(unit),
    unit_crd_(unit_crd),
    orient_(orient) {}

void Move::Execute() const {
  // Если монета или здоровье, то игрок уже сдвинулся и изменять координаты не нужно,
  // иначе игрок не двигается, но кооридинаты нужно соответствующим образом изменять

  // Игровое поле
  Field::PlayingField* pf_ptr = game_->GetPF();

  //Field::Point2D plr_crd = pf_ptr->GetPlayerCoord();

  // Если юнит защищается, то он не может ходить
  if (unit_->GetFightState() != Units::FightState::DEFENSE) {
    switch (orient_) {
      case Units::Orientation::UP: {
        // Элемент, находящийся сверху
        Elements::IElement& up_elem = pf_ptr->GetField()[unit_crd_.first - 1][unit_crd_.second].GetElement();

        // Перемещение юнита заблокировано, если он взаимодействует с непересекаемым объектом
        if (up_elem.GetIsPassable()) {
          unit_crd_ = {unit_crd_.first - 1, unit_crd_.second};
          pf_ptr->NotifyListeners();
        }
        *unit_ + up_elem;

        // Меняем ориентацию юнита
        unit_->SetOrient(Units::Orientation::UP);
        break;
      }
      case Units::Orientation::RIGHT: {
        // Элемент, находящийся справа
        Elements::IElement& right_elem = pf_ptr->GetField()[unit_crd_.first][unit_crd_.second + 1].GetElement();

        // Перемещение юнита заблокировано, если он взаимодействует с непересекаемым объектом
        if (right_elem.GetIsPassable()) {
          unit_crd_ = {unit_crd_.first, unit_crd_.second + 1};
          pf_ptr->NotifyListeners();
        }
        *unit_ + right_elem;

        // Меняем ориентацию юнита
        unit_->SetOrient(Units::Orientation::RIGHT);
        break;
      }
      case Units::Orientation::DOWN: {
        // Элемент, находящийся снизу
        Elements::IElement& down_elem = pf_ptr->GetField()[unit_crd_.first + 1][unit_crd_.second].GetElement();

        // Перемещение юнита заблокировано, если он взаимодействует с непересекаемым объектом
        if (down_elem.GetIsPassable()) {
          unit_crd_ = {unit_crd_.first + 1, unit_crd_.second};
          pf_ptr->NotifyListeners();
        }
        *unit_ + down_elem;

        // Меняем ориентацию юнита
        unit_->SetOrient(Units::Orientation::DOWN);
        break;
      }
      case Units::Orientation::LEFT: {
        // Элемент, находящийся слева
        Elements::IElement& left_elem = pf_ptr->GetField()[unit_crd_.first][unit_crd_.second - 1].GetElement();

        // Перемещение юнита заблокировано, если он взаимодействует с непересекаемым объектом
        if (left_elem.GetIsPassable()) {
          unit_crd_ = {unit_crd_.first, unit_crd_.second - 1};
          pf_ptr->NotifyListeners();
        }
        *unit_ + left_elem;

        // Меняем ориентацию юнита
        unit_->SetOrient(Units::Orientation::LEFT);
        break;
      }
    }
  }
}

}
