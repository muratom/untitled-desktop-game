#include <QtTest>

#include <iostream>
#include <memory>

#include "Game/game.h"
#include "Game/Command/newgame.h"
#include "Game/Command/move.h"
#include "Game/gameloader.h"
#include "Units/iunit.h"
#include "Units/player.h"

class TestInteraction : public QObject {

  Q_OBJECT

  using GamePtr = std::shared_ptr<Game::Game>;

public:
  TestInteraction();
  ~TestInteraction();

private slots:
  // called before every test function
  void init();

  void WithWall();
  void WithLava();

  void Coin();

  void HealthWithFull();
  void HealthWithAlmostFull();
  void HealthWithNotFull();

  void LavaWithAlmostDead();
  void LavaWithNotAlmostDead();

private:
  GamePtr game = std::make_shared<Game::Game>();
};

TestInteraction::TestInteraction() {
  if (!game->NewGame("../../../UntitledDesktopGame/tests/TestInteraction/test_level.txt")) {
    return;
  }
}

TestInteraction::~TestInteraction() {}

void TestInteraction::init() {
  // game->GetPF()->SetPlayerCoord({1, 1});
}

void TestInteraction::Coin() {
  // Arrange
  Units::Player plr(100, 0, 10, 5, Units::FightState::NEUTRAL, Units::Orientation::RIGHT);
  Elements::Coin coin;

  // Act
  plr + coin;

  // Assert
  QCOMPARE(plr.GetPoints(), 1);
//  game->SetMoveCmd(std::make_shared<Command::Move>(game, Units::Orientation::RIGHT));
//  game->MovePlayer();
//  QCOMPARE(game->GetPlayer()->GetPoints(), 1);
}

void TestInteraction::HealthWithFull() {
  // Arrange
  Units::Player plr(100, 0, 10, 5, Units::FightState::NEUTRAL, Units::Orientation::RIGHT);
  Elements::Health health;

  // Act
  plr + health;

  // Assert
  QCOMPARE(plr.GetHealth(), 100);

//  game->SetMoveCmd(std::make_shared<Command::Move>(game, Units::Orientation::RIGHT));
//  game->MovePlayer();
//  game->SetMoveCmd(std::make_shared<Command::Move>(game, Units::Orientation::RIGHT));
//  game->MovePlayer();
//  game->SetMoveCmd(std::make_shared<Command::Move>(game, Units::Orientation::DOWN));
//  game->MovePlayer();
//  game->SetMoveCmd(std::make_shared<Command::Move>(game, Units::Orientation::LEFT));
//  game->MovePlayer();
  //  QCOMPARE(game->GetPlayer()->GetHealth(), 100);
}

void TestInteraction::HealthWithAlmostFull() {
  // Arrange
  Units::Player plr(95, 0, 10, 5, Units::FightState::NEUTRAL, Units::Orientation::RIGHT);
  Elements::Health health;

  // Act
  plr + health;

  // Assert
  QCOMPARE(plr.GetHealth(), 100);
}

void TestInteraction::HealthWithNotFull() {
  // Arrange
  Units::Player plr(70, 0, 10, 5, Units::FightState::NEUTRAL, Units::Orientation::RIGHT);
  Elements::Health health;

  // Act
  plr + health;

  // Assert
  QCOMPARE(plr.GetHealth(), 80);
}

void TestInteraction::LavaWithAlmostDead() {
  // Arrange
  Units::Player plr(5, 0, 10, 5, Units::FightState::NEUTRAL, Units::Orientation::RIGHT);
  Elements::Lava lava;

  // Act
  plr100 + lava;
  plrAlmostDead + lava;

  // Assert
  QCOMPARE(plr100.GetHealth(), 90);
  QCOMPARE(plrAlmostDead.GetHealth(), 0);
//  game->SetMoveCmd(std::make_shared<Command::Move>(game, Units::Orientation::RIGHT));
//  game->MovePlayer();
//  game->SetMoveCmd(std::make_shared<Command::Move>(game, Units::Orientation::RIGHT));
//  game->MovePlayer();
  //  QCOMPARE(game->GetPlayer()->GetHealth(), 90);
}

void TestInteraction::LavaWithNotAlmostDead() {
  // Arrange
  Units::Player plr100(100, 0, 10, 5, Units::FightState::NEUTRAL, Units::Orientation::RIGHT);
  Units::Player plrAlmostDead(5, 0, 10, 5, Units::FightState::NEUTRAL, Units::Orientation::RIGHT);
  Elements::Lava lava;

  // Act
  plr100 + lava;
  plrAlmostDead + lava;

  // Assert
  QCOMPARE(plr100.GetHealth(), 90);
  QCOMPARE(plrAlmostDead.GetHealth(), 0);
}

QTEST_APPLESS_MAIN(TestInteraction)

#include "tst_testinteraction.moc"
