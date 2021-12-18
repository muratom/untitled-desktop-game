#include "enemyturn.h"
#include "game.h"
#include "Units/enemy.h"
#include "Units/player.h"
#include "playerturn.h"

#include <QDebug>

namespace Turn {

// Пока что без рандомного передвижения врага

EnemyTurn::EnemyTurn(Game::Game& game)
    : game_(game) {
  // Для генерации псевдослучайных чисел
  std::srand(static_cast<unsigned int>(time(0)));
}

void EnemyTurn::MakeMove() {
  using Point2D = std::pair<int16_t, int16_t>;

  Field::PlayingField* pf_ptr = game_.GetPF();

  // Координты противников
  auto& enemies_crd = pf_ptr->GetEnemiesCoord();
  auto& enemies = game_.GetEnemies();

  auto& bbeams = game_.GetBlasterBeams();

  // Обновляем расположение лучей бластеров
  auto beam_iter = bbeams.begin();
  while (beam_iter != bbeams.end()) {
    switch (beam_iter->orient) {
      case Units::Orientation::UP: {
        // Элемент, находящийся сверху
        Elements::IElement& up_elem = pf_ptr->GetField()[beam_iter->crd.first - 1][beam_iter->crd.second].GetElement();

        // Перемещение луча заблокировано, если он взаимодействует с непересекаемым объектом
        if (up_elem.GetIsPassable()) {
          beam_iter->crd = { beam_iter->crd.first - 1, beam_iter->crd.second };
          // Луч наносит урон игроку, если он попадает в него
          if (pf_ptr->GetPlayerCoord() == beam_iter->crd) {
            game_.GetPlayer()->SetHealth(game_.GetPlayer()->GetHealth() - beam_iter->damage);
            beam_iter = bbeams.erase(beam_iter);
          } else {
            ++beam_iter;
          }
        } else {
          beam_iter = bbeams.erase(beam_iter);
          continue;
        }
        break;
      }
      case Units::Orientation::RIGHT: {
        // Элемент, находящийся справа
        Elements::IElement& right_elem = pf_ptr->GetField()[beam_iter->crd.first][beam_iter->crd.second + 1].GetElement();

        // Перемещение луча заблокировано, если он взаимодействует с непересекаемым объектом
        if (right_elem.GetIsPassable()) {
          beam_iter->crd = { beam_iter->crd.first, beam_iter->crd.second + 1 };
          // Луч наносит урон игроку, если он попадает в него
          if (pf_ptr->GetPlayerCoord() == beam_iter->crd) {
            game_.GetPlayer()->SetHealth(game_.GetPlayer()->GetHealth() - beam_iter->damage);
            beam_iter = bbeams.erase(beam_iter);
          } else {
            ++beam_iter;
          }
        } else {
          beam_iter = bbeams.erase(beam_iter);
          continue;
        }
        break;
      }
      case Units::Orientation::DOWN: {
        // Элемент, находящийся снизу
        Elements::IElement& down_elem = pf_ptr->GetField()[beam_iter->crd.first + 1][beam_iter->crd.second].GetElement();

        // Перемещение луча заблокировано, если он взаимодействует с непересекаемым объектом
        if (down_elem.GetIsPassable()) {
          beam_iter->crd = { beam_iter->crd.first + 1, beam_iter->crd.second };
          // Луч наносит урон игроку, если он попадает в него
          if (pf_ptr->GetPlayerCoord() == beam_iter->crd) {
            game_.GetPlayer()->SetHealth(game_.GetPlayer()->GetHealth() - beam_iter->damage);
            beam_iter = bbeams.erase(beam_iter);
          } else {
            ++beam_iter;
          }
        } else {
          beam_iter = bbeams.erase(beam_iter);
          continue;
        }
        break;
      }
      case Units::Orientation::LEFT: {
        // Элемент, находящийся слева
        Elements::IElement& left_elem = pf_ptr->GetField()[beam_iter->crd.first][beam_iter->crd.second - 1].GetElement();

        // Перемещение луча заблокировано, если он взаимодействует с непересекаемым объектом
        if (left_elem.GetIsPassable()) {
          beam_iter->crd = { beam_iter->crd.first, beam_iter->crd.second - 1 };
          // Луч наносит урон игроку, если он попадает в него
          if (pf_ptr->GetPlayerCoord() == beam_iter->crd) {
            game_.GetPlayer()->SetHealth(game_.GetPlayer()->GetHealth() - beam_iter->damage);
            beam_iter = bbeams.erase(beam_iter);
          } else {
            ++beam_iter;
          }
        } else {
          beam_iter = bbeams.erase(beam_iter);
          continue;
        }
        break;
      }
    }
  }

  // Обновляем расположение врагов
  for (size_t i = 0; i < enemies.size(); ++i) {
    if (enemies[i]->GetHealth() != 0) {
      switch (enemies[i]->GetOrient()) {
        case Units::Orientation::UP: {
          // Элемент, находящийся сверху
          Elements::IElement& up_elem = pf_ptr->GetField()[enemies_crd[i].first - 1][enemies_crd[i].second].GetElement();

          // Перемещение врага заблокировано, если он взаимодействует с непересекаемым объектом
          if (up_elem.GetIsPassable()) {
            pf_ptr->SetEnemyCoord(i, {enemies_crd[i].first - 1, enemies_crd[i].second});
          } else {
            enemies[i]->SetOrient(Units::Orientation::DOWN);
          }
          *enemies[i] + up_elem;
          break;
        }
        case Units::Orientation::RIGHT: {
          // Элемент, находящийся справа
          Elements::IElement& right_elem = pf_ptr->GetField()[enemies_crd[i].first][enemies_crd[i].second + 1].GetElement();

          // Перемещение врага заблокировано, если он взаимодействует с непересекаемым объектом
          if (right_elem.GetIsPassable()) {
            pf_ptr->SetEnemyCoord(i, {enemies_crd[i].first, enemies_crd[i].second + 1});
          } else {
            enemies[i]->SetOrient(Units::Orientation::LEFT);
          }
          *enemies[i] + right_elem;
          break;
        }
        case Units::Orientation::DOWN: {
          // Элемент, находящийся снизу
          Elements::IElement& down_elem = pf_ptr->GetField()[enemies_crd[i].first + 1][enemies_crd[i].second].GetElement();

          // Перемещение врага заблокировано, если он взаимодействует с непересекаемым объектом
          if (down_elem.GetIsPassable()) {
            pf_ptr->SetEnemyCoord(i, {enemies_crd[i].first + 1, enemies_crd[i].second});
          } else {
            enemies[i]->SetOrient(Units::Orientation::UP);
          }
          *enemies[i] + down_elem;
          break;
        }
        case Units::Orientation::LEFT: {
          // Элемент, находящийся слева
          Elements::IElement& left_elem = pf_ptr->GetField()[enemies_crd[i].first][enemies_crd[i].second - 1].GetElement();

          // Перемещение врага заблокировано, если он взаимодействует с непересекаемым объектом
          if (left_elem.GetIsPassable()) {
            pf_ptr->SetEnemyCoord(i, {enemies_crd[i].first, enemies_crd[i].second - 1});
          } else {
            enemies[i]->SetOrient(Units::Orientation::RIGHT);
          }
          *enemies[i] + left_elem;
          break;
        }
      }

      if (enemies[i]->GetAttackPltc() == Units::AttackPolitic::DISTANT) {
        static size_t counter = 0;
        ++counter;
        if (counter % 8 == 0) {
          switch(enemies[i]->GetOrient()) {
            // Здесь намерено указаны направления лучей, отличющиеся от направления движения врага
            case Units::Orientation::UP: {
              bbeams.push_back({Point2D(enemies_crd[i].first, enemies_crd[i].second + 1), Units::Orientation::RIGHT, enemies[i]->GetAttackPower()});
              break;
            }
            case Units::Orientation::RIGHT: {
              bbeams.push_back({Point2D(enemies_crd[i].first + 1, enemies_crd[i].second), Units::Orientation::DOWN, enemies[i]->GetAttackPower()});
              break;
            }
            case Units::Orientation::DOWN: {
              bbeams.push_back({Point2D(enemies_crd[i].first, enemies_crd[i].second - 1), Units::Orientation::LEFT, enemies[i]->GetAttackPower()});
              break;
            }
            case Units::Orientation::LEFT: {
              bbeams.push_back({Point2D(enemies_crd[i].first - 1, enemies_crd[i].second), Units::Orientation::UP, enemies[i]->GetAttackPower()});
              break;
            }
          }
          counter = 0;
        }
      }
      // Взаимодействие
      if (pf_ptr->GetEnemiesCoord()[i] == pf_ptr->GetPlayerCoord()) {
        *game_.GetPlayer() - *enemies[i];
      }
    } else { // enemies[i].GetHealth() == 0
      enemies.erase(enemies.begin() + i);
      pf_ptr->GetEnemiesCoord().erase(pf_ptr->GetEnemiesCoord().begin() + i);
      // Данный декремент нужен, чтобы не нарушать индексацию после удаления врага
      --i;
    }
  }

  // Смена хода
  game_.SetTurn(std::make_shared<Turn::PlayerTurn>(game_));

  // qDebug() << "Enemy's turn ended";
}
}
