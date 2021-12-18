#include "player.h"
#include "Elements/Strategy/coinstrategy.h"
#include "enemy.h"

namespace Units {

Player::Player(int16_t health, int16_t points,
               int16_t attack_power, int16_t defense_coeff,
               FightState fstate, Orientation orient)
    : fstate_(fstate),
      orient_(orient),
      interaction_strategy_(nullptr) {
  // Проверка инвариантов
  // NotifyListeners ничего не сделает, так как
  // объект создается и никто на него ещё не подписан
  SetHealth(health);
  SetPoints(points);

  // Ни атака, ни защита не могут быть неположительными
  SetAttackPower(attack_power);
  if (defense_coeff <= 0)
    defense_coeff = 1;
}

void Player::SetHealth(int16_t h) {
  health_ = h;
  if (health_ < 0)
    health_ = 0;
  else if (health_ > 100)
    health_ = 100;
  NotifyListeners();
}

void Player::SetPoints(int16_t p) {
  // Отрицательного количества очков не может быть
  if (p < 0)
    points_ = 0;
  else
    points_ = p;

  NotifyListeners();
}

void Player::SetAttackPower(int16_t attack) {
  attack_power_ = attack;
  if (attack_power_ <= 0)
    attack_power_ = 1;
}

void Player::SetFightState(FightState fs) {
  fstate_ = fs;
  NotifyListeners();
}

IUnit& Player::operator+(Elements::IElement& elem) {
  if (typeid (elem) == typeid (Elements::Coin))
    interaction_strategy_ = std::make_shared<Elements::CoinStrategy>();
  else if (typeid (elem) == typeid (Elements::Health))
    interaction_strategy_ = std::make_shared<Elements::HealthStrategy>();
  else if (typeid (elem) == typeid (Elements::Lava))
    interaction_strategy_ = std::make_shared<Elements::LavaStrategy>();
  else
    interaction_strategy_ = nullptr;

  if (interaction_strategy_)
    interaction_strategy_->InteractWith(*this, elem);

  return *this;
}

Player& Player::operator-(IEnemy& enemy) {
  switch (fstate_) {
    case FightState::ATTACK:
      // Пока что враги только атакуют, они не могут защищаться
      SetHealth(health_ - enemy.GetAttackPower());
      break;
    case FightState::DEFENSE:
      SetHealth(health_ - enemy.GetAttackPower() / defense_coeff_);
      break;
    case FightState::NEUTRAL:
      SetHealth(health_ - enemy.GetAttackPower());
      break;
  }
  return *this;
}

void Player::Connect(Observer::IReceiver* rec) {
  receiver_list_.push_back(rec);
}

void Player::Disconnect(Observer::IReceiver* rec) {
  receiver_list_.remove(rec);
}

void Player::NotifyListeners() {
  for (auto& rec : receiver_list_) {
    rec->Update(*this);
  }
}

Player::Memento Player::SaveState() {
  return Memento(*this);
}

void Player::RestoreState(Player::Memento& m) {
  health_ = m.GetHealth();
  points_ = m.GetPoints();
  attack_power_ = m.GetAttackPower();
  defense_coeff_ = m.GetDefenseCoeff();
  fstate_ = m.GetFightState();
  orient_ = m.GetOrientation();
  // Нет необходимости сохранять стратегию
  interaction_strategy_ = nullptr;
  receiver_list_ = m.GetReceivers();
}

void Player::Print(std::ostream& os) const {
  if (health_ > 0) {
    os << "Player: health = " << health_ << ", points = " << points_ << ", state = ";
    switch (fstate_) {
      case FightState::ATTACK: {
        os << "attack\n";
        break;
      }
      case FightState::DEFENSE: {
        os << "defense\n";
        break;
      }
      case FightState::NEUTRAL: {
        os << "neutral\n";
        break;
      }
    }
  } else {
    os << "You are dead!\n";
  }
}

Player::Memento::Memento(const Player& plr)
    : health_(plr.health_),
      points_(plr.points_),
      attack_power_(plr.attack_power_),
      defense_coeff_(plr.defense_coeff_),
      fstate_(plr.fstate_),
      orient_(plr.orient_),
      receiver_list_(plr.receiver_list_) {}
}
