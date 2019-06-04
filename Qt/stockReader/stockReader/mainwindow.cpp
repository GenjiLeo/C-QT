#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    date= ui->currentDate->text();
    datelength=5;
}

MainWindow::~MainWindow()
{
    delete ui;
}

//We need the arrays of stocks to read, for how long, and a start date.
void MainWindow::readCSV(bool * chosen, int& length, QString &date, QString &dateToEnd){


    //qDebug()<<"DateToEnd"<< dateToEnd;
    if(chart!=0){
       chart->removeAllSeries();
       m_tooltip=0;
    }
       bool datePast = false;
       bool dateEnd = false;
       bool oneFound=false;
       QDateTime moment;
       QDateTime currentDate = QDateTime::fromString(date,"yyyy-MM-dd");
       QDateTime endDate = QDateTime::fromString(dateToEnd,"yyyy-MM-dd");
      QFile* files = new QFile[5];
      QLineSeries* series = new QLineSeries[5];
      files[0].setFileName("../NASDAQ100.csv");
      files[1].setFileName("../SP500.csv");
      files[2].setFileName("../DJCA.csv");
      files[3].setFileName("../RU3000TR.csv");
      files[4].setFileName("../WILL5000IND.csv");

    for(int i = 0; i < 5 ; ++i){
      if(chosen[i]){
         if (files[i].open(QIODevice::ReadOnly)) {
            datePast=false;
            dateEnd=false;
            // Qfiles[i] files[i]("../NASDAQ100.csv");
              series = new QLineSeries();

                QTextStream in(&files[i]);
                //qDebug()<<"I'm in";
                while (!in.atEnd() && !dateEnd) {

                    QStringList data;
                    QStringList dates;
                    QString line = files[i].readLine();


                    int pos = line.lastIndexOf(QChar('\r'));
                    data.append(line.left(pos).split(','));
                    //qDebug()<<data[0]; //date
                    //qDebug()<<data[1]; //value

                    dates = data[0].split("-",QString::SkipEmptyParts);


                    moment = QDateTime::fromString(data[0],"yyyy-MM-dd");
                    //qDebug()<<"moment"<< moment;
                    if(moment.toString()==currentDate.toString()){//We iterated and found the start date
                        datePast=true;
                        oneFound=true;
                        //qDebug()<<"Date " <<currentDate.toString()<<" found";
                    }
                    if(moment.date()>=endDate.date())
                        dateEnd=true;

                    if(moment.isValid() && data[1].toDouble()>0){
                       if(datePast){
                         //qDebug()<<"Adding value";
                        series->append(moment.toMSecsSinceEpoch(), data[1].toDouble());
                       }
                    }
                }
                files[i].close();
                switch(i){
                case 0: seriesNasdaq=series; break;
                case 1: seriesSp500=series; break;
                case 2: seriesDow=series; break;
                case 3: seriesRu3000=series; break;
                case 4: seriesWil5000=series; break;
                default: break;


                }
            }
            }

      }

        if(oneFound)
           updateChart(chosen);
        else {
            QMessageBox dial;
            dial.setText("The date/stocks combination you were looking for has not been found!");
            dial.setIcon(QMessageBox::Warning);
            dial.setWindowTitle("Failure!");
            dial.exec();
        }
       }







