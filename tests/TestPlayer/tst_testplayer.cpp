#include <QtTest>

#include "Units/player.h"
#include "Units/enemy.h"
#include "Elements/FactoryMethod/Products/coin.h"
#include "Elements/FactoryMethod/Products/wall.h"

class TestPlayer : public QObject {
  Q_OBJECT

public:
  TestPlayer();
  ~TestPlayer();

private slots:
  // Взаимодействие со здоровьем
  void HealthInteractionWhenFullHealth();
  void HealthInteractionWhenAlmostFullHealth();
  void HealthInteractionWhenMiddelHealth();

  // Взаимодействие с монетой
  void CoinInteraction();

  // Взаимодействие с лавой
  void LavaInteractionWhenAlmostDead();
  void LavaInteractionWhenMiddleHealth();

  // Взаимодействие со стеной
  void WallInteraction();

  // Взаимодействие с врагом
  void EnemyAttackNotDefendingPlayer();
  void EnemyAttackDefendingPlayer();
};

TestPlayer::TestPlayer() {}

TestPlayer::~TestPlayer() {}

void TestPlayer::HealthInteractionWhenFullHealth() {
  // Arrange
  Units::Player plr(100, 0, 10, 5, Units::FightState::NEUTRAL, Units::Orientation::RIGHT);
  Elements::Health health;

  // Act
  plr + health;

  // Assert
  QCOMPARE(plr.GetHealth(), 100);
  QCOMPARE(health.IsUsed(), false);
}

void TestPlayer::HealthInteractionWhenAlmostFullHealth() {
  // Arrange
  Units::Player plr(95, 0, 10, 5, Units::FightState::NEUTRAL, Units::Orientation::RIGHT);
  Elements::Health health;

  // Act
  plr + health;

  // Assert
  QCOMPARE(plr.GetHealth(), 100);
  QCOMPARE(health.IsUsed(), true);
}

void TestPlayer::HealthInteractionWhenMiddelHealth() {
  // Arrange
  Units::Player plr(70, 0, 10, 5, Units::FightState::NEUTRAL, Units::Orientation::RIGHT);
  Elements::Health health;

  // Act
  plr + health;

  // Assert
  QCOMPARE(plr.GetHealth(), 80);
  QCOMPARE(health.IsUsed(), true);
}

void TestPlayer::CoinInteraction() {
  // Arrange
  Units::Player plr(100, 0, 10, 5, Units::FightState::NEUTRAL, Units::Orientation::RIGHT);
  Elements::Coin coin;

  // Act
  plr + coin;

  // Assert
  QCOMPARE(plr.GetPoints(), 1);
  QCOMPARE(coin.IsUsed(), true);
}

void TestPlayer::LavaInteractionWhenAlmostDead() {
  // Arrange
  Units::Player plr(5, 0, 10, 5, Units::FightState::NEUTRAL, Units::Orientation::RIGHT);
  Elements::Lava lava;

  // Act
  plr + lava;

  // Assert
  QCOMPARE(plr.GetHealth(), 0);
}

void TestPlayer::LavaInteractionWhenMiddleHealth() {
  // Arrange
  Units::Player plr(50, 0, 10, 5, Units::FightState::NEUTRAL, Units::Orientation::RIGHT);
  Elements::Lava lava;

  // Act
  plr + lava;

  // Assert
  QCOMPARE(plr.GetHealth(), 40);
}

void TestPlayer::WallInteraction() {
  // Arrange
  Units::Player plr(50, 1, 10, 5, Units::FightState::NEUTRAL, Units::Orientation::RIGHT);
  Elements::Wall wall;

  // Act
  plr + wall;

  // Assert
  QCOMPARE(plr.GetHealth(), 50);
  QCOMPARE(plr.GetOrient(), Units::Orientation::RIGHT);
  QCOMPARE(plr.GetPoints(), 1);
  QCOMPARE(plr.GetAttackPower(), 10);
}

void TestPlayer::EnemyAttackNotDefendingPlayer() {
  // Arrange
  Units::Player plr(50, 0, 10, 5, Units::FightState::NEUTRAL, Units::Orientation::RIGHT);
  Units::Enemy<Units::MovementPolitic::HORIZONTAL, Units::AttackPolitic::NEAR> enemy(100, 30, Units::FightState::ATTACK, Units::Orientation::RIGHT);

  // Act
  plr - enemy;

  // Assert
  QCOMPARE(plr.GetHealth(), 20);
}

void TestPlayer::EnemyAttackDefendingPlayer() {
  // Arrange
  Units::Player plr(50, 0, 10, 5, Units::FightState::DEFENSE, Units::Orientation::RIGHT);
  Units::Enemy<Units::MovementPolitic::HORIZONTAL, Units::AttackPolitic::NEAR> enemy(100, 30, Units::FightState::ATTACK, Units::Orientation::RIGHT);

  // Act
  plr - enemy;

  // Assert
  QCOMPARE(plr.GetHealth(), 44);
}

QTEST_APPLESS_MAIN(TestPlayer)

#include "tst_testplayer.moc"
