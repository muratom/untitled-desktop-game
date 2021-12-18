#ifndef ICOMMAND_H
#define ICOMMAND_H

namespace Command {
class ICommand {
public:
  virtual ~ICommand() = default;
  virtual void Execute() const = 0;
};
}

#endif // ICOMMAND_H
