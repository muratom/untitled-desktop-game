#ifndef PLAYINGFIELD_H
#define PLAYINGFIELD_H

#include <memory>
#include <string>
#include <vector>
#include <list>

#include "Field/cell.h"
#include "Elements/FactoryMethod/Products/ielement.h"
#include "Log/Observer/iemitter.h"

namespace Field {
using FieldPtr = std::shared_ptr<std::shared_ptr<Cell[]>[]>;
using Point2D = std::pair<int16_t, int16_t>;
//using CellPtr = std::weak_ptr<Cell>;

class BadFieldException : public std::exception {
public:
  BadFieldException(std::string info = "")
    : info_(info) {}
  const char* what() const noexcept { return info_.c_str(); }
private:
  std::string info_;
};

// Инварианты:
// 1) height_ > 0 && width_ > 0
// 2) Для всех координат: x > 0 && y > 0
// 3) field == nullptr тогда и только тогда, когда поле очищено с помощью Clear()
class PlayingField : public Observer::IEmitter {
public:
  PlayingField(const PlayingField&) = delete;
  PlayingField& operator=(const PlayingField&) = delete;
  ~PlayingField() = default;
  // https://stackoverflow.com/questions/23771194/why-should-i-delete-move-constructor-and-move-assignment-operator-in-a-singleton
  // C++11 12.8/9

  static PlayingField& GetInstance();

  void CustomizeField(int16_t h, int16_t w, const FieldPtr& field,
                      const Point2D& plr_crd, const std::vector<Point2D>& enemies_crd,
                      const Point2D& entrance_crd, const Point2D& exit_crd);

  void Clear();

  int16_t GetHeight() const { return height_; }
  int16_t GetWidth() const { return width_; }

  Point2D& GetPlayerCoord() { return player_coord_; }
  void SetPlayerCoord(Point2D crd);

  std::vector<Point2D>& GetEnemiesCoord() { return enemies_coord_; }
  void SetEnemyCoord(int16_t enemy_index, const Point2D& crd);

  const Point2D& GetExitCoord() const { return exit_; }
  const FieldPtr& GetField() const { return field_; }


  // Паттерн "Итератор"
  class Iterator
      : public ::std::iterator<::std::bidirectional_iterator_tag, Cell> {

  public:
    Iterator() = default;
    Iterator(const Iterator& other);
    Iterator& operator=(const Iterator& other);
    Iterator(const PlayingField& pf, const Point2D& coord = { 0, 0 });
    ~Iterator() {};

    Iterator& operator++(); // prefix
    Iterator operator++(int); // postfix

    Iterator& operator--(); // prefix
    Iterator operator--(int); // postfix

    bool operator==(const Iterator& other) const;
    bool operator!=(const Iterator& other) const;

    Cell& operator*() const;
    Cell* operator->() const; // a->x ==> *(a->).x

    const FieldPtr& GetData() const { return pf_ptr_->field_; }
    const Point2D& GetCurrentCoord() const { return current_coord_; }

  private:
    const PlayingField* pf_ptr_;
    Point2D current_coord_ = { 0, 0 };
  };

  Iterator Begin() const { return Iterator(*this); }
  Iterator End() const { return Iterator(*this, { height_, 0 }); }

  // Паттерн "Наблюдатель"
  void Connect(Observer::IReceiver* rec) override;
  void Disconnect(Observer::IReceiver* rec) override;
  void NotifyListeners() override;

  // Паттерн "Снимок"
  class Memento {
  public:
    Memento(const PlayingField& pf);

    const FieldPtr& GetField() { return fld_; }
    const Point2D& GetPlrCrd() { return plr_crd_; }
    const std::vector<Point2D>& GetEnemiesCrd() { return enemies_crd_; }
    const Point2D& GetEntrance() { return entrance_; }
    const Point2D& GetExit() { return exit_; }
    int16_t GetHeight() { return height_; }
    int16_t GetWidth() { return width_; }
    const std::list<Observer::IReceiver*>& GetReceivers() { return receiver_list_; }

  private:
    const FieldPtr& fld_;
    const Point2D& plr_crd_;
    const std::vector<Point2D>& enemies_crd_;
    const Point2D& entrance_;
    const Point2D& exit_;
    int16_t height_;
    int16_t width_;
    const std::list<Observer::IReceiver*>& receiver_list_;
  };

  Memento SaveState();
  void RestoreState(Memento& m);

private:
  PlayingField() = default;

  void Print(std::ostream& os) const override;

  FieldPtr field_ = nullptr;

  Point2D player_coord_ = {0, 0};
  // В классе Game имеется list врагов, их координты находятся по соотвествующему индексу
  std::vector<Point2D> enemies_coord_;

  Point2D entrance_ = {0, 0};
  Point2D exit_ = {0, 0};
  int16_t height_ = 0;
  int16_t width_ = 0;

  std::list<Observer::IReceiver*> receiver_list_;
};
}

#endif // PLAYINGFIELD_H
