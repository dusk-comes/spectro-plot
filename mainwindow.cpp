#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setGeometry(400, 250, 542, 390);
    color_map = new QCPColorMap(ui->customPlot->xAxis, ui->customPlot->yAxis);
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

void MainWindow::set_data(std::vector<std::vector<double> > data)
{
    set_map_size(data.size(), data.front().size());
    for (std::size_t x; x < data.size(); ++x)
    {
        for(std::size_t y; y < data.front().size(); ++y)
        {
            color_map->data()->setCell(x, y, data.at(x).at(y));
        }
    }
}
