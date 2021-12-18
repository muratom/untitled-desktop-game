#ifndef FIELDWIDGET_H
#define FIELDWIDGET_H

#include <memory>
#include <typeinfo>

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QDir>
#include <QTimer>
#include <QDebug>

#include "Game/game.h"
#include "Elements/FactoryMethod/Products/coin.h"
#include "Elements/FactoryMethod/Products/health.h"
#include "Elements/FactoryMethod/Products/lava.h"
#include "Elements/FactoryMethod/Products/wall.h"
#include "Elements/FactoryMethod/Products/floor.h"

// Размер изображении в пикселях, то есть (image_size * image_size) пикселей
constexpr uint16_t image_size = 40;

namespace Gui {

// Инвариант:
// Если загружаются не все изображения, то объект не создается
class FieldWidget : public QWidget {
  Q_OBJECT
  using PixmapPtr = std::shared_ptr<QPixmap>;
  using GamePtr = std::shared_ptr<Game::Game>;

public:
  explicit FieldWidget(GamePtr& game, QWidget* parent = nullptr);

  void LoadImages();

protected:
  void paintEvent(QPaintEvent*) override;

private:
  // Поле находится в RW-сегменте памяти (очищение после завершения программы),
  // поэтому нельзя использовать умные указатели
  GamePtr& game_;

  PixmapPtr left_player_img_ = nullptr;
  PixmapPtr right_player_img_ = nullptr;
  PixmapPtr front_player_img_ = nullptr;
  PixmapPtr back_player_img_ = nullptr;

  PixmapPtr left_fighter_img_ = nullptr;
  PixmapPtr right_fighter_img_ = nullptr;

  PixmapPtr left_shooter_img_ = nullptr;
  PixmapPtr right_shooter_img_ = nullptr;
  PixmapPtr blaster_beam_img_ = nullptr;

  PixmapPtr wall_img_ = nullptr;
  PixmapPtr floor_img_ = nullptr;
  PixmapPtr lava_img_ = nullptr;
  PixmapPtr health_img_ = nullptr;
  PixmapPtr coin_img_ = nullptr;
  PixmapPtr exit_img_ = nullptr;
};
}
#endif // FIELDWIDGET_H
