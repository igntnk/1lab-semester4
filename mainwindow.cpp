#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setMinimumSize(600,400);
    this->setWindowTitle("FunctionGraphic");

    functionText = new QLabel(this);//Function text setting
    functionText->setGeometry(10,10,150,20);
    functionText->setText("y=ax +bx+cx+d");
    functionText->setFont(QFont("Arial", 13));
    QLabel* twoText = new QLabel(this);
    twoText->setText("2");
    twoText->setFont(QFont("Arial",9));
    twoText->setGeometry(46,5,15,15);

    for(int c=0;c<4;c++)//QLineEdit setting
    {
        changePar.push_back(new QLineEdit(this));
        changePar[c]->setGeometry(25,35+25*c,40,20);
        changePar[c]->setText("1");

        parName.push_back(new QLabel(this));
        parName[c]->setText(QChar(97+c));
        parName[c]->setGeometry(10,35+25*c,20,20);
    }

    markerX = new QLabel(this);//Letter X and Y near of cordinate lines
    markerY = new QLabel(this);
    markerX->setText("X");
    markerY->setText("Y");
    markerX->setFont(QFont("Arial", 12));
    markerY->setFont(QFont("Arial", 12));
    markerX->setGeometry(shiftX_static+130,shiftY-18,20,20);
    markerY->setGeometry(shiftX+10,shiftY_static-150,20,20);

    connect(changePar[0],&QLineEdit::textChanged,this,&MainWindow::textChanged1);
    connect(changePar[1],&QLineEdit::textChanged,this,&MainWindow::textChanged2);
    connect(changePar[2],&QLineEdit::textChanged,this,&MainWindow::textChanged3);
    connect(changePar[3],&QLineEdit::textChanged,this,&MainWindow::textChanged4);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter drawer(this);
    doPainting(&drawer);
}

void MainWindow::doPainting(QPainter *drawer)
{
    drawer->setRenderHint(QPainter::Antialiasing);

    QPainterPath borderBack;
    QPainterPath borderMain;
    QPen pen;
    QRadialGradient shadow(QPointF(shiftX_static,shiftY_static),200);
    shadow.setColorAt(0, QColor(0,0,0,100));
    shadow.setColorAt(1, QColor(0,0,0,0));

    borderBack.addRoundedRect(QRectF(QPointF(shiftX_static-150,shiftY_static-150),QSizeF(350,350)),25,25);//Rectangle shadow
    pen.setColor(QColor(0,0,0,0));
    pen.setWidth(0);
    drawer->setPen(pen);
    drawer->fillPath(borderBack,QBrush(shadow));
    drawer->drawPath(borderBack);

    borderBack.clear();

    pen.setColor(QColor(191, 177, 142));//Rectangle background
    pen.setWidth(0);
    drawer->setPen(pen);
    borderBack.addRoundedRect(QRectF(QPointF(shiftX_static-150,shiftY_static-150),QSizeF(300,300)),25,25);
    drawer->fillPath(borderBack,QColor(242, 234, 216));
    drawer->drawPath(borderBack);

    pen.setColor(QColor(130,2,2));//Coordinate lines
    pen.setWidth(2);
    pen.setStyle(Qt::DashLine);
    drawer->setPen(pen);
    if(shiftY>=38 and shiftY <= 338)
    {
        drawer->drawLine(shiftX_static-150,shiftY,shiftX_static+150,shiftY);
    }
    if(shiftX>=250 and shiftX<=550)
    {
        drawer->drawLine(shiftX,shiftY_static-150,shiftX,shiftY_static+150);
    }

    pen.setColor(QColor(150,2,2));
    pen.setWidth(3);
    pen.setStyle(Qt::SolidLine);
    drawer->setPen(pen);

    QPainterPath path;//Graphic path
    int checker = 0;
    for(int x=-shiftX+250;x<-shiftX+550;x++)//Path's lines
    {
        double functionResult = changePar[0]->text().toDouble()*pow(x,2)+
                changePar[1]->text().toDouble()*(x)+
                changePar[2]->text().toDouble()*(x)+
                changePar[3]->text().toDouble();

        for(float y=shiftY-338;y<shiftY-38;y++)
        {
            if(functionResult >= y-0.5 and functionResult <= y+0.5)
            {
                checker++;
                if(checker==1)
                {
                    path.moveTo(x+shiftX,-y+shiftY);
                }
                else
                {
                    path.lineTo(x+shiftX,-y+shiftY);
                }
            }
        }
    }
    checker = 0;
    drawer->drawPath(path);

    pen.setColor(QColor(242, 234, 216));//Border line
    pen.setWidth(8);
    drawer->setPen(pen);
    borderMain.addRoundedRect(QRectF(QPointF(shiftX_static-150,shiftY_static-150),QSizeF(300,300)),25,25);
    drawer->drawPath(borderMain);
}

void MainWindow::textChanged1(const QString &text)
{
    changePar[0]->setText(text);
    this->update();
}

void MainWindow::textChanged2(const QString &text)
{
    changePar[1]->setText(text);
    this->update();
}

void MainWindow::textChanged3(const QString &text)
{
    changePar[2]->setText(text);
    this->update();
}

void MainWindow::textChanged4(const QString &text)
{
    changePar[3]->setText(text);
    this->update();
}

void MainWindow::mousePressEvent(QMouseEvent *eventPress)
{
    if(eventPress->pos().x() >= shiftX_static-150 and eventPress->pos().x() < shiftX_static+150 and
            eventPress->pos().y() > shiftY_static-150 and eventPress->pos().y() < shiftY_static+150)
    {
        pressOnRect = true;
        controllX = shiftX-eventPress->pos().x();
        controllY = shiftY-eventPress->pos().y();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *eventMove)
{
    if(eventMove->pos().x() >= shiftX_static-150 and eventMove->pos().x() < shiftX_static+150 and
            eventMove->pos().y() > shiftY_static-150 and eventMove->pos().y() < shiftY_static+150 and pressOnRect)
   {
        shiftX=eventMove->pos().x()+controllX;
        shiftY=eventMove->pos().y()+controllY;
        markerX->setGeometry(shiftX_static+130,shiftY-18,20,20);
        markerY->setGeometry(shiftX+10,shiftY_static-150,20,20);
        qDebug() << shiftX;
        this->update();
    }

    if(shiftY>=50 and shiftY <= 338)
    {
        markerX->setVisible(true);
        markerX->setGeometry(shiftX_static+130,shiftY-18,20,20);
    }
    else
    {
        markerX->setVisible(false);
    }

    if(shiftX>=250 and shiftX<=530)
    {
        markerY->setVisible(true);
        markerY->setGeometry(shiftX+10,shiftY_static-150,20,20);
    }
    else
    {
        markerY->setVisible(false);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *releaseEvent)
{
    pressOnRect = false;
}
