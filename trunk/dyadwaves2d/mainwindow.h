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



private slots:
    void openFile2();
    void loadFile2(const QString &);
    void setCurrentFile(const QString &);
    void dispImage();
    void DWTdialog2();
    void setDecom(int);
    void setWave(const QString &);
    void computeDWT2();
    void dispSWT(vector<double> &,int ,int , int);
    void dispSWT_RGB(vector<double> &,vector<double> &,vector<double> &,int ,int , int);
    void dispDWT_PER(vector<vector<double> > &,int ,int , int);
    void dispDWT_PER_RGB(vector<vector<double> > &,vector<vector<double> > &,vector<vector<double> > &,
                         int ,int , int);

    void dispDWT_SYM(vector<double> &,int ,vector<int> );
    void dispDWT_SYM_RGB(vector<double> &,vector<double> &,vector<double> &,int ,vector<int> );
    void setGauss_size(int);

    void appx_coeff_per(vector<vector<double> > & );
    void dispAPPX_PER(vector<vector<double> > &);
    void dispAPPX_PER_RGB(vector<vector<double> > &,vector<vector<double> > &,vector<vector<double> > &);
    void dispDENOISE(vector<vector<double> > &);
    void dispDENOISE_RGB(vector<vector<double> > &,vector<vector<double> > &,vector<vector<double> > &);
    void enableIDWT();
    void setMode(const QString &);
    void setAppxMode(const QString &);
    void setFilter(const QString &);
    void imageFILTER2();
    void setExt(int);
    void setColProc(const QString &);
    void setColProc_appx(const QString &);
    void setColProc_denoise(const QString &);
    void* showmsg();
    void SIGplot(vector<double> &);
    void SWTplot(vector<double> &,vector<double> &, int, int);
    void lineplot(vector<double> &,int, int , double , double );
    void lineplotmod(vector<double> &, int);
    void lineplotmod2(vector<double> &, int, int,double,double);
    void errormessage();

    void DWT_SYMplot(vector<double> &,vector<double> &,int,vector<int> &);
    void DWT_PERplot(vector<double> &,vector<double> &, int );
    void* maxval(const vector<double> &, double &);
    void* minval(const vector<double> &, double &);
    void* maxval2(vector<vector<double> > &, double &);
    void* minval2(vector<vector<double> > &, double &);
    void loadlena();
    void loadnoisylena();
    void loadsnow();
    void loadmandril();
    bool eventFilter(QObject *, QEvent *);
    void APPXdialog2();
    void DISPdialog2();
    void setAppxCoef(int);
    void approximateSig2();
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
    void pointplot2(vector<double> &, int, int );
    void dispMEDIAN(vector<vector<double> > &);
    void dispMEDIAN_RGB(vector<vector<double> > &,vector<vector<double> > &,vector<vector<double> > &);

    void setIMAGE();
    void resetIMAGE();


    void freqdisp();
    void freqdisp2();
    void DENOISEdialog2();
    void setDenoiseDecom(int);
    void setDenoiseWave(const QString &);
    void setDenoiseMode(const QString &);
    void signalDENOISE2();
    void setDenoiseMethod(const QString &);
    void setDenoiseThresh(const QString &);
    void FILTERdialog2();
    void OUTPUTconsole2();
    int sgn(double);
    void median(vector<double> &,double &);
    void DENOISEplot(vector<double> &,vector<double> &);
    void l2norm(const vector<double> &, double &) ;
    void minindex(const vector<double> &, int & );
    void* freq_one(vector<double> &, vector<double> &) ;
    void filtfreq();
    void filtfreq2();
    void about();
    void reportDWT();
    void saveDWT2();
    void saveAPPX2();
    void saveAPPXCOEF();
    void saveDENOISE2();
    void saveFILTER2();
    void saveDENOISECOEF();
    void appx_coeff_sym(vector<double>  &);
    void setExt_dn(int);

    void conv2dfft(vector<double> &, int , int );
    void setColProc_filt(const QString &);
    void setSIGMA(const QString &);

    void appxFULLVIEW();
    void denoiseFULLVIEW();
    void filtFULLVIEW();
    void fftFULLVIEW();
    void dwtFULLVIEW();
    void setSWTVAL(int);

    void createEXP(vector<double> &, vector<int> &, int );
    void dwtEXPVIEW();

protected:
     void mousePressEvent(QGraphicsSceneMouseEvent *);



private:

    void createActions2();
    void createMenus2();
    void createToolBars2();
    void createStatusBar();

 //   virtual void mousePressEvent(QGraphicsSceneMouseEvent *);
 //   virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *);

    QImage image;
    QImage dwtimage;
    QImage fftimage;
    QImage approximatedimage;
    QImage denoisedimage;
    QImage filteredimage;
    QImage backupimage;
    QImage swtblur;
    QImage swth;
    QImage swtv;
    QImage swtd;
    QImage expimage;

    QMenu *fileMenu;
    QMenu *signalMenu;
    QMenu *appMenu;
    QMenu *helpMenu;

    QToolBar *fileToolBar;
    QAction *exitAct;
    QAction *openAct;
    QAction *appxAct;
    QAction *lenaAct;
    QAction *noisylenaAct;
    QAction *snowAct;
    QAction *mandrilAct;
    QAction *aboutAct;

    QWidget *dwtdial;
    QWidget *denoisedial;



    QPushButton *dwtbutton;
//    QPushButton *idwtbutton;
    QCheckBox *idwtbutton;
    QComboBox *extension;
    QComboBox *extension_dn;

    QComboBox *colorbox;
    QComboBox *colorbox_appx;
    QComboBox *colorbox_denoise;
    QComboBox *colorbox_filt;
    QVBoxLayout *vlayout;
    QVBoxLayout *vlayout2;
    QGridLayout *glayout;
    QVBoxLayout *vlayout3;
    QHBoxLayout *mwlay;
    QPushButton *appxbutton;
    QPushButton *filtdispbutton;
    QPushButton *wavedispbutton;
    QPushButton *freqdispbutton;
    QPushButton *filtfreqbutton;
    QPushButton *denoisebutton;
    QPushButton* dwtoutbutton;
    QPushButton* freqoutbutton;
    QPushButton* appxoutbutton;
    QPushButton* appxcoefbutton;
    QPushButton* denoiseoutbutton;
    QPushButton* filteroutbutton;
    QPushButton* denoisecoefbutton;
    QPushButton *reportbutton;
    QPushButton *filtimagebutton;
    QPushButton *setimagebutton;
    QPushButton *resetimagebutton;
    QPushButton *expdwtbutton;
    QComboBox *gaussbox;
    QComboBox *wave;
    QComboBox *wave2;
    QSpacerItem *spacer;
    QSpacerItem *vspacer;
    QSpacerItem *hspacer1;
    QSpacerItem *hspacer2;

    QLineEdit *sigmaline;
    QSignalMapper *signalMapper;


    QGraphicsScene *scene;
    QGraphicsView *view;
    QObject* obj;
    QEvent* event;

    //DWT_PER

    QComboBox *dwtlevels;

//    friend class mouseitem;



};

#endif // MAINWINDOW_H


