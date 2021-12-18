#include "consolelog.h"

void Log::ConsoleLog::Update(Observer::IEmitter& em) {
  std::cerr << em; // std::cerr - для вывода в real-time
}
