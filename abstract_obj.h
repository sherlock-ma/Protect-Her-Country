#ifndef ABSTRACT_OBJ_H
#define ABSTRACT_OBJ_H

#include <QObject>
#include <QImage>
#include <QPoint>
#include <QPainter>


//an abstract base class for all soldiers, enemies, thrownable objects(like balls, arrows, etc)
class Abstract_obj:public QObject
{
private:
    //the total number of images
    int _img_num;
    //if it is true, in window.cpp this object will be deleted next cycle
    bool _deletable;
    //the "ideal location" for this object
    //with respect to the upper left corner of the window as origin
    QPoint _obj_location;
    //the image location, i.e. the location of upper left corner of the image
    QPoint _img_location;
    //a pointer to an array of images (using new and delete to allocate according to _img_num)
    QImage *_pimg;
public:
    Abstract_obj(const QPoint & obj_location,const int img_num, const char *const*dir_set,const QPoint &rlocation=QPoint());
    const QPoint& getObj_location()const {return _obj_location;}
    int getObj_locationX(void)const {return _obj_location.x();}
    int getObj_locationY(void)const {return _obj_location.y();}
    const QPoint & getImg_location()const {return _img_location;}
    int getImgX()const {return _pimg[0].width();}
    int getImgY()const {return _pimg[0].height();}
    //return the distance with another Abstract_obj
    //using _obj_location to calculate
    int ObjDistanceWith(const Abstract_obj & obj)const;
    bool isDeletable(void)const {return _deletable;}
    virtual ~Abstract_obj(){delete []_pimg;}
protected:
    //draw the index-th image in the image array
    virtual void drawImage(QPainter &p,int index);    
    void setObj_location(const QPoint & obj_location);
    //actual deletion operation is conducted in main
    virtual void deleteIt(void) {_deletable=true;}
};


#endif // ABSTRACT_OBJ_H
