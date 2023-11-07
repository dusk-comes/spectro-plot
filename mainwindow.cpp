#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setGeometry(400, 250, 542, 390);
    color_map = new QCPColorMap(ui->customPlot->xAxis, ui->customPlot->yAxis);

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%m:%s:%z");
    ui->customPlot->xAxis->setTicker(timeTicker);

    QCPColorGradient greenGradient;
    greenGradient.clearColorStops();
    greenGradient.setColorStopAt(0, QColor(0, 0, 0));
    greenGradient.setColorStopAt(1, QColor(0, 255, 0));
    color_map->setGradient(greenGradient);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::set_map_size(int nx, int ny)
{
    color_map->data()->setSize(nx, ny);
}

void MainWindow::set_map_range(double vx, double vy)
{
    color_map->data()->setRange(QCPRange(0, vx), QCPRange(0, vy));
}

void MainWindow::update(const SAMPLE_ARRAY &data)
{
    static std::size_t x = 0;

    for (std::size_t y = 0; y < data.size() - 1; ++y)
    {
        color_map->data()->setCell(x, y, data.at(y));
    }
    ++x;

    color_map->rescaleDataRange();
    ui->customPlot->rescaleAxes();
    show();
}
