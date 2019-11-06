#include "shape.h"



shape::shape(ShapeForm s, int p, int x, int y, QObject *parent):
    type(s),pattern(p),xcor(x),ycor(y){}

shape::shape(const shape &other)
{
    type = other.type;
    pattern = other.pattern;
    xcor = other.xcor;
    ycor = other.ycor;
}

shape &shape::operator=(const shape &other)
{
    type = other.type;
    pattern = other.pattern;
    xcor = other.xcor;
    ycor = other.ycor;
}

void shape::printShape()
{
    qDebug()<<"type:"<<type<<"  pattern:"<<pattern;
    qDebug()<<"  x:"<<xcor<<"  y:"<<ycor;
}



bool shape::isInside(int x, int y)
{
    int xRela = x - xcor;
    int yRela = y - ycor;
    switch(pattern)
    {
        //直角边平放的三角形
        case 1:case 2:case 3:case 4:
        {
            int ZhiJiaoBian;
            if(type==BigTri1 || type==BigTri2)
                ZhiJiaoBian = 2*MiniLength;
            else if(type==MidTri)
                ZhiJiaoBian = OddLength;
            else
                ZhiJiaoBian = MiniLength;
            if(pattern == 1)
            {
//                for(int i = 0;i<ZhiJiaoBian;i++)
//                {
//                    for(int j = i;j<ZhiJiaoBian;j++)
//                    {
//                        nodes<<point(xcor+j,ycor+i);
//                    }
//                }
                if(yRela>xRela)
                    return false;
                if(xRela<0 || xRela>=ZhiJiaoBian)
                    return false;
                if(yRela<0 || yRela>=ZhiJiaoBian)
                    return false;

                return true;
            }
            else if(pattern == 2)
            {
//                for(int i = 0;i<ZhiJiaoBian;i++)
//                {
//                    for(int j = 0;j<ZhiJiaoBian-i;j++)
//                    {
//                        nodes<<point(xcor+j,ycor+i);
//                    }
//                }
                if(xRela<0 || xRela>=ZhiJiaoBian)
                    return false;
                if(yRela<0 || yRela>=ZhiJiaoBian)
                    return false;
                if(yRela+xRela>=ZhiJiaoBian)
                    return false;

                return true;
            }
            else if(pattern == 3)
            {
//                for(int i = 0;i<ZhiJiaoBian;i++)
//                {
//                    for(int j = 0;j<=i;j++)
//                    {
//                        nodes<<point(xcor+j,ycor+i);
//                    }
//                }
                if(xRela<0 || xRela>=ZhiJiaoBian)
                    return false;
                if(yRela<0 || yRela>=ZhiJiaoBian)
                    return false;
                if(yRela<xRela)
                    return false;

                return true;
            }
            else if(pattern == 4)
            {
//                for(int i = 0;i<ZhiJiaoBian;i++)
//                {
//                    for(int j = 0;j<=i;j++)
//                    {
//                        nodes<<point(xcor-j,ycor+i);
//                    }
//                }
                if(yRela<-xRela)
                    return false;
                if(xRela>0 || -xRela>=ZhiJiaoBian)
                    return false;
                if(yRela<0 || yRela>=ZhiJiaoBian)
                    return false;


                return true;
            }
        break;
        }
        //正放的正方形
        case 9:
        {
//            for(int i = 0;i<MiniLength;i++)
//            {
//                for(int j = 0;j<MiniLength;j++)
//                {
//                    nodes<<point(xcor+i,ycor+j);
//                }
//            }

//            return nodes;
            if(xRela>=0 && xRela<MiniLength && yRela>=0 && yRela<MiniLength)
                return true;
            return false;
        break;
        }

        //斜放的正方形
        case 10:
        {
            //int triHeight = (OddLength+1)>>1;
            if(OddLength%2 == 0)
            {
                if(-xRela>yRela || yRela>xRela+OddLength-1)
                    return false;
                if(xRela>yRela+1 || yRela+xRela>OddLength)
                    return false;
                return true;
            }
            else
            {
                if(-xRela>yRela || yRela>xRela+OddLength-1)
                    return false;
                if(xRela>yRela || yRela+xRela>=OddLength)
                    return false;
                return true;

            }
        break;
        }

        //直角边斜放的三角形
        case 5:case 6:case 7:case 8:
        {
            int XieBian;
            if(type==BigTri1 || type==BigTri2)
                XieBian = 2*OddLength;
            else if(type==MidTri)
                XieBian = 2*MiniLength;
            else
                XieBian = OddLength;

            int triHeight = (XieBian+1)>>1;

            if(pattern == 5)
            {
                if(xRela<0 || xRela>=triHeight)
                    return false;
                if(yRela<0 || yRela>=XieBian)
                    return false;
                if(xRela>yRela || xRela+yRela>=XieBian)
                    return false;
                return true;
            }
            else if(pattern == 6)
            {
                if(xRela>0 || -xRela>=triHeight)
                    return false;
                if(yRela<0 || yRela>=XieBian)
                    return false;
                if(-xRela>yRela || yRela-xRela>=XieBian)
                    return false;
                return true;
            }
            else if(pattern == 7)
            {
                if(xRela<0 || xRela>=XieBian)
                    return false;
                if(yRela<0 || yRela>=triHeight)
                    return false;
                if(yRela>xRela || xRela+yRela>=XieBian)
                    return false;
                return true;

            }
            else if(pattern == 8)
            {
                if(yRela>=triHeight)
                    return false;
                if(xRela>yRela)
                    return false;
                if(-xRela>yRela)
                    return false;
                return true;

            }
        break;
        }
        //对角线平放的平四
        case 11:
        {
            //int triHeight = (OddLength+1)>>1;

            if(xRela>0 || -xRela>=MiniLength)
                return false;
            if(-xRela>yRela || xRela+yRela>=MiniLength)
                return false;
            return true;
        break;
        }
        case 12:
        {
            //int triHeight = (OddLength+1)>>1;

            if(yRela<0 || yRela>=MiniLength)
                return false;
            if(xRela<yRela || yRela<=xRela-MiniLength)
                return false;
            return true;
        break;
        }
        case 13:
        {
            //int triHeight = (OddLength+1)>>1;

            if(yRela<0 || yRela>=MiniLength)
                return false;
            if(-xRela>yRela || xRela+yRela>=MiniLength)
                return false;
            return true;
        break;
        }
        case 14:
        {
            //int triHeight = (OddLength+1)>>1;

            if(xRela<0 || xRela>=MiniLength)
                return false;
            if(xRela>yRela || yRela>=xRela+MiniLength)
                return false;
            return true;
        break;
        }
        //对角线斜放的平四
        case 15:
        {
            int triHeight = (OddLength+1)>>1;
            if(yRela<0 || yRela>=triHeight)
                return false;
            if(-xRela>yRela || xRela+yRela>=OddLength)
                return false;
            return true;
        break;
        }
        case 16:
        {
            int triHeight = (OddLength+1)>>1;
            if(xRela<0 || xRela>=triHeight)
                return false;
            if(xRela>yRela || yRela>=xRela+OddLength)
                return false;
            return true;
        break;
        }
        case 17:
        {
            int triHeight = (OddLength+1)>>1;
            if(xRela>0 || -xRela>=triHeight)
                return false;
            if(-xRela>yRela || xRela+yRela>=OddLength)
                return false;
            return true;
        break;
        }
        case 18:
        {
            int triHeight = (OddLength+1)>>1;
            if(yRela<0 || yRela>=triHeight)
                return false;
            if(xRela<yRela || yRela<=xRela-OddLength)
                return false;
            return true;
        break;
        }

    }
}


