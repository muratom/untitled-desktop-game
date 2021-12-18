#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <typeinfo>
#include <ostream>
#include <list>

#include "Elements/FactoryMethod/Products/ielement.h"
#include "Elements/Strategy/iinteractionstrategy.h"
#include "Elements/Strategy/healthstrategy.h"
#include "Elements/Strategy/lavastrategy.h"

#include "Units/iunit.h"
#include "Units/ienemy.h"

namespace Units {

/*
Идеи:
1) Добавить возможность взять броню
2) Добавить возможность взять другое оружие
*/

// Инварианты:
// 1) 0 <= health <= 100
// 2) 0 <= points
// 3) 1 <= attack_power
// 4) 1 <= defense_coeff

class Player : public IUnit {
public:
  Player() = default;
  Player(int16_t health, int16_t points,
         int16_t attack_power, int16_t defense_coeff,
         FightState fstate, Orientation orient);
  ~Player() = default;

  int16_t GetHealth() const override { return health_; }
  void SetHealth(int16_t h) override;

  int16_t GetPoints() const { return points_; }
  void SetPoints(int16_t p);

  Orientation GetOrient() const  override { return orient_; }
  void SetOrient(Orientation o) override { orient_ = o; }

  int16_t GetAttackPower() const override { return attack_power_; }
  void SetAttackPower(int16_t attack) override;

  FightState GetFightState() const override { return fstate_; }
  void SetFightState(FightState fs) override;

  IUnit& operator+(Elements::IElement& elem) override;

  // Ход врага
  // Возможно, здесь можно воспользоваться лишь интерфейсом IUnit
  Player& operator-(IEnemy& enemy);

  // Паттерн "Стратегия"
  void SetStrategy(const StrategyPtr& strategy) override { interaction_strategy_ = strategy; }

  // Паттерн "Наблюдатель"
  void Connect(Observer::IReceiver* rec) override;
  void Disconnect(Observer::IReceiver* rec) override;
  void NotifyListeners() override;

  // Паттерн "Снимок"
  class Memento {
  public:
    Memento(const Player& plr);

    int16_t GetHealth() { return health_; }
    int16_t GetPoints() { return points_; }
    int16_t GetAttackPower() { return attack_power_; }
    int16_t GetDefenseCoeff() { return defense_coeff_; }
    FightState GetFightState() { return fstate_; }
    Orientation GetOrientation() { return orient_; }
    // const StrategyPtr& GetStrategyPtr() { return interaction_strategy_; }
    std::list<Observer::IReceiver*>& GetReceivers() { return receiver_list_; }

  private:
    int16_t health_;
    int16_t points_;
    int16_t attack_power_;
    int16_t defense_coeff_; // Во сколько раз уменьшится атака врага

    FightState fstate_;
    Orientation orient_; // Куда ориентирован игрок
    // const StrategyPtr& interaction_strategy_;
    std::list<Observer::IReceiver*> receiver_list_;
  };

  Memento SaveState();
  void RestoreState(Memento& m);

protected:
  void Print(std::ostream& os) const override;

private:
  int16_t health_ = 100;
  int16_t points_ = 0;
  int16_t attack_power_ = 50;
  int16_t defense_coeff_ = 5; // Во сколько раз уменьшится атака врага

  FightState fstate_ = NEUTRAL;

  Orientation orient_ = RIGHT; // Куда ориентирован игрок

  StrategyPtr interaction_strategy_ = nullptr;

  std::list<Observer::IReceiver*> receiver_list_;
};

}

#endif // PLAYER_H
