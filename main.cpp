#include <QApplication>

#include "mainwindow.hpp"
#include "model.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    model md("resources/test.wav", 8192U);
    md.calculate();

    MainWindow mw;
    mw.set_map_size(md.stripes(), md.bins());
    mw.set_map_range(md.stripes() * md.time_resolution().count(), md.bins() * md.freq_resolutions());
    mw.set_data(md.m_data_to_display);
    mw.show();
    return a.exec();
}
