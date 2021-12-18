#include "configurelog.h"

namespace Command {

ConfigureLog::ConfigureLog(ConfigureLog::LogPtr& log, bool inFile, bool inConsole)
  : log_(log), inFile_(inFile), inConsole_(inConsole) {}

void ConfigureLog::Execute() const {
  if (inFile_ && inConsole_)
    log_ = std::make_shared<Log::Log>(std::make_shared<Log::MultipleLog>("./log.txt"));
  else if (inFile_)
    log_ = std::make_shared<Log::Log>(std::make_shared<Log::FileLog>("./log.txt"));
  else if (inConsole_)
    log_ = std::make_shared<Log::Log>(std::make_shared<Log::ConsoleLog>());
  else
    log_ = nullptr;
}
}
