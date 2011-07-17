#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include "wavelet3.h"
#include "fftw3.h"
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_canvas.h>
#include <qwt_symbol.h>
#include <qwt_text_label.h>
#include <qwt_legend.h>
#include <qwt_legend_item.h>
#include <qwt_plot_renderer.h>
#include <qwt_abstract_scale_draw.h>






using namespace std;

class QAction;
class QMenu;
class QWidget;



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

signals:
  //  void legendClicked(QwtPlotItem *);

private slots:
    void openFile();
    void loadFile(const QString &);
    void setCurrentFile(const QString &);
    void DWTdialog();
    void defaultSIG();
    void setDecom(int);
    void setWave(const QString &);
    void computeDWT();
    void enableIDWT();
    void setMode(const QString &);
    void setAppxMode(const QString &);
    void setExt(int);
    void* showmsg();
    void SIGplot(vector<double> &);
    void SWTplot(vector<double> &,vector<double> &, int, int);
    void lineplot(vector<double> &, int, double, double);
    void lineplotmod(vector<double> &, int);
    void qwtlineplot(vector<double> &, int,int);
    void DWT_SYMplot(vector<double> &,vector<double> &,int,vector<int> &);
    void DWT_PERplot(vector<double> &,vector<double> &, int );
    void* maxval(const vector<double> &, double &);
    void* minval(const vector<double> &, double &);
    void loadpoly();
    void loadreg();
    void loadreg2();
    void loadheavisine();
    void loadnoisyheavisine();
    void loadnoisybumps();
    void loadecg();
    bool eventFilter(QObject *, QEvent *);
    void APPXdialog();
    void DISPdialog();
    void setAppxCoef(int);
    void approximateSig();
    void findthresh(vector<double> , int , double& );
    void APPXplot(vector<double> &,vector<double> &);
    void wavedisp();
    void altflip(vector<double> &, vector<double> &);
    void iterorth(vector<double> &,vector<double>& , int, string );
    void ORTHplot(vector<double> &, vector<double> &);
    void iterbiorth(vector<double> &,vector<double> &,vector<double> &,vector<double> &,
                    vector<double>&,vector<double>& ,vector<double>& ,
                    vector<double>& ,int) ;
    void BIORTHplot(vector<double> &, vector<double> &,vector<double> &, vector<double> &);
    void filtdisp();
    void pointplot(vector<double> &, int );
    void freqdisp();
    void DENOISEdialog();
    void setDenoiseDecom(int);
    void setDenoiseWave(const QString &);
    void setDenoiseMode(const QString &);
    void signalDENOISE();
    void setDenoiseMethod(const QString &);
    void setDenoiseThresh(const QString &);
    void OUTPUTconsole();
    int sgn(double);
    void median(vector<double> &,double &);
    void DENOISEplot(vector<double> &,vector<double> &);
    void l2norm(const vector<double> &, double &) ;
    void minindex(const vector<double> &, int & );
    void* freq_one(vector<double> &, vector<double> &) ;
    void filtfreq();
    void about();
    void reportDWT();
    void saveDWT();
    void saveAPPX();
    void saveAPPXCOEF();
    void saveDENOISE();
    void saveDENOISECOEF();
    void newPlot(QwtPlotItem *,bool);
    void newPlot_print();
    void savePLOT();
    void savePLOTPDF();
    void savePLOT2();
    void savePLOTPDF2();
    void fullPLOT();


protected:
     void mousePressEvent(QGraphicsSceneMouseEvent *);
     void mouseMoveEvent(QGraphicsSceneMouseEvent *);
     void mouseReleaseEvent(QGraphicsSceneMouseEvent *);



private:

    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();

 //   virtual void mousePressEvent(QGraphicsSceneMouseEvent *);
 //   virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *);

    QMenu *fileMenu;
    QMenu *signalMenu;
    QMenu *appMenu;
    QMenu *helpMenu;

    QToolBar *fileToolBar;
    QAction *exitAct;
    QAction *openAct;
    QAction *regular2Act;
    QAction *regularAct;
    QAction *polyAct;
    QAction *heavisineAct;
    QAction *noisyheavisineAct;
    QAction *appxAct;
    QAction *noisybumpsAct;
    QAction *ecgAct;
    QAction *aboutAct;

    QRubberBand *rubberband;

    QWidget *dwtdial;
    QWidget *denoisedial;

    QPoint origin;
    bool active;



    QPushButton *dwtbutton;
//    QPushButton *idwtbutton;
    QCheckBox *idwtbutton;
    QComboBox *extension;
    QVBoxLayout *vlayout;
    QVBoxLayout *vlayout2;
    QVBoxLayout *vlayout3;
    QHBoxLayout *mwlay;
    QPushButton *appxbutton;
    QPushButton *filtdispbutton;
    QPushButton *wavedispbutton;
    QPushButton *freqdispbutton;
    QPushButton *filtfreqbutton;
    QPushButton *denoisebutton;
    QPushButton* dwtoutbutton;
    QPushButton* fullgraphbutton;
    QPushButton* freqoutbutton;
    QPushButton* appxoutbutton;
    QPushButton* appxcoefbutton;
    QPushButton* denoiseoutbutton;
    QPushButton* denoisecoefbutton;
    QPushButton *reportbutton;
    QComboBox *wave;
    QComboBox *wave2;

    QGraphicsScene *scene;
    QGraphicsView *view;
    QObject* obj;
    QEvent* event;

    QwtPlotCanvas *canvas;
    QwtPlot *printplot;
    QwtPlot *printplot2;
    QwtPlotItem* printcurve;
//    friend class mouseitem;



};

#endif // MAINWINDOW_H


