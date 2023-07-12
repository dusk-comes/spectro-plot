#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setGeometry(400, 250, 542, 390);
    setup_plot();

    connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));

    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(real_time_data()));
    dataTimer.start(0); // Interval 0 means to refresh as fast as possible

    connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(tweak_scrollbar(QCPRange)));
    connect(this, SIGNAL(drag(int)), this, SLOT(tweak_axis(int)));

    ui->customPlot->replot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::real_time_data()
{
    static QTime timeStart = QTime::currentTime();
    // calculate two new data points:
    double key = timeStart.msecsTo(QTime::currentTime())/1000.0; // time elapsed since start
    static double lastPointKey = 0;
    if (key-lastPointKey > 0.002) // at most add point every 2 ms
    {
      ui->customPlot->graph(0)->addData(key, qSin(key)+std::rand()/(double)RAND_MAX*1*qSin(key/0.3843));
      lastPointKey = key;
    }
    if (!ui->horizontalScrollBar->isSliderDown())
    {
        ui->customPlot->xAxis->setRange(key, 8, Qt::AlignRight);
        ui->customPlot->replot();
    }
    else
    {
        drag(ui->horizontalScrollBar->value());
    }

}

void MainWindow::tweak_scrollbar(QCPRange range)
{
    if (!ui->horizontalScrollBar->isSliderDown())
    {
        static auto data = ui->customPlot->graph(0)->data();
        auto size = data->size();
        auto last_value = data->at(size-1)->key;
        ui->horizontalScrollBar->setRange(0, qRound(last_value*100));
        ui->horizontalScrollBar->setValue(ui->horizontalScrollBar->maximum());
        ui->horizontalScrollBar->setPageStep(qRound(range.size() * 100));
    }
}

void MainWindow::tweak_axis(int value)
{
   if (qAbs(ui->customPlot->xAxis->range().center() - value/100.0) > 0.01)
   {
       ui->customPlot->xAxis->setRange(value/100.0, ui->customPlot->xAxis->range().size(), Qt::AlignCenter);
       ui->customPlot->replot();
   }
}

void MainWindow::setup_plot()
{
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setPen(QPen(QColor(40, 110, 255)));

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    ui->customPlot->xAxis->setTicker(timeTicker);
    ui->customPlot->axisRect()->setupFullAxesBox();
    ui->customPlot->yAxis->setRange(-1.2, 1.2);
}
