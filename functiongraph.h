#include <QLabel>
#include <QLineEdit>
#include <vector>
#include <QPaintEvent>
#include <QPainter>
#include <QPainterPath>
#include <cmath>

#ifndef FUNCTIONGRAPH_H
#define FUNCTIONGRAPH_H


class FunctionGraph : public QLabel
{
    Q_OBJECT
public:
    FunctionGraph(QWidget* parent);

    void setMousePoint(const QPointF& refer);
    void setMousePress(const QPointF& refer);
    void setHitChecker(bool refer);
    bool getHitChecker();
    void setChangePar(float refer,int par);

private:

    QPointF mouseEvent;
    //QPointF mousePress;
    void paintEvent(QPaintEvent *event);
    void doPainting(QPainter* drawer);

    int size = 400;
    int scrollShifterX=0;
    int scrollShifterY=0;
    int centerX= size/2;// Graphic shift
    int centerY = size/2;
    float scale = 1;//Graphic scale
    int controllX;
    int controllY;

    bool pressOnRect = false;//Checker for rectangle hit

    QLabel* markerX;//Letters of coordinates
    QLabel* markerY;

    std::vector<QLabel*> degreesX;//Numerical divisions
    std::vector<QLabel*> degreesY;
    std::vector<int> counterX;
    std::vector<int> counterY;
    std::vector<float> changePar;

    void mouseMoveEvent();
};

#endif // FUNCTIONGRAPH_H
