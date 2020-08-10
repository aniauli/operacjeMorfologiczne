#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QImage>
#include <QMouseEvent>
#include <QColorDialog>
#include <QColor>
#include "punkt.h"

namespace Ui {
    class MyWindow;
}

class MyWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MyWindow(QWidget *parent = 0);

    ~MyWindow();

private:
    Ui::MyWindow *ui;

    QImage *img;

    QColor backgroundColor;
    QColor foregroundColor;
    QColor temporaryColor;

    int szer;
    int wys;

    punkt pocz;
    punkt start;
    punkt stop;

    void czysc();
    void zamalujPiksel(punkt &piksel, QColor &color);
    void zmienObraz(char operacja);
    void pikselDylacja(punkt &piksel);
    void pikselErozja(punkt &piksel);

private slots:
    void on_cleanButton_clicked();
    void on_exitButton_clicked();
    void paintEvent(QPaintEvent*);
    void on_powrotButton_clicked();
    void on_dylacjaButton_clicked();
    void on_erozjaButton_clicked();
    void on_otwarcieButton_clicked();
    void on_zamkniecieButton_clicked();
};

#endif
