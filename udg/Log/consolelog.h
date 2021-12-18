#ifndef CONSOLELOG_H
#define CONSOLELOG_H

#include <iostream>

#include "logimpl.h"

namespace Log {
class ConsoleLog : public LogImpl {
public:
  ~ConsoleLog() = default;
  void Update(Observer::IEmitter& em) override;
};

}

#endif // CONSOLELOG_H
