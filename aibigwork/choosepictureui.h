#ifndef CHOOSEPICTUREUI_H
#define CHOOSEPICTUREUI_H

#include <QDialog>
#include<QButtonGroup>
#include<QLabel>
#include<QCheckBox>

namespace Ui {
class ChoosePictureUI;
}



class ChoosePictureUI : public QDialog
{
    Q_OBJECT

public:
    explicit ChoosePictureUI(QWidget *parent = nullptr);
    ~ChoosePictureUI();

private slots:
    void on_no_clicked();

    void on_yes_clicked();

signals:
    //选好了新图
    void ImageSelected(QString fileName);




private:
    Ui::ChoosePictureUI *ui;
    QButtonGroup* m_ButtonGroup;    //按钮组
    QLabel** m_Pics;
    int PicNum;


};

#endif // CHOOSEPICTUREUI_H
