#ifndef UNTITLEDDESKTOPGAME_H
#define UNTITLEDDESKTOPGAME_H

#include "ui_untitleddesktopgame.h"

#include <fstream>
#include <string>
#include <memory>
#include <list>

#include <QDebug>
#include <QPixmap>
#include <QPainter>
#include <QDir>
#include <QMainWindow>
#include <QPixmap>
#include <QPaintEvent>
#include <QInputDialog>
#include <QFileDialog>
#include <QKeyEvent>
#include <QLabel>

#include "fieldwidget.h"
#include "UDG/fieldwidget.h"

#include "Game/Command/newgame.h"
#include "Game/Command/exitgame.h"
#include "Game/Command/move.h"
#include "Game/game.h"
#include "Game/gamesaver.h"
#include "Game/gameloader.h"

QT_BEGIN_NAMESPACE
namespace Ui { class UntitledDesktopGame; }
QT_END_NAMESPACE

namespace Gui {
// Инварианты:
// Таймер работает только тогда, когда in_game_ = true
class UntitledDesktopGame : public QMainWindow {
  Q_OBJECT

  using GamePtr = std::shared_ptr<Game::Game>;
  using FieldWidgetPtr = std::shared_ptr<FieldWidget>;
public:
  UntitledDesktopGame(QWidget* parent = nullptr);
  ~UntitledDesktopGame();

  // double GetCurrentTime() const;

  void ConfigureLog();
  void UpdateStatusBar();

  const GamePtr& GetGame() const { return game_; }

  void keyPressEvent(QKeyEvent* e) override;

public slots:
  void NewGame();
  void SaveGame();
  void LoadGame();
  void CloseGame();
  void GameCycle();

private:
  Ui::UntitledDesktopGame* ui;
  QTimer* timer_ = new QTimer(this); // Обычный указатель, так как есть parent

  GamePtr game_ = nullptr;

  FieldWidgetPtr field_widget_ = nullptr;

  QLabel* player_health_lbl = new QLabel(this);
  QLabel* player_points_lbl = new QLabel(this);
  QLabel* game_status_lbl = new QLabel(this);
  QLabel* fight_state_status_bar = new QLabel(this);
};
}


#endif // UNTITLEDDESKTOPGAME_H
