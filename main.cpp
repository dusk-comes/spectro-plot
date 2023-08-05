#include "mainwindow.hpp"
#include <vector>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.set_map_range(4, 4);

    std::vector<std::vector<double>> data;
    for (double i = 0.; i < 1; i += 0.01) {
        std::vector<double> stripe;
        for (double j = 0.; j < 1; j += 0.01) {
            double r = 3 * qSqrt(i * i + j * j) + 1e-2;
            double z = 2 * i * (qCos(r + 2) - qSin(r + 2)) / r;
            stripe.push_back(z);
        }
        data.push_back(stripe);
    }
    w.set_data(data);
    w.show();
    return a.exec();
}
