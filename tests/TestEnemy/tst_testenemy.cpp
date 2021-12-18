#include <QtTest>

#include "Units/player.h"
#include "Units/enemy.h"
#include "Elements/FactoryMethod/Products/coin.h"
#include "Elements/FactoryMethod/Products/wall.h"

class TestEnemy : public QObject {

  Q_OBJECT

public:
  TestEnemy();
  ~TestEnemy();

private slots:
  // Взаимодействие со здоровьем
  void HealthInteractionWhenFullHealth();
  void HealthInteractionWhenAlmostFullHealth();
  void HealthInteractionWhenMiddelHealth();

  // Взаимодействие с монетой (враг не может собирать монеты)
  void CoinInteraction();

  // Взаимодействие с лавой
  void LavaInteractionWhenAlmostDead();
  void LavaInteractionWhenMiddleHealth();

  // Взаимодействие со стеной
  void WallInteraction();

  // Взаимодействие с игроком
  // Оно зависит от Fight state игрока
  void NotAttackingPlayerInteractWithEnemy();
  void AttackingPlayerInteractWithEnemy();

//  // Взаимодействие луча с игроком
//  void BeamAttackPlayer();
};

TestEnemy::TestEnemy() {}

TestEnemy::~TestEnemy() {}

void TestEnemy::HealthInteractionWhenFullHealth() {
  // Arrange
  Units::Enemy<Units::MovementPolitic::HORIZONTAL, Units::AttackPolitic::NEAR> enemy(100, 30, Units::FightState::ATTACK, Units::Orientation::RIGHT);
  Elements::Health health;

  // Act
  enemy + health;

  // Assert
  QCOMPARE(enemy.GetHealth(), 100);
  QCOMPARE(health.IsUsed(), false);
}

void TestEnemy::HealthInteractionWhenAlmostFullHealth() {
  // Arrange
  Units::Enemy<Units::MovementPolitic::HORIZONTAL, Units::AttackPolitic::NEAR> enemy(95, 30, Units::FightState::ATTACK, Units::Orientation::RIGHT);
  Elements::Health health;

  // Act
  enemy + health;

  // Assert
  QCOMPARE(enemy.GetHealth(), 100);
  QCOMPARE(health.IsUsed(), true);
}

void TestEnemy::HealthInteractionWhenMiddelHealth() {
  // Arrange
  Units::Enemy<Units::MovementPolitic::HORIZONTAL, Units::AttackPolitic::NEAR> enemy(50, 30, Units::FightState::ATTACK, Units::Orientation::RIGHT);
  Elements::Health health;

  // Act
  enemy + health;

  // Assert
  QCOMPARE(enemy.GetHealth(), 60);
  QCOMPARE(health.IsUsed(), true);
}

void TestEnemy::CoinInteraction() {
  // Arrange
  Units::Enemy<Units::MovementPolitic::HORIZONTAL, Units::AttackPolitic::NEAR> enemy(100, 30, Units::FightState::ATTACK, Units::Orientation::RIGHT);
  Elements::Coin coin;

  // Act
  enemy + coin;

  // Assert
  // Enemy cannot collect points
  QCOMPARE(coin.IsUsed(), false);
}

void TestEnemy::LavaInteractionWhenAlmostDead() {
  // Arrange
  Units::Enemy<Units::MovementPolitic::HORIZONTAL, Units::AttackPolitic::NEAR> enemy(5, 30, Units::FightState::ATTACK, Units::Orientation::RIGHT);
  Elements::Lava lava;

  // Act
  enemy + lava;

  // Assert
  QCOMPARE(enemy.GetHealth(), 0);
}

void TestEnemy::LavaInteractionWhenMiddleHealth() {
  // Arrange
  Units::Enemy<Units::MovementPolitic::HORIZONTAL, Units::AttackPolitic::NEAR> enemy(77, 30, Units::FightState::ATTACK, Units::Orientation::RIGHT);
  Elements::Lava lava;

  // Act
  enemy + lava;

  // Assert
  QCOMPARE(enemy.GetHealth(), 67);
}

void TestEnemy::WallInteraction() {
  // Arrange
  Units::Enemy<Units::MovementPolitic::HORIZONTAL, Units::AttackPolitic::NEAR> enemy(77, 30, Units::FightState::ATTACK, Units::Orientation::RIGHT);
  Elements::Wall wall;

  // Act
  enemy + wall;

  // Assert
  QCOMPARE(enemy.GetHealth(), 77);
  QCOMPARE(enemy.GetOrient(), Units::Orientation::RIGHT);
  QCOMPARE(enemy.GetAttackPower(), 30);
}

void TestEnemy::NotAttackingPlayerInteractWithEnemy() {
  // Arrange
  Units::Player plr(100, 0, 10, 5, Units::FightState::NEUTRAL, Units::Orientation::RIGHT);
  Units::Enemy<Units::MovementPolitic::HORIZONTAL, Units::AttackPolitic::NEAR> enemy(100, 30, Units::FightState::ATTACK, Units::Orientation::RIGHT);

  // Act
  enemy - plr;

  // Assert
  QCOMPARE(enemy.GetHealth(), 100);
}

void TestEnemy::AttackingPlayerInteractWithEnemy() {
  // Arrange
  Units::Player plr(100, 0, 40, 5, Units::FightState::ATTACK, Units::Orientation::RIGHT);
  Units::Enemy<Units::MovementPolitic::HORIZONTAL, Units::AttackPolitic::NEAR> enemy(100, 30, Units::FightState::ATTACK, Units::Orientation::RIGHT);

  // Act
  enemy - plr;

  // Assert
  QCOMPARE(enemy.GetHealth(), 60);
}


QTEST_APPLESS_MAIN(TestEnemy)

#include "tst_testenemy.moc"
