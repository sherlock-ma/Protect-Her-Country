#ifndef LIVE_PLAYER_H
#define LIVE_PLAYER_H

#include "constant.h"
#include "thrown_obj.h"

class Thrown_obj;

class Live_player:public Abstract_obj
{
    //a macro to use signal & slot functionality in Qt
    Q_OBJECT
private:
    int _HP;
    int _MAXHP;
    //within this range, Live_player gets hurt
    int _hurtable_range;
    //within this range, Live_player can attack others
    int _attack_range;
    //the total distance between the current location
    //and the destination location in x direction and y direction
    int _dx;
    int _dy;
    //the distance this player can move within each frame
    int _speed;
    //the last picture being drawn
    int last_index;
    //TODO:the meaning of this two value?
    bool _pause;
    bool _frozen;
    static const int _HPBar_height=5;
    //a map between actual max HP value and length of HP bar
    constexpr static const double _HPBar_elastic=0.25;
    int _HPBar_length;
    QPoint _heart;
    QPoint _obj_rheart;//心相对于_obj_location的坐标
    QPoint _destination;
    //set dx, dy
    void setdpoint();
public:
    Live_player(const QPoint & obj_location,const QPoint & rlocation,const QPoint & rheart,const int img_num,const char **dir_set,
           const int hurtable_range,const int attack_range,const int MAXHP,int speed=0,const QPoint & des=QPoint());
    const QPoint & getHeart(void)const {return _heart;}
    int getHP(void)const {return _HP;}
    int getMAXHP(void)const {return _MAXHP;}
    int getDx(void)const {return _dx;}
    int getDy(void) {return _dy;}
    int getSpeed(void) {return _speed;}
    bool isPausing(void)const {return _pause;}
    int getHurtable_range(void)const {return _hurtable_range;}
    int getAttack_range(void)const {return _attack_range;}
    int getDestinationX(void)const {return _destination.x();}
    int getDestinationY(void)const {return _destination.y();}
    int HeartDistanceWith(const Abstract_obj & obj)const;
    bool inMyLeft(const Live_player & obj)const;
    bool inMyRight(const Live_player & obj)const {return !inMyLeft(obj);}
    bool inAttack_range(const Live_player & obj)const;
    virtual void setObj_location(const QPoint & obj_location);
    virtual void setDestination(const QPoint & des);
    //test if the Thrown_obj can hurt this Live_player
    bool inHurtableRange(const Thrown_obj &obj)const;
    virtual void draw(QPainter &p)=0;
    virtual void process(Live_player &obj)=0;
    virtual Type getType()const=0;
    virtual ~Live_player(){}
protected:
    void setMAXHP(int MAXHP) {_MAXHP=MAXHP;}
    void setHurtable_range(int hurtable_range){_hurtable_range=hurtable_range;}
    void setAttack_range(int attack_range){_attack_range=attack_range;}
    void setHP(int HP) {_HP=HP;if(_HP>_MAXHP) _HP=_MAXHP;}
    void setSpeed(int speed) {_speed=speed;}
    void deleteIt(){if(_pause||_frozen) return; Abstract_obj::deleteIt();}
    virtual void drawImage(QPainter &p,int index);
    virtual void move();
public slots:
    void reduceHP(int amount);
    void setPause(bool pause){_pause=pause;}
    void setFrozen(bool newFrozen){_frozen=newFrozen;}
};


/*class pLive_player
{
private:
    Live_player * _p;
public:
    pLive_player(Live_player * p):_p(p){}
    pLive_player(const pLive_player & obj):_p(new Live_player(*obj.use())){}
    const pLive_player & operator =(const pLive_player & obj)
    {
        _p=new Live_player(*obj.use());
        return *this;
    }
    Live_player * use(void)const {return _p;}
    ~pLive_player(){delete _p;}
};
*/
#endif // LIVE_PLAYER_H
