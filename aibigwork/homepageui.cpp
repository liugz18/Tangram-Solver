#include "homepageui.h"
#include "ui_homepageui.h"
#include<QMovie>
#include<QMessageBox>

homepageUI::homepageUI(QString fileName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::homepageUI)
{
    bigTri = new MPolygon*[7];

    ui->setupUi(this);
    setFixedSize(1100,640);

    ui->background->setStyleSheet("background-color: rgb(255,255,255);");
    QMovie* movie = new QMovie(":/tupian/giphy6.gif");


    ui->gif->setMovie(movie);

    movie->start();
    ui->gif->lower();
    ui->youce->raise();




    setStyleSheet("color:white");

    //无边框处理
    setWindowFlags(Qt::FramelessWindowHint| Qt::Dialog);
    setWindowOpacity(1);


    //title构造
    ui->titlee->setStyleSheet("background: transparent;");

    ui->titlee->setPixmap(QPixmap(":/tupian/titlee2.png"));
    //ui->titlee->setIconSize(ui->titlee->size());
    //先构造picture对象
    thePicture = new picture(fileName,this);
    connect(thePicture,&picture::ChangeImage,this,&homepageUI::GetNewImage);


    ui->label->setFixedSize(800,640);
    ui->label->setPixmap(QPixmap(fileName).scaled(800,640,Qt::KeepAspectRatio));



    //重新定义鼠标事件
    setMouseTracking(true);
    m_areaMovable = geometry();
    m_bPressed = false;

    //创建用户拼图界面
    int SCENESIZE1 = 820;
    int SCENESIZE2 = 640;
    QGraphicsScene* scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0,SCENESIZE1,SCENESIZE2);
    addPolygonsToScene(*scene);

    QGraphicsView* view = new QGraphicsView(scene,this);
    view->setStyleSheet("background-color: rgb(255,255,255);");

    //view.setStyleSheet("border:0px;background-color: rgb(255,255,255);");
    //view.setWindowFlags(Qt::FramelessWindowHint);
    view->resize(SCENESIZE1, SCENESIZE2);

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //ui->stackedWidget->addWidget(view);
    //view->show();
    ui->stackedWidget->addWidget(view);
    ui->stackedWidget->setCurrentIndex(0);


}

homepageUI::~homepageUI()
{
    delete ui;
    if(bigTri)
        delete [] bigTri;
}



void homepageUI::on_start_clicked()
{
    if(ui->start->text() == "Start!")
    {
        int Finished = Occupy[0] + Occupy[1] + Occupy[2] + Occupy[3] + Occupy[4] + Occupy[5] + Occupy[6];
    //    while (Finished != 7)
    //    {
    //        bool tempOccupy[7];
    //        for(int i = 0;i < 7;i++)
    //        {
    //            tempOccupy[i] = Occupy[i];
    //            Occupy[i] = thePicture->preOccupy[i];
    //            thePicture->preOccupy[i] = tempOccupy[i];
    //        }

    //        QList<shape> tempState;
    //        tempState = thePicture->state;
    //        thePicture->state = thePicture->preState;
    //        thePicture->preState = tempState;

            //ReverseOrder = !ReverseOrder;

            //Finished = Occupy[0] + Occupy[1] + Occupy[2] + Occupy[3] + Occupy[4] + Occupy[5] + Occupy[6];

            printNum = 0;
            thePicture->findSoluntion(Finished);
            //Finished = Occupy[0] + Occupy[1] + Occupy[2] + Occupy[3] + Occupy[4] + Occupy[5] + Occupy[6];
    }
    //}
    //thePicture->findSoluntion(0);
    else if(ui->start->text() == "OK!")
    {

        for(int i = 0;i < 7;i ++)
        {
            if(!bigTri[i]->scene()->collidingItems(bigTri[i]).isEmpty())
            {
                QMessageBox::warning(this, "Warning!", "Pieces collide with each other!!! can't solve this Orz");
                return;
            }
        }


        int SCENESIZE1 = 820;
        int SCENESIZE2 = 640;
        QPixmap* image = new QPixmap(  ui->stackedWidget->widget(2)->grab(QRect(0,0,SCENESIZE1,SCENESIZE2)) );

        delete thePicture;

        QImage aimage = image->toImage();
        aimage.save("/Users/tnoy/Desktop/testimage.png");

        thePicture = new picture(&aimage);
        connect(thePicture,&picture::ChangeImage,this,&homepageUI::GetNewImage);

        ui->label->setPixmap(*image);

        ui->stackedWidget->setCurrentIndex(0);
        ui->inload->show();
        ui->draw->setText("Draw picture");
        ui->choose->setText("Choose picture");
        ui->start->setText("Start!");


    }

}




