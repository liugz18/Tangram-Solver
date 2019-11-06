#include "picture.h"

picture::picture(const QString &fileName,QObject *parent)

{
    QImage origin(fileName);
    Height = origin.height();
    Width = origin.width();
    int blacks = 0;//黑色面积

    pic = new bool*[origin.height()];

    QRgb * line = nullptr;
    for(int y = 0;y < origin.height();y++)
    {
        line = (QRgb *)origin.scanLine(y);
        pic[y] = new bool[origin.width()];

        for(int x = 0; x < origin.width(); x++)
        {
            if( (qRed(line[x]) + qGreen(line[x]) + qRed(line[x]) ))
                pic[y][x] = false;
            else
            {
                pic[y][x] = true;
                blacks++;
            }
        }
    }

    Blacks = blacks;
    MiniLength = static_cast<int>(sqrt( (double)blacks/8 )) + 2;
    OddLength = static_cast<int>(sqrt( (double)blacks/4 )) + 2;
//    MiniLength = 88;
//    OddLength = 174;
    qDebug()<<"MiniLength:"<<MiniLength;
    qDebug()<<"OddLength:"<<OddLength;

    generateShapes();

    for(int i = 0;i < 7;i++)
        preOccupy[i] = false;

    //qDebug() << STDNodes.count();

}

picture::picture(const QImage *origin, QObject *parent)
{

    Height = origin->height();
    Width = origin->width();
    int blacks = 0;//黑色面积

    pic = new bool*[origin->height()];

    QRgb * line = nullptr;
    for(int y = 0;y < origin->height();y++)
    {
        line = (QRgb *)origin->scanLine(y);
        pic[y] = new bool[origin->width()];

        for(int x = 0; x < origin->width(); x++)
        {
            if( (qRed(line[x]) + qGreen(line[x]) + qRed(line[x]) ))
                pic[y][x] = false;
            else
            {
                pic[y][x] = true;
                blacks++;
            }
        }
    }

    Blacks = blacks;
    MiniLength = static_cast<int>(sqrt( (double)blacks/8 )) + 2;
    OddLength = static_cast<int>(sqrt( (double)blacks/4 )) + 2;
//    MiniLength = 88;
//    OddLength = 174;
    qDebug()<<"MiniLength:"<<MiniLength;
    qDebug()<<"OddLength:"<<OddLength;

    generateShapes();
    for(int i = 0;i < 7;i++)
        preOccupy[i] = false;
}

picture::~picture()
{
    for(int y = 0;y < Height;y++)
    {
       delete[]pic[y];
    }

    delete []pic;

    Blacks = 0;
    MiniLength = 0;
    OddLength = 0;
    Width = 0;
    Height = 0;

    StartPoint = 0;
    printNum = 0;

    for(int i = 0;i < 7;i++)
    {
        if(Occupy[i])
            Occupy[i] = false;

    }

}

int picture::black(int x, int y)
{
    if(x < 0 || y < 0 || x >= Width || y >= Height)
        return 0;
    if(!pic[y][x])
        return 0;
    int nowInserted = state.count();
    for(int i = 0;i < nowInserted;i++)
    {
        if(state[i].isInside(x,y))
            return 10+state[i].type;
    }
    return 1;

}

void picture::scan(int &x, int &y)
{
    for(int i = StartPoint;i < Width+2*(Height-1);i++)
    {
        for(int j = (i>=Width)*((i-Width+2)>>1);(i-2*j>0 && j<Height);j++)
        {
            //if(black(i-2*j,j)==1&&floodfill(i-2*j,j)&&insertAble(i-2*j,j))
            if(black(i-2*j,j)==1 && insertAble(i-2*j,j))
            {
                x = i-2*j;
                y = j;
                if(StartPoint == 0)
                {
                    StartPoint = i-1;
                }
                return;
            }
        }
    }

}

