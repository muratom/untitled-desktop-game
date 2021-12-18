#include "multiplelog.h"

namespace Log {
MultipleLog::MultipleLog(const std::string& file_name)
  : ofs_(new std::ofstream(file_name)) {}

MultipleLog::~MultipleLog() {
  if (ofs_->is_open())
    ofs_->close();
}

void MultipleLog::Update(Observer::IEmitter& em) {
  std::cerr << em;
  *ofs_ << em;
}

}
