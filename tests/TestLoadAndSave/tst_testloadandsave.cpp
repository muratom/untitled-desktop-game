#include <QtTest>

#include <iostream>
#include <memory>

#include "Game/game.h"
#include "Game/Command/newgame.h"
#include "Game/Command/move.h"
#include "Game/gameloader.h"
#include "Units/iunit.h"

/*
 * 1) Файлы правильного формата, но со странными данными
 * 2) Снимок неинициализированной игры
 */

class TestLoadAndSave : public QObject {

  Q_OBJECT

  using GamePtr = std::shared_ptr<Game::Game>;

public:
  TestLoadAndSave();
  ~TestLoadAndSave();

private slots:
  void NewCorrectFile();
  void NewIncorrectFile();

  // Чтобы не сохранять файл при каждом запуске тестов
//  void SaveInitializedGame();
  void SaveUninitializedGame();
  void SaveCompletedGame();

  void LoadCorrectFile();
  void LoadIncorrectHeader();
  void LoadIncorrectField();
  void LoadIncorrectEnd();

private:
  GamePtr game = std::make_shared<Game::Game>();
};

TestLoadAndSave::TestLoadAndSave() {}

TestLoadAndSave::~TestLoadAndSave() {}

void TestLoadAndSave::NewCorrectFile() {
  bool isNewGame = game->NewGame("../../../UntitledDesktopGame/tests/TestLoadAndSave/correct_level.txt");
  QCOMPARE(isNewGame, true);
}

void TestLoadAndSave::NewIncorrectFile() {
  bool isNewGame = game->NewGame("../../../UntitledDesktopGame/tests/TestLoadAndSave/incorrect_level.txt");
  QCOMPARE(isNewGame, false);
}

void TestLoadAndSave::SaveUninitializedGame() {
  Game::Game g;
  bool isSaved = g.SaveGame();
  QCOMPARE(isSaved, false);
}

void TestLoadAndSave::SaveCompletedGame() {
  Game::Game g;
  g.SetInGame(false);
  bool isSaved = g.SaveGame();
  QCOMPARE(isSaved, false);
}

//void TestLoadAndSave::SaveInitializedGame() {
//  game->NewGame("../../../UntitledDesktopGame/tests/TestLoadAndSave/correct_level.txt");
//  bool isSaved = game->SaveGame();
//  QCOMPARE(isSaved, true);
//}

void TestLoadAndSave::LoadCorrectFile() {
  bool isLoaded = game->LoadGame("../../../UntitledDesktopGame/tests/TestLoadAndSave/correct_level.txt");
  QCOMPARE(isLoaded, true);
}

void TestLoadAndSave::LoadIncorrectHeader() {
  bool isLoaded = game->LoadGame("../../../UntitledDesktopGame/tests/TestLoadAndSave/incorrect_header.txt");
  QCOMPARE(isLoaded, false);
}

void TestLoadAndSave::LoadIncorrectField() {
  bool isLoaded = game->LoadGame("../../../UntitledDesktopGame/tests/TestLoadAndSave/incorrect_field.txt");
  QCOMPARE(isLoaded, false);
}

void TestLoadAndSave::LoadIncorrectEnd() {
  bool isLoaded = game->LoadGame("../../../UntitledDesktopGame/tests/TestLoadAndSave/incorrect_end.txt");
  QCOMPARE(isLoaded, false);
}

QTEST_APPLESS_MAIN(TestLoadAndSave)

#include "tst_testloadandsave.moc"