//尝试缩小放入时的范围
int shrinkNum = 10;


QList<point> shape::allNodes()
{
    QList<point> nodes;
    switch(pattern)
    {
        //直角边平放的三角形
        case 1:case 2:case 3:case 4:
        {
            int ZhiJiaoBian;
            if(type==BigTri1 || type==BigTri2)
                ZhiJiaoBian = 2*MiniLength;
            else if(type==MidTri)
                ZhiJiaoBian = OddLength;
            else
                ZhiJiaoBian = MiniLength;
            //尝试缩小放入时的范围
            ZhiJiaoBian -= 3*shrinkNum;

            if(pattern == 1)
            {
                for(int i = 0;i<ZhiJiaoBian;i++)
                {
                    for(int j = i;j<ZhiJiaoBian;j++)
                    {
                        nodes<<point(xcor+j+2*shrinkNum,ycor+i+shrinkNum);
                    }
                }
            }
            else if(pattern == 2)
            {
                for(int i = 0;i<ZhiJiaoBian;i++)
                {
                    for(int j = 0;j<ZhiJiaoBian-i;j++)
                    {
                        nodes<<point(xcor+j+shrinkNum,ycor+i+shrinkNum);
                    }
                }
            }
            else if(pattern == 3)
            {
                for(int i = 0;i<ZhiJiaoBian;i++)
                {
                    for(int j = 0;j<=i;j++)
                    {
                        nodes<<point(xcor+j+shrinkNum,ycor+i+2*shrinkNum);
                    }
                }
            }
            else if(pattern == 4)
            {
                for(int i = 0;i<ZhiJiaoBian;i++)
                {
                    for(int j = 0;j<=i;j++)
                    {
                        nodes<<point(xcor-j-shrinkNum,ycor+i+2*shrinkNum);
                    }
                }
            }
            return nodes;
        break;
        }
        //正放的正方形
        case 9:
        {
            //尝试缩小放入时的范围

            for(int i = 0;i<MiniLength - 2*shrinkNum;i++)
            {
                for(int j = 0;j<MiniLength - 2*shrinkNum;j++)
                {
                    nodes<<point(xcor+i+shrinkNum,ycor+j+shrinkNum);
                }
            }

            return nodes;
        break;
        }

        //斜放的正方形
        case 10:
        {
            if(OddLength%2 == 0)
            {
                int triHeight = ((OddLength+1)>>1) - shrinkNum;
                for(int i = 0;i < triHeight;i++)
                {
                    for(int j = i;j < OddLength-i - 2*shrinkNum;j++)
                    {
                        nodes<<point(xcor-i,ycor+j +shrinkNum);
                    }
                }
                for(int i = 0;i < triHeight;i++)
                {
                    for(int j = i;j < OddLength-i - 2*shrinkNum;j++)
                    {
                        nodes<<point(xcor+1+i,ycor+j +shrinkNum);
                    }
                }
            }
            else
            {
                int triHeight = ((OddLength+1)>>1) - shrinkNum;
                for(int i = 0;i < triHeight;i++)
                {
                    for(int j = i;j < OddLength-i - 2*shrinkNum;j++)
                    {
                        nodes<<point(xcor-i,ycor+j +shrinkNum);
                    }
                }
                for(int i = 0;i < triHeight-1;i++)
                {
                    for(int j = i;j < OddLength-2-i - 2*shrinkNum;j++)
                    {
                        nodes<<point(xcor+1+i,ycor+1+j +shrinkNum);
                    }
                }

            }
            return nodes;
        break;
        }

        //直角边斜放的三角形
        case 5:case 6:case 7:case 8:
        {
            int XieBian;
            if(type==BigTri1 || type==BigTri2)
                XieBian = 2*OddLength;
            else if(type==MidTri)
                XieBian = 2*MiniLength;
            else
                XieBian = OddLength;

            XieBian -= 4*shrinkNum;

            int triHeight = (XieBian+1)>>1;

            if(pattern == 5)
            {
                //qDebug()<<"constructing Pattern 5";
                for(int i = 0;i < triHeight;i++)
                {
                    for(int j = i;j < XieBian-i;j++)
                    {
                        nodes<<point(xcor+i+shrinkNum,ycor+j+2*shrinkNum);
                    }
                }
            }
            else if(pattern == 6)
            {
                for(int i = 0;i < triHeight;i++)
                {
                    for(int j = i;j < XieBian-i;j++)
                    {
                        nodes<<point(xcor-i-shrinkNum,ycor+j+2*shrinkNum);
                    }
                }
            }
            else if(pattern == 7)
            {
                for(int i = 0;i < triHeight;i++)
                {
                    for(int j = i;j < XieBian-i;j++)
                    {
                        nodes<<point(xcor+j+2*shrinkNum,ycor+i+shrinkNum);
                    }
                }
            }
            else if(pattern == 8)
            {
                int xcorPrime = xcor-((XieBian+1)>>1) ;
                int ycorPrime = ycor + shrinkNum +((XieBian+1)>>1) ;
                for(int i = 0;i < triHeight;i++)
                {
                    for(int j = i;j < XieBian-i;j++)
                    {
                        nodes<<point(xcorPrime+j,ycorPrime-i);
                    }
                }
            }
            return nodes;
        break;
        }
        //对角线平放的平四
        case 11:
        {
        //注释了以前错误的图形建模
            for(int i = 0;i < MiniLength - 2*shrinkNum;i++)
            {
                for(int j = 0;j < MiniLength - 2*shrinkNum;j++)
                {
                    nodes<<point(xcor-i - shrinkNum,ycor+i+j + 2*shrinkNum);
                }
            }
            return nodes;
//        int triHeight = (OddLength+1)>>1;
//        for(int i = 0;i < triHeight;i++)
//        {
//            for(int j = 0;j < OddLength;j++)
//            {
//                nodes<<point(xcor-i,ycor+i+j);
//            }
//        }
//        return nodes;
        break;
        }
        case 12:
        {
        //注释了以前错误的图形建模

            for(int i = 0;i < MiniLength - 2*shrinkNum;i++)
            {
                for(int j = 0;j < MiniLength - 2*shrinkNum;j++)
                {
                    nodes<<point(xcor+i+j + 2*shrinkNum,ycor+i +shrinkNum);
                }
            }
//        int triHeight = (OddLength+1)>>1;
//        for(int i = 0;i < triHeight;i++)
//        {
//            for(int j = 0;j < OddLength;j++)
//            {
//                nodes<<point(xcor+i+j,ycor+i);
//            }
//        }
            return nodes;
        break;
        }
        case 13:
        {
        //注释了以前错误的图形建模

            for(int i = 0;i < MiniLength - 2*shrinkNum;i++)
            {
                for(int j = 0;j < MiniLength - 2*shrinkNum;j++)
                {
                    nodes<<point(xcor-i+j,ycor+i +shrinkNum);
                }
            }
//        int triHeight = (OddLength+1)>>1;
//        for(int i = 0;i < triHeight;i++)
//        {
//            for(int j = 0;j < OddLength;j++)
//            {
//                nodes<<point(xcor-i+j,ycor+i);
//            }
//        }
            return nodes;
        break;
        }
        case 14:
        {
        //注释了以前错误的图形建模

            for(int i = 0;i < MiniLength - 2*shrinkNum;i++)
            {
                for(int j = 0;j < MiniLength - 2*shrinkNum;j++)
                {
                    nodes<<point(xcor+i + shrinkNum,ycor+i+j + 2*shrinkNum);
                }
            }
//        int triHeight = (OddLength+1)>>1;
//        for(int i = 0;i < triHeight;i++)
//        {
//            for(int j = 0;j < OddLength;j++)
//            {
//                nodes<<point(xcor+i,ycor+i+j);
//            }
//        }
            return nodes;
//        break;
        }
        //对角线斜放的平四
        case 15:
        {
            int triHeight = ((OddLength+1)>>1) - 2*shrinkNum;
            for(int i = 0;i < triHeight;i++)
            {
                for(int j = 0;j < OddLength - 2*shrinkNum;j++)
                {
                    nodes<<point(xcor-i+j,ycor+i +shrinkNum);
                }
            }

            return nodes;
        break;
        }
        case 16:
        {
            int triHeight = ((OddLength+1)>>1) - 2*shrinkNum;
            for(int i = 0;i < triHeight;i++)
            {
                for(int j = 0;j < OddLength - 2*shrinkNum;j++)
                {
                    nodes<<point(xcor+i +shrinkNum,ycor+i+j + 2*shrinkNum);
                }
            }

            return nodes;
        break;
        }
        case 17:
        {
            int triHeight = ((OddLength+1)>>1) - 2*shrinkNum;
            for(int i = 0;i < triHeight;i++)
            {
                for(int j = 0;j < OddLength - 2*shrinkNum;j++)
                {
                    nodes<<point(xcor-i - shrinkNum,ycor+i+j + 2*shrinkNum);
                }
            }

            return nodes;
        break;
        }
        case 18:
        {
            int triHeight = (OddLength+1)>>1 - 2*shrinkNum;
            for(int i = 0;i < triHeight;i++)
            {
                for(int j = 0;j < OddLength;j++)
                {
                    nodes<<point(xcor+i+j + 2*shrinkNum,ycor+i + 2*shrinkNum);
                }
            }

            return nodes;
        break;
        }
    }


}



point::point(int xin, int yin):x(xin),y(yin)
{

}
