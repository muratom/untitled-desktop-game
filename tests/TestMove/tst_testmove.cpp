#include <QtTest>
#include <QCoreApplication>

#include <memory>
#include <vector>

#include "Game/game.h"
#include "Game/Command/move.h"
#include "Units/iunit.h"

Q_DECLARE_METATYPE(Units::Orientation);

class TestMove : public QObject {
  Q_OBJECT

  using Point2D = std::pair<int16_t, int16_t>;

public:
  TestMove();
  ~TestMove();

private slots:
  void initTestCase();
  void init();
//  void cleanupTestCase();

  void Move();
  void Move_data();

private:
  std::shared_ptr<Game::Game> game_ = std::make_shared<Game::Game>();
};

TestMove::TestMove() {}

TestMove::~TestMove() {}

void TestMove::initTestCase() {
  game_->NewGame("../../../untitled-desktop-game/tests/TestMove/test_level.txt");
}

void TestMove::init() {
  game_->GetPF()->SetPlayerCoord({2, 2});
}

void TestMove::Move() {
  QFETCH(std::vector<Units::Orientation>, orientations);
  QFETCH(Point2D, coordinates);

  std::shared_ptr<Command::ICommand> move_cmd = nullptr;
  for (auto& elem : orientations) {
    qDebug() << "elem = " << elem;
    move_cmd = std::make_shared<Command::Move>(game_, game_->GetPlayer(), game_->GetPF()->GetPlayerCoord(), elem);
    game_->SetMoveCmd(move_cmd);
    game_->MoveUnit();
  }

  QCOMPARE(game_->GetPF()->GetPlayerCoord(), coordinates);
}

void TestMove::Move_data() {
  QTest::addColumn<std::vector<Units::Orientation>>("orientations");
  QTest::addColumn<Point2D>("coordinates");

  std::vector<Units::Orientation> vec1;
  vec1.push_back(Units::Orientation::UP);
  QTest::addRow("Up") << vec1 << Point2D(1, 2);

  std::vector<Units::Orientation> vec2;
  vec2.push_back(Units::Orientation::RIGHT);
  QTest::addRow("Right") << vec2 << Point2D(2, 3);

  std::vector<Units::Orientation> vec3;
  vec3.push_back(Units::Orientation::DOWN);
  QTest::addRow("Down") << vec3 << Point2D(3, 2);

  std::vector<Units::Orientation> vec4;
  vec4.push_back(Units::Orientation::LEFT);
  QTest::addRow("Left") << vec4 << Point2D(2, 1);

  std::vector<Units::Orientation> vec5;
  vec5.push_back(Units::Orientation::RIGHT);
  vec5.push_back(Units::Orientation::DOWN);
  vec5.push_back(Units::Orientation::LEFT);
  vec5.push_back(Units::Orientation::LEFT);
  vec5.push_back(Units::Orientation::UP);
  vec5.push_back(Units::Orientation::UP);
  vec5.push_back(Units::Orientation::RIGHT);
  vec5.push_back(Units::Orientation::RIGHT);
  vec5.push_back(Units::Orientation::DOWN);
  vec5.push_back(Units::Orientation::LEFT);
  QTest::addRow("Circle") << vec5 << Point2D(2, 2);

  std::vector<Units::Orientation> vec6;
  vec6.push_back(Units::Orientation::RIGHT);
  vec6.push_back(Units::Orientation::RIGHT);
  QTest::addRow("Right wall") << vec6 << Point2D(2, 3);

  std::vector<Units::Orientation> vec7;
  vec7.push_back(Units::Orientation::LEFT);
  vec7.push_back(Units::Orientation::LEFT);
  QTest::addRow("Left wall") << vec7 << Point2D(2, 1);

  std::vector<Units::Orientation> vec8;
  vec8.push_back(Units::Orientation::UP);
  vec8.push_back(Units::Orientation::UP);
  QTest::addRow("Up wall") << vec8 << Point2D(1, 2);

  std::vector<Units::Orientation> vec9;
  vec9.push_back(Units::Orientation::DOWN);
  vec9.push_back(Units::Orientation::DOWN);
  QTest::addRow("Down wall") << vec9 << Point2D(3, 2);
}

QTEST_MAIN(TestMove)

#include "tst_testmove.moc"
