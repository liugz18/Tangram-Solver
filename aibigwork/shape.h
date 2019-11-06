#ifndef SHAPE_H
#define SHAPE_H

#include <QObject>
#include<cmath>
#include<QDebug>
#include<QStack>

class point
{
public:
    int x;
    int y;

public:
    point(int xin = 0,int yin = 0);
};
//表示七巧板元件的类
extern int MiniLength;//小三角形横放的直角边长度
extern int OddLength;//小三竖放的斜边长度

//全图的长宽,面积
extern int Width;
extern int Height;
extern int Blacks;
extern int StartPoint;
extern bool Occupy[7];
extern int printNum;
extern bool ReverseOrder;


enum ShapeForm{BigTri1,BigTri2,Square,Parallel,MidTri,SmallTri1,SmallTri2};


class shape : public QObject
{
    Q_OBJECT

public:
    ShapeForm type;
    int pattern;
    int xcor;
    int ycor;


public:

    //构造函数，什么形状，以什么姿态，放在哪里
    explicit shape(ShapeForm s = BigTri1,int p=0,int x=0,int y=0,QObject *parent = nullptr);

    shape(const shape& other);

    shape& operator=(const shape& other);


    //打印当前图形
    void printShape();

    //给一个点判断是否在图形中
    bool isInside(int x,int y);

    //输出图形中所有的点
    QList<point> allNodes();





signals:

public slots:
};

#endif // SHAPE_H
