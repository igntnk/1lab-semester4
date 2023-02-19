#include "functiongraph.h"

FunctionGraph::FunctionGraph(QWidget* parent):
    QLabel(parent)
{
    this->setMinimumSize(size,size);

    for(int c=0;c<4;c++)
    {
        changePar.push_back(1);
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////Numeric degrees setting
    for(int c=0;c<11;c++)
    {
        int deaderX = ((c-5)*size/11)/scale+size/11*scrollShifterX;
        int deaderY = ((c-5)*size/11)/scale+size/11*scrollShifterY;
        degreesX.push_back(new QLabel(this));
        degreesX[c]->setFont(QFont("Arial",size/57));
        degreesX[c]->setText(QString::number(deaderX));
        degreesY.push_back(new QLabel(this));
        degreesY[c]->setFont(QFont("Arial",size/57));
        degreesY[c]->setText(QString::number(deaderY));
        degreesX[c]->setGeometry(c*size/11+10,centerY-36,50,50);
        degreesY[c]->setGeometry(centerX+10,c*size/11,50,50);
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////X and Y letters setting
    markerX = new QLabel(this);
    markerY = new QLabel(this);
    markerX->setText("X");
    markerY->setText("Y");
    markerX->setFont(QFont("Arial", size/40));
    markerY->setFont(QFont("Arial", size/40));
    markerX->setGeometry(size-20,centerY,20,20);
    markerY->setGeometry(centerX-20,10,20,20);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void FunctionGraph::setMousePoint(const QPointF& refer)
{
    mouseEvent = refer;
    mouseMoveEvent();
}
void FunctionGraph::setMousePress(const QPointF& refer)
{
    //mousePress = refer;
    controllX=centerX-refer.x();
    controllY=centerY-refer.y();
}
void FunctionGraph::setHitChecker(bool refer){pressOnRect = refer;}
bool FunctionGraph::getHitChecker(){return pressOnRect;}
void FunctionGraph::setChangePar(float refer,int par)
{
    changePar[par] = refer;
    mouseMoveEvent();
}

void FunctionGraph::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter drawer(this);
    doPainting(&drawer);
}

void FunctionGraph::doPainting(QPainter *drawer)
{
    drawer->setRenderHint(QPainter::Antialiasing);//Render mode

    QPainterPath borderBack;
    QPainterPath borderMain;
    QPen pen;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////Rounded rectangle fill
    pen.setColor(QColor(191, 177, 142));
    pen.setWidth(0);
    drawer->setPen(pen);
    borderBack.addRoundedRect(QRectF(QPointF(0,0),QSizeF(size,size)),size/12,size/12);
    drawer->fillPath(borderBack,QColor(242, 234, 216));
    drawer->drawPath(borderBack);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////Coordinate lines draw
    pen.setColor(QColor(130,2,2));
    pen.setWidth(2);
    pen.setStyle(Qt::DashLine);
    drawer->setPen(pen);
    if(centerY>=0 and centerY <= size)
    {
        drawer->drawLine(0,centerY,size,centerY);
    }
    if(centerX>=0 and centerX<=size)
    {
        drawer->drawLine(centerX,0,centerX,size);
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////Draw funtion graph
    pen.setColor(QColor(150,2,2));
    pen.setWidth(3);
    pen.setStyle(Qt::SolidLine);
    drawer->setPen(pen);
    QPainterPath path;
    int checker = 0;
    for(int x=-centerX-size;x<-centerX/2+size;x++)
    {
        double functionResult = (changePar[0]*pow(x,3)+changePar[1]*pow(x,2)+changePar[2]*x+changePar[3])/scale;

        for(int y=centerY-size*2;y<=size+centerY;y++)
        {
            if(functionResult >= y-1 and functionResult <= y+1)
            {
                checker++;
                if(checker==1)
                {
                    path.moveTo(x+centerX,-y+centerY);
                }
                else
                {
                    path.lineTo(x+centerX,-y+centerY);
                }
            }
        }
    }
    drawer->drawPath(path);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////Rectangle border
    pen.setColor(QColor(242, 234, 216));
    pen.setWidth(8);
    drawer->setPen(pen);
    borderMain.addRoundedRect(QRectF(QPointF(0,0),QSizeF(size,size)),size/12,size/12);
    drawer->drawPath(borderMain);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void FunctionGraph::mouseMoveEvent()
{
    int checkScrollSideX =centerX;
    int checkScrollSideY =centerY;
    if(mouseEvent.x() >= 0 and mouseEvent.x() < size and
            mouseEvent.y() > 0 and mouseEvent.y() < size and pressOnRect)
   {
        centerX=mouseEvent.x()+controllX;
        centerY=mouseEvent.y()+controllY;
        markerX->setGeometry(size-20,centerY,20,20);
        markerY->setGeometry(centerX-20,10,20,20);
        this->update();

    }

    if(centerY>=0 and centerY <= size){markerX->setVisible(true);}
    else{markerX->setVisible(false);}

    if(centerX>=0 and centerY<=size){markerY->setVisible(true);}
    else{markerY->setVisible(false);}


    for(int c=0;c<11;c++)
    {
        degreesX[c]->setGeometry((c+scrollShifterX)*size/11+10+centerX-size/2,centerY-36,50,50);
        degreesY[c]->setGeometry(centerX+10,(c+scrollShifterY)*size/11+centerY-size/2,50,50);

        if(degreesX[c]->geometry().x()<0 and centerX<checkScrollSideX)
        {
            ++scrollShifterX;
        }
        else if(degreesX[c]->geometry().x()>size and centerX>checkScrollSideX)
        {
            --scrollShifterX;
        }
        int deaderX = (((c-5)*size/11)+size/11*scrollShifterX)/scale;
        int deaderY = (((c-5)*size/11)+size/11*scrollShifterY)/scale;
        degreesX[c]->setText(QString::number(deaderX));

        if(degreesY[c]->geometry().y()>size and centerY>checkScrollSideY)
        {
            --scrollShifterY;
        }
        else if(degreesY[c]->geometry().y()<0 and centerY<checkScrollSideY)
        {
            ++scrollShifterY;
        }
        degreesY[c]->setText(QString::number(deaderY));

        if(centerY<0 or centerY>size){degreesX[c]->setVisible(false);}
        else{degreesX[c]->setVisible(true);}

        if(centerX<0 or centerX>size){degreesY[c]->setVisible(false);}
        else{degreesY[c]->setVisible(true);}
    }
}

