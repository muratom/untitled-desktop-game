QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT

# Чтобы программа запускалась через исполняемый файл
QMAKE_LFLAGS += -no-pie

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#SOURCES += \
#    Elements/FactoryMethod/Creators/coincreator.cpp \
#    Elements/FactoryMethod/Creators/floorcreator.cpp \
#    Elements/FactoryMethod/Creators/healthcreator.cpp \
#    Elements/FactoryMethod/Creators/lavacreator.cpp \
#    Elements/FactoryMethod/Creators/wallcreator.cpp \
#    Elements/FactoryMethod/Products/coin.cpp \
#    Elements/FactoryMethod/Products/floor.cpp \
#    Elements/FactoryMethod/Products/health.cpp \
#    Elements/FactoryMethod/Products/lava.cpp \
#    Elements/FactoryMethod/Products/wall.cpp \
#    Elements/Strategy/coinstrategy.cpp \
#    Elements/Strategy/healthstrategy.cpp \
#    Elements/Strategy/lavastrategy.cpp \
#    Field/cell.cpp \
#    Field/playingfield.cpp \
#    Game/Command/configurelog.cpp \
#    Game/Command/exitgame.cpp \
#    Game/Command/move.cpp \
#    Game/Command/newgame.cpp \
#    Game/enemyturn.cpp \
#    Game/game.cpp \
#    Game/gameloader.cpp \
#    Game/gamesaver.cpp \
#    Game/playerturn.cpp \
#    Log/consolelog.cpp \
#    Log/filelog.cpp \
#    Log/log.cpp \
#    Log/multiplelog.cpp \
#    UDG/fieldwidget.cpp \
#    UDG/untitleddesktopgame.cpp \
#    Units/enemy.cpp \
#    Units/ienemy.cpp \
#    Units/player.cpp \
#    main.cpp \

#HEADERS += \
#    Elements/FactoryMethod/Creators/coincreator.h \
#    Elements/FactoryMethod/Creators/creator.h \
#    Elements/FactoryMethod/Creators/floorcreator.h \
#    Elements/FactoryMethod/Creators/healthcreator.h \
#    Elements/FactoryMethod/Creators/lavacreator.h \
#    Elements/FactoryMethod/Creators/wallcreator.h \
#    Elements/FactoryMethod/Products/coin.h \
#    Elements/FactoryMethod/Products/floor.h \
#    Elements/FactoryMethod/Products/health.h \
#    Elements/FactoryMethod/Products/ielement.h \
#    Elements/FactoryMethod/Products/lava.h \
#    Elements/FactoryMethod/Products/wall.h \
#    Elements/Strategy/coinstrategy.h \
#    Elements/Strategy/healthstrategy.h \
#    Elements/Strategy/iinteractionstrategy.h \
#    Elements/Strategy/lavastrategy.h \
#    Elements/iusableelement.h \
#    Field/cell.h \
#    Field/playingfield.h \
#    Game/Command/configurelog.h \
#    Game/Command/exitgame.h \
#    Game/Command/icommand.h \
#    Game/Command/move.h \
#    Game/Command/newgame.h \
#    Game/enemyturn.h \
#    Game/game.h \
#    Game/gameloader.h \
#    Game/gamesaver.h \
#    Game/iturn.h \
#    Game/playerturn.h \
#    Log/Observer/iemitter.h \
#    Log/Observer/ireceiver.h \
#    Log/consolelog.h \
#    Log/filelog.h \
#    Log/log.h \
#    Log/logimpl.h \
#    Log/multiplelog.h \
#    UDG/fieldwidget.h \
#    UDG/untitleddesktopgame.h \
#    Units/enemy.h \
#    Units/ienemy.h \
#    Units/iunit.h \
#    Units/player.h

include(udg.pri)
SOURCES += main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Images/coin40x40.png \
    Images/exit40x40.png \
    Images/floor40x40.png \
    Images/health40x40.png \
    Images/lava40x40.png \
    Images/sonic40x40.png \
    Images/wall40x40.png \
    Levels/level1.txt \
    Levels/level2.txt \
    Levels/level_rules.txt \
    Levels/test_level.txt \
    Log/temp \
    SaveLevels/Tue Dec 15 01:14:16 2020 \
    SaveLevels/Tue Dec 15 01:14:16 2020 \
    SaveLevels/Tue Dec 15 11:34:07 2020 \
    SaveLevels/level_example.txt \
    SaveLevels/save_example_2.txt \
    UML-diagrams/lb1.qmodel \
    UML-diagrams/lb2_factory_method.qmodel \
    UML-diagrams/lb2_player.qmodel \
    UML-diagrams/lb2_strategy.qmodel \
    UML-diagrams/lb3.qmodel \
    UML-diagrams/lb4_facade_and_command.qmodel \
    UML-diagrams/lb5_state.qmodel \
    UML-diagrams/lb6_momento.qmodel \
    lb1.qmodel \
    lb2_factory_method.qmodel \
    lb2_strategy.qmodel \
    udg.pri

RESOURCES += \
    Images.qrc \
    Levels.qrc
