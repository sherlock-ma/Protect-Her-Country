#include "princess.h"
#include <QPoint>
#include <QDebug>

static const char *dir_set[]=
    {":/princess/image/princess/lstand1.png",
     ":/princess/image/princess/rstand1.png",
     ":/princess/image/princess/l_longattack1.png",
     ":/princess/image/princess/l_longattack2.png",
     ":/princess/image/princess/l_longattack3.png",
     ":/princess/image/princess/l_longattack4.png",
     ":/princess/image/princess/r_longattack1.png",
     ":/princess/image/princess/r_longattack2.png",
     ":/princess/image/princess/r_longattack3.png",
     ":/princess/image/princess/r_longattack4.png",
     ":/princess/image/princess/lmove1.png",
     ":/princess/image/princess/rmove1.png",
     ":/princess/image/princess/death1.png",
     ":/princess/image/princess/death2.png",
     ":/princess/image/princess/death3.png",
     ":/princess/image/princess/death4.png",
     ":/princess/image/princess/death5.png",
     ":/princess/image/princess/death6.png",
     ":/princess/image/princess/appear1.png",
     ":/princess/image/princess/appear2.png",
     ":/princess/image/princess/appear3.png",
     ":/princess/image/princess/appear4.png",
     ":/princess/image/princess/appear5.png",
     ":/princess/image/princess/appear5.png",
     ":/princess/image/princess/appear4.png",
     ":/princess/image/princess/appear3.png",
     ":/princess/image/princess/appear2.png",
     ":/princess/image/princess/appear1.png",

    };

static const QPoint rlocation=QPoint(42,67);
static const QPoint rheart=QPoint(42,44);
static const QPoint l_riceball=QPoint(-23,-45);
static const QPoint r_riceball=QPoint(23,-45);
static const int hurtable_range=30;
static const int attack_range=200;
static const int MAXHP=400;
static const int img_num=28;
static const int speed=10;
static const char* profile_dir = ":/princess/image/princess/profile.png";
//注意：每增加一次图片，对应在头文件Condition对应位置要写上状态
//并且更新img_num
//照片顺序最好符合逻辑

//以上定义了这么多的符号常量
//仅仅为了下面构造函数使用符号常量不适用裸露的数字，方便修改
//代码中尽量不出现裸露的数字是一个很好的习惯
//这样修改初始值的时候好修改，不用到下面繁杂的代码里面修改
//照片顺序最好先左后右，同一个运动状态的照片放一起
//照片名称最好和condition对应状态一致


Princess::Princess(const QPoint & obj_location):
    Live_player(obj_location,rlocation,rheart,img_num,dir_set,hurtable_range,attack_range,MAXHP,speed,obj_location),
    _condition(rstand1),profile(profile_dir),MP(MAXMP),
    k_HP(95/(double)MAXHP),k_MP(95/(double)MAXMP),deathSignal(false){}

void Princess::reset()
{
    setHP(MAXHP);
    deathSignal=false;
    _condition=rstand1;
}

bool Princess::isLeft()const
{
    bool c1=(_condition==lstand1);
    bool c2=_condition>=l_longattack1&&_condition<=l_longattack4;
    bool c3=_condition==lmove1;
    return c1||c2||c3;
}


void Princess::setObj_location(const QPoint &obj_location)
{
    Live_player::setObj_location(obj_location);
    Live_player::setDestination(obj_location);
}

void Princess::flashMove(const QPoint &des)
{
    nextDes=des;
    _condition=disappear1;
}

void Princess::turnFace(const QPoint &pos)
{
    if(pos.x()<getObj_locationX())
            react(Command::Lstand);
        else
            react(Command::Rstand);
}

void Princess::react(Command cmd)
{
    switch (cmd) {
    case Command::Lstand:
        if(!isStanding()) return;
        _condition=lstand1;
        break;
    case Command::Rstand:
        if(!isStanding()) return;
        _condition=rstand1;
        break;
    case Command::Longattack:
        if(!isStanding()) return;
        else if(isLeft())
            _condition=l_longattack1;
        else
            _condition=r_longattack1;
        break;
    default:
        break;
    }
}

void Princess::draw(QPainter &p)
{
    Abstract_obj::drawImage(p,_condition);  
    if(global_condition==Background::map1||
       global_condition==Background::map2||
       global_condition==Background::map3)
    {
        p.drawImage(QPoint(0,0),profile);
        p.setPen(Qt::NoPen);
        p.setBrush(Qt::red);
        p.drawRect(5,97,k_HP*getHP(),4);
        p.setBrush(Qt::blue);
        p.drawRect(5,108,k_MP*MP,4);
        p.setPen(Qt::SolidLine);
        p.setBrush(Qt::NoBrush);
    }

    //process death situation
    if(getHP()==0)
    {
        //already dead
        if(deathSignal) return;
        if(_condition==death6)
        {
            emit princessDeath();
            deathSignal=true;
        }
        else if(_condition>=death1&&_condition<death6)
            _condition=Condition(1+_condition);
        else _condition=death1;
        return;
    }

    //the princess is "flash moving"
    if(_condition>=disappear1&&_condition<=appear5)
    {
        if(_condition==disappear5)
        {
            setObj_location(nextDes);
        }
        if(_condition==appear5) _condition=rstand1;
        else
            _condition=Condition(1+_condition);
        return;
    }

    //emit the iceball as an attack
    if(_condition==l_longattack3)
        emit iceball(getObj_location()+l_riceball);
    else if(_condition==r_longattack3)
        emit iceball(getObj_location()+r_riceball);

    //the princess is attacking
    if(_condition>=l_longattack1&&_condition<l_longattack4)
        _condition=Condition(1+_condition);
    else if(_condition==l_longattack4)
        _condition=lstand1;
    else if(_condition>=r_longattack1&&_condition<r_longattack4)
        _condition=Condition(1+_condition);
    else if(_condition==r_longattack4)
        _condition=rstand1;
    else
        {

        int dx=getDx();
        int dy=getDy();
        if(dx==0&&dy==0)
        {
            //此时已到达终点
            if(isLeft())
                _condition=lstand1;
            else _condition=rstand1;
            return;
        }
        else if(dx>0)
        {
            //这里在中间再改一次状态是为了
            //一次移动没有做完，用户就又点击鼠标进行下一次移动
            //此时人脸的方向仍然是上一个move状态的方向
            _condition=rmove1;
            move();
        }
        else
        {
            _condition=lmove1;
            move();
        }
    }
}


