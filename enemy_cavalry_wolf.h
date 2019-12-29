#ifndef Enemy_cavalry_wolf_H
#define Enemy_cavalry_wolf_H
#include "constant.h"
#include "live_player.h"
#include <QPoint>

class Enemy_cavalry_wolf:public Live_player

{
    Q_OBJECT
signals:
    void death(void);
    void lose(void);

public:
    Enemy_cavalry_wolf(int route);
    void lrun();
    void rrun();
    void dying();
    void draw(QPainter &p);
    Type getType()const {return Type::enemy;}
    bool hurtedBy(Thrown_obj &obj);
    void process(Live_player & obj){}//去掉了const

    ~Enemy_cavalry_wolf(){}

private:
    enum Condition{lrun1,lrun2,lrun3,lrun4,lrun5,lrun6,lrun7,lrun8,
                   rrun1,rrun2,rrun3,rrun4,rrun5,rrun6,rrun7,rrun8,
                   lstand,rstand,
                  dying1,dying2,dying3,dying4,dying5,dying6,dying7,dying8,
                  dying9,dying10,dying11,dying12,dying13,dying14,dying15,dying16};
    Condition _condition;
    int point_destination;//标记下一个要去的点是第几个。针对destination数组中的列数，0-3
    int _route;
};

#endif // Enemy_cavalry_wolf_H
