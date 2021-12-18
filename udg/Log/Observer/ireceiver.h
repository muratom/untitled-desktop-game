#ifndef IRECEIVER_H
#define IRECEIVER_H

#include "Log/Observer/iemitter.h"

namespace Observer {
class IEmitter;
class IReceiver {
public:
  virtual ~IReceiver() = default;

  virtual void Update(IEmitter& em) = 0;
};
}


#endif // IRECEIVER_H
