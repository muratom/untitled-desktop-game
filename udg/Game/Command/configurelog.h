#ifndef CONFIGURELOG_H
#define CONFIGURELOG_H

#include "icommand.h"
#include "Log/log.h"
#include "Log/consolelog.h"
#include "Log/filelog.h"
#include "Log/multiplelog.h"

namespace Command {
class ConfigureLog : public ICommand {
  using LogPtr = std::shared_ptr<Log::Log>;
public:
  explicit ConfigureLog(LogPtr& log, bool inFile, bool inConsole);
  void Execute() const override;

private:
  LogPtr& log_;
  bool inFile_;
  bool inConsole_;
};
}

#endif // CONFIGURELOG_H
