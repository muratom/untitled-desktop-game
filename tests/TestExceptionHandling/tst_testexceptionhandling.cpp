#include <QtTest>

#include "Game/game.h"
#include "Game/gameloader.h"
#include "Game/gamesaver.h"

class TestExceptionHandling : public QObject {
  Q_OBJECT

  using GamePtr = std::shared_ptr<Game::Game>;
  using GameLoaderPtr = std::shared_ptr<Game::GameLoader>;
public:
  TestExceptionHandling();
  ~TestExceptionHandling();

private slots:
  void LoadIncorrectFilePath();

  void SaveUninitializedGame();
  void SaveCompletedGame();

  void LoadIncorrectHeader();

  void LoadIncorrectMiddle();
  void LoadIncorrectEnd();

  void LoadIncorrectFieldMap();
  void LoadZeroFieldSize();
  void LoadNegativeFieldSize();
  void LoadIncorrectPlayerCrd();
  void LoadIncorrectEnemiesCrd();

  void LoadIncorrectEntranceCrd();

  void LoadIncorrectEnemyCount();
  void LoadIncorrectBlasterBeamCount();

private:
  Game::Game game_;
  GameLoaderPtr game_loader_;
};

TestExceptionHandling::TestExceptionHandling() {}

TestExceptionHandling::~TestExceptionHandling() {}


void TestExceptionHandling::LoadIncorrectFilePath() {
  try {
    game_loader_ = std::make_shared<Game::GameLoader>(game_, "IT_IS_A_TRAP!");
  }  catch (Game::LoadException& le) {
    QCOMPARE(le.what(), "Loading file doesn't exist");
  }
}

void TestExceptionHandling::SaveUninitializedGame() {
  Game::Game uninit_game;
  std::shared_ptr<Game::GameSaver> game_saver(new Game::GameSaver(uninit_game));
  try {
    game_saver->Save();
  } catch (Game::SaveException& se) {
    QCOMPARE(se.what(), "You try to save the uninitialized game");
  }
}

void TestExceptionHandling::SaveCompletedGame() {
  Game::Game completed_game;
  completed_game.NewGame("../../../UntitledDesktopGame/tests/TestExceptionHandling/correct_level.txt");
  completed_game.SetInGame(false);
  std::shared_ptr<Game::GameSaver> game_saver(new Game::GameSaver(completed_game));
  try {
    game_saver->Save();
  } catch (Game::SaveException& se) {
    QCOMPARE(se.what(), "You try to save the completed game");
  }
}

void TestExceptionHandling::LoadIncorrectHeader() {
  game_loader_ = std::make_shared<Game::GameLoader>(game_, "../../../UntitledDesktopGame/tests/TestExceptionHandling/incorrect_header.txt");
  try {
    game_loader_->Load();
  } catch (Game::LoadException& le) {
    QCOMPARE(le.what(), "Loading file is incorrect, because head is wrong");
  }
}

void TestExceptionHandling::LoadIncorrectMiddle() {
  game_loader_ = std::make_shared<Game::GameLoader>(game_, "../../../UntitledDesktopGame/tests/TestExceptionHandling/incorrect_middle.txt");
  try {
    game_loader_->Load();
  } catch (Game::LoadException& le) {
    QCOMPARE(le.what(), "Loading file is incorrect");
  }
}

void TestExceptionHandling::LoadIncorrectEnd() {
  game_loader_ = std::make_shared<Game::GameLoader>(game_, "../../../UntitledDesktopGame/tests/TestExceptionHandling/incorrect_end.txt");
  try {
    game_loader_->Load();
  } catch (Game::LoadException& le) {
    QCOMPARE(le.what(), "Loading file is incorrect: bad end");
  }
 }

void TestExceptionHandling::LoadIncorrectFieldMap() {
  game_loader_ = std::make_shared<Game::GameLoader>(game_, "../../../UntitledDesktopGame/tests/TestExceptionHandling/incorrect_field_map.txt");
  try {
    game_loader_->Load();
  } catch (Game::LoadException& le) {
    QCOMPARE(le.what(), "Loading file is incorrect: field contains unsupported symbols");
  }
}

void TestExceptionHandling::LoadNegativeFieldSize() {
  game_loader_ = std::make_shared<Game::GameLoader>(game_, "../../../UntitledDesktopGame/tests/TestExceptionHandling/negative_field_size.txt");
  try {
    game_loader_->Load();
  } catch (Game::LoadException& le) {
    QCOMPARE(le.what(), "Loading file is incorrect: bad coordinates");
  }
}

void TestExceptionHandling::LoadZeroFieldSize() {
  game_loader_ = std::make_shared<Game::GameLoader>(game_, "../../../UntitledDesktopGame/tests/TestExceptionHandling/zero_field_size.txt");
  try {
    game_loader_->Load();
  } catch (Game::LoadException& le) {
    QCOMPARE(le.what(), "Loading file is incorrect: bad coordinates");
  }
}

void TestExceptionHandling::LoadIncorrectPlayerCrd() {
  game_loader_ = std::make_shared<Game::GameLoader>(game_, "../../../UntitledDesktopGame/tests/TestExceptionHandling/incorrect_player_crd.txt");
  try {
    game_loader_->Load();
  } catch (Field::BadFieldException& bfe) {
    QCOMPARE(bfe.what(), "Incorrect player's coordinates");
  }
}

void TestExceptionHandling::LoadIncorrectEnemiesCrd() {
  game_loader_ = std::make_shared<Game::GameLoader>(game_, "../../../UntitledDesktopGame/tests/TestExceptionHandling/incorrect_enemy_crd.txt");
  try {
    game_loader_->Load();
  } catch (Field::BadFieldException& bfe) {
    QCOMPARE(bfe.what(), "Incorrect enemies' coordinates");
  }
}

void TestExceptionHandling::LoadIncorrectEnemyCount() {
  game_loader_ = std::make_shared<Game::GameLoader>(game_, "/home/mur/Programing/QtProjects/UntitledDesktopGame/tests/TestExceptionHandling/incorrect_enemy_count.txt");
  try {
    game_loader_->Load();
  } catch (Game::LoadException& le) {
    QCOMPARE(le.what(), "Loading file is incorrect: bad enemies count");
  }
}

void TestExceptionHandling::LoadIncorrectEntranceCrd() {
  game_loader_ = std::make_shared<Game::GameLoader>(game_, "../../../UntitledDesktopGame/tests/TestExceptionHandling/incorrect_entrance_crd.txt");
  try {
    game_loader_->Load();
  } catch (Game::LoadException& le) {
    QCOMPARE(le.what(), "Loading file is incorrect: bad coordinates");
  }
}

void TestExceptionHandling::LoadIncorrectBlasterBeamCount() {
  game_loader_ = std::make_shared<Game::GameLoader>(game_, "../../../UntitledDesktopGame/tests/TestExceptionHandling/incorrect_blaster_beams_count.txt");
  try {
    game_loader_->Load();
  } catch (Game::LoadException& le) {
    QCOMPARE(le.what(), "Loading file is incorrect: bad blaster beams count");
  }
}


QTEST_APPLESS_MAIN(TestExceptionHandling)

#include "tst_testexceptionhandling.moc"