void MainWindow::updateChart(bool * chosen){
        chart = new QChart();


    QDateTimeAxis *axisX = new QDateTimeAxis();
    axisX->setFormat("yy-MM-dd");
    axisX->setRange(QDateTime::fromString(date),QDateTime::fromString(dateEnd));
    chart->addAxis(axisX,Qt::AlignBottom);
    QValueAxis *axisY = new QValueAxis();
    //qDebug()<<"Ticks: "<<axisY->tickCount();
    axisY->setRange(minRange,maxRange);
    axisY->setTickCount(10);
    chart->addAxis(axisY,Qt::AlignLeft);



        if(chosen[0]==true){
            chart->addSeries(seriesNasdaq);
            //qDebug()<<"I'm adding Nasdaq";
            seriesNasdaq->attachAxis(axisX);
            seriesNasdaq->attachAxis(axisY);
            seriesNasdaq->setName("Nasdaq");
           // seriesNasdaq->setPointLabelsVisible(true); Bad looking
            //seriesNasdaq->setUseOpenGL(true);

            connect(seriesNasdaq,&QLineSeries::hovered,this,&MainWindow::tooltip,Qt::UniqueConnection);
        }
        if(chosen[1]){
            chart->addSeries(seriesSp500);
            //qDebug()<<"I'm adding Sp";
            seriesSp500->attachAxis(axisX);
            seriesSp500->attachAxis(axisY);
            seriesSp500->setName("Sp500");
           // seriesSp500->setUseOpenGL(true);
            connect(seriesSp500,&QLineSeries::hovered,this,&MainWindow::tooltip,Qt::UniqueConnection);
        }
        if(chosen[2]){
            chart->addSeries(seriesDow);
            //qDebug()<<"I'm adding Dow";
            seriesDow->attachAxis(axisX);
            seriesDow->attachAxis(axisY);
            seriesDow->setName("Dow Jones");

            connect(seriesDow,&QLineSeries::hovered,this,&MainWindow::tooltip,Qt::UniqueConnection);
        }
        if(chosen[3]){
            chart->addSeries(seriesRu3000);
            //qDebug()<<"I'm adding Ru";
            seriesRu3000->attachAxis(axisX);
            seriesRu3000->attachAxis(axisY);
            seriesRu3000->setName("Ru3000");
            connect(seriesRu3000,&QLineSeries::hovered,this,&MainWindow::tooltip,Qt::UniqueConnection);

        }
        if(chosen[4]){
            chart->addSeries(seriesWil5000);
            //qDebug()<<"I'm adding Wil";
            seriesWil5000->attachAxis(axisX);
            seriesWil5000->attachAxis(axisY);
            seriesWil5000->setName("Wil5000");
            connect(seriesWil5000,&QLineSeries::hovered,this,&MainWindow::tooltip,Qt::UniqueConnection);
        }



        ui->graphicsView->setChart(chart);
        //Ci permette di aumentare e diminuire lo zoom sul grafico con Lclick/Rclick
        ui->graphicsView->setRubberBand(ui->graphicsView->RectangleRubberBand);



        chart->legend()->setShowToolTips(true); 
        chart->setAcceptHoverEvents(true);
        ui->graphicsView->update();




}

void MainWindow::tooltip(QPointF point, bool state)
{
    if (m_tooltip == 0)
        m_tooltip = new Callout(chart);



    QDate x =QDateTime::fromMSecsSinceEpoch(point.x()).date();
    ////qDebug()<<"x value: "<< x;
    QString y = QString::number(point.y());
     ////qDebug()<<"Y value: " << y;

     QString finalText= "Date: ";
     finalText.append(x.toString("yyyy-MM-dd"));
     finalText.append("\n");
     finalText.append("Value: ");
     finalText.append(y);

    if (state) {
        m_tooltip->setText(finalText);
        m_tooltip->setAnchor(point);
        m_tooltip->setZValue(11);
        m_tooltip->updateGeometry();
        m_tooltip->show();
    } else {
        m_tooltip->hide();
    }

}

void MainWindow::on_fiveYears_clicked()
{
    bool nasdaq=ui->nasdaq->isChecked();
    bool sp500=ui->sp500->isChecked();
    bool djca=ui->dowjones->isChecked();
    bool ru3000=ui->russel->isChecked();
    bool wil5000=ui->wilshire->isChecked();
    datelength=1825;

    bool* stocks= new bool[5];
    stocks[0]=nasdaq;
    stocks[1]=sp500;
    stocks[2]=djca;
    stocks[3]=ru3000;
    stocks[4]=wil5000;
    date= ui->currentDate->text();
    QDate endDate= ui->currentDate->date().addYears(5);
    dateEnd=endDate.toString("yyyy-MM-dd");
    readCSV(stocks,datelength,date,dateEnd);

}

void MainWindow::on_oneYear_clicked()
{
    bool nasdaq=ui->nasdaq->isChecked();
    bool sp500=ui->sp500->isChecked();
    bool djca=ui->dowjones->isChecked();
    bool ru3000=ui->russel->isChecked();
    bool wil5000=ui->wilshire->isChecked();
    datelength=365;

    bool* stocks= new bool[5];
    stocks[0]=nasdaq;
    stocks[1]=sp500;
    stocks[2]=djca;
    stocks[3]=ru3000;
    stocks[4]=wil5000;
    date= ui->currentDate->text();

    QDate endDate= ui->currentDate->date().addYears(1);
    dateEnd=endDate.toString("yyyy-MM-dd");
    readCSV(stocks,datelength,date,dateEnd);

}

void MainWindow::on_sixMonths_clicked()
{
    bool nasdaq=ui->nasdaq->isChecked();
    bool sp500=ui->sp500->isChecked();
    bool djca=ui->dowjones->isChecked();
    bool ru3000=ui->russel->isChecked();
    bool wil5000=ui->wilshire->isChecked();
    datelength=30*6;

    bool* stocks= new bool[5];
    stocks[0]=nasdaq;
    stocks[1]=sp500;
    stocks[2]=djca;
    stocks[3]=ru3000;
    stocks[4]=wil5000;
    date= ui->currentDate->text();

    QDate endDate= ui->currentDate->date().addMonths(6);
    dateEnd=endDate.toString("yyyy-MM-dd");
    readCSV(stocks,datelength,date,dateEnd);

}

