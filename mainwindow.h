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
    int shiftX= 400;// Graphic shift
    int shiftY = 188;

    const int shiftX_static = 400;
    const int shiftY_static = 188;

    int controllX;
    int controllY;

    bool pressOnRect = false;

    QLabel* functionText;

    QLabel* markerX;
    QLabel* markerY;

    std::vector<QLineEdit*> changePar;
    std::vector<QLabel*> parName;

    void textChanged1(const QString &text);
    void textChanged2(const QString &text);
    void textChanged3(const QString &text);
    void textChanged4(const QString &text);

    void mouseMoveEvent(QMouseEvent *eventMove);
    void mousePressEvent(QMouseEvent *eventPress);
    void mouseReleaseEvent(QMouseEvent *releaseEvent);
};
#endif // MAINWINDOW_H
