#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "callout.h"

#include <QMainWindow>
#include <QtCharts>

#include <QDebug>
#include <QFile>

using namespace QtCharts;

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void readCSV(bool* chosen, int& length, QString &date,QString &dateToEnd);
    void tooltip(QPointF point, bool state);
    void updateChart(bool * chosen);



    int minRange=0;
    int maxRange=9000;
     QLineSeries *seriesNasdaq=0;
     QLineSeries *seriesDow=0;
     QLineSeries *seriesSp500=0;
     QLineSeries *seriesWil5000=0;
     QLineSeries *seriesRu3000=0;
     int datelength;
     QString date;
     QString dateEnd;
     QGraphicsSimpleTextItem *m_coordX;
     QGraphicsSimpleTextItem *m_coordY;
     Callout *m_tooltip= 0;
     QChart *chart =0;



private slots:

    void on_fiveYears_clicked();

    void on_oneYear_clicked();

    void on_sixMonths_clicked();

    void on_oneMonth_clicked();

    void on_fiveDays_clicked();


    void on_next_clicked();

    void on_previous_clicked();

    void on_min_valueChanged(int arg1);

    void on_max_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
