 #ifndef IEMITTER_H
#define IEMITTER_H

#include <ostream>

#include "ireceiver.h"

namespace Observer {
class IReceiver;
class IEmitter {
public:
  virtual ~IEmitter() = default;
  virtual void Connect(IReceiver* rec) = 0;
  virtual void Disconnect(IReceiver* rec) = 0;
  virtual void NotifyListeners() = 0;

  // https://stackoverflow.com/questions/2059058/c-abstract-class-operator-overloading-and-interface-enforcement-question
  friend std::ostream& operator<<(std::ostream& os, const IEmitter& rec) {
    rec.Print(os);
    return os;
  }

private:
  virtual void Print(std::ostream& os) const = 0;
};
}

#endif // IEMITTER_H
