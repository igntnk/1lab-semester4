#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <vector>
#include <QPaintEvent>
#include <QPainter>
#include <QPainterPath>
#include <QGraphicsDropShadowEffect>
#include <cmath>
#include "functiongraph.h"

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    FunctionGraph* functionPanel;
    QPoint graphPos;

    QLabel* functionText;//Visible tex of function

    std::vector<QLineEdit*> changePar;//Places to change parameters
    std::vector<QLabel*> parName;//Parameters' names

    void textChanged1(const QString &text);
    void textChanged2(const QString &text);
    void textChanged3(const QString &text);
    void textChanged4(const QString &text);

    void mouseMoveEvent(QMouseEvent *eventMove);
    void mousePressEvent(QMouseEvent *eventPress);
    void mouseReleaseEvent(QMouseEvent *releaseEvent);
};
#endif // MAINWINDOW_H
