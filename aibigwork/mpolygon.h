#ifndef MPOLYGON_H
#define MPOLYGON_H

#include <QWidget>
#include <QGraphicsScene>
#include<QGraphicsPolygonItem>
#include<QGraphicsSceneMouseEvent>
#include<QDebug>
#include<QPainter>

class MPolygon :public QObject, public QGraphicsPolygonItem
{
    Q_OBJECT
public:
    explicit MPolygon(QPolygon& Polygon,QWidget *parent = nullptr);

    // Shift+左键：进行选择  Alt：准备缩放
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    // Alt+拖拽：进行缩放  移动
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);


    //重写基本函数
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    QPainterPath shape() const;


    //QVariant itemChange(GraphicsItemChange change, const QVariant &value);
signals:

public slots:
};

#endif // MPOLYGON_H