void homepageUI::GetNewImage(const QPixmap newPixmap)
{
    ui->label->setPixmap(newPixmap.scaled(800,640,Qt::KeepAspectRatio));
}

void homepageUI::GetNewMission(QString fileName)
{
    qDebug()<<"watch!!!!"<<fileName;
    if(fileName !="")
    {
        delete thePicture;

        thePicture = new picture(fileName);
        connect(thePicture,&picture::ChangeImage,this,&homepageUI::GetNewImage);

        ui->label->setPixmap(QPixmap(fileName).scaled(800,640,Qt::KeepAspectRatio));
    }
}


/*-------------------------------------------------
【函数名】：鼠标事件
【隶属自】：HomePageUI类
【功能简介】：以下几个函数重定义了鼠标事件，使得用户按住界面任何地方都可以拖动界面
【开发者及时间】：lgz 2019.7.28
-------------------------------------------------*/



void homepageUI::mousePressEvent(QMouseEvent *e)
{
  //鼠标左键
  if(e->button() == Qt::LeftButton)
  {
  m_ptPress = e->pos();
  //qDebug() << pos() << e->pos() << m_ptPress;
  m_bPressed = m_areaMovable.contains(m_ptPress);
  }
}

void homepageUI::mouseMoveEvent(QMouseEvent *e)
{
  if(m_bPressed)
  {
  //qDebug() << pos() << e->pos() << m_ptPress;
  move(pos() + e->pos() - m_ptPress);
  }
}

void homepageUI::mouseReleaseEvent(QMouseEvent *e)
{
    m_bPressed = false;
}


//生成用户拼图的元件
int FixedMiniLength = 120;//用户拼图时的单元尺寸
void homepageUI::addPolygonsToScene(QGraphicsScene &scene)
{
    QPolygon aTri[7];
    //大三角形生成
    aTri[0] << QPoint(2*FixedMiniLength,2*FixedMiniLength) << QPoint(0,0) << QPoint(2*FixedMiniLength,0);
    //aTri[0] << QPoint(100,100) << QPoint(0,0) << QPoint(100,0);

    aTri[1] << QPoint(2*FixedMiniLength+300,2*FixedMiniLength+300) << QPoint(300,300) << QPoint(2*FixedMiniLength+300,300);
    //正方形生成
    aTri[2] << QPoint(0,0+130) << QPoint(FixedMiniLength,0+130) <<  QPoint(FixedMiniLength,FixedMiniLength+130) << QPoint(0,FixedMiniLength+130)  ;

    //平四生成
    aTri[3] << QPoint(0,0+260) << QPoint(FixedMiniLength,0+260) <<  QPoint(2*FixedMiniLength,FixedMiniLength+260) << QPoint(FixedMiniLength,FixedMiniLength+260)  ;

    //中三生成
    aTri[4] << QPoint(0,0+390) << QPoint(2*FixedMiniLength,0+390) << QPoint(FixedMiniLength,FixedMiniLength+390);

    //小三生成
    aTri[5] << QPoint(FixedMiniLength+260,FixedMiniLength) << QPoint(260,0) << QPoint(FixedMiniLength+260,0);
    aTri[6] << QPoint(FixedMiniLength+390,FixedMiniLength) << QPoint(390,0) << QPoint(FixedMiniLength+390,0);


    bigTri[0] = new MPolygon(aTri[0],this);
    scene.addItem(bigTri[0]);
    bigTri[1] = new MPolygon(aTri[1],this);
    scene.addItem(bigTri[1]);
    bigTri[2] = new MPolygon(aTri[2],this);
    scene.addItem(bigTri[2]);
    bigTri[3] = new MPolygon(aTri[3],this);
    scene.addItem(bigTri[3]);
    bigTri[4] = new MPolygon(aTri[4],this);
    scene.addItem(bigTri[4]);
    bigTri[5] = new MPolygon(aTri[5],this);
    scene.addItem(bigTri[5]);
    bigTri[6] = new MPolygon(aTri[6],this);
    scene.addItem(bigTri[6]);



}





