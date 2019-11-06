#ifndef HOMEPAGEUI_H
#define HOMEPAGEUI_H

#include <QDialog>
#include<QFileDialog>
#include<QGraphicsView>
#include"picture.h"
#include"choosepictureui.h"
#include"mpolygon.h"



namespace Ui {
class homepageUI;
}

class homepageUI : public QDialog
{
    Q_OBJECT

public:
    explicit homepageUI(QString fileName,QWidget *parent = nullptr);
    ~homepageUI();

    void setAreaMovable(const QRect rt);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

    void addPolygonsToScene(QGraphicsScene& scene);


private slots:
    //得到一张新图
    void GetNewImage(const QPixmap newPixmap);

    //用户选择了一张新的图片
    void GetNewMission(QString fileName);

    void on_start_clicked();



    void on_inload_clicked();

    void on_choose_clicked();




    void on_pushButton_clicked();

    void on_draw_clicked();

private:
    Ui::homepageUI *ui;
    picture* thePicture;



    MPolygon** bigTri;//用于存储用户拼图的元件
    QRect m_areaMovable;//可移动窗口的区域，鼠标只有在该区域按下才能移动窗口
    bool m_bPressed;//鼠标按下标志（不分左右键）
    QPoint m_ptPress;//鼠标按下的初始位置
};

#endif // HOMEPAGEUI_H