bool picture::fit(shape &insert)
{
    //更改：取消每次都生成图形，改用STDNodes
    //QList<point> nodes = insert.allNodes();
    QList<point>& nodes = STDNodes[getRankFromShape(insert)];
    int nodesNum = nodes.count();
    int match = 0;
    int chongHe = 0;//跟其他图形重合的点数，过大直接返回;??
    QListIterator<point> iter1(nodes);
    while(iter1.hasNext())
    {
        point one=iter1.next();
        switch (black(one.x + insert.xcor,one.y + insert.ycor))
        {
            case 1:
            match++;
            break;

            case 0:
            break;
        default:
            chongHe++;
            break;
        }

    }


    double matchRatio = ((double)match)/nodesNum;
    if(insert.type ==MidTri && insert.pattern == 7)
        qDebug()<< "Look AT MidTRI at 7 with its matchratio:"<<matchRatio;

    if(matchRatio >= 0.98)
        return true;
    return false;
}

int picture::cut()
{
    if(state.empty())
        return -1;
    shape Temp = state.takeLast();
    return Temp.type;
}

//注意这个函数在black后没有更新
bool picture::floodfill(int x, int y)
{
    QStack<point> pointStack;
    pointStack.push(point(x,y));
    int blackArea = 1;
    QList<point> writtenPoints;

    pic[y][x] = false;
    writtenPoints.append(point(x,y));

    while(!pointStack.isEmpty())
    {
        //如果有超过40个黑点认为此处可以开始拼
        if(blackArea >= 1000)
        {

            QListIterator<point> iter1(writtenPoints);
            while(iter1.hasNext())
            {
                point one=iter1.next();

                pic[one.y][one.x] = true;
            }
            //注释寻秩访问，使用迭代器
            //int writtenNum = writtenPoints.count();
//            for(int i = 0;i < writtenNum;i++)
//            {
//                pic[writtenPoints[i].y][writtenPoints[i].x] = true;
//            }
            return true;
        }

        point temp = pointStack.pop();
        //四个方向如果有黑点，涂白并存入两个数据结构中
        if(temp.x-1>0 && black(temp.x-1,temp.y))
        {
            blackArea++;
            pic[temp.y][temp.x-1] = false;
            pointStack.push(point(temp.x-1,temp.y));
            writtenPoints.append(point(temp.x-1,temp.y));
        }
        if(temp.x+1<Width && black(temp.x+1,temp.y))
        {
            blackArea++;
            pic[temp.y][temp.x+1] = false;
            pointStack.push(point(temp.x+1,temp.y));
            writtenPoints.append(point(temp.x+1,temp.y));
        }
        if(temp.y-1>0 && black(temp.x,temp.y-1))
        {
            blackArea++;
            pic[temp.y-1][temp.x] = false;
            pointStack.push(point(temp.x,temp.y-1));
            writtenPoints.append(point(temp.x,temp.y-1));
        }
        if(temp.y+1<Height && black(temp.x,temp.y+1))
        {
            blackArea++;
            pic[temp.y+1][temp.x] = false;
            pointStack.push(point(temp.x,temp.y+1));
            writtenPoints.append(point(temp.x,temp.y+1));
        }
    }
    return false;


}
//加入深度上限
int DepthMaximum = 500;
bool picture::findSoluntion(int lunci)
{
    qDebug()<<"lunci:"<<lunci;
    //7轮次时已经找到解
    if(lunci == 7)
    {
        for(int i = 0;i < 7;i++)
        {
            state[i].printShape();
        }
        printState();
        //Occupy[cut()] = false;
        //Occupy[cut()] = false;



        return true;
    }

    //到达深度上限
//    if(printNum >= 500)
//        return true;


//    if(Occupy[0] && Occupy[1] && Occupy[2] && Occupy[3] && Occupy[4] && Occupy[5] && Occupy[6])
//        return true;

    //搜索

    //找到可以拼的点
    int x = -1;
    int y = -1;
    scan(x,y);

    qDebug()<<"x:"<<x<<"y"<<y;
//    qDebug()<<state.count();
    if(x == -1 && y == -1)
        return false;

    //大三角形搜索
    if(!(Occupy[BigTri1] && Occupy[BigTri2]))
    {
        shape aBigTri(BigTri1,1,x,y);
        if(Occupy[BigTri1])
            aBigTri.type = BigTri2;



        if(ReverseOrder)
        {
            for(int i = 8;i > 0;i--)
            {
                aBigTri.pattern = i;
                if(fit(aBigTri))
                {
                    qDebug()<<"Try to insert BigTri! pattern:"<<i<<"at"<<x<<" "<<y;

                    //qDebug()<<aBigTri.xcor<<aBigTri.ycor;
                    state<<aBigTri;
                    printState();
                    if(!Occupy[BigTri1])
                        Occupy[BigTri1] = true;
                    else
                        Occupy[BigTri2] = true;

                    if(findSoluntion(lunci+1))
                        return true;
                }
            }

        }
        else
        {

            for(int i = 1;i <= 8;i++)
            {
                aBigTri.pattern = i;
                if(fit(aBigTri))
                {
                    qDebug()<<"Try to insert BigTri! pattern:"<<i<<"at"<<x<<" "<<y;

                    //qDebug()<<aBigTri.xcor<<aBigTri.ycor;
                    state<<aBigTri;
                    printState();
                    if(!Occupy[BigTri1])
                        Occupy[BigTri1] = true;
                    else
                        Occupy[BigTri2] = true;

                    if(findSoluntion(lunci+1))
                        return true;
                }
            }
        }
    }

    //正方形搜索

    if(!Occupy[Square])
    {

        shape aSquare(Square,9,x,y);
        if(fit(aSquare))
        {
            qDebug()<<"Try to insert Square 9!"<<"at"<<x<<" "<<y;

            state<<aSquare;
            printState();
            Occupy[Square] = true;
            if(findSoluntion(lunci+1))
                return true;
        }
        aSquare.pattern = 10;
        if(fit(aSquare))
        {
            qDebug()<<"Try to insert Square 10!"<<"at"<<x<<" "<<y;
            state<<aSquare;
            printState();
            Occupy[Square] = true;
            if(findSoluntion(lunci+1))
                return true;
        }
    }

    //平行四边形搜索
    if(!Occupy[Parallel])
    {

        shape aParallel(Parallel,11,x,y);

        for(int i = 11;i < 19;i++)
        {
            aParallel.pattern = i;
            if(fit(aParallel))
            {
                qDebug()<<"Try to insert Parallel! pattern:"<<i<<"at"<<x<<" "<<y;
                state<<aParallel;
                printState();
                Occupy[Parallel] = true;
                if(findSoluntion(lunci+1))
                    return true;
            }
        }
    }

    //中三角形搜索
    if(!Occupy[MidTri])
    {
        shape aMidTri(MidTri,1,x,y);

        for(int i = 1;i < 9;i++)
        {
            aMidTri.pattern = i;
            if(fit(aMidTri))
            {
                qDebug()<<"Try to insert MidTri! pattern:"<<i<<"at"<<x<<" "<<y;

                state<<aMidTri;
                printState();
                Occupy[MidTri] = true;
                if(findSoluntion(lunci+1))
                    return true;
            }
        }
    }
    //小三角形搜索
    if(!(Occupy[SmallTri1] && Occupy[SmallTri2]))
    {

        shape aSmallTri(SmallTri1,1,x,y);
        if(Occupy[SmallTri1])
            aSmallTri.type = SmallTri2;

        for(int i = 1;i < 9;i++)
        {
            aSmallTri.pattern = i;
            if(fit(aSmallTri))
            {
                qDebug()<<"Try to insert SmallTri Pattern:"<<i<<"at:"<<x<<" "<<y;

                state<<aSmallTri;
                printState();
                if(!Occupy[SmallTri1])
                    Occupy[SmallTri1] = true;
                else
                    Occupy[SmallTri2] = true;

                if(findSoluntion(lunci+1))
                    return true;
            }
        }
    }

    //如果此处放不进去
    //printState();
    int cutt = cut();
    qDebug()<<"cutt:"<<cutt;
    if(cutt!=-1)
        Occupy[cutt] = false;
    return false;


}

