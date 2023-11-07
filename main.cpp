#include <QApplication>

#include "mainwindow.hpp"
#include "data_manager.hpp"
#include "spectrogram_builder.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::shared_ptr<MainWindow> mw = std::make_shared<MainWindow>(nullptr);

    SAMPLE_SIZE buffer_size = 512;
    double overlapping_coef = 0.5;
    spectrogram_builder builder;
    std::shared_ptr<spectrogram> sg = builder
                                          .set_data_length(buffer_size)
                                          .set_overlapping_coefficient(overlapping_coef)
                                          .build();
    sg->prepare();

    const std::filesystem::path &filename("resources/test.wav");
    data_manager dm(filename);
    dm.setup_core(sg);
    dm.add_listener(task::display, mw);

    mw->set_map_size(dm.stripes(), dm.bins());
    mw->set_map_range(dm.time_domain(), dm.freq_domain());

    dm.play(buffer_size);

    return a.exec();
}
