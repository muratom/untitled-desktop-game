#ifndef IUNIT_H
#define IUNIT_H

#include <memory>

#include "Elements/Strategy/iinteractionstrategy.h"
#include "Log/Observer/iemitter.h"

namespace Units {

using StrategyPtr = std::shared_ptr<Elements::IInteractionStrategy>;

enum Orientation : int16_t {
  UP, RIGHT, DOWN, LEFT
};

enum FightState : int16_t {
  NEUTRAL, ATTACK, DEFENSE
};

class IUnit : public Observer::IEmitter {
public:
  virtual ~IUnit() = default;

  virtual int16_t GetHealth() const = 0;
  virtual void SetHealth(int16_t h) = 0;

  virtual Orientation GetOrient() const = 0;
  virtual void SetOrient(Orientation o) = 0;

  virtual void SetStrategy(const StrategyPtr& strategy) = 0;

  virtual int16_t GetAttackPower() const = 0;
  virtual void SetAttackPower(int16_t attack) = 0;

  virtual FightState GetFightState() const = 0;
  virtual void SetFightState(FightState fs) = 0;

  virtual IUnit& operator+(Elements::IElement& elem) = 0;
};
}


#endif // IUNIT_H