void MainWindow::on_oneMonth_clicked()
{
    bool nasdaq=ui->nasdaq->isChecked();
    bool sp500=ui->sp500->isChecked();
    bool djca=ui->dowjones->isChecked();
    bool ru3000=ui->russel->isChecked();
    bool wil5000=ui->wilshire->isChecked();
    datelength=30;

    bool* stocks= new bool[5];
    stocks[0]=nasdaq;
    stocks[1]=sp500;
    stocks[2]=djca;
    stocks[3]=ru3000;
    stocks[4]=wil5000;
    date= ui->currentDate->text();

    QDate endDate= ui->currentDate->date().addMonths(1);
    dateEnd=endDate.toString("yyyy-MM-dd");
    readCSV(stocks,datelength,date,dateEnd);


}

void MainWindow::on_fiveDays_clicked()
{
    bool nasdaq=ui->nasdaq->isChecked();
    bool sp500=ui->sp500->isChecked();
    bool djca=ui->dowjones->isChecked();
    bool ru3000=ui->russel->isChecked();
    bool wil5000=ui->wilshire->isChecked();
    datelength=5;

    bool* stocks= new bool[5];
    stocks[0]=nasdaq;
    stocks[1]=sp500;
    stocks[2]=djca;
    stocks[3]=ru3000;
    stocks[4]=wil5000;
    date= ui->currentDate->text();

    QDate endDate= ui->currentDate->date().addDays(5);
    dateEnd=endDate.toString("yyyy-MM-dd");
    readCSV(stocks,datelength,date,dateEnd);


}



void MainWindow::on_next_clicked()
{
    bool nasdaq=ui->nasdaq->isChecked();
    bool sp500=ui->sp500->isChecked();
    bool djca=ui->dowjones->isChecked();
    bool ru3000=ui->russel->isChecked();
    bool wil5000=ui->wilshire->isChecked();


    bool* stocks= new bool[5];
    stocks[0]=nasdaq;
    stocks[1]=sp500;
    stocks[2]=djca;
    stocks[3]=ru3000;
    stocks[4]=wil5000;
    ui->currentDate->setDate(ui->currentDate->date().addDays(datelength));
    date = ui->currentDate->text();
    //qDebug()<<"Current date: "<< date;

    if(ui->currentDate->date()==ui->currentDate->maximumDate()){
       // //qDebug()<<"End of the ride buddy";
        QMessageBox dial;
        dial.setText("Maximum allowed date reached");
        dial.setIcon(QMessageBox::Warning);
        dial.setWindowTitle("Failure!");
        dial.exec();
    }
    else{
        QDate endDate= ui->currentDate->date().addDays(datelength);
        dateEnd=endDate.toString("yyyy-MM-dd");
        readCSV(stocks,datelength,date,dateEnd);
    }

}

void MainWindow::on_previous_clicked()
{
    bool nasdaq=ui->nasdaq->isChecked();
    bool sp500=ui->sp500->isChecked();
    bool djca=ui->dowjones->isChecked();
    bool ru3000=ui->russel->isChecked();
    bool wil5000=ui->wilshire->isChecked();


    bool* stocks= new bool[5];
    stocks[0]=nasdaq;
    stocks[1]=sp500;
    stocks[2]=djca;
    stocks[3]=ru3000;
    stocks[4]=wil5000;
    ui->currentDate->setDate(ui->currentDate->date().addDays(-datelength));
    date = ui->currentDate->text();

    if(ui->currentDate->date()==ui->currentDate->minimumDate()){
        ////qDebug()<<"Too early to ride buddy";
        QMessageBox dial;
        dial.setText("Minimum allowed date reached");
        dial.setIcon(QMessageBox::Warning);
        dial.setWindowTitle("Failure!");
        dial.exec();
    }
    else{
        QDate endDate= ui->currentDate->date().addDays(datelength);
        dateEnd=endDate.toString("yyyy-MM-dd");
        readCSV(stocks,datelength,date,dateEnd);
      }
}

void MainWindow::on_min_valueChanged(int arg1)
{
    if(arg1<maxRange)
        minRange=arg1;
}

void MainWindow::on_max_valueChanged(int arg1)
{
    if(arg1>minRange)
        maxRange=arg1;
}
