#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qcustomplot.h>
#include <queue>
#include <vector>

#include "iobserver.hpp"
#include "common.hpp"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public iobserver
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void set_map_size(int nx, int ny);
    void set_map_range(double vx, double vy);
    void update(const SAMPLE_ARRAY&) override;

public slots:
    void update_slot(const SAMPLE_ARRAY&);

private:
    Ui::MainWindow *ui;
    QCPColorMap *color_map;
};

Q_DECLARE_METATYPE(SAMPLE_ARRAY);
#endif // MAINWINDOW_H
