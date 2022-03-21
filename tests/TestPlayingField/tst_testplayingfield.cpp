#include <QtTest>

#include "Game/game.h"

class TestPlayingField : public QObject {
  Q_OBJECT

public:
  TestPlayingField();
  ~TestPlayingField();

private slots:
  void SizeCustomization();
  void PointerCustomization();
  void PlrCrdCustomization();
  void EnemyCrdCustomization();
  void EntranceCrdCustomization();
  void ExitCrdCustomization();

  void IteratorBegin();
  void IteratorEnd();
  void IteratorIncDec();
  void IteratorCurCrdNotBound();
  void IteratorCurCrdBound();

private:
  Field::PlayingField* pf_;
};

TestPlayingField::TestPlayingField() {
  Game::Game game;
  game.NewGame("../../../untitled-desktop-game/tests/TestPlayingField/correct_level.txt");
  // В pf_ хранится корректное поле (его размер 20x35)
  pf_ = game.GetPF();
}

TestPlayingField::~TestPlayingField() {}

void TestPlayingField::SizeCustomization() {
  Field::PlayingField& pf = Field::PlayingField::GetInstance();
  try {
    pf.CustomizeField(0, -1, pf_->GetField(), {0, 0}, {{0, 0}}, {0, 0}, {0, 0});
  } catch (Field::BadFieldException& bfe) {
    QCOMPARE(bfe.what(), "Incorrect field parameters");
  }
}

void TestPlayingField::PointerCustomization() {
  Field::PlayingField& pf = Field::PlayingField::GetInstance();
  try {
    pf.CustomizeField(1, 1, nullptr, {0, 0}, {{0, 0}}, {0, 0}, {0, 0});
  } catch (Field::BadFieldException& bfe) {
    QCOMPARE(bfe.what(), "Incorrect field pointer");
  }
}

void TestPlayingField::PlrCrdCustomization() {
  Field::PlayingField& pf = Field::PlayingField::GetInstance();

  // Under
  try {
    pf.CustomizeField(1, 1, pf_->GetField(), {0, 0}, {{0, 0}}, {0, 0}, {0, 0});
  } catch (Field::BadFieldException& bfe) {
    QCOMPARE(bfe.what(), "Incorrect player's coordinates");
  }

  // Over
  try {
    pf.CustomizeField(5, 5, pf_->GetField(), {6, 3}, {{0, 0}}, {0, 0}, {0, 0});
  } catch (Field::BadFieldException& bfe) {
    QCOMPARE(bfe.what(), "Incorrect player's coordinates");
  }
}

void TestPlayingField::EnemyCrdCustomization() {
  Field::PlayingField& pf = Field::PlayingField::GetInstance();

  // Under
  try {
    pf.CustomizeField(5, 5, pf_->GetField(), {3, 3}, {{0, 0}, {2, 3}}, {0, 0}, {0, 0});
  } catch (Field::BadFieldException& bfe) {
    QCOMPARE(bfe.what(), "Incorrect enemies' coordinates");
  }

  // Over
  try {
    pf.CustomizeField(5, 5, pf_->GetField(), {3, 3}, {{7, 7}, {2, 3}}, {0, 0}, {0, 0});
  } catch (Field::BadFieldException& bfe) {
    QCOMPARE(bfe.what(), "Incorrect enemies' coordinates");
  }
}

void TestPlayingField::EntranceCrdCustomization() {
  Field::PlayingField& pf = Field::PlayingField::GetInstance();

  // Under
  try {
    pf.CustomizeField(5, 5, pf_->GetField(), {3, 3}, {{4, 1}, {2, 3}}, {-1, -42}, {-100, 0});
  } catch (Field::BadFieldException& bfe) {
    QCOMPARE(bfe.what(), "Incorrect entrance or exit coordinates");
  }

  // Over
  try {
    pf.CustomizeField(5, 5, pf_->GetField(), {3, 3}, {{4, 1}, {2, 3}}, {5, 5}, {-100, 0});
  } catch (Field::BadFieldException& bfe) {
    QCOMPARE(bfe.what(), "Incorrect entrance or exit coordinates");
  }
}

void TestPlayingField::ExitCrdCustomization() {
  Field::PlayingField& pf = Field::PlayingField::GetInstance();

  // Under
  try {
    pf.CustomizeField(5, 5, pf_->GetField(), {3, 3}, {{4, 1}, {2, 3}}, {1, 1}, {-100, 0});
  } catch (Field::BadFieldException& bfe) {
    QCOMPARE(bfe.what(), "Incorrect entrance or exit coordinates");
  }

  // Over
  try {
    pf.CustomizeField(5, 5, pf_->GetField(), {3, 3}, {{4, 1}, {2, 3}}, {1, 1}, {100, 42});
  } catch (Field::BadFieldException& bfe) {
    QCOMPARE(bfe.what(), "Incorrect entrance or exit coordinates");
  }
}

void TestPlayingField::IteratorBegin() {
  std::pair<int16_t, int16_t> pair(0, 0);
  QCOMPARE(pf_->Begin().GetCurrentCoord(), pair);
}

void TestPlayingField::IteratorEnd() {
  std::pair<int16_t, int16_t> pair(20, 0);
  QCOMPARE(pf_->End().GetCurrentCoord(), pair);
}

void TestPlayingField::IteratorIncDec() {
  QCOMPARE(--(++pf_->Begin()), pf_->Begin());
  QCOMPARE((pf_->End()--)++, pf_->End());
}

void TestPlayingField::IteratorCurCrdNotBound() {
  Field::PlayingField::Iterator iter(*pf_, {15, 15});
  ++iter;
  std::pair<int16_t, int16_t> pair(15, 16);
  QCOMPARE(iter.GetCurrentCoord(), pair);
}

void TestPlayingField::IteratorCurCrdBound() {
  Field::PlayingField::Iterator iter(*pf_, {19, 34});
  ++iter;
  std::pair<int16_t, int16_t> pair(20, 0);
  QCOMPARE(iter.GetCurrentCoord(), pair);
}

QTEST_APPLESS_MAIN(TestPlayingField)

#include "tst_testplayingfield.moc"
