#include <QtTest>

#include "Game/game.h"

class TestGame : public QObject
{
  Q_OBJECT

public:
  TestGame();
  ~TestGame();

private slots:
  void NewGameInit();
  void LoadGameInit();
  void ExitGameNotInit();

  void PlayerAliveCase();
  void PlayerDeadCase();

  void LevelCompleteCase();
};

TestGame::TestGame() {}

TestGame::~TestGame() {}

void TestGame::NewGameInit() {
  Game::Game game;
  game.NewGame("../../../UntitledDesktopGame/tests/TestPlayingField/correct_level.txt");
  QCOMPARE(game.GetIsInitialized(), true);
  QCOMPARE(game.GetInGame(), true);
}

void TestGame::LoadGameInit() {
  Game::Game game;
  game.LoadGame("../../../UntitledDesktopGame/tests/TestPlayingField/correct_level.txt");
  QCOMPARE(game.GetIsInitialized(), true);
  // Сохранение может содержать игру в
  // QCOMPARE(game.GetInGame(), true);
}

void TestGame::ExitGameNotInit() {
  Game::Game game;
  game.NewGame("../../../UntitledDesktopGame/tests/TestPlayingField/correct_level.txt");
  game.ExitGame();
  QCOMPARE(game.GetIsInitialized(), false);
  QCOMPARE(game.GetInGame(), false);
}

void TestGame::PlayerAliveCase() {
  Game::Game game;
  game.NewGame("../../../UntitledDesktopGame/tests/TestPlayingField/correct_level.txt");
  QCOMPARE(game.IsPlayerAlive(), true);
  QCOMPARE(game.GetInGame(), true);
}

void TestGame::PlayerDeadCase() {
  Game::Game game;
  game.NewGame("../../../UntitledDesktopGame/tests/TestPlayingField/correct_level.txt");
  game.GetPlayer()->SetHealth(0);
  QCOMPARE(game.IsPlayerAlive(), false);
  QCOMPARE(game.GetInGame(), false);
}

void TestGame::LevelCompleteCase() {
  Game::Game game;
  game.NewGame("../../../UntitledDesktopGame/tests/TestPlayingField/correct_level.txt");
  game.GetPlayer()->SetPoints(game.GetTargetPoints());
  game.GetPF()->SetPlayerCoord(game.GetPF()->GetExitCoord());
  QCOMPARE(game.IsLevelComplete(), true);
  QCOMPARE(game.GetInGame(), false);
}


QTEST_APPLESS_MAIN(TestGame)

#include "tst_testgame.moc"
