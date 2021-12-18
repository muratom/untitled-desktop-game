#include "gameloader.h"

namespace Game {
GameLoader::GameLoader(Game& game, const std::string& file_name)
  : game_(game), load_file_(std::fstream(file_name)) {
  if (!load_file_.is_open())
    throw LoadException("Loading file doesn't exist");
}

GameLoader::~GameLoader() {
  if (load_file_.is_open())
    load_file_.close();
}

void GameLoader::Load() {
  // Проверяем заголовок файла
  std::string file_head;
  load_file_ >> file_head;
  if (file_head != "Answer_to_the_Ultimate_Question_of_Life,_the_Universe,_and_Everything_is_42") {
    throw LoadException("Loading file is incorrect, because head is wrong");
  }

  /*
    Содержимое файла с сохранением:
    1) Игровое поле (PlayingField): высота, ширина, целевые очки, координаты входа, выхода, карта
    2) Игрок (Player): координаты игрока, здоровье, очки, атака, коэффициент защиты, боевое состояние, ориентация
    3) Враги и лучи бластера (Enemies and BlasterBeams): количество врагов, координаты, здоровье, сила атаки, боевое состояние, ориентация, тип врага (MovePltc, AttackPltc)
       количество лучей, координаты (x,y), ориентация и урон
    4) Игра (Game): состояние игры
  */

  // ИГРОВОЕ ПОЛЕ

  // Высота и ширина поля
  int16_t height;
  int16_t width;
  load_file_ >> height;
  load_file_ >> width;

  // Целевые очки
  int16_t tp;
  load_file_ >> tp;
  game_.SetTargetPoints(tp);

  // Координаты входа и выхода
  Field::Point2D entr_crd;
  Field::Point2D exit_crd;

  load_file_ >> entr_crd.first >> entr_crd.second;
  load_file_ >> exit_crd.first >> exit_crd.second;

  // Если координаты входа и выхода не валидны,
  // то выбрасываем исключение
  // (CustomizeField не обработает данную ошибку, так как
  // при инициализации клеток на входе и выходе может произойти Segmentation Fault)
  if ((entr_crd.first >= height) || (entr_crd.second >= width) ||
      (entr_crd.first <= 0) || (entr_crd.second <= 0) ||
      (exit_crd.first >= height) || (exit_crd.second >= width) ||
      (exit_crd.first <= 0) || (exit_crd.second <= 0)) {
    throw LoadException("Loading file is incorrect: bad coordinates");
  }

  // Если файл уже некорректный, то нет необходимости выделять память для поля
  if (load_file_.eof())
    throw LoadException("Loading file is incorrect");

  // Карта
  Field::FieldPtr field = Field::FieldPtr(new std::shared_ptr<Field::Cell[]>[height]);
  for (int16_t i = 0; i < height; ++i) {
    field[i] = std::shared_ptr<Field::Cell[]>(new Field::Cell[width]);
  }

  // Для создания объектов (использование паттерна "Фабричный метод")
  CreatorPtr creator = nullptr;
//  Elements::FloorCreator fc;
//  Elements::WallCreator wc;
//  Elements::CoinCreator cc;
//  Elements::HealthCreator hc;
//  Elements::LavaCreator lc;

  // Настройка лога
  // (данная инструкция расположена здесь, так как элементам поля уже нужен объект лога)
  game_.ConfigureLog();

  // Проходим по каждой строке в файле
  char c;
  for (int16_t i = 0; i < height; ++i) { //std::getline(load_file_, cur_line); ++cur_row) {
    for (int16_t j = 0; j < width; ++j) {
      load_file_ >> c;
      switch (c) {
        case 'f': { // Пол
          creator = std::make_shared<Elements::FloorCreator>();
          field[i][j] = Field::Cell(creator->CreateElement());
          break;
        }
        case 'w': { // Стена
          creator = std::make_shared<Elements::WallCreator>();
          field[i][j] = Field::Cell(creator->CreateElement());
          break;
        }
        case 'c': { // Монета
          creator = std::make_shared<Elements::CoinCreator>();
          field[i][j] = Field::Cell(creator->CreateElement());

          auto c = creator->CreateElement();
          field[i][j] = Field::Cell(c);
          if (game_.log_)
            c->Connect(game_.log_.get());
          break;
        }
        case 'l': { // Лава
          creator = std::make_shared<Elements::LavaCreator>();
          field[i][j] = Field::Cell(creator->CreateElement());
          break;
        }
        case 'h': { // Здоровье
          creator = std::make_shared<Elements::HealthCreator>();
          field[i][j] = Field::Cell(creator->CreateElement());

          auto h = creator->CreateElement();
          field[i][j] = Field::Cell(h);
          if (game_.log_)
            h->Connect(game_.log_.get());
          break;
        }
        default: // Если встретился сторонний символ
          throw LoadException("Loading file is incorrect: field contains unsupported symbols");
          break;
      }
    }
    // Символ переноса строки не нужен
    load_file_.get();
  }

  creator = std::make_shared<Elements::FloorCreator>();
  field[entr_crd.first][entr_crd.second] = Field::Cell(creator->CreateElement());
  field[exit_crd.first][exit_crd.second] = Field::Cell(creator->CreateElement());

  // ИГРОК

  // Координаты
  Point2D plr_crd;
  load_file_ >> plr_crd.first >> plr_crd.second;

  // qDebug() << "Player's coordinates: " << plr_crd.first << ' ' << plr_crd.second;

  // Здоровье, очки, атака, коэффициент защиты, боевое состояние, ориентация
  int16_t health;
  int16_t points;
  int16_t attack_power;
  int16_t defense_coeff; // Во сколько раз уменьшится атака врага
  int16_t fstate;
  int16_t orient; // Куда ориентирован игрок

  load_file_ >> health >> points >> attack_power >>
      defense_coeff >> fstate >> orient;

  // Если файл уже некорректный, то нет необходимости создавать игрока
  if (load_file_.eof())
    throw LoadException("Loading file is incorrect");

  // Новый объект игрока (старый пока что не удален)
  // Используется остаток от деления, чтобы значение входило в enum
  PlayerPtr plr = PlayerPtr(new Units::Player(health, points, attack_power, defense_coeff,
                                              static_cast<Units::FightState>(fstate % 3),
                                              static_cast<Units::Orientation>(orient % 4)));

  // ВРАГИ

  // Количество врагов
  int16_t enemies_count;
  load_file_ >> enemies_count;

  // Количество врагов должно быть неотрицательным
  if (enemies_count < 0) {
    throw LoadException("Loading file is incorrect: bad enemies count");
  }

  // Координаты, здоровье, сила атаки, боевое состояние, ориентация, тип врага (MovePltc, AttackPltc)
  // std::vector<EnemyInfo> enemies_info;

  std::vector<Point2D> enemies_coord;
  Point2D cur_crd;
  int16_t cur_mp;
  int16_t cur_ap;

  // Старые враги удаляются
  game_.enemies_.clear();

  for (int16_t i = 0; i < enemies_count; ++i) {
    load_file_ >> cur_crd.first >> cur_crd.second >>
        health >> attack_power >>
        fstate >> orient >>
        cur_mp >> cur_ap;

    // Если файл уже некорректный, то нет необходимости продолжать чтение
    if (load_file_.eof())
      throw LoadException("Loading file is incorrect");

    enemies_coord.push_back(cur_crd);

    // Используется остаток от деления, чтобы значение входило в enum
    switch (cur_mp) {
      case Units::HORIZONTAL:
        switch (cur_ap) {
          case Units::DISTANT:
            game_.enemies_.push_back(std::make_shared<HorizontalShooter>
                                     (health, attack_power,
                                      static_cast<Units::FightState>(fstate % 3),
                                      static_cast<Units::Orientation>(orient % 4)));
            break;
          case Units::NEAR:
            game_.enemies_.push_back(std::make_shared<HorizontalFighter>
                                     (health, attack_power,
                                      static_cast<Units::FightState>(fstate % 3),
                                      static_cast<Units::Orientation>(orient % 4)));
            break;
        }
        break;
      case Units::VERTICAL:
        switch (cur_ap) {
          case Units::DISTANT:
            game_.enemies_.push_back(std::make_shared<VerticalShooter>
                                     (health, attack_power,
                                      static_cast<Units::FightState>(fstate % 3),
                                      static_cast<Units::Orientation>(orient % 4)));
            break;

          case Units::NEAR:
            game_.enemies_.push_back(std::make_shared<HorizontalFighter>
                                     (health, attack_power,
                                      static_cast<Units::FightState>(fstate % 3),
                                      static_cast<Units::Orientation>(orient % 4)));
            break;
        }
        break;
    }
  }

  // Количество лучей, координаты (x,y), ориентация и урон
  int16_t bbeams_count;
  load_file_ >> bbeams_count;

  // Количество лучей должно быть неотрицательным
  if (bbeams_count < 0) {
    throw LoadException("Loading file is incorrect: bad blaster beams count");
  }

  // Старые лучи удаляются
  game_.blaster_beams_.clear();
  for (int16_t i = 0; i < bbeams_count; ++i) {
    load_file_ >> cur_crd.first >> cur_crd.second >> orient >> attack_power;
    game_.blaster_beams_.emplace_back(cur_crd, orient, attack_power);
  }

  // ИГРА
  load_file_ >> game_.in_game_;

  // Если файл уже некорректный, то нет необходимости продолжать чтение
  if (load_file_.eof())
    throw LoadException("Loading file is incorrect: bad end");

  // Первым ходит игрок
  game_.turn_ = TurnPtr(new Turn::PlayerTurn(game_));

  // За удаление предыдущей версии поля отвечает CustomizeField (удаляются старые издатели)
  game_.pf_ptr_->CustomizeField(height, width, field, plr_crd, enemies_coord, entr_crd, exit_crd);

  // Старый игрок удаляется
  game_.GetPlayer() = plr;

  // Элементы поля, игрок и враги, на которые был подписан текущий объект класс Log, удалены
  // Разрывать связь старого объекта класса Log с объектами этих классов нет смысла.

  // Лог наблюдает за полем, игроком, врагами и самой игрой
  if (game_.log_) {
    game_.Connect(game_.log_.get());
    game_.pf_ptr_->Connect(game_.log_.get());
    game_.player_->Connect(game_.log_.get());
    for (auto& e : game_.enemies_)
      e->Connect(game_.log_.get());
  }
}
}

