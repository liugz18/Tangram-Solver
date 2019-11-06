#include "homepageui.h"
#include"shape.h"
#include"picture.h"

#include <QApplication>
#include<QImage>

int MiniLength = 0;//小三角形横放的直角边长度
int OddLength = 0;//小三竖放的斜边长度

//全图的长宽,面积
int Width = 0;
int Height = 0;
int Blacks = 0;

int printNum = 0;//当前打印了几张图

int StartPoint = 0;//开始扫描的斜线编号

bool Occupy[7]={0,0,0,0,0,0,0};//表示当前哪些板已经使用

bool ReverseOrder = false;//为真表示大三角形倒序搜索，可以避免在错误的方向上走太深。





int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    MiniLength = 800;
//    OddLength = 1000;
//    shape atri(Parallel,18,1200,1000);
//    QList<point> nodes = atri.allNodes();
//    int nodesNum = nodes.count();

//    QImage * newImage = new QImage(4000,4000, QImage::Format_ARGB32);
//    for(int y = 0; y<newImage->height(); y++)
//    {


//        for(int x = 0; x<newImage->width(); x++)
//            {

//                newImage->setPixel(x,y, qRgb(255,255,255));
//            }
//    }

//    for(int i = 0;i<nodesNum;i++)
//    {
//        newImage->setPixel(nodes[i].x,nodes[i].y, qRgb(0,0,0));
//    }


//   newImage->save("/Users/tnoy/Desktop/erci12.bmp");

//    //picture one("/Users/tnoy/Desktop/erci12.bmp");
//    one.findSoluntion(0);


    homepageUI* homepage = new homepageUI(":/tupian/4.bmp");

    homepage->exec();




   return 0;
}
