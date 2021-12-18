#include "log.h"

namespace Log {

Log::Log(const std::shared_ptr<LogImpl>& impl)
  : impl_(impl) {}

void Log::Update(Observer::IEmitter& em) {
  impl_->Update(em);
}

}
