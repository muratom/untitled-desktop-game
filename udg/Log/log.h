#ifndef LOG_H
#define LOG_H

#include <memory>
#include <ostream>

#include "Observer/ireceiver.h"
#include "logimpl.h"

namespace Log {
class Log : public Observer::IReceiver {
public:
  Log(const std::shared_ptr<LogImpl>& impl);
  ~Log() = default;
  void Update(Observer::IEmitter& em);

private:
  std::shared_ptr<LogImpl> impl_ = nullptr;
};
}


#endif // LOG_H
