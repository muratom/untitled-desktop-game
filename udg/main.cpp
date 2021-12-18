#include "UDG/untitleddesktopgame.h"

#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Gui::UntitledDesktopGame udg;
  udg.show();
  return a.exec();
}
