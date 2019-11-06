#ifndef PICTURE_H
#define PICTURE_H
//表示原图以及当前状态的类
#include <QObject>
#include<QList>
#include<shape.h>
#include<QImage>
#include<QDateTime>
#include<QPixmap>

class QPixmap;
class picture : public QObject
{
    Q_OBJECT
public:
    bool** pic;
    QList<shape> state;
    int area;

    QVector<QList<point>> STDNodes; //存储所有姿态的图形用于加速拼图

    //加入深度上限所用
    QList<shape> preState;
    bool preOccupy[7];


public:
    explicit picture(const QString& fileName,QObject *parent = nullptr);
    explicit picture(const QImage* origin,QObject *parent = nullptr);

    ~picture();


    //输入坐标判断是否是黑色块
    int black(int x,int y);

    //扫描得到一个可以开始搜索的点(Flood fill??)
    void scan(int& x,int& y);

    //判断某个元件能否插入
    bool fit(shape& insert);

    //删除最近一步决策,返回删除的元件类型,失败返回-1
    int cut();

    //洪水填充
    bool floodfill(int x,int y);

    //搜索函数
    bool findSoluntion(int lunci);

    //判断改点是否可拼
    bool insertAble(int x,int y);

    //打印当前状态到bmp图
    void printState();

    //生成所有姿态的图形
    void generateShapes();

    //根据形状的类型找到它在STDNodes中的秩
    int getRankFromShape(const shape& insert);



signals:

    void ChangeImage(const QPixmap newPixmap);


public slots:
};

#endif // PICTURE_H
