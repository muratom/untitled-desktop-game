#include "untitleddesktopgame.h"

namespace Gui {
UntitledDesktopGame::UntitledDesktopGame(QWidget *parent)
  : QMainWindow(parent),
    ui(new Ui::UntitledDesktopGame),
    game_(std::make_shared<Game::Game>()) {

  ui->setupUi(this);

  connect(ui->action_new_game, &QAction::triggered,
          this, &UntitledDesktopGame::NewGame);
  connect(ui->action_save_game, &QAction::triggered,
          this, &UntitledDesktopGame::SaveGame);
  connect(ui->action_load_game, &QAction::triggered,
          this, &UntitledDesktopGame::LoadGame);
  connect(ui->action_close_game, &QAction::triggered,
          this, &UntitledDesktopGame::CloseGame);
  connect(ui->action_exit, &QAction::triggered,
          this, &QApplication::quit);

  connect(timer_, &QTimer::timeout,
          this, &UntitledDesktopGame::GameCycle);

  ui->statusbar->addWidget(player_health_lbl);
  ui->statusbar->addWidget(player_points_lbl);
  ui->statusbar->addWidget(fight_state_status_bar);
  ui->statusbar->addWidget(game_status_lbl);
}

UntitledDesktopGame::~UntitledDesktopGame() {
  delete ui;
}

void UntitledDesktopGame::GameCycle() {
  if (game_->GetInGame()) {
    game_->MakeMove();
    field_widget_->update();
    // Обновляем status bar
    UpdateStatusBar();
  }
}


//double UntitledDesktopGame::GetCurrentTime() const {
//  return ((double) clock()) / CLOCKS_PER_SEC;
//}

void UntitledDesktopGame::keyPressEvent(QKeyEvent* e) {
  if (game_->GetInGame()) {
    std::shared_ptr<Command::ICommand> move_cmd = nullptr;
    switch (e->key()) {
      case Qt::Key_Up: {
        move_cmd = std::make_shared<Command::Move>(game_, game_->GetPlayer(), game_->GetPF()->GetPlayerCoord(), Units::Orientation::UP);
        break;
      }
      case Qt::Key_Right: {
        move_cmd = std::make_shared<Command::Move>(game_, game_->GetPlayer(), game_->GetPF()->GetPlayerCoord(), Units::Orientation::RIGHT);
        break;
      }
      case Qt::Key_Down: {
        move_cmd = std::make_shared<Command::Move>(game_, game_->GetPlayer(), game_->GetPF()->GetPlayerCoord(), Units::Orientation::DOWN);
        break;
      }
      case Qt::Key_Left: {
        move_cmd = std::make_shared<Command::Move>(game_, game_->GetPlayer(), game_->GetPF()->GetPlayerCoord(), Units::Orientation::LEFT);
        break;
      }
      // Похоже, что здесь происходит смешивание бизнес-логики и GUI
      case Qt::Key_A: {
        auto& plr = game_->GetPlayer();
        if (plr->GetFightState() != Units::FightState::ATTACK) {
          // Игрок хочет атаковать, он сможет это сделать тогда, когда ему дадут ход
          plr->SetFightState(Units::FightState::ATTACK);
        } else {
          // При выходе из атаки игрок переходит в нейтральное состояние
          plr->SetFightState(Units::FightState::NEUTRAL);
        }
        break;
      }
      case Qt::Key_D: {
        auto& plr = game_->GetPlayer();
        if (plr->GetFightState() != Units::FightState::DEFENSE) {
          // Игрок будет находится в защите, пока пользователь снова не нажмет кнопку
          plr->SetFightState(Units::FightState::DEFENSE);
        } else {
          // При выходе из защиты игрок переходит в нейтральное состояние
          plr->SetFightState(Units::FightState::NEUTRAL);
        }
        break;
      }
    }

    game_->SetMoveCmd(move_cmd);

    // game_->MovePlayer();

    // qDebug() << "Current player's coordinates: " << game_->GetPF()->GetPlayerCoord();

//    // Обновляем экран
//    field_widget_->update();

//    // Обновляем status bar
//    UpdateStatusBar();
  }
}

void UntitledDesktopGame::ConfigureLog() {
  // Учитывание настроек лога при создании новой игры
  std::shared_ptr<Command::ICommand> log_cmd = nullptr;

  if (ui->action_file_log->isChecked() && ui->action_console_log->isChecked()) {
    log_cmd = std::make_shared<Command::ConfigureLog>(game_->GetLog(), true, true);
  } else if (ui->action_file_log->isChecked()) {
    log_cmd = std::make_shared<Command::ConfigureLog>(game_->GetLog(), true, false);
  } else if (ui->action_console_log->isChecked()) {
    log_cmd = std::make_shared<Command::ConfigureLog>(game_->GetLog(), false, true);
  } else {
    log_cmd = nullptr;
  }

  game_->SetConfLogCmd(log_cmd);
}

void UntitledDesktopGame::UpdateStatusBar() {
  // Игра завершена, если игрок остался без здоровья
  if (!game_->IsPlayerAlive()) {
    game_status_lbl->setText("Game status: Game over");
  }

  // Уровень завершен при определенных условиях (игрок дошел до финиша и набрал определенное кол-во очков)
  if (game_->IsLevelComplete()) {
    game_status_lbl->setText("Game status: Level complete");
  }

  player_health_lbl->setText("Health: " + QString::number(game_->GetPlayer()->GetHealth()));
  player_points_lbl->setText("Points: " + QString::number(game_->GetPlayer()->GetPoints()) +
                             "/" + QString::number(game_->GetTargetPoints()));

  auto fs = game_->GetPlayer()->GetFightState();
  switch (fs) {
    case Units::FightState::ATTACK:
      fight_state_status_bar->setText("FightState: ATTACK");
      break;
    case Units::FightState::DEFENSE:
      fight_state_status_bar->setText("FightState: DEFENSE");
      break;
    case Units::FightState::NEUTRAL:
      fight_state_status_bar->setText("FightState: NEUTRAL");
      break;
  }
}


void UntitledDesktopGame::NewGame() {
  QString open_file_name = QFileDialog::getOpenFileName(this, "Choose the level", "/home/mur/Programing/QtProjects/UntitledDesktopGame/udg/Levels");
  if (open_file_name.isNull()) {
    qDebug() << "User didn't choose a file";
    return;
  }

  ConfigureLog();

  if (!game_->LoadGame(open_file_name.toStdString())) {
    return;
  }

//  // Сохраняем "снимок" класса игры, если игра была запущена до этого
//  if (game_->GetPlayer()) {
//    auto game_m = game_->SaveState();
//    if (!game_->NewGame(open_file_name.toStdString())) {
//      // Восстановление
//      game_->RestoreState(game_m);
//      return;
//    }
//  } else {
//    if (!game_->NewGame(open_file_name.toStdString())) {
//      return;
//    }
//  }

//  try {
//    game_->SetNewGameCmd(std::make_shared<Command::NewGame>(game_, open_file_name.toStdString()));
//    game_->ExecNewGameCmd();
//  }  catch (Game::LoadException& le) {
//    std::cerr << le.what() << std::endl;
//    return;
//  }


  // Если недостаточно памяти для загрузки изображении,
  // то виждет не создается и процесс загрузки игры завершается
  try {
    // Старый виждет удаляется
    field_widget_ = std::make_shared<FieldWidget>(game_);
  } catch (std::bad_alloc& ba) {
    field_widget_.reset();
    return;
  }

  // Добавляем виждет на экран
  ui->gridLayout->addWidget(field_widget_.get(), 1, 1);
  field_widget_->setFixedSize(game_->GetPF()->GetWidth() * image_size, game_->GetPF()->GetHeight() * image_size);

  // Обновляем status bar
  game_status_lbl->setText("Game status: In game");

  // Игровой цикл запускается только тогда, когда происходит вход в игру
  timer_->start(70);
  GameCycle();
}

void UntitledDesktopGame::SaveGame() {
  // Если не удалось сохранить игру, то
  // ничего дальше делать не нужно
  if (!game_->SaveGame())
    return;

//  try {
//    game_->SaveGame();
//  } catch (Game::SaveException& se) {
//    std::cerr << se.what() << std::endl;
//    return;
//  }
}

void UntitledDesktopGame::LoadGame() {
  QString open_file_name = QFileDialog::getOpenFileName(this, "Choose the level", "/home/mur/Programing/QtProjects/UntitledDesktopGame/udg/SaveLevels");
  if (open_file_name.isNull()) {
    qDebug() << "User didn't choose a file";
    return;
  }

  ConfigureLog();

  if (!game_->LoadGame(open_file_name.toStdString())) {
    return;
  }
  // Сохраняем "снимок" класса игры, если игра была запущена до этого
//  if (game_->GetPlayer()) {
//    auto game_m = game_->SaveState();
//    if (!game_->LoadGame(open_file_name.toStdString())) {
//      // Восстановление
//      game_->RestoreState(game_m);
//      return;
//    }
//  } else {
//    if (!game_->LoadGame(open_file_name.toStdString())) {
//      return;
//    }
//  }
//    try {
//      game_->LoadGame(open_file_name.toStdString());
//    }  catch (Game::LoadException& le) {
//      // Восстановление
//      game_->RestoreState(game_m);
//      std::cerr << le.what() << std::endl;
//      return;
//    }
//  } else {
//    try {
//      game_->LoadGame(open_file_name.toStdString());
//    }  catch (Game::LoadException& le) {
//      std::cerr << le.what() << std::endl;
//      return;
//    }
//  }


  // Если недостаточно памяти для загрузки изображении,
  // то виждет не создается и процесс загрузки игры завершается
  try {
    // Старый виждет удаляется
    field_widget_ = std::make_shared<FieldWidget>(game_);
  } catch (std::bad_alloc& ba) {
    field_widget_.reset();
    return;
  }

  // Добавляем виждет на экран
  ui->gridLayout->addWidget(field_widget_.get(), 1, 1);
  field_widget_->setFixedSize(game_->GetPF()->GetWidth() * image_size, game_->GetPF()->GetHeight() * image_size);

  // Обновляем status bar
  game_status_lbl->setText("Game status: In game");
  // Если же на самом деле игра окончена, то информация обновится вызовом следующей функций
  UpdateStatusBar();

  // Игровой цикл запускается только тогда, когда происходит вход в игру
  timer_->start(70);
  GameCycle();
}

void UntitledDesktopGame::CloseGame() {
  // Игра завершается, следовательно, таймер не нужен
  timer_->stop();

  game_->SetExitGameCmd(std::make_shared<Command::ExitGame>(game_));
  game_->ExecExitGameCmd();

  field_widget_.reset();

  player_health_lbl->clear();
  player_points_lbl->clear();
  game_status_lbl->clear();
}
}
