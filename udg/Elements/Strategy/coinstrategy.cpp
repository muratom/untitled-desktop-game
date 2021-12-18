#include "coinstrategy.h"
#include "Units/player.h"

void Elements::CoinStrategy::InteractWith(Units::IUnit& unit, Elements::IElement& elem) {
  Coin& coin = static_cast<Coin&>(elem);
  if (coin.IsUsed() || (typeid (unit) != typeid (Units::Player)))
    return;

  // С монетой может взамодействовать только игрок
  Units::Player& plr = static_cast<Units::Player&>(unit);
  plr.SetPoints(plr.GetPoints() + coin.GetValue());
  coin.SetIsUsed(true);
  qDebug() << "Interaction with coin ended: plr.GetPoints() = " << plr.GetPoints();
}
