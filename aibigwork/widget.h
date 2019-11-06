#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QMouseEvent>
#include<QGraphicsScene>
#include"picture.h"


namespace Ui {
class Widget;
}

class picture;
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(picture & one,QWidget *parent = nullptr);
    ~Widget();



    void setAreaMovable(const QRect rt);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);




    friend picture;


public slots:

    //得到一张新图
    void GetNewImage(const QPixmap newPixmap);

    void on_toolButton_clicked();

private:
    Ui::Widget *ui;
    QGraphicsScene* scene;
    picture& thePicture;



    QRect m_areaMovable;//可移动窗口的区域，鼠标只有在该区域按下才能移动窗口
    bool m_bPressed;//鼠标按下标志（不分左右键）
    QPoint m_ptPress;//鼠标按下的初始位置
};

#endif // WIDGET_H
