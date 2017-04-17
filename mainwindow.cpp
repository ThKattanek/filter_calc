#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <math.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

   // this->showMaximized();

    setWindowTitle("FilterCalcPro");

    in = (double*) fftw_malloc(sizeof(double) * 10000);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * 10000);
    p = fftw_plan_dft_r2c_1d(10000, in, out, FFTW_ESTIMATE);

    osc = new OscClass(44100);

    wave1 = new WaveBufferClass(44100);
    wave2 = new WaveBufferClass(44100);
    wave3 = new WaveBufferClass(44100);

    for(int x=0; x<44100; x++)
    {
        float a = 1.0 / 44100;
        float w1,w2,w3;

        /*
        w1 = sin(x*a*M_PI*4000);
        w2 = sin(x*a*M_PI*200);

        wave1->WriteData(x,w1);
        wave2->WriteData(x,w2);
        */

        wave3->WriteData(x,w1*w2);
    }

    //ui->widget->addTrace(wave1,QColor(255,0,0,255));
    //ui->widget->addTrace(wave2,QColor(0,255,0,255));
    //ui->widget->addTrace(wave3,QColor(0,0,255,255));


    qDebug("Trace1 - Min: %.4f - Max: %.4f",wave1->GetMin(), wave1->GetMax());
    qDebug("Trace2 - Min: %.4f - Max: %.4f",wave2->GetMin(), wave2->GetMax());
    qDebug("Trace3 - Min: %.4f - Max: %.4f",wave3->GetMin(), wave3->GetMax());



    ui->widget->addGraph();
    ui->widget->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
    ui->widget->graph(0)->setBrush(QBrush(QColor(255, 0, 0, 20))); // first graph will be filled with translucent blue

    ui->widget->addGraph();
    ui->widget->graph(1)->setPen(QPen(Qt::red)); // line color blue for first graph
    //ui->widget->graph(1)->setBrush(QBrush(QColor(0, 255, 0, 20))); // first graph will be filled with translucent blue

    ui->widget->xAxis2->setVisible(true);
    ui->widget->xAxis2->setTickLabels(false);
    ui->widget->yAxis2->setVisible(true);
    ui->widget->yAxis2->setTickLabels(false);

    ui->widget->xAxis->setLabel("t (sek)");
    ui->widget->yAxis->setLabel("U (V)");

    //ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    float a = 1.0 / 44100.0;
    for(int x=0; x<10000; x++)
    {
        wave1->WriteData(x,osc->GetNextSample());

        in[x] =  wave1->ReadData(x);
    }

    for(int x=0; x<1000; x++)
    {
        ui->widget->graph(0)->addData(x * a,in[x]);
    }

     fftw_execute(p);

    ui->widget->rescaleAxes();


    ui->widget_2->addGraph();
    ui->widget_2->graph(0)->setPen(QPen(Qt::black)); // line color blue for first graph
    ui->widget_2->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 50))); // first graph will be filled with translucent blue

    ui->widget_2->xAxis2->setVisible(true);
    ui->widget_2->xAxis2->setTickLabels(false);
    ui->widget_2->yAxis2->setVisible(true);
    ui->widget_2->yAxis2->setTickLabels(false);

    // X Achse Logaritmisch
    ui->widget_2->xAxis->grid()->setSubGridVisible(true);
    ui->widget_2->xAxis2->grid()->setSubGridVisible(true);
    ui->widget_2->xAxis->setScaleType(QCPAxis::stLogarithmic);
    //ui->widget_2->xAxis2->setScaleType(QCPAxis::stLogarithmic);



     ui->widget_2->xAxis->setNumberFormat("eb"); // e = exponential, b = beautiful decimal powers
     ui->widget_2->xAxis->setNumberPrecision(1); // makes sure "1*10^4" is displayed only as "10^4"
      ui->widget_2->xAxis->setRange(1e-2, 1e10);
      ui->widget_2->xAxis2->setRange(1e-2, 1e10);
      ui->widget_2->xAxis->setLabel("Frequenz (Hz)");
    // make range draggable and zoomable:
    ui->widget_2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);





     //ui->widget_2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);


    a = 44100  / 10000;

     for(int x=0; x<10000; x++)
     {
         float betrag = sqrt(pow(out[x][0],2.0) + pow(out[x][1],2.0));
        ui->widget_2->graph(0)->addData(x * a,betrag);
     }

     ui->widget_2->rescaleAxes();

     //ui->widget->graph(0)->setAntialiased(false);
     //ui->widget->graph(1)->setAntialiased(false);
     //ui->widget_2->graph(0)->setAntialiased(false);
}

MainWindow::~MainWindow()
{
    fftw_destroy_plan(p);
        fftw_free(in); fftw_free(out);

    delete osc;
    delete wave1;
    delete ui;
}

void MainWindow::on_actionAdd_triggered()
{

}

void MainWindow::on_actionDel_triggered()
{

}
