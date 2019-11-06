#include "choosepictureui.h"
#include "ui_choosepictureui.h"
#include<QDebug>

ChoosePictureUI::ChoosePictureUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChoosePictureUI)
{
    setWindowTitle("Select Picture");
    //setFixedSize(580,480);
    ui->setupUi(this);


    PicNum = 23;

    m_ButtonGroup = new QButtonGroup;
    m_ButtonGroup->setExclusive(true);

    m_Pics = new QLabel*[PicNum];

    ui->Layout->setVerticalSpacing(10);

    //ui->scrollArea->setWidgetResizable(true);

    //ui->scrollAreaContents->

    ui->scrollAreaContents->resize(477,PicNum*410+5);

    //设置勾选菜单和发布人看到的报名者信息：
    for(int i = 1;i <= PicNum;i++)
    {
        QCheckBox* m_RadioButton = new QCheckBox("",this);
        m_ButtonGroup->addButton(m_RadioButton,i-1);
        m_Pics[i-1] = new QLabel(this);

        m_Pics[i-1]->setFixedSize(480,400);
        m_Pics[i-1]->setPixmap(QPixmap(":/tupian/"+ QString::number(i) +".bmp").scaled(480,400,Qt::IgnoreAspectRatio));
        ui->Layout->addRow(m_RadioButton,m_Pics[i-1]);
    }


}

ChoosePictureUI::~ChoosePictureUI()
{
    if(m_Pics != nullptr)
        delete [] m_Pics;
    delete ui;
}

void ChoosePictureUI::on_no_clicked()
{
    close();
}

void ChoosePictureUI::on_yes_clicked()
{
    for(int i = 0;i < PicNum;i++)
    {
        if(static_cast<QCheckBox*>(m_ButtonGroup->button(i))->checkState() == 2)
        {
            qDebug()<<i;
            emit ImageSelected(":/tupian/"+ QString::number(i+1) +".bmp");
            close();

        }
    }
}
