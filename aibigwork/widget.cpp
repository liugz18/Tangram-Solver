#include "Widget.h"
#include "ui_Widget.h"

Widget::Widget(picture &one, QWidget *parent) :
    thePicture(one),QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint| Qt::Dialog);
    setWindowOpacity(1);

    connect(&one,&picture::ChangeImage,this,&Widget::GetNewImage);



    scene = new QGraphicsScene;

    QPixmap* image = new QPixmap("/Users/tnoy/Desktop/人智/pic_09_28/2.bmp");

    scene->addPixmap(*image);


    ui->graphicsView->setScene(scene);
    ui->graphicsView->resize(image->width() + 10, image->height() + 10);
    setFixedSize(image->width() + 100,image->height() + 100);
    //ui->graphicsView->show();

    setMouseTracking(true);
    m_areaMovable = geometry();
    m_bPressed = false;
}


Widget::~Widget()
{
    delete ui;
}

void Widget::GetNewImage(const QPixmap newPixmap)
{
    scene->addPixmap(newPixmap);
}

void Widget::on_toolButton_clicked()
{
    thePicture.findSoluntion(0);
}







/*-------------------------------------------------
【函数名】：鼠标事件
【隶属自】：HomePageUI类
【功能简介】：以下几个函数重定义了鼠标事件，使得用户按住界面任何地方都可以拖动界面
【开发者及时间】：lgz 2019.7.28
-------------------------------------------------*/

class QMouseEvent;

void Widget::mousePressEvent(QMouseEvent *e)
{
  //鼠标左键
  if(e->button() == Qt::LeftButton)
  {
  m_ptPress = e->pos();
  //qDebug() << pos() << e->pos() << m_ptPress;
  m_bPressed = m_areaMovable.contains(m_ptPress);
  }
}

void Widget::mouseMoveEvent(QMouseEvent *e)
{
  if(m_bPressed)
  {
  //qDebug() << pos() << e->pos() << m_ptPress;
  move(pos() + e->pos() - m_ptPress);
  }
}

void Widget::mouseReleaseEvent(QMouseEvent *e)
{
    m_bPressed = false;
}



//设置鼠标按下的区域
void Widget::setAreaMovable(const QRect rt)
{
  if(m_areaMovable != rt)
  {
  m_areaMovable = rt;
  }
}
