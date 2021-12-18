#include "gamesaver.h"

namespace Game {
GameSaver::GameSaver(Game& game)
  : game_(game) {}

void GameSaver::Save() const {
  /*
    Содержимое файла с сохранением:
    1) Игровое поле (PlayingField): высота, ширина, целевые очки, координаты входа, выхода, карта
    2) Игрок (Player): координаты игрока, здоровье, очки, атака, коэффициент защиты, боевое состояние, ориентация
    3) Враги и лучи бластера (Enemies and BlasterBeams): количество врагов, координаты, здоровье, сила атаки, боевое состояние, ориентация, тип врага (MovePltc, AttackPltc)
       количество лучей, координаты (x,y), ориентация и урон
    4) Игра (Game): состояние игры
  */

  // Если совершена попытка сохранения еще не инициализированной игры, то выбрасывается исключение
  if (!game_.GetIsInitialized())
    throw SaveException("You try to save the uninitialized game");

  // Если совершена попытка сохранения завершенной игры, то выбрасывается исключение
  if (!game_.GetInGame()) {
    throw SaveException("You try to save the completed game");
  }


  std::time_t now = std::time(0);
  std::string date = std::ctime(&now);
  date.pop_back();
  std::replace_if(date.begin(), date.end(), isspace, '_');
  std::ofstream save_file("/home/mur/Programing/QtProjects/UntitledDesktopGame/udg/SaveLevels/" + date + ".txt");

  try {
    // В начало файла добавляется строка для упрощения проверки корректности при загрузке уровня
    save_file << "Answer_to_the_Ultimate_Question_of_Life,_the_Universe,_and_Everything_is_42\n";

    Game::Memento gm = game_.SaveState();

    int16_t w = gm.GetPfState()->GetWidth();

    // ИГРОВОЕ ПОЛЕ
    auto pf_m = gm.GetPfState();

    // Высота и ширина
    save_file << pf_m->GetHeight() << "\n";
    save_file << w << "\n";

    // Целевые очки
    save_file << gm.GetTP() << '\n';

    // Координаты входа и выхода
    auto entr = pf_m->GetEntrance();
    save_file << entr.first << ' ' << entr.second << '\n';

    auto exit = pf_m->GetExit();
    save_file << exit.first << ' ' << exit.second << '\n';

    // Карта
    auto e = game_.GetPF()->End();
    int16_t counter = 1;
    for (auto i = game_.GetPF()->Begin(); i != e; ++i) {
      if (typeid(i->GetElement()) == typeid(Elements::Floor)) {
        save_file << 'f';
      } else if (typeid(i->GetElement()) == typeid(Elements::Wall)) {
        save_file << 'w';
      } else if (typeid(i->GetElement()) == typeid(Elements::Coin)) {
        // Если монета не использована, то отмечаем её на карте
        if (!static_cast<Elements::Coin&>(i->GetElement()).IsUsed())
          save_file << 'c';
        else
          save_file << 'f';
      } else if (typeid(i->GetElement()) == typeid(Elements::Lava)) {
        save_file << 'l';
      } else if (typeid(i->GetElement()) == typeid(Elements::Health)) {
        // Если здоровье не использовано, то отмечаем его на карте
        if (!static_cast<Elements::Health&>(i->GetElement()).IsUsed())
          save_file << 'h';
        else
          save_file << 'f';
      }
      if (counter == w) {
        save_file << '\n';
        counter = 0;
      }
      ++counter;
    }

    // ИГРОК
    auto plr_m = gm.GetPlrState();

    // Координаты игрока
    auto plr_crd = pf_m->GetPlrCrd();
    save_file << plr_crd.first << ' ' << plr_crd.second << '\n';

    // Здоровье, очки, атака, коэффициент защиты, боевое состояние и ориентация (без переноса строки)
    save_file << plr_m->GetHealth() << ' ' << plr_m->GetPoints() << ' ' << plr_m->GetAttackPower() << ' ' <<
                 plr_m->GetDefenseCoeff() << ' ' << plr_m->GetFightState() << ' ' <<  plr_m->GetOrientation() << '\n';
  //  save_file << plr_m->GetPoints() << '\n';
  //  save_file << plr_m->GetAttackPower() << '\n';
  //  save_file << plr_m->GetDefenseCoeff() << '\n';
  //  save_file << plr_m->GetFightState() << '\n';
  //  save_file << plr_m->GetOrientation() << '\n';

    // ВРАГИ И ЛУЧИ БЛАСТЕРА
    auto& enemies_m = gm.GetEnemies();
    auto& enemies_crd_m = gm.GetPfState()->GetEnemiesCrd();
    auto& bbeams_m = gm.GetBlasterBeams();

    // Количество врагов
    save_file << enemies_m.size() << '\n';

    // Координаты, здоровье, сила атаки, боевое состояние, ориентация, тип врагов
    for (size_t i = 0; i < enemies_m.size(); ++i) {
      save_file << enemies_crd_m[i].first << ' ' << enemies_crd_m[i].second << ' ' <<
                   enemies_m[i]->GetHealth() << ' ' << enemies_m[i]->GetAttackPower() << ' ' <<
                   enemies_m[i]->GetFightState() << ' ' << enemies_m[i]->GetOrient() << ' ' <<
                   enemies_m[i]->GetMovePltc() << ' ' << enemies_m[i]->GetAttackPltc() << '\n';
    }

    // Количество лучей
    save_file << bbeams_m.size() << '\n';

    // Координаты, ориентация и урон
    for (auto& bb : bbeams_m) {
      save_file << bb.crd.first << ' ' << bb.crd.second << ' ' << bb.orient << ' ' << bb.damage << '\n';
    }

    // ИГРА

    // Состояние игры
    save_file << gm.GetInGame() << '\n';

//    // Чей ход
//    if (typeid (*gm.GetTurn()) == typeid (Turn::PlayerTurn)) {
//      save_file << "PlayerTurn\n";
//    } else {
//      save_file << "EnemyTurn\n";
//    }

    // Тип лога
//    if (gm.GetLog()) {
//      if (typeid (*gm.GetLog()) == typeid (Log::FileLog)) {
//        save_file << "FileLog\n";
//      } else if (typeid (*gm.GetLog()) == typeid (Log::ConsoleLog)) {
//        save_file << "ConsoleLog\n";
//      } else {
//        save_file << "MultipleLog\n";
//      }
//    }

    save_file.close();

  }  catch (...) {
    save_file.close();
    std::remove(std::string("/home/mur/Programing/QtProjects/UntitledDesktopGame/udg/SaveLevels/" + date).c_str());
  }
}
}