bool picture::insertAble(int x, int y)
{
    /*注释了用正方形框选来判定是否可拼，因为有特殊情况漏了
    int RightBlack = 0;//该点右侧的黑点数
    int LeftBlack = 0;//该点左侧的黑点数

    for(int i = 0;i < MiniLength;i++)
    {
        for(int j = 0;j< MiniLength;j++)
        {
            if(black(x+i,y+j))
                RightBlack++;
            if(black(x-i,y+j))
                LeftBlack++;
        }
    }

    double RightRatio = (double)RightBlack/(MiniLength*MiniLength);
    if(RightRatio >= 0.49)
        return true;
    double LeftRatio = (double)LeftBlack/(MiniLength*MiniLength);
    if(LeftRatio >= 0.49)
        return true;*/

    int aBlack = 0;//a区域的黑点数
    int bBlack = 0;//b区域的黑点数
    int cBlack = 0;//c区域的黑点数
    int dBlack = 0;//d区域的黑点数

    //int verifyLength = (OddLength+1)>>1;
    int verifyLength = 10;
    double verifyArea = verifyLength*verifyLength/2.0;

    for(int i = 0;i < verifyLength;i++)
    {
        for(int j = i;j < verifyLength;j++)
        {
            if(black(x+j,y+i)==1)
                aBlack++;
            if(black(x+i,y+j)==1)
                bBlack++;
            if(black(x-i,y+j)==1)
                cBlack++;
            int xPrime = x+verifyLength-1;
            if(black(xPrime-j,y+i)==1)
                dBlack++;
        }
    }

    if(aBlack/verifyArea >=1 || bBlack/verifyArea >=1 || cBlack/verifyArea >=1 || dBlack/verifyArea >=1)
        return true;


    return false;
}