//设置鼠标按下的区域
void homepageUI::setAreaMovable(const QRect rt)
{
  if(m_areaMovable != rt)
  {
  m_areaMovable = rt;
  }
}



void homepageUI::on_inload_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Inload Picture"), " ",  "Images (*.png *.bmp *.jpg)");

    if(fileName !="")
    {
        delete thePicture;

        thePicture = new picture(fileName);
        connect(thePicture,&picture::ChangeImage,this,&homepageUI::GetNewImage);

        ui->label->setPixmap(QPixmap(fileName).scaled(800,640,Qt::KeepAspectRatio));
    }

}

void homepageUI::on_choose_clicked()
{
    if(ui->choose->text() == "Choose picture")
    {
        ChoosePictureUI* window = new ChoosePictureUI(this);
        connect(window,&ChoosePictureUI::ImageSelected,this,&homepageUI::GetNewMission);
        window->exec();
    }
    else if(ui->choose->text() == "Save picture")
    {
        int SCENESIZE1 = 820;
        int SCENESIZE2 = 640;
        QString fileName = QFileDialog::getExistingDirectory(this, tr("Save Picture"));

        QPixmap* image = new QPixmap(  ui->stackedWidget->widget(2)->grab(QRect(0,0,SCENESIZE1,SCENESIZE2)) );

        qDebug()<<fileName;

        QImage aimage = image->toImage();
        if(fileName != "")
            aimage.save(fileName + "/" + QDateTime::currentDateTime().toString() + ".png");
    }
}

void homepageUI::on_pushButton_clicked()
{
    close();
}

void homepageUI::on_draw_clicked()
{
    //注释了生成view,在构造函数中生成;
//    int SCENESIZE1 = 820;
//    int SCENESIZE2 = 640;

    if(ui->draw->text() == "Draw picture")
    {

        ui->inload->hide();
        ui->draw->setText("Back");
        ui->choose->setText("Save picture");
        ui->start->setText("OK!");

//        QGraphicsScene* scene = new QGraphicsScene(this);
//        scene->setSceneRect(0, 0,SCENESIZE1,SCENESIZE2);
//        addPolygonsToScene(*scene);

//        QGraphicsView* view = new QGraphicsView(scene,this);
//        view->setStyleSheet("background-color: rgb(255,255,255);");

//        //view.setStyleSheet("border:0px;background-color: rgb(255,255,255);");
//        //view.setWindowFlags(Qt::FramelessWindowHint);
//        view->resize(SCENESIZE1, SCENESIZE2);

//        view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//        view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

//        //ui->stackedWidget->addWidget(view);
//        //view->show();
        //ui->stackedWidget->setCurrentIndex(ui->stackedWidget->addWidget(view));
        ui->stackedWidget->setCurrentIndex(2);
    }
    else
    {
        ui->stackedWidget->setCurrentIndex(0);
        ui->inload->show();
        ui->draw->setText("Draw picture");
        ui->choose->setText("Choose picture");
        ui->start->setText("Start!");
    }
}
