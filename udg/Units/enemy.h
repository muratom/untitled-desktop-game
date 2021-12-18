#ifndef ENEMY_H
#define ENEMY_H

#include <list>

#include "Elements/FactoryMethod/Products/ielement.h"
#include "Elements/Strategy/iinteractionstrategy.h"
#include "Elements/Strategy/healthstrategy.h"
#include "Elements/Strategy/lavastrategy.h"
#include "Elements/Strategy/coinstrategy.h"
#include "Units/ienemy.h"
// #include "player.h"

namespace Units {

class Player;

// Инварианты:
// 1) 0 <= health <= 100
// 2) 1 <= attack_power

template<MovementPolitic mp, AttackPolitic ap>
class Enemy : public IEnemy {
public:
  Enemy(int16_t attack_power);
  Enemy(int16_t health, int16_t attack_power,
        FightState fstate, Orientation orient);
  ~Enemy() = default;

  int16_t GetHealth() const override { return health_; }
  void SetHealth(int16_t h) override;

  Orientation GetOrient() const  override { return orient_; }
  void SetOrient(Orientation o) override { orient_ = o; }

  int16_t GetAttackPower() const override { return attack_power_; }
  void SetAttackPower(int16_t attack) override;

  void SetStrategy(const StrategyPtr& strategy) override { interaction_strategy_ = strategy; }

  FightState GetFightState() const override { return fstate_; }
  void SetFightState(FightState fs) override { fstate_ = fs; }

  MovementPolitic GetMovePltc() const override { return mp; }
  AttackPolitic GetAttackPltc() const override { return ap; }

  // Возможно, это нужно будет вынести в интерфейс
  IUnit& operator+(Elements::IElement& elem) override;

  // Ход игрока
  // Возможно, здесь можно воспользоваться лишь интерфейсом IUnit
  IEnemy& operator-(Player& plr) override;

  void Connect(Observer::IReceiver* rec) override;
  void Disconnect(Observer::IReceiver* rec) override;
  void NotifyListeners() override;

protected:
  void Print(std::ostream& os) const override;

private:
  int16_t health_ = 100;
  int16_t attack_power_;

  FightState fstate_ = NEUTRAL;

  Orientation orient_;

  StrategyPtr interaction_strategy_ = nullptr;

  std::list<Observer::IReceiver*> receiver_list_;
};
}

#include "Units/enemy.cpp"


#endif // ENEMY_H