void picture::printState()
{
    QImage * newImage = new QImage(Width,Height, QImage::Format_ARGB32);
    for(int y = 0; y<newImage->height(); y++){


        for(int x = 0; x<newImage->width(); x++){


//            if(black(x,y)==1)
//            {
//               newImage->setPixel(x,y, qRgb(0,0,0));
//            }
//            else
//            {
//                newImage->setPixel(x,y, qRgb(255,255,255));
//            }
            switch (black(x,y))
            {
                case 0:
                newImage->setPixel(x,y, qRgb(255,255,255));
                break;

                case 1:
                newImage->setPixel(x,y, qRgb(0,0,0));
                break;

                case 10:
                newImage->setPixel(x,y, qRgb(255,106,106));
                break;

            case 11:
            newImage->setPixel(x,y, qRgb(0,255,0));
            break;

            case 12:
            newImage->setPixel(x,y, qRgb(99,184,255));
            break;

            case 13:
            newImage->setPixel(x,y, qRgb(238,58,140));
            break;

            case 14:
            newImage->setPixel(x,y, qRgb(148,0,211));
            break;

            case 15:
            newImage->setPixel(x,y, qRgb(205,255,112));
            break;

            case 16:
            newImage->setPixel(x,y, qRgb(0,245,255));
            break;

            default:
                break;

            }
        }

    }


    QString savePlace ="/Users/tnoy/Desktop/n3/"  + QString::number(printNum)  + QDateTime::currentDateTime().toString() +".png";
    printNum++;

    //newImage->save(savePlace);

    //TheWidget.scene->addPixmap(QPixmap::fromImage(*newImage));
    emit ChangeImage(QPixmap::fromImage(*newImage));



}

void picture::generateShapes()
{
    if(!STDNodes.isEmpty())
        STDNodes.clear();

    //生成大三角形的所有姿态 秩为0～7
    for(int i = 0;i < 8;i++)
    {
        shape TempBigTri(BigTri1,i+1,0,0);
        STDNodes.append(TempBigTri.allNodes());
    }

    //生成正方形所有姿态 秩为8，9
    for(int i = 0;i < 2;i++)
    {
        shape Temp(Square,i+9,0,0);
        STDNodes.append(Temp.allNodes());
    }

    //生成平四所有姿态 秩为10～17
    for(int i = 0;i < 8;i++)
    {
        shape Temp(Parallel,i+11,0,0);
        STDNodes.append(Temp.allNodes());
    }

    //生成中三角形的所有姿态 秩为18~25
    for(int i = 0;i < 8;i++)
    {
        shape TempBigTri(MidTri,i+1,0,0);
        STDNodes.append(TempBigTri.allNodes());
    }

    //生成小三角形的所有姿态 秩为26~33
    for(int i = 0;i < 8;i++)
    {
        shape TempBigTri(SmallTri1,i+1,0,0);
        STDNodes.append(TempBigTri.allNodes());
    }

}

int picture::getRankFromShape(const shape &insert)
{
    if(insert.type == BigTri1 || insert.type == BigTri2 || insert.type == Square || insert.type == Parallel)
    {
        return insert.pattern - 1;
    }

    if(insert.type == MidTri)
    {
        return insert.pattern + 17;
    }

    if(insert.type == SmallTri1 || insert.type == SmallTri2)
    {
        return insert.pattern + 25;
    }

}
