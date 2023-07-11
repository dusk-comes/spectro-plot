#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void value_added(int value);

private slots:
    void real_time_data();
    void tweak_scrollbar(int value);

private:
    Ui::MainWindow *ui;
    QTimer dataTimer;

    void setup_plot();
};
#endif // MAINWINDOW_H
