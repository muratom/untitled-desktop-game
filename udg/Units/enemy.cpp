#ifndef ENEMY_CPP
#define ENEMY_CPP

#include "enemy.h"
#include "player.h"

namespace Units {

template<MovementPolitic mp, AttackPolitic ap>
Enemy<mp, ap>::Enemy(int16_t attack_power) {
  if (attack_power < 1) {
    attack_power = 1;
  } else {
    attack_power_ = attack_power;
  }
  switch (mp) {
    case MovementPolitic::HORIZONTAL: {
      orient_ = RIGHT;
      break;
    }
    case MovementPolitic::VERTICAL: {
      orient_ = UP;
      break;
    }
  }
}

template<MovementPolitic mp, AttackPolitic ap>
Enemy<mp, ap>::Enemy(int16_t health, int16_t attack_power,
                     FightState fstate, Orientation orient)
    : fstate_(fstate),
      orient_(orient),
      interaction_strategy_(nullptr) {
  // В списке инициализации значения по модулю берутся для того,
  // чтобы переданное в аргументе значение не выходило за пределы enum'а

  // Проверка инварианта
  // NotifyListeners ничего не сделает, так как
  // объект создается и никто на него ещё не подписан
  SetHealth(health);
  SetAttackPower(attack_power);
}

template<MovementPolitic mp, AttackPolitic ap>
void Enemy<mp, ap>::SetHealth(int16_t h) {
  health_ = h;
  if (health_ < 0)
    health_ = 0;
  else if (health_ > 100)
    health_ = 100;
  NotifyListeners();
}

template<MovementPolitic mp, AttackPolitic ap>
void Enemy<mp, ap>::SetAttackPower(int16_t attack) {
  attack_power_ = attack;
  if (attack_power_ < 1) {
    attack_power_ = 1;
  }
  NotifyListeners();
}

template<MovementPolitic mp, AttackPolitic ap>
IUnit& Enemy<mp, ap>::operator +(Elements::IElement& elem) {
  if (typeid (elem) == typeid (Elements::Health))
    interaction_strategy_ = std::make_shared<Elements::HealthStrategy>();
  else if (typeid (elem) == typeid (Elements::Lava))
    interaction_strategy_ = std::make_shared<Elements::LavaStrategy>();
  else
    interaction_strategy_ = nullptr;

  if (interaction_strategy_)
    interaction_strategy_->InteractWith(*this, elem);

  return *this;
}

template<MovementPolitic mp, AttackPolitic ap>
IEnemy& Enemy<mp, ap>::operator -(Player& plr) {
  if (plr.GetFightState() == FightState::ATTACK) {
    SetHealth(health_ - plr.GetAttackPower());
  }
  return *this;
}

template<MovementPolitic mp, AttackPolitic ap>
void Enemy<mp, ap>::Connect(Observer::IReceiver* rec) {
  receiver_list_.push_back(rec);
}

template<MovementPolitic mp, AttackPolitic ap>
void Enemy<mp, ap>::Disconnect(Observer::IReceiver* rec) {
  receiver_list_.remove(rec);
}

template<MovementPolitic mp, AttackPolitic ap>
void Enemy<mp, ap>::NotifyListeners() {
  for (auto& rec : receiver_list_) {
    rec->Update(*this);
  }
}

template<MovementPolitic mp, AttackPolitic ap>
void Enemy<mp, ap>::Print(std::ostream& os) const {
  if (health_ > 0) {
    os << "Enemy: health = " << health_ << ", attack power = " << attack_power_ <<  "\n";
  } else {
    os << "Enemy is dead!\n";
  }
}

}

#endif // ENEMY_CPP
