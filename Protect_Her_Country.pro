QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    abstract_obj.cpp \
    arrow.cpp \
    bullet.cpp \
    button.cpp \
    constant.cpp \
    enemy_boss_a.cpp \
    enemy_boss_b.cpp \
    enemy_cavalry_wolf.cpp \
    enemy_firecow.cpp \
    enemy_firemonster.cpp \
    enemy_firewizard.cpp \
    enemy_firewolf.cpp \
    enemy_greenmonster.cpp \
    enemy_monster.cpp \
    enemy_pigsoldier.cpp \
    enemy_spider.cpp \
    enemy_wolf.cpp \
    enemy_woodmonster.cpp \
    fireball.cpp \
    fireball2.cpp \
    fireball3.cpp \
    greenstone.cpp \
    guard_archer.cpp \
    iceball.cpp \
    icecone.cpp \
    icefrozen.cpp \
    lightning.cpp \
    live_player.cpp \
    main.cpp \
    missile.cpp \
    mymissile.cpp \
    orangeball.cpp \
    princess.cpp \
    scene_bag.cpp \
    scene_battle.cpp \
    scene_home.cpp \
    scene_startup.cpp \
    scene_transition.cpp \
    shooter.cpp \
    stable_obj.cpp \
    thrown_obj.cpp \
    window.cpp

HEADERS += \
    abstract_obj.h \
    arrow.h \
    bullet.h \
    button.h \
    constant.h \
    enemy_boss_a.h \
    enemy_boss_b.h \
    enemy_cavalry_wolf.h \
    enemy_firecow.h \
    enemy_firemonster.h \
    enemy_firewizard.h \
    enemy_firewolf.h \
    enemy_greenmonster.h \
    enemy_monster.h \
    enemy_pigsoldier.h \
    enemy_spider.h \
    enemy_wolf.h \
    enemy_woodmonster.h \
    fireball.h \
    fireball2.h \
    fireball3.h \
    greenstone.h \
    guard_archer.h \
    iceball.h \
    icecone.h \
    icefrozen.h \
    lightning.h \
    live_player.h \
    missile.h \
    mymissile.h \
    orangeball.h \
    princess.h \
    scene_bag.h \
    scene_battle.h \
    scene_home.h \
    scene_startup.h \
    scene_transition.h \
    shooter.h \
    stable_obj.h \
    thrown_obj.h \
    window.h

FORMS += \
    window.ui

CONFIG += \
    resources_big

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
