#ifndef MULTIPLELOG_H
#define MULTIPLELOG_H

#include <iostream>
#include <string>

#include "logimpl.h"

namespace Log {
// Инвариант:
// Файл закрывается, когда уничтожается объект класса
class MultipleLog : public LogImpl {
public:
  MultipleLog(const std::string& file_name);
  ~MultipleLog();
  void Update(Observer::IEmitter& em) override;
private:
  std::ofstream* ofs_;
};
}


#endif // MULTIPLELOG_H
