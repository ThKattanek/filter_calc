#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <fftw3.h>

#include "./wave_buffer_class.h"
#include "./osc_class.h"

#include "./qcustomplot/qcustomplot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionAdd_triggered();
    void on_actionDel_triggered();

private:
    Ui::MainWindow *ui;

    WaveBufferClass *wave1, *wave2, *wave3;

    OscClass *osc;

    double *in;
    fftw_complex *out;
    fftw_plan p;
};

#endif // MAINWINDOW_H
