#include "mpolygon.h"

MPolygon::MPolygon(QPolygon &Polygon, QWidget *parent)
    :QGraphicsPolygonItem(Polygon)
{
    QPen p = QPen();
    p.setWidth(0);
    p.setColor(QColor(0, 160, 230));

    //TriItem.setFillRule(Qt::WindingFill);
    setPen(p);
    setBrush(QBrush(QColor(0, 0, 0)));

    // 可选择、可移动
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemSendsGeometryChanges);

    setTransformOriginPoint(Polygon[0]);
}

void MPolygon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        // 选中 item
        setSelected(true);


        qDebug() << "Custom item left clicked.";
        QGraphicsItem::mousePressEvent(event);
        event->accept();
     }
     else if (event->button() == Qt::RightButton)
    {
        qDebug() << "Custom item right clicked.";
        //event->ignore();
        this->setRotation(45+this->rotation());


    }

}
float TILE_SIZE = 100;

//QVariant MPolygon::itemChange(GraphicsItemChange change, const QVariant &value)
//  {

//      qDebug() << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
//      if (change == ItemPositionChange && scene()) {
//          // value is the new position.
//          QPointF newPos = value.toPointF();
//          QRectF rect = scene()->sceneRect();
//          if (!rect.contains(newPos)) {
//              // Keep the item inside the scene rect.
//              newPos.setX(qMin(rect.right() , qMax(newPos.x(), rect.left())));
//              newPos.setY(qMin(rect.bottom() , qMax(newPos.y(), rect.top())));
//              return newPos;
//          }
//      }
//      return QGraphicsItem::itemChange(change, value);
//  }

void MPolygon::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    scene()->collidingItems(this).isEmpty() ?
                    setBrush(QBrush(QColor(0,0,0))) :
                    setBrush(QBrush(QColor(255,0,0)));
    //qDebug() << "Custom item moved.";
    QGraphicsItem::mouseMoveEvent(event);

    //qDebug() << "moved" << pos();
    int ItemNum = scene()->items().count();

//    qDebug() << ItemNum;
//    for(int i = 0;i < ItemNum;i++)
//    {
//        qDebug() << collidesWithItem(scene()->items()[i]);
//        if( collidesWithItem(scene()->items()[i]) )
//        {
//            setBrush(QBrush(QColor(255, 0, 0)));
//            break;
//        }
//    }
}

void MPolygon::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

//    scene()->collidingItems(this).isEmpty() ?
//                    setBrush(QBrush(QColor(0,0,0))) :
//                    setBrush(QBrush(QColor(255,0,0)));
//    if(!scene()->collidingItems(this).isEmpty())
//        setBrush(QBrush(QColor(255,215,0)));
   QGraphicsItem::mouseReleaseEvent(event);
    setSelected(false);

//    int ItemNum = scene()->items().count();

//    qDebug() << ItemNum;
//    for(int i = 0;i < ItemNum;i++)
//    {
//        qDebug() << collidesWithItem(scene()->items()[i]);
//        if( collidesWithItem(scene()->items()[i]) )
//        {
//            qDebug() << "hhhhhhhhhhhhhhhhhhhhhhhhhhhh";
//            this->setBrush(QBrush(QColor(255, 0, 0)));
//            break;
//        }
//    }

}


//float FOOD_RADIUS = 20;

QRectF MPolygon::boundingRect() const
{
//    return QRectF(0, 0,
//                  TILE_SIZE * 2, TILE_SIZE * 2 );

    return this->polygon().boundingRect();
}

void MPolygon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //painter->save();

    //painter->setRenderHint(QPainter::Antialiasing);
    //painter->fillPath(shape(), Qt::black);
    scene()->collidingItems(this).isEmpty() ?
//                painter->fillPath(shape(), Qt::black):
//                painter->fillPath(shape(), Qt::red);
                setPen( QPen(QColor(0,0,0)) ):
                setPen( QPen(QColor(255,0,0)) );
//                       setBrush(QBrush(QColor(0,120,110))):
//                       setBrush(QBrush(QColor(0,0,0))) ;

    QGraphicsPolygonItem::paint(painter, option, widget);

    //painter->restore();
}

QPainterPath MPolygon::shape() const
{
    QPainterPath p;
       // p.addEllipse(QPointF(TILE_SIZE / 2, TILE_SIZE / 2), FOOD_RADIUS, FOOD_RADIUS);
    p.addPolygon(this->polygon());
    return p;
}
