#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setMinimumSize(800,600);
    this->setWindowTitle("FunctionGraphic");

    graphPos = QPoint(250,40);
    functionPanel = new FunctionGraph(this);
    functionPanel->setGeometry(QRect(graphPos,QSize(402,402)));
    QGraphicsDropShadowEffect* rectangleShadow = new QGraphicsDropShadowEffect();
    rectangleShadow->setColor(QColor(0,0,0,40));
    rectangleShadow->setOffset(QPointF(10,10));
    rectangleShadow->setBlurRadius(90);
    functionPanel->setGraphicsEffect(rectangleShadow);

    functionText = new QLabel(this);//Function text setting
    functionText->setGeometry(10,10,150,20);
    functionText->setText("y=ax +bx +cx+d");
    functionText->setFont(QFont("Arial", 13));
    QLabel* threeText = new QLabel(this);
    threeText->setText("3");
    QLabel* twoText = new QLabel(this);
    twoText->setText("2");
    threeText->setFont(QFont("Arial",9));
    threeText->setGeometry(45,5,15,15);
    twoText->setFont(QFont("Arial",9));
    twoText->setGeometry(76,5,15,15);

    for(int c=0;c<4;c++)//QLineEdit setting
    {
        changePar.push_back(new QLineEdit(this));
        changePar[c]->setGeometry(25,35+25*c,40,20);
        changePar[c]->setText("1");

        parName.push_back(new QLabel(this));
        parName[c]->setText(QChar(97+c));
        parName[c]->setGeometry(10,35+25*c,20,20);
    }

    connect(changePar[0],&QLineEdit::textChanged,this,&MainWindow::textChanged1);
    connect(changePar[1],&QLineEdit::textChanged,this,&MainWindow::textChanged2);
    connect(changePar[2],&QLineEdit::textChanged,this,&MainWindow::textChanged3);
    connect(changePar[3],&QLineEdit::textChanged,this,&MainWindow::textChanged4);
}

void MainWindow::textChanged1(const QString &text)
{
    changePar[0]->setText(text);
    functionPanel->setChangePar(changePar[0]->text().toFloat(),0);
    this->update();
}

void MainWindow::textChanged2(const QString &text)
{
    changePar[1]->setText(text);
    functionPanel->setChangePar(changePar[1]->text().toFloat(),1);
    this->update();
}

void MainWindow::textChanged3(const QString &text)
{
    changePar[2]->setText(text);
    functionPanel->setChangePar(changePar[2]->text().toFloat(),2);
    this->update();
}

void MainWindow::textChanged4(const QString &text)
{
    changePar[3]->setText(text);
    functionPanel->setChangePar(changePar[3]->text().toFloat(),3);
    this->update();
}

void MainWindow::mousePressEvent(QMouseEvent *eventPress)
{
    if(eventPress->pos().x() > functionPanel->geometry().x() and
            eventPress->pos().x() < functionPanel->geometry().x()+functionPanel->geometry().width() and
            eventPress->pos().y() > functionPanel->geometry().y() and
            eventPress->pos().y() < functionPanel->geometry().y()+functionPanel->geometry().height())
    {
        functionPanel->setHitChecker(true);
        functionPanel->setMousePress(eventPress->pos()-graphPos);
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *eventMove)
{
    if(eventMove->pos().x() > functionPanel->geometry().x() and
            eventMove->pos().x() < functionPanel->geometry().x()+functionPanel->geometry().width() and
            eventMove->pos().y() > functionPanel->geometry().y() and
            eventMove->pos().y() < functionPanel->geometry().y()+functionPanel->geometry().height() and functionPanel->getHitChecker())
    {
        functionPanel->setMousePoint(eventMove->pos()-graphPos);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *releaseEvent)
{
    functionPanel->setHitChecker(true);
}
