#ifndef ITURN_H
#define ITURN_H


namespace Turn {
class ITurn {
public:
  virtual ~ITurn() = default;
  virtual void MakeMove() = 0;
};
}

#endif // ITURN_H
