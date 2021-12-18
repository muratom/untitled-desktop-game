#ifndef LOGIMPL_H
#define LOGIMPL_H

#include <memory>
#include <ostream>
#include <fstream>

#include "Observer/ireceiver.h"

namespace Log {
class LogImpl : public Observer::IReceiver {
public:
  virtual ~LogImpl() = default;
  virtual void Update(Observer::IEmitter& em) = 0;
};
}


#endif // LOGIMPL_H
