#ifndef FILELOG_H
#define FILELOG_H

#include <string>

#include "logimpl.h"

namespace Log {
// Инвариант:
// Файл закрывается, когда уничтожается объект класса
class FileLog : public LogImpl {
public:
  FileLog(const std::string& file_name);
  ~FileLog();
  void Update(Observer::IEmitter& em) override;
private:
  std::ofstream* ofs_;
};
}

#endif // FILELOG_H
