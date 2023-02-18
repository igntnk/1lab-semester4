#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <vector>
#include <QPaintEvent>
#include <QPainter>
#include <QPainterPath>
#include <cmath>

#ifndef MAINWINDOW_H

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event);
    void doPainting(QPainter* drawer);

private:
    int scrollShifterX=0;
    int scrollShifterY=0;
    int shiftX= 400;// Graphic shift
    int shiftY = 188;
    float scale = 1;//Graphic scale

    const int shiftX_static = 400;//Static graphic shift for rectangles
    const int shiftY_static = 188;

    int controllX;//Varialables for mose drag
    int controllY;

    bool pressOnRect = false;//Checker for rectangle hit

    QLabel* functionText;//Visible tex of function

    QLabel* markerX;//Letters of coordinates
    QLabel* markerY;

    std::vector<QLineEdit*> changePar;//Places to change parameters
    std::vector<QLabel*> parName;//Parameters' names
    std::vector<QLabel*> degreesX;//Numerical divisions
    std::vector<QLabel*> degreesY;
    std::vector<int> counterX;
    std::vector<int> counterY;

    void textChanged1(const QString &text);
    void textChanged2(const QString &text);
    void textChanged3(const QString &text);
    void textChanged4(const QString &text);

    void mouseMoveEvent(QMouseEvent *eventMove);
    void mousePressEvent(QMouseEvent *eventPress);
    void mouseReleaseEvent(QMouseEvent *releaseEvent);
};
#endif // MAINWINDOW_H
