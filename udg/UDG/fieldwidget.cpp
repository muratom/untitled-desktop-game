#include "fieldwidget.h"

namespace Gui {

FieldWidget::FieldWidget(GamePtr& game, QWidget* parent)
    : QWidget(parent), game_(game) {
//  QTimer* timer = new QTimer(this); // Обычный указатель, так как есть parent
//  connect(timer, &QTimer::timeout,
//          this, QOverload<>::of(&FieldWidget::update));
//  timer->start(16); // 60 FPS

  LoadImages();
  update();
}

void FieldWidget::LoadImages() {
  try {
    right_player_img_ = PixmapPtr(new QPixmap(":/Images/right_sonic_40x40.png"));
    left_player_img_ = PixmapPtr(new QPixmap(":/Images/left_sonic_40x40.png"));
    front_player_img_ = PixmapPtr(new QPixmap(":/Images/front_sonic_40x40.png"));
    back_player_img_ = PixmapPtr(new QPixmap(":/Images/back_sonic_40x40.png"));

    left_fighter_img_ = PixmapPtr(new QPixmap(":/Images/left_darth_vader_40x40.png"));
    right_fighter_img_ = PixmapPtr(new QPixmap(":/Images/right_darth_vader_40x40.png"));

    left_shooter_img_ = PixmapPtr(new QPixmap(":/Images/left_stormtrooper_40x40.png"));
    right_shooter_img_ = PixmapPtr(new QPixmap(":/Images/right_stormtrooper_40x40.png"));
    blaster_beam_img_ = PixmapPtr(new QPixmap(":/Images/blaster_beam_40x40.png"));

    wall_img_ = PixmapPtr(new QPixmap(":/Images/wall40x40.png"));
    floor_img_ = PixmapPtr(new QPixmap(":/Images/floor40x40.png"));
    coin_img_ = PixmapPtr(new QPixmap(":/Images/coin40x40.png"));
    exit_img_ = PixmapPtr(new QPixmap(":/Images/exit40x40.png"));
    health_img_ = PixmapPtr(new QPixmap(":/Images/health40x40.png"));
    lava_img_ = PixmapPtr(new QPixmap(":/Images/lava40x40.png"));
  } catch (std::bad_alloc& ba) {
    std::cerr << ba.what() << std::endl;
    throw std::bad_alloc();
  }
}

void FieldWidget::paintEvent(QPaintEvent*) {
  QPainter qp(this);
  Field::PlayingField* pf_ptr = game_->GetPF();
  // Обновляем все элементы поля учитывая,
  // что элемент может перейти в состояние
  // "использованный", тогда мы заменяем его на "пол".
  for (auto pf_iter = pf_ptr->Begin(); pf_iter != pf_ptr->End(); ++pf_iter) {
    const Elements::IElement& elem = pf_iter->GetElement();
    // drawPixmap(w, h, Pixmap) => second, first
    if (typeid (elem) == typeid (Elements::Wall))
      qp.drawPixmap(pf_iter.GetCurrentCoord().second * image_size, pf_iter.GetCurrentCoord().first * image_size, *wall_img_);
    else if (typeid (elem) == typeid (Elements::Lava))
      qp.drawPixmap(pf_iter.GetCurrentCoord().second * image_size, pf_iter.GetCurrentCoord().first * image_size, *lava_img_);
    else if (typeid (elem) == typeid (Elements::Floor))
      qp.drawPixmap(pf_iter.GetCurrentCoord().second * image_size, pf_iter.GetCurrentCoord().first * image_size, *floor_img_);
    if (typeid (elem) == typeid (Elements::Coin)) {
      const Elements::Coin& coin = static_cast<const Elements::Coin&>(elem);
      qp.drawPixmap(pf_iter.GetCurrentCoord().second * image_size, pf_iter.GetCurrentCoord().first * image_size, *floor_img_);
      if (!coin.IsUsed())
        qp.drawPixmap(pf_iter.GetCurrentCoord().second * image_size, pf_iter.GetCurrentCoord().first * image_size, *coin_img_);
    } else if (typeid (elem) == typeid (Elements::Health)) {
      const Elements::Health& health = static_cast<const Elements::Health&>(elem);
      qp.drawPixmap(pf_iter.GetCurrentCoord().second * image_size, pf_iter.GetCurrentCoord().first * image_size, *floor_img_);
      if (!health.IsUsed())
        qp.drawPixmap(pf_iter.GetCurrentCoord().second * image_size, pf_iter.GetCurrentCoord().first * image_size, *health_img_);
    }
  }
  // Отрисовываем выход
  qp.drawPixmap(pf_ptr->GetExitCoord().second * image_size, pf_ptr->GetExitCoord().first * image_size, *exit_img_);

  // Обновляем расположение игрока на поле
  auto& plr_crd = pf_ptr->GetPlayerCoord();
  switch (game_->GetPlayer()->GetOrient()) {
    case Units::Orientation::RIGHT:
      qp.drawPixmap(plr_crd.second * image_size, plr_crd.first * image_size, *right_player_img_);
      break;
    case Units::Orientation::LEFT:
      qp.drawPixmap(plr_crd.second * image_size, plr_crd.first * image_size, *left_player_img_);
      break;
    case Units::Orientation::DOWN:
      qp.drawPixmap(plr_crd.second * image_size, plr_crd.first * image_size, *front_player_img_);
      break;
    case Units::Orientation::UP:
      qp.drawPixmap(plr_crd.second * image_size, plr_crd.first * image_size, *back_player_img_);
      break;
  }
  // Обновляем расположение врага на поле
  auto& enemies = game_->GetEnemies();
  for (size_t i = 0; i < enemies.size(); ++i) {
    if (game_->GetEnemies()[i]->GetHealth() != 0) {
      auto& enemy_crd = pf_ptr->GetEnemiesCoord()[i];
      switch(game_->GetEnemies()[i]->GetOrient()) {
        case Units::Orientation::LEFT: {
          if (enemies[i]->GetAttackPltc() == Units::AttackPolitic::DISTANT)
            qp.drawPixmap(enemy_crd.second * image_size, enemy_crd.first * image_size, *left_shooter_img_);
          else
            qp.drawPixmap(enemy_crd.second * image_size, enemy_crd.first * image_size, *left_fighter_img_);
          break;
        }
        case Units::Orientation::RIGHT: {
          if (enemies[i]->GetAttackPltc() == Units::AttackPolitic::DISTANT)
            qp.drawPixmap(enemy_crd.second * image_size, enemy_crd.first * image_size, *right_shooter_img_);
          else
            qp.drawPixmap(enemy_crd.second * image_size, enemy_crd.first * image_size, *right_fighter_img_);
          break;
        }
        default: {
          if (plr_crd.second <= enemy_crd.second) {
            if (enemies[i]->GetAttackPltc() == Units::AttackPolitic::DISTANT)
              qp.drawPixmap(enemy_crd.second * image_size, enemy_crd.first * image_size, *left_shooter_img_);
            else
              qp.drawPixmap(enemy_crd.second * image_size, enemy_crd.first * image_size, *left_fighter_img_);
          } else {
            if (enemies[i]->GetAttackPltc() == Units::AttackPolitic::DISTANT)
              qp.drawPixmap(enemy_crd.second * image_size, enemy_crd.first * image_size, *right_shooter_img_);
            else
              qp.drawPixmap(enemy_crd.second * image_size, enemy_crd.first * image_size, *right_fighter_img_);
          }
        }
      }
    }
  }

  // Обновляем расположение лучей на поле
  for (auto& beam : game_->GetBlasterBeams()) {
    qp.drawPixmap(beam.crd.second * image_size, beam.crd.first * image_size, *blaster_beam_img_);
  }
}
}
