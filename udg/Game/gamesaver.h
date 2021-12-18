#ifndef GAMESAVER_H
#define GAMESAVER_H

#include <exception>
#include <fstream>
#include <ctime>
#include <cstdio>

#include "game.h"

namespace Game {

class SaveException : public std::exception {
public:
  SaveException(std::string info)
    : info_(info) {}
  const char* what() const noexcept { return info_.c_str(); }
private:
  std::string info_;
};

// Инвариант:
// В критических ситуациях выбрасывается исключение и удаляется файл,
// в который велось сохранение, иначе игра полностью сохраняется
class GameSaver {
public:
  GameSaver(Game& game);
  void Save() const;
private:
  Game& game_;
};
}


#endif // GAMESAVER_H
