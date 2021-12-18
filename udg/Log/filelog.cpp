#include "filelog.h"

namespace Log {
FileLog::FileLog(const std::string& file_name)
  : ofs_(new std::ofstream(file_name)) {}

FileLog::~FileLog() {
  if (ofs_->is_open())
    ofs_->close();
}

void FileLog::Update(Observer::IEmitter& em) {
  *ofs_ << em;
}
}
