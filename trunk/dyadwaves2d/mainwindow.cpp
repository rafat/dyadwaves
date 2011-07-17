#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <QGraphicsScene>

using namespace std;

static QString curFile;
static int J = 1;
static string nm = "db1";
static string mode = "dwt_sym";
static int ext = 0;
static int ext_dn = 0;
static int n_coef = 25;
static vector<double> original_signal;
static string mode_appx = "dwt_per";
static string mode_denoise = "dwt_per";
static string nm_dn = "db1";
static string mode_color = "GrayScale (Faster)";
static string mode_color_appx = "GrayScale (Faster)";
static string mode_color_denoise = "GrayScale (Faster)";
static string mode_color_filt = "GrayScale (Faster)";
static int J_dn = 1;
static string dn_thresh = "soft";
static string dn_method = "visushrink";
static vector<double>  dwt_coefficients;
static vector<double> approximated_signal;
static vector<double> approximation_coefficients;
static vector<double> denoised_signal;
static vector<double> denoising_coefficients;
static int exec_time;
static vector<int> sym_coeff_length;
static vector<int> per_coeff_length;
static string im_filter = "Moving Average 3x3";
static int gauss_size = 3;
static double gauss_sigma = 4.0;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    createActions2();
    createMenus2();
    createToolBars2();
    DWTdialog2();
    DISPdialog2();
    APPXdialog2();
    DENOISEdialog2();
    FILTERdialog2();
    OUTPUTconsole2();

    dwtdial = new QWidget();
    dwtdial->setLayout(vlayout);

    QWidget *mw = new QWidget(this);

    scene = new QGraphicsScene();

  //  QGraphicsEllipseItem *ellipse= new QGraphicsEllipseItem(-10,-10,120,50);
    QPen pen(QColor(72,118,255), 1, Qt::SolidLine);
    QFont font;
    font.setPixelSize(40);
    font.setBold(false);
    font.setFamily("Times");

//    QGraphicsSimpleTextItem * io = scene->addSimpleText("WAVELET GUI");
//    io->setFont(font);
//    io->setBrush(Qt::white);


    QImage sig_img;
    sig_img.load(":/images/sig.bmp");

    QPixmap pix_sig;
    pix_sig.convertFromImage(sig_img);
    QGraphicsPixmapItem* item_sig = scene->addPixmap(pix_sig);
    item_sig->setPos(40,0);

    QImage ll1_img;
    ll1_img.load(":/images/ll1.bmp");

    QPixmap pix_ll1;
    pix_ll1.convertFromImage(ll1_img);
    QGraphicsPixmapItem* item_ll1 = scene->addPixmap(pix_ll1);
    item_ll1->setPos(40,150);

    scene->addLine(90,100,90,150,pen);

    QImage lh1_img;
    lh1_img.load(":/images/lh1.bmp");

    QPixmap pix_lh1;
    pix_lh1.convertFromImage(lh1_img);
    QGraphicsPixmapItem* item_lh1 = scene->addPixmap(pix_lh1);
    item_lh1->setPos(170,150);

    scene->addLine(90,100,220,150,pen);

    QImage hl1_img;
    hl1_img.load(":/images/hl1.bmp");

    QPixmap pix_hl1;
    pix_hl1.convertFromImage(hl1_img);
    QGraphicsPixmapItem* item_hl1 = scene->addPixmap(pix_hl1);
    item_hl1->setPos(300,150);

    scene->addLine(90,100,350,150,pen);


    QImage hh1_img;
    hh1_img.load(":/images/hh1.bmp");

    QPixmap pix_hh1;
    pix_hh1.convertFromImage(hh1_img);
    QGraphicsPixmapItem* item_hh1 = scene->addPixmap(pix_hh1);
    item_hh1->setPos(430,150);

    scene->addLine(90,100,480,150,pen);


    QImage ll2_img;
    ll2_img.load(":/images/ll2.bmp");

    QPixmap pix_ll2;
    pix_ll2.convertFromImage(ll2_img);
    QGraphicsPixmapItem* item_ll2 = scene->addPixmap(pix_ll2);
    item_ll2->setPos(40,300);

    scene->addLine(90,250,90,300,pen);

    QImage lh2_img;
    lh2_img.load(":/images/lh2.bmp");

    QPixmap pix_lh2;
    pix_lh2.convertFromImage(lh2_img);
    QGraphicsPixmapItem* item_lh2 = scene->addPixmap(pix_lh2);
    item_lh2->setPos(170,300);

    scene->addLine(90,250,220,300,pen);

    QImage hl2_img;
    hl2_img.load(":/images/hl2.bmp");

    QPixmap pix_hl2;
    pix_hl2.convertFromImage(hl2_img);
    QGraphicsPixmapItem* item_hl2 = scene->addPixmap(pix_hl2);
    item_hl2->setPos(300,300);

    scene->addLine(90,250,350,300,pen);


    QImage hh2_img;
    hh2_img.load(":/images/hh2.bmp");

    QPixmap pix_hh2;
    pix_hh2.convertFromImage(hh2_img);
    QGraphicsPixmapItem* item_hh2 = scene->addPixmap(pix_hh2);
    item_hh2->setPos(430,300);

    scene->addLine(90,250,480,300,pen);


    scene->setBackgroundBrush(Qt::black);
 //   scene->installEventFilter(this);
    setMouseTracking(TRUE);
    createStatusBar();
    view = new QGraphicsView();
    view->setScene(scene);

    view->viewport()->installEventFilter(this);
    view->viewport()->setMouseTracking(true);

    glayout = new QGridLayout;
    glayout->addWidget(view,0,0);

//    QImage img("lena512.bmp");
//    QPixmap pix;
//    pix.convertFromImage(img);

//    QLabel *labelpix = new QLabel(this);
//    labelpix->setPixmap(pix);

//    glayout->addWidget(labelpix);

    denoisedial = new QWidget();
    denoisedial->setLayout(vlayout3);

    mwlay = new QHBoxLayout;
    mw->setLayout(mwlay);
    mwlay->addWidget(dwtdial);
    mwlay->addLayout(glayout);
    mwlay->addWidget(denoisedial);

    setCentralWidget(mw);

}

void MainWindow::createActions2() {
  exitAct =new QAction(tr("E&xit"),this);
  exitAct->setShortcut(tr("Ctrl+Q"));
  connect(exitAct,SIGNAL(triggered()),this,SLOT(close()));

  openAct= new QAction(tr("O&pen"),this);
  openAct->setShortcut(tr("Ctrl+O"));
  connect(openAct,SIGNAL(triggered()),this,SLOT(openFile2()));

  aboutAct = new QAction(tr("A&bout"),this);
  connect(aboutAct,SIGNAL(triggered()),this,SLOT(about()));


  lenaAct = new QAction(tr("Lena - 512-by-512 "),this);
  connect(lenaAct,SIGNAL(triggered()),this,SLOT(loadlena()));

  snowAct = new QAction(tr("Snow - 250-by-189 "),this);
  connect(snowAct,SIGNAL(triggered()),this,SLOT(loadsnow()));

  mandrilAct = new QAction(tr("Mandril - 512-by-512 Color"),this);
  connect(mandrilAct,SIGNAL(triggered()),this,SLOT(loadmandril()));


  noisylenaAct = new QAction(tr("Noisy Lena - 256-by-256 (PSNR ~20 db) "),this);
  connect(noisylenaAct,SIGNAL(triggered()),this,SLOT(loadnoisylena()));

  appxAct= new QAction(tr("Signal Approximation"), this);
//  connect(appxAct,SIGNAL(triggered()),this,SLOT())

}

void MainWindow::createMenus2(){
fileMenu=menuBar()->addMenu(tr("&File"));
fileMenu->addAction(openAct);
fileMenu->addAction(exitAct);

signalMenu=menuBar()->addMenu(tr("&Test Images"));
signalMenu->addAction(lenaAct);
signalMenu->addAction(snowAct);
signalMenu->addAction(noisylenaAct);
signalMenu->addAction(mandrilAct);

//appMenu=menuBar()->addMenu(tr("&Applications"));
//appMenu->addAction(appxAct);

helpMenu=menuBar()->addMenu(tr("&Help"));
helpMenu->addAction(aboutAct);

}

void MainWindow::createToolBars2() {
    fileToolBar = addToolBar(tr("File"));
}

void MainWindow::openFile2() {

    QString filename = QFileDialog::getOpenFileName(0,
                     QObject::tr("Open Signal File"), "../", QObject::tr("Image Files (*.png *.bmp *.jpg *.tiff *.tif)"));

    if (!filename.isEmpty())
        loadFile2(filename);
         setCurrentFile(filename);
}



void MainWindow::loadlena() {
 //   QFile::copy(":/images/lena512.bmp","lena512.bmp");
    QFileInfo dir6(":/images/lena512.bmp");
    QString filename = dir6.absoluteFilePath();

    loadFile2(filename);
    setCurrentFile(filename);
}

void MainWindow::loadsnow() {
  //  QFile::copy(":/images/snow.jpg","snow.jpg");
    QFileInfo dir5(":/images/snow.jpg");
    QString filename = dir5.absoluteFilePath();

    loadFile2(filename);
    setCurrentFile(filename);
}

void MainWindow::loadnoisylena() {
 //   QFile::copy(":/images/lena_color20db.tif","noisylena.tif");
    QFileInfo dir5(":/images/lena_color20db.tif");
    QString filename = dir5.absoluteFilePath();

    loadFile2(filename);
    setCurrentFile(filename);
}

void MainWindow::loadmandril() {
  //  QFile::copy(":/images/mandril_color.tif","mandril.tif");
    QFileInfo dir6(":/images/mandril_color.tif");
    QString filename = dir6.absoluteFilePath();

    loadFile2(filename);
    setCurrentFile(filename);
}

void MainWindow::about() {
    QMessageBox msgBox;
    msgBox.setTextFormat(Qt::RichText);
    QString strabout;
    strabout = "DyadWaves : \n \n";
    strabout.append(QString("Wavelet Based Signal processing Software"));
    strabout.append(QString("Version No. 0.1.1.1"));
    msgBox.setText(strabout);
    msgBox.setInformativeText("(c) 2011,    Rafat Hussain");
    msgBox.setWindowTitle("About");
    msgBox.exec();
}

void MainWindow::errormessage() {
    QMessageBox errorBox;
    errorBox.setTextFormat(Qt::RichText);
    errorBox.critical(0,QString("Load Image Error"),QString("No Image Loaded. Use File Menu or Load Image to load Image."),QMessageBox::Ok,QMessageBox::NoButton);
    loadsnow();
}


void MainWindow::loadFile2(const QString &fileName){
//    original_signal.clear();
    image.load(fileName);
    int f = image.format();
    if ( f != 3) {
        colorbox->setEnabled(true);
        colorbox_appx->setEnabled(true);
        colorbox_denoise->setEnabled(true);
        colorbox_filt->setEnabled(true);
    } else {
        colorbox->setEnabled(false);
        colorbox_appx->setEnabled(false);
        colorbox_denoise->setEnabled(false);
        colorbox_filt->setEnabled(false);


    }
    backupimage = image;

// int width = image.width();
// int height = image.height();
 dispImage();

}

void MainWindow::setCurrentFile(const QString &filename){
    curFile = filename;
}

void MainWindow::DWTdialog2() {
    QLabel *dwthead = new QLabel("DWT Dashboard");
    dwthead->setStyleSheet("QLabel {background-color : black; color : #4876FF; font : bold 12px}");
    dwthead->setAlignment(Qt::AlignCenter);
    QHBoxLayout *hdwthead =  new QHBoxLayout;
    hdwthead->addWidget(dwthead);

    QHBoxLayout *hlayout = new QHBoxLayout;
    wave = new QComboBox();
    QLabel *label = new QLabel("Choose Wavelet Family");
    QPushButton *inpbutton = new QPushButton(QObject::tr("Load Image"));
//      QPushButton *helloButton = new QPushButton("Show Label");
    QStringList wavefamily;
    wavefamily << "db1" << "db2" << "db3" << "db4" << "db5" << "db6" << "db7" << "db8"
             << "db9" << "db10" << "db11" << "db12" << "db13" << "db14" << "db15" << "bior1.1"
             << "bior1.3" << "bior1.5" << "bior2.2" << "bior2.4" << "bior2.6" << "bior2.8"
               << "bior3.1" << "bior3.3" << "bior3.5" << "bior3.7" << "bior3.9" << "bior4.4"
               << "bior5.5" << "bior6.8" << "coif1" << "coif2" << "coif3" <<"coif4" <<"coif5"
               << "sym2" << "sym3" << "sym4" << "sym5" << "sym6" << "sym7" << "sym8" << "sym9"
               << "sym10";

    wave->addItems(wavefamily);
    QObject::connect(wave, SIGNAL(activated(const QString &)),this, SLOT(setWave(const QString &)));
    QObject::connect(inpbutton, SIGNAL(clicked()),this, SLOT(openFile2()));
    hlayout->addWidget(label);
    hlayout->addWidget(wave);

    QLabel *label2 = new QLabel("Enter Decompostion Levels");
    QStringList decom;
    decom << "1" << "2" << "3" << "4" << "5" << "6" << "7" << "8" << "9" << "10" << "11" <<
            "12" << "13" << "14" << "15" <<"16" << "17" << "18" << "19" << "20" << "21" <<
            "22" << "23" << "24" << "25" << "26" << "27" << "28" << "29" << "30" << "31" << "32";
    QComboBox *decoml = new QComboBox();
    decoml->addItems(decom);
    QHBoxLayout *hlayout2 = new QHBoxLayout;
    QObject::connect(decoml, SIGNAL(activated(int)),this, SLOT(setDecom(int)));

    hlayout2->addWidget(label2);
    hlayout2->addWidget(decoml);

    QLabel *label3 = new QLabel("Enter Mode");
    QStringList modes;
    modes << "dwt_sym" << "swt" << "dwt_per";

    QComboBox *modebox = new QComboBox();
    modebox->addItems(modes);
    QHBoxLayout *hlayout3 = new QHBoxLayout;
    QObject::connect(modebox, SIGNAL(activated(const QString &)),this, SLOT(setMode(const QString &)));

    hlayout3->addWidget(label3);
    hlayout3->addWidget(modebox);

    QLabel *label4 = new QLabel("Symmetric Extension Length");
    QStringList ext1;
    ext1 << "0" << "1" << "2" << "3" << "4" << "5" << "6" << "7" << "8" << "9" << "10" << "11" << "12" << "13"
            << "14" << "15" << "16" << "17" << "18" << "19" << "20" << "21" << "22" << "23" << "24" << "25" << "26"
            << "27" << "28" << "29" << "30" << "31" << "32" << "33" << "34" << "35" << "36" << "37" <<
            "38" << "39";
    extension = new QComboBox();
    extension->addItems(ext1);
    QHBoxLayout *hlayout4 = new QHBoxLayout;
    QObject::connect(extension, SIGNAL(activated(int)),this, SLOT(setExt(int)));

    hlayout4->addWidget(label4);
    hlayout4->addWidget(extension);

    colorbox = new QComboBox();
    QStringList colorproc;
    colorproc << "GrayScale (Faster)" << "Color (Slower)" ;
    colorbox->addItems(colorproc);

    QLabel *labelcol = new QLabel("2D DWT Option");
    QHBoxLayout *hlayoutcol = new QHBoxLayout;

    hlayoutcol->addWidget(labelcol);
    hlayoutcol->addWidget(colorbox);

    QObject::connect(colorbox, SIGNAL(activated(const QString &)),this, SLOT(setColProc(const QString &)));
    colorbox->setEnabled(false);


    dwtbutton = new QPushButton(QObject::tr("Perform DWT"));
//    idwtbutton = new QPushButton(QObject::tr("Perform IDWT"));
//    idwtbutton->setEnabled(false);
    idwtbutton = new QCheckBox("Perform IDWT");
    idwtbutton->setChecked(false);
    idwtbutton->setEnabled(false);

    QObject::connect(dwtbutton, SIGNAL(clicked()),this, SLOT(computeDWT2()));
 //   QObject::connect(dwtbutton, SIGNAL(clicked()),this, SLOT(enableIDWT()));

    reportbutton = new QPushButton(QObject::tr("View DWT Report"));
    QObject::connect(reportbutton,SIGNAL(clicked()),this,SLOT(reportDWT()));
    reportbutton->setEnabled(false);

    vlayout = new QVBoxLayout;
    vlayout->addLayout(hdwthead);
    vlayout->addWidget(inpbutton);
    vlayout->addLayout(hlayout);
    vlayout->addLayout(hlayout2);
    vlayout->addLayout(hlayout3);
   // vlayout->addLayout(hlayout4);
    vlayout->addLayout(hlayoutcol);
    vlayout->addWidget(idwtbutton);
    vlayout->addWidget(dwtbutton);
    vlayout->addWidget(reportbutton);

}
void MainWindow::APPXdialog2(){
    QFrame* line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    vlayout->addWidget(line);
    QLabel *appxhead = new QLabel("Signal Approximation");
    appxhead->setStyleSheet("QLabel {background-color : black; color : #4876FF; font : bold 12px}");
    appxhead->setAlignment(Qt::AlignCenter);

    QHBoxLayout *happxhead = new QHBoxLayout;

    happxhead->addWidget(appxhead);

    QStringList appxmodes;
    appxmodes << "dwt_per" << "dwt_sym";

    QLabel *dwtappxlabel = new QLabel("Enter DWT Mode");
    QComboBox *dwtappx = new QComboBox();

    QObject::connect(dwtappx, SIGNAL(activated(const QString &)),this, SLOT(setAppxMode(const QString &)));

    dwtappx->addItems(appxmodes);
    QHBoxLayout *hdwtappx = new QHBoxLayout;

    hdwtappx->addWidget(dwtappxlabel);
    hdwtappx->addWidget(dwtappx);

    QLabel *appxlabel = new QLabel("Select Coefficients (0-100%)");
    QComboBox *appxinp = new QComboBox();
    //appxlabel->setBuddy(appxinp);
   // appxinp->setMaxLength(3);
    for (int i=0; i < 101;i++){
        QString itemx;
        itemx=itemx.setNum(i);
        appxinp->addItem(itemx);
    }
    appxinp->setCurrentIndex(25);

    QHBoxLayout *happxlabel = new QHBoxLayout;
    happxlabel->addWidget(appxlabel);
    happxlabel->addWidget(appxinp);

 //   QHBoxLayout *appxh = new QHBoxLayout;
 //   appxh->addWidget(appxlabel);

    colorbox_appx = new QComboBox();
    QStringList colorproc;
    colorproc << "GrayScale (Faster)" << "Color (Slower)" ;
    colorbox_appx->addItems(colorproc);

    QLabel *labelcol = new QLabel("2D DWT Option");
    QHBoxLayout *hlayoutcol = new QHBoxLayout;

    hlayoutcol->addWidget(labelcol);
    hlayoutcol->addWidget(colorbox_appx);

    QObject::connect(colorbox_appx, SIGNAL(activated(const QString &)),this, SLOT(setColProc_appx(const QString &)));
    colorbox_appx->setEnabled(false);

    vlayout->addLayout(happxhead);
    vlayout->addLayout(hdwtappx);
    vlayout->addLayout(happxlabel);
    vlayout->addLayout(hlayoutcol);
 //   vlayout->addWidget(appxinp);

    appxbutton = new QPushButton(QObject::tr("Approximate Image"));
    vlayout->addWidget(appxbutton);

    QObject::connect(appxinp, SIGNAL(activated(int)),this, SLOT(setAppxCoef(int)));
    QObject::connect(appxbutton, SIGNAL(clicked()),this, SLOT(approximateSig2()));

}

void MainWindow::DISPdialog2() {
    QLabel *disphead = new QLabel("Display Dashboard");
    disphead->setStyleSheet("QLabel {background-color : black; color : #4876FF; font : bold 12px}");
    disphead->setAlignment(Qt::AlignCenter);

    filtdispbutton = new QPushButton(QObject::tr("Display Wavelet Filters"));
    wavedispbutton = new QPushButton(QObject::tr("Display Wavelets"));
    freqdispbutton = new QPushButton(QObject::tr("Image Frequency Response"));
    filtfreqbutton = new QPushButton(QObject::tr("Filters Frequency Response"));

    QObject::connect(filtdispbutton, SIGNAL(clicked()),this, SLOT(filtdisp()));
    QObject::connect(wavedispbutton, SIGNAL(clicked()),this, SLOT(wavedisp()));
    QObject::connect(freqdispbutton, SIGNAL(clicked()),this, SLOT(freqdisp2()));
    QObject::connect(filtfreqbutton, SIGNAL(clicked()),this, SLOT(filtfreq2()));
  //  freqdispbutton->setEnabled(false);
  //  filtfreqbutton->setEnabled(false);


    vlayout->addWidget(disphead);
    vlayout->addWidget(filtdispbutton);
    vlayout->addWidget(wavedispbutton);
    vlayout->addWidget(freqdispbutton);
    vlayout->addWidget(filtfreqbutton);

}

void MainWindow::DENOISEdialog2() {
    vlayout3 = new QVBoxLayout;
    QLabel *denoisehead = new QLabel("Wavelet DeNoising");
    denoisehead->setStyleSheet("QLabel {background-color : black; color : #4876FF; font : bold 12px}");
    denoisehead->setAlignment(Qt::AlignCenter);

    QHBoxLayout *hlayoutdnmethod = new QHBoxLayout;

    QStringList denoisemethod;
    denoisemethod << "visushrink" << "sureshrink" << "bayesshrink";

    QLabel *denoiselabelmethod = new QLabel("DeNoise Method");
    QComboBox *dwtdenoisemethod = new QComboBox();

    dwtdenoisemethod->addItems(denoisemethod);
    QObject::connect(dwtdenoisemethod, SIGNAL(activated(const QString &)),this, SLOT(setDenoiseMethod(const QString &)));

    hlayoutdnmethod->addWidget(denoiselabelmethod);
    hlayoutdnmethod->addWidget(dwtdenoisemethod);

    QHBoxLayout *hlayoutdnthresh = new QHBoxLayout;

    QStringList denoisethresh;
    denoisethresh << "soft" << "hard";

    QLabel *denoiselabelthresh = new QLabel("Thresholding Type");
    QComboBox *dwtdenoisethresh = new QComboBox();

    dwtdenoisethresh->addItems(denoisethresh);
    QObject::connect(dwtdenoisethresh, SIGNAL(activated(const QString &)),this, SLOT(setDenoiseThresh(const QString &)));

    hlayoutdnthresh->addWidget(denoiselabelthresh);
    hlayoutdnthresh->addWidget(dwtdenoisethresh);

    QHBoxLayout *hlayoutdn1 = new QHBoxLayout;

    QStringList denoisemodes;
    denoisemodes << "dwt_per" << "dwt_sym";

    QLabel *denoiselabel1 = new QLabel("Enter DWT Mode");
    QComboBox *dwtdenoise = new QComboBox();

    dwtdenoise->addItems(denoisemodes);
    QObject::connect(dwtdenoise, SIGNAL(activated(const QString &)),this, SLOT(setDenoiseMode(const QString &)));

    hlayoutdn1->addWidget(denoiselabel1);
    hlayoutdn1->addWidget(dwtdenoise);

    wave2 = new QComboBox();
    QStringList wavefamily2;
    wavefamily2 << "db1" << "db2" << "db3" << "db4" << "db5" << "db6" << "db7" << "db8"
             << "db9" << "db10" << "db11" << "db12" << "db13" << "db14" << "db15" << "bior1.1"
             << "bior1.3" << "bior1.5" << "bior2.2" << "bior2.4" << "bior2.6" << "bior2.8"
               << "bior3.1" << "bior3.3" << "bior3.5" << "bior3.7" << "bior3.9" << "bior4.4"
               << "bior5.5" << "bior6.8" << "coif1" << "coif2" << "coif3" <<"coif4" <<"coif5"
               << "sym2" << "sym3" << "sym4" << "sym5" << "sym6" << "sym7" << "sym8" << "sym9"
               << "sym10";

    wave2->addItems(wavefamily2);
    QObject::connect(wave2, SIGNAL(activated(const QString &)),this, SLOT(setDenoiseWave(const QString &)));

    QLabel *denoiselabel2 = new QLabel("Choose Wavelet Family");

    QHBoxLayout *hlayoutdn2 = new QHBoxLayout;

    hlayoutdn2->addWidget(denoiselabel2);
    hlayoutdn2->addWidget(wave2);

    QLabel *denoiselabel3 = new QLabel("Enter Decompostion Levels");
    QStringList denoisedecom;

    denoisedecom << "1" << "2" << "3" << "4" << "5" << "6" << "7" << "8" << "9" << "10" << "11" <<
            "12" << "13" << "14" << "15" <<"16" << "17" << "18" << "19" << "20" << "21" <<
            "22" << "23" << "24" << "25" << "26" << "27" << "28" << "29" << "30" << "31" << "32";
    QComboBox *denoisedecoml = new QComboBox();
    denoisedecoml->addItems(denoisedecom);
    QHBoxLayout *hlayoutdn3 = new QHBoxLayout;
    QObject::connect(denoisedecoml, SIGNAL(activated(int)),this, SLOT(setDenoiseDecom(int)));

    hlayoutdn3->addWidget(denoiselabel3);
    hlayoutdn3->addWidget(denoisedecoml);

    QLabel *label4 = new QLabel("Symmetric Extension Length");
    QStringList ext1;
    ext1 << "0" << "1" << "2" << "3" << "4" << "5" << "6" << "7" << "8" << "9" << "10" << "11" << "12" << "13"
            << "14" << "15" << "16" << "17" << "18" << "19" << "20" << "21" << "22" << "23" << "24" << "25" << "26"
            << "27" << "28" << "29" << "30" << "31" << "32" << "33" << "34" << "35" << "36" << "37" <<
            "38" << "39";

    extension_dn = new QComboBox();
    extension_dn->addItems(ext1);
    QHBoxLayout *hlayoutdn4 = new QHBoxLayout;
    QObject::connect(extension_dn, SIGNAL(activated(int)),this, SLOT(setExt_dn(int)));

    hlayoutdn4->addWidget(label4);
    hlayoutdn4->addWidget(extension_dn);

    denoisebutton = new QPushButton(QObject::tr("DeNoise Image"));
    QObject::connect(denoisebutton, SIGNAL(clicked()),this, SLOT(signalDENOISE2()));

    colorbox_denoise = new QComboBox();
    QStringList colorproc;
    colorproc << "GrayScale (Faster)" << "Color (Slower)" ;
    colorbox_denoise->addItems(colorproc);

    QLabel *labelcol = new QLabel("2D DWT Option");
    QHBoxLayout *hlayoutcol = new QHBoxLayout;

    hlayoutcol->addWidget(labelcol);
    hlayoutcol->addWidget(colorbox_denoise);

    QObject::connect(colorbox_denoise, SIGNAL(activated(const QString &)),this, SLOT(setColProc_denoise(const QString &)));
    colorbox_denoise->setEnabled(false);

    vlayout3->addWidget(denoisehead);
    vlayout3->addLayout(hlayoutdnmethod);
    vlayout3->addLayout(hlayoutdnthresh);
    vlayout3->addLayout(hlayoutdn1);
    vlayout3->addLayout(hlayoutdn2);
    vlayout3->addLayout(hlayoutdn3);
  //  vlayout3->addLayout(hlayoutdn4);

    vlayout3->addLayout(hlayoutcol);
    vlayout3->addWidget(denoisebutton);

}

void MainWindow::FILTERdialog2() {

    QLabel *filthead = new QLabel("Additional Processing");
    filthead->setStyleSheet("QLabel {background-color : black; color : #4876FF; font : bold 12px}");
    filthead->setAlignment(Qt::AlignCenter);

    QHBoxLayout *filtlayout = new QHBoxLayout;

    QLabel *labelfilt = new QLabel("Choose Filter :");

    QStringList filtlist;

    filtlist << "Moving Average 3x3" << "Moving Average 5x5" << "Moving Average 7x7" << "Median Filter"
            << "Roberts Mask (H)" << "Roberts Mask (V)" << "Sobel Mask (H)" << "Sobel Mask (V)"
            << "Prewitt Mask (H)" << "Prewitt Mask (V)" << "LaPlacian" << "LaPlacian Sharp" << "Gaussian";

    QComboBox *filterbox = new QComboBox();
    filterbox->addItems(filtlist);
    filtlayout->addWidget(labelfilt);
    filtlayout->addWidget(filterbox);

    filtimagebutton = new QPushButton(QObject::tr("Filter Image"));
    setimagebutton = new QPushButton(QObject::tr("Set Image"));
    resetimagebutton = new QPushButton(QObject::tr("Reset Image"));

    QObject::connect(filterbox, SIGNAL(activated(const QString &)),this, SLOT(setFilter(const QString &)));
    QObject::connect(filtimagebutton, SIGNAL(clicked()),this, SLOT(imageFILTER2()));
    QObject::connect(setimagebutton, SIGNAL(clicked()),this, SLOT(setIMAGE()));
    QObject::connect(resetimagebutton, SIGNAL(clicked()),this, SLOT(resetIMAGE()));
    setimagebutton->setEnabled(false);
    resetimagebutton->setEnabled(false);



    QHBoxLayout *setlayout = new QHBoxLayout;

    setlayout->addWidget(setimagebutton);
    setlayout->addWidget(resetimagebutton);

    QHBoxLayout *gausslayout = new QHBoxLayout;

    QLabel *gausssizelabel = new QLabel("Gaussian Size(nxn), n:");
    QStringList gausssize;
    gausssize << "3" << "5" << "7" << "9" << "11" << "13" << "15";
    gaussbox = new QComboBox;
    gaussbox->addItems(gausssize);
    gaussbox->setEnabled(false);

    gausslayout->addWidget(gausssizelabel);
    gausslayout->addWidget(gaussbox);
    QObject::connect(gaussbox, SIGNAL(activated(int)),this, SLOT(setGauss_size(int)));

    QDoubleValidator *sigmavalid = new QDoubleValidator(-100.0,100.0,3,this);
    sigmaline = new QLineEdit;
    sigmaline->setMaximumWidth(80);
    sigmaline->setValidator(sigmavalid);
    sigmaline->setText("4.0");
    sigmaline->setEnabled(false);


    QHBoxLayout *sigmalayout = new QHBoxLayout;

    QLabel *sigmalabel = new QLabel("Standard Deviation :");
//    QComboBox *sigmaval = new QComboBox;
//    QStringList sigmavalues;
//    sigmavalues << "-4.0" << "-3.0" << "-2.0" << "-1.0";
//    sigmaval->addItems(sigmavalues);
    sigmalayout->addWidget(sigmalabel,0,Qt::AlignLeft);
    sigmalayout->addWidget(sigmaline,0,Qt::AlignRight);
    QObject::connect(sigmaline, SIGNAL(textChanged(const QString &)),this, SLOT(setSIGMA(const QString &)));


    colorbox_filt = new QComboBox();
    QStringList colorfilt;
    colorfilt << "GrayScale (Faster)" << "Color (Slower)" ;
    colorbox_filt->addItems(colorfilt);

    QLabel *gausslabelcol = new QLabel("Color Option");
    QHBoxLayout *gausslayoutcol = new QHBoxLayout;

    gausslayoutcol->addWidget(gausslabelcol);
    gausslayoutcol->addWidget(colorbox_filt);

    QObject::connect(colorbox_filt, SIGNAL(activated(const QString &)),this, SLOT(setColProc_filt(const QString &)));
    colorbox_filt->setEnabled(false);

    filteroutbutton = new QPushButton(QObject::tr("Save Filtered Image"));
    QObject::connect(filteroutbutton, SIGNAL(clicked()),this, SLOT(saveFILTER2()));

    filteroutbutton->setEnabled(false);

    vlayout3->addWidget(filthead);
    vlayout3->addLayout(filtlayout);
    vlayout3->addLayout(gausslayout);
    vlayout3->addLayout(gausslayoutcol);
    vlayout3->addLayout(sigmalayout);

    vlayout3->addWidget(filtimagebutton);
    vlayout3->addWidget(filteroutbutton);
    vlayout3->addLayout(setlayout);

}

void MainWindow::OUTPUTconsole2() {
    QLabel *outputhead = new QLabel("Save Output(s)");
    outputhead->setStyleSheet("QLabel {background-color : black; color : #4876FF; font : bold 12px}");
    outputhead->setAlignment(Qt::AlignCenter);

    dwtoutbutton = new QPushButton(QObject::tr("Save DWT Image"));
    QObject::connect(dwtoutbutton, SIGNAL(clicked()),this, SLOT(saveDWT2()));

    dwtoutbutton->setEnabled(false);

    appxoutbutton = new QPushButton(QObject::tr("Save Approximated Image"));
    QObject::connect(appxoutbutton, SIGNAL(clicked()),this, SLOT(saveAPPX2()));

    appxoutbutton->setEnabled(false);

    appxcoefbutton = new QPushButton(QObject::tr("Save Approximation Coeffs"));
    QObject::connect(appxcoefbutton, SIGNAL(clicked()),this, SLOT(saveAPPXCOEF()));

    appxcoefbutton->setEnabled(false);

    denoiseoutbutton = new QPushButton(QObject::tr("Save Denoised Image"));
    QObject::connect(denoiseoutbutton, SIGNAL(clicked()),this, SLOT(saveDENOISE2()));

    denoiseoutbutton->setEnabled(false);

    denoisecoefbutton = new QPushButton(QObject::tr("Save Denoising Coeffs"));
    QObject::connect(denoisecoefbutton, SIGNAL(clicked()),this, SLOT(saveDENOISECOEF()));

    denoisecoefbutton->setEnabled(false);

    vlayout3->addWidget(outputhead);
    vlayout3->addWidget(dwtoutbutton);
    vlayout3->addWidget(appxoutbutton);
    vlayout3->addWidget(denoiseoutbutton);


}

void MainWindow::setDecom(int index){
    J = index + 1;

}

void MainWindow::setDenoiseDecom(int ind){
    J_dn = ind + 1;

}

void MainWindow::setExt_dn(int index){
    ext_dn = index ;

}

void MainWindow::setExt(int index){
    ext= index ;

}

void MainWindow::setWave(const QString &text) {
    nm=text.toStdString();
}

void MainWindow::setDenoiseWave(const QString &text2) {
    nm_dn=text2.toStdString();
}

void MainWindow::setMode(const QString &text) {
    mode=text.toStdString();
    if (mode == "dwt_sym"){
        extension->setEnabled(true);
    } else {
        extension->setEnabled(false);
    }

}

void MainWindow::setAppxMode(const QString &textappx) {
    mode_appx=textappx.toStdString();

}

void MainWindow::setColProc(const QString &colproc) {
    mode_color=colproc.toStdString();

}

void MainWindow::setColProc_appx(const QString &colproc) {
    mode_color_appx=colproc.toStdString();

}

void MainWindow::setColProc_filt(const QString &colproc) {
    mode_color_filt=colproc.toStdString();

}

void MainWindow::setFilter(const QString &imfilt) {
    im_filter=imfilt.toStdString();
    if (im_filter == "Gaussian") {
        gaussbox->setEnabled(true);
        sigmaline->setEnabled(true);
    } else {
        gaussbox->setEnabled(false);
        sigmaline->setEnabled(false);


    }

}

void MainWindow::setColProc_denoise(const QString &colproc) {
    mode_color_denoise=colproc.toStdString();

}

void MainWindow::setDenoiseMode(const QString &textdenoise) {
    mode_denoise=textdenoise.toStdString();

}

void MainWindow::setDenoiseMethod(const QString &method) {
    dn_method=method.toStdString();

}

void MainWindow::setDenoiseThresh(const QString &thresh) {
    dn_thresh =thresh.toStdString();
}

void MainWindow::setAppxCoef(int index) {
    n_coef = index;
    if (n_coef == 0) {
        n_coef = 1;
    }
}

void MainWindow::setGauss_size(int size) {
    gauss_size = 2*(size + 2) -1;
}

void MainWindow::setSIGMA(const QString &val) {
    bool ok;
    gauss_sigma = val.toDouble(&ok);

}

void MainWindow::enableIDWT(){
    idwtbutton->setEnabled(true);
}

void MainWindow::dispImage() {
    QLayoutItem *child;
    while ((child = glayout->takeAt(0)) != 0)
    {
    delete child->widget();
    delete child;
    }
    if (image.isNull()) {
        errormessage();
    }
    vspacer = new QSpacerItem( 10, 10, QSizePolicy::Minimum,
    QSizePolicy::Expanding );
    hspacer1 = new QSpacerItem( 10, 10, QSizePolicy::Expanding,
    QSizePolicy::Minimum );
    hspacer2 = new QSpacerItem( 10, 10, QSizePolicy::Expanding,
    QSizePolicy::Minimum );
    spacer = new QSpacerItem( 10, 10, QSizePolicy::Minimum,
    QSizePolicy::Expanding );


    QPixmap pix;

    pix.convertFromImage(image);


    QLabel *label1 = new QLabel("Input Image");
    label1->setAlignment(Qt::AlignCenter);
    label1->setScaledContents(true);


    QLabel *label2 = new QLabel(this);
    label2->setPixmap(pix);
    label2->setAlignment(Qt::AlignCenter);
    label2->setScaledContents(true);


    glayout->addWidget(label1,1,1);
    glayout->addWidget(label2,2,1);
    glayout->addItem(vspacer,0,1);
    glayout->addItem(spacer,3,1);
    glayout->addItem(hspacer1,1,0);
    glayout->addItem(hspacer2,1,2);


//    glayout->addWidget(label4,1,2,1,1);
//    glayout->addWidget(label5,1,4,1,1);

    glayout->update();

}

void MainWindow::setIMAGE() {
    image = filteredimage;
    dispImage();
}

void MainWindow::resetIMAGE() {
    image = backupimage;
    dispImage();
}

void MainWindow::computeDWT2() {
    dwtbutton->setEnabled(false);
    if (image.isNull()) {
        errormessage();
    }

    int width = image.width();
    int height = image.height();

    vector<vector<double> > vec(height,vector<double>(width));
    vector<vector<double> > vecred(height,vector<double>(width));
    vector<vector<double> > vecgreen(height,vector<double>(width));
    vector<vector<double> > vecblue(height,vector<double>(width));


    int max_dec = (int) floor((double)log(min(width,height))/log(2.0)) - 1;
    if ( J >= max_dec) {
        J = max_dec;
    }

    int form = image.format();

    if (form == 3) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            vec[i][j] = (double) (image.pixelIndex(j,i));
        }
    }
} else if ((form != 3) && (mode_color == "GrayScale (Faster)")) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
    QRgb value = image.pixel(j,i);
    double temp1 = (double) (qRed(value));
    double temp2 = (double) (qGreen(value));
    double temp3 = (double) (qBlue(value));
    vec[i][j] =  0.59 * temp2 + 0.30 * temp1 + 0.11 * temp3;
    form = 3;
}
    }
} else {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            QRgb value = image.pixel(j,i);
            vecred[i][j] = (double) (qRed(value));
            vecgreen[i][j] = (double) (qGreen(value));
            vecblue[i][j] = (double) (qBlue(value));
        }
    }
}


  vector<double> flag,flag_r,flag_g,flag_b,dwt_output,dwt_output_r,dwt_output_g,dwt_output_b,signal;
  int rr1,cc1;
  dwt_output_dim(vec, rr1, cc1 );
  vector<vector<double> >  dwt_output_per(rr1, vector<double>(cc1));
  vector<vector<double> >  dwt_output_per_r(rr1, vector<double>(cc1));
  vector<vector<double> >  dwt_output_per_g(rr1, vector<double>(cc1));
  vector<vector<double> >  dwt_output_per_b(rr1, vector<double>(cc1));

  vector<vector<double> >  idwt_output_per(rr1, vector<double>(cc1));
  vector<int> length,length_r,length_g,length_b;

  QTime cpu_time;

  // perform J-Level SWT/DWT
  if (mode == "swt"){
      cpu_time.start();
      if (form == 3) {
          swt_2d(vec,J,nm,dwt_output);
          exec_time = cpu_time.elapsed();
          int rr1 = vec.size();
          int cc1 = vec[0].size();
          dispSWT(dwt_output,J,rr1,cc1);


      } else {

          swt_2d(vecred,J,nm,dwt_output_r);
          swt_2d(vecgreen,J,nm,dwt_output_g);
          swt_2d(vecblue,J,nm,dwt_output_b);

          exec_time = cpu_time.elapsed();
     //     dwt_output_dim(vecred,rr1,cc1);
          int rr1 = vecred.size();
          int cc1 = vecred[0].size();

          dispSWT_RGB(dwt_output_r,dwt_output_g,dwt_output_b,J,rr1,cc1);

      }


 } else if ( mode == "dwt_per") {
     flag.clear();
     cpu_time.start();
     if ( form == 3) {
     dwt_2d(vec,J, nm, dwt_output,flag,length );
     per_coeff_length = length;
     exec_time = cpu_time.elapsed();
     dispDWT_SYM(dwt_output,J, length);
     createEXP(dwt_output,length,J);

 } else {
     dwt_2d(vecred,J, nm, dwt_output_r,flag_r,length_r );
     dwt_2d(vecgreen,J, nm, dwt_output_g,flag_g,length_g );
     dwt_2d(vecblue,J, nm, dwt_output_b,flag_b,length_b );
     length = length_r;
     exec_time = cpu_time.elapsed();
     dispDWT_SYM_RGB(dwt_output_r,dwt_output_g,dwt_output_b,J,length);
     per_coeff_length = length;
 }

} else if (mode == "dwt_sym") {
     flag.clear();
     cpu_time.start();
     if (form == 3) {
     dwt_2d_sym(vec,J,nm,dwt_output,flag,length,ext);
     exec_time = cpu_time.elapsed();
     dispDWT_SYM(dwt_output,J,length);
     createEXP(dwt_output,length,J);

     sym_coeff_length = length;
 } else {
     dwt_2d_sym(vecred,J,nm,dwt_output_r,flag_r,length_r,ext);
     dwt_2d_sym(vecgreen,J,nm,dwt_output_g,flag_g,length_g,ext);
     dwt_2d_sym(vecblue,J,nm,dwt_output_b,flag_b,length_b,ext);
     length = length_r;
     exec_time = cpu_time.elapsed();
     dispDWT_SYM_RGB(dwt_output_r,dwt_output_g,dwt_output_b,J,length);
     sym_coeff_length = length;
 }
}
dwt_coefficients = dwt_output;

  dwtbutton->setEnabled(true);
  dwtoutbutton->setEnabled(true);
  reportbutton->setEnabled(true);

}

void MainWindow::createEXP(vector<double> &signal, vector<int> &dwtlen, int J) {

    vector<int> dwtlen2;
    dwt_output_dim2(dwtlen, dwtlen2, J);
    int row = dwtlen2[dwtlen2.size()-2];
    int col = dwtlen2[dwtlen2.size()-1];
    vector<vector<double> > expout(row,vector<double>(col));
    int sum = 0;

    for (int iter = 0; iter < J; iter++) {

        int rows_n = dwtlen2[2*iter];
        int cols_n = dwtlen2[2*iter +1];

        int r1 = dwtlen[2*iter];
        int c1 = dwtlen[2*iter + 1];

        if (iter == 0) {
                for(int i =0; i < rows_n; i++){
                        for (int j =0; j < cols_n; j++){
                                expout[i][j]=signal[i*cols_n + j];
                        }
                }

                for(int i =0; i < rows_n; i++){
                        for (int j = cols_n; j < cols_n * 2; j++){
                                expout[i][j]= signal[rows_n * cols_n + i * cols_n + (j - cols_n)];
                        }
                }
                for(int i = rows_n; i < rows_n * 2; i++){
                        for (int j =0; j < cols_n; j++){
                                expout[i][j]=signal[2 * rows_n * cols_n+ (i - rows_n) * cols_n + j];
                        }
                }


                for(int i = rows_n; i < rows_n * 2; i++){
                        for (int j = cols_n; j < cols_n * 2; j++){
                                expout[i][j]=signal[3 * rows_n * cols_n+ (i -rows_n) * cols_n + (j -cols_n)];
                        }
                }
            }

        else {

                for(int i =0; i < rows_n; i++){
                                        for (int j = cols_n; j < cols_n * 2; j++){
                                            if ((i < r1) && (j < cols_n + c1)) {
                                                expout[i][j]= signal[sum + i * c1 + (j - cols_n)];
                                            } else {
                                                expout[i][j] =0;
                                            }
                                        }
                                }

                                for(int i = rows_n; i < rows_n * 2; i++){
                                        for (int j =0; j < cols_n; j++){
                                            if ((i < rows_n + r1) && (j < c1)) {
                                                expout[i][j]=signal[sum + r1 * c1+ (i - rows_n) * c1 + j];
                                            } else {
                                                expout[i][j] = 0;
                                            }
                                        }
                                }


                                for(int i = rows_n; i < rows_n * 2; i++){
                                        for (int j = cols_n; j < cols_n * 2; j++){
                                            if ((i < rows_n+r1) && (j < cols_n+c1)) {
                                                expout[i][j]=signal[sum + 2 * r1 * c1+ (i -rows_n) * c1 + (j -cols_n)];
                                            } else {
                                                expout[i][j] = 0;

                                            }
                                        }

                                }


            }


            if (iter == 0) {
                    sum+= 4*rows_n*cols_n;
            } else {
                    sum+= 3*r1 * c1;
            }


    }

    QImage exp_image(col,row,QImage::Format_RGB32);

    double max;

    maxval2(expout,max);


    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if ( expout[i][j] <= 0.0){
                expout[i][j] = 0.0;
            }
            unsigned int temp;
            if ( (i <= (row/pow(2.0,(double) J))) && (j <= (col/pow(2.0,(double) J)))) {
            temp = (unsigned int) ((expout[i][j] / max) * 255.0);
        } else {
            temp = (unsigned int) expout[i][j] ;
        }
            QRgb value = qRgb(temp,temp,temp);
            exp_image.setPixel(j,i,value);
        }
    }


    expimage = exp_image;


}

void MainWindow::dispSWT(vector<double> &output,int J,int row, int col){
    QLayoutItem *child;
    while ((child = glayout->takeAt(0)) != 0)
    {
    delete child->widget();
    delete child;
    }

    vspacer = new QSpacerItem( 10, 10, QSizePolicy::Minimum,
    QSizePolicy::Expanding );
    hspacer1 = new QSpacerItem( 10, 10, QSizePolicy::Expanding,
    QSizePolicy::Minimum );
    hspacer2 = new QSpacerItem( 10, 10, QSizePolicy::Expanding,
    QSizePolicy::Minimum );
    spacer = new QSpacerItem( 10, 10, QSizePolicy::Minimum,
    QSizePolicy::Expanding );

    QLabel *label1 = new QLabel("Original Image");
    label1->setAlignment(Qt::AlignCenter);
    label1->setScaledContents(true);

    QPixmap pix;

    pix.convertFromImage(image);

    QLabel *labelorig = new QLabel(this);
    labelorig->setPixmap(pix);
    double sfact = 1.0;
    if ((pix.width() < labelorig->width()) || (pix.height() < labelorig->height())) {
    sfact =min((double) pix.width()/(double) labelorig->width(),(double) pix.height()/(double) labelorig->height());
    labelorig->resize(sfact * labelorig->pixmap()->size());
} else if ((pix.width() >= labelorig->width()) && (pix.height() >= labelorig->height())) {
    sfact =min((double) pix.width()/(double) labelorig->width(),(double) pix.height()/(double) labelorig->height());
    labelorig->resize(sfact * labelorig->size());
    labelorig->setScaledContents(true);

} else {
    labelorig->setScaledContents(true);

}

glayout->addItem(vspacer,0,1);
glayout->addItem(hspacer1,1,0);
glayout->addWidget(label1,1,1);
glayout->addWidget(labelorig,2,1);
glayout->addItem(hspacer2,1,4);

    vector<vector<double> > blur(row,vector<double>(col));
    vector<vector<double> > detail_h(row,vector<double>(col));
    vector<vector<double> > detail_v(row,vector<double>(col));
    vector<vector<double> > detail_d(row,vector<double>(col));

       for (int i=0;i < row; i++){
               for (int j=0; j < col;j++){
            double temp = output[i*col + j];
            blur[i][j]= temp;
               }
       }
       for (int i=0;i < row; i++){
               for (int j=0; j < col;j++){
            double temp = output[row * col + i*col + j];
            detail_h[i][j]= temp;
               }
       }

       for (int i=0;i < row; i++){
               for (int j=0; j < col;j++){
            double temp = output[2 * row * col + i*col + j];
            detail_v[i][j]= temp;
               }
       }

       for (int i=0;i < row; i++){
               for (int j=0; j < col;j++){
            double temp = output[3 *row * col + i*col + j];
            detail_d[i][j]= temp;
               }
       }

       QImage blurimg(col,row,QImage::Format_RGB32);
       QImage detail_himg(col,row,QImage::Format_RGB32);
       QImage detail_vimg(col,row,QImage::Format_RGB32);
       QImage detail_dimg(col,row,QImage::Format_RGB32);

       double max;

       maxval(output,max);


       for (int i = 0; i < row; i++) {
           for (int j = 0; j < col; j++) {
               if ( blur[i][j] <= 0.0){
                   blur[i][j] = 0.0;
               }
           unsigned int temp;
           temp = (unsigned int) ((blur[i][j] / max) * 255.0);
           QRgb value = qRgb(temp,temp,temp);
           blurimg.setPixel(j,i,value);
           }
       }

       for (int i = 0; i < row; i++) {
           for (int j = 0; j < col; j++) {
               if ( detail_h[i][j] <= 0.0){
                   detail_h[i][j] = 0.0;
               }
               if ( detail_h[i][j] >= 255.0){
                   detail_h[i][j] = 255.0;
               }
           unsigned int temp;
           temp = (unsigned int) detail_h[i][j] ;
           QRgb value = qRgb(temp,temp,temp);
           detail_himg.setPixel(j,i,value);
           }
       }

       for (int i = 0; i < row; i++) {
           for (int j = 0; j < col; j++) {
               if ( detail_v[i][j] <= 0.0){
                   detail_v[i][j] = 0.0;
               }
               if ( detail_v[i][j] >= 255.0){
                   detail_v[i][j] = 255.0;
               }
           unsigned int temp;
           temp = (unsigned int) detail_v[i][j] ;
           QRgb value = qRgb(temp,temp,temp);
           detail_vimg.setPixel(j,i,value);
           }
       }

       for (int i = 0; i < row; i++) {
           for (int j = 0; j < col; j++) {
               if ( detail_d[i][j] <= 0.0){
                   detail_d[i][j] = 0.0;
               }
               if ( detail_d[i][j] >= 255.0){
                   detail_d[i][j] = 255.0;
               }
           unsigned int temp;
           temp = (unsigned int) detail_d[i][j] ;
           QRgb value = qRgb(temp,temp,temp);
           detail_dimg.setPixel(j,i,value);
           }
       }

       QLabel *label2 = new QLabel(QString("Approximated Image at Level %1").arg(J));
       QLabel *label3 = new QLabel(QString("Horizontal Details at Level %1").arg(J));
       QLabel *label4 = new QLabel(QString("Vertical Details at Level %1").arg(J));
       QLabel *label5 = new QLabel(QString("Diagonal Details at Level %1").arg(J));
       label2->setAlignment(Qt::AlignCenter);
       label3->setAlignment(Qt::AlignCenter);
       label4->setAlignment(Qt::AlignCenter);
       label5->setAlignment(Qt::AlignCenter);
       label2->setScaledContents(true);
       label3->setScaledContents(true);
       label4->setScaledContents(true);
       label5->setScaledContents(true);

       dwtimage = blurimg;

       QPixmap pixblur;

       pixblur.convertFromImage(blurimg);

       QLabel *labelblur = new QLabel(this);
       labelblur->setPixmap(pixblur);

       QPixmap pixdetail_h;

       pixdetail_h.convertFromImage(detail_himg);

       QLabel *labeldetail_h = new QLabel(this);
       labeldetail_h->setPixmap(pixdetail_h);

       QPixmap pixdetail_v;

       pixdetail_v.convertFromImage(detail_vimg);

       QLabel *labeldetail_v = new QLabel(this);
       labeldetail_v->setPixmap(pixdetail_v);

       QPixmap pixdetail_d;

       pixdetail_d.convertFromImage(detail_dimg);

       QLabel *labeldetail_d = new QLabel(this);
       labeldetail_d->setPixmap(pixdetail_d);
       sfact = 1.0;
       if ((pixblur.width() < labelblur->width()) || (pixblur.height() < labelblur->height())) {
       sfact =min((double) pixblur.width()/(double) labelblur->width(),(double) pixblur.height()/(double) labelblur->height());
       labelblur->resize(sfact * labelblur->pixmap()->size());
   } else if ((pixblur.width() >= labelblur->width()) && (pixblur.height() >= labelblur->height())) {
       sfact =min((double) pixblur.width()/(double) labelblur->width(),(double) pixblur.height()/(double) labelblur->height());
       labelblur->resize(sfact * labelblur->size());
       labelblur->setScaledContents(true);

   } else {
       labelblur->setScaledContents(true);

   }

   sfact = 1.0;
   if ((pixdetail_h.width() < labeldetail_h->width()) || (pixdetail_h.height() < labeldetail_h->height())) {
   sfact =min((double) pixdetail_h.width()/(double) labeldetail_h->width(),(double) pixdetail_h.height()/(double) labeldetail_h->height());
   labeldetail_h->resize(sfact * labeldetail_h->pixmap()->size());
} else if ((pixdetail_h.width() >= labeldetail_h->width()) && (pixdetail_h.height() >= labeldetail_h->height())) {
   sfact =min((double) pixdetail_h.width()/(double) labeldetail_h->width(),(double) pixdetail_h.height()/(double) labeldetail_h->height());
   labeldetail_h->resize(sfact * labeldetail_h->size());
   labeldetail_h->setScaledContents(true);

} else {
   labeldetail_h->setScaledContents(true);

}

sfact = 1.0;
if ((pixdetail_v.width() < labeldetail_v->width()) || (pixdetail_v.height() < labeldetail_v->height())) {
sfact =min((double) pixdetail_v.width()/(double) labeldetail_v->width(),(double) pixdetail_v.height()/(double) labeldetail_v->height());
labeldetail_v->resize(sfact * labeldetail_v->pixmap()->size());
} else if ((pixdetail_v.width() >= labeldetail_v->width()) && (pixdetail_v.height() >= labeldetail_v->height())) {
sfact =min((double) pixdetail_v.width()/(double) labeldetail_v->width(),(double) pixdetail_v.height()/(double) labeldetail_v->height());
labeldetail_v->resize(sfact * labeldetail_v->size());
labeldetail_v->setScaledContents(true);

} else {
labeldetail_v->setScaledContents(true);

}

sfact = 1.0;
if ((pixdetail_d.width() < labeldetail_d->width()) || (pixdetail_d.height() < labeldetail_d->height())) {
sfact =min((double) pixdetail_d.width()/(double) labeldetail_d->width(),(double) pixdetail_d.height()/(double) labeldetail_d->height());
labeldetail_d->resize(sfact * labeldetail_d->pixmap()->size());
} else if ((pixdetail_d.width() >= labeldetail_d->width()) && (pixdetail_d.height() >= labeldetail_d->height())) {
sfact =min((double) pixdetail_d.width()/(double) labeldetail_d->width(),(double) pixdetail_d.height()/(double) labeldetail_d->height());
labeldetail_d->resize(sfact * labeldetail_d->size());
labeldetail_d->setScaledContents(true);

} else {
labeldetail_d->setScaledContents(true);

}

  QPushButton *blurbutton = new QPushButton("View FullSize Image");
  QPushButton *hdetailbutton = new QPushButton("View FullSize Image");
  QPushButton *vdetailbutton = new QPushButton("View FullSize Image");
  QPushButton *ddetailbutton = new QPushButton("View FullSize Image");

  swtblur = blurimg;
  swth = detail_himg;
  swtv = detail_vimg;
  swtd = detail_dimg;

      signalMapper = new QSignalMapper(this);
      signalMapper->setMapping(blurbutton, 0);
      signalMapper->setMapping(hdetailbutton, 1);
      signalMapper->setMapping(vdetailbutton, 2);
      signalMapper->setMapping(ddetailbutton, 3);

      connect(blurbutton, SIGNAL(clicked()),
          signalMapper, SLOT (map()));
      connect(hdetailbutton, SIGNAL(clicked()),
          signalMapper, SLOT (map()));
      connect(vdetailbutton, SIGNAL(clicked()),
          signalMapper, SLOT (map()));
      connect(ddetailbutton, SIGNAL(clicked()),
          signalMapper, SLOT (map()));

      connect(signalMapper, SIGNAL(mapped(int )),this, SLOT(setSWTVAL(int )));



       glayout->addWidget(label2,1,2);
       glayout->addWidget(labelblur,2,2);
       glayout->addWidget(blurbutton,3,2);
       glayout->addWidget(label3,4,1);
       glayout->addWidget(label4,4,2);
       glayout->addWidget(label5,4,3);
       glayout->addWidget(labeldetail_h,5,1);
       glayout->addWidget(labeldetail_v,5,2);
       glayout->addWidget(labeldetail_d,5,3);
       glayout->addWidget(hdetailbutton,6,1);
       glayout->addWidget(vdetailbutton,6,2);
       glayout->addWidget(ddetailbutton,6,3);
       glayout->addItem(spacer,7,1);

       glayout->update();

}

void MainWindow::dispSWT_RGB(vector<double> &output_r,vector<double> &output_g,vector<double> &output_b,int J,int row, int col){
    QLayoutItem *child;
    while ((child = glayout->takeAt(0)) != 0)
    {
    delete child->widget();
    delete child;
    }

    vspacer = new QSpacerItem( 10, 10, QSizePolicy::Minimum,
    QSizePolicy::Expanding );
    hspacer1 = new QSpacerItem( 10, 10, QSizePolicy::Expanding,
    QSizePolicy::Minimum );
    hspacer2 = new QSpacerItem( 10, 10, QSizePolicy::Expanding,
    QSizePolicy::Minimum );
    spacer = new QSpacerItem( 10, 10, QSizePolicy::Minimum,
    QSizePolicy::Expanding );

    QLabel *label1 = new QLabel("Original Image");
    label1->setAlignment(Qt::AlignCenter);
    label1->setScaledContents(true);

    QPixmap pix;

    pix.convertFromImage(image);

    QLabel *labelorig = new QLabel(this);
    labelorig->setPixmap(pix);
    labelorig->setScaledContents(true);

    glayout->addItem(vspacer,0,1);
    glayout->addItem(hspacer1,1,0);
    glayout->addWidget(label1,1,1);
    glayout->addWidget(labelorig,2,1);
    glayout->addItem(hspacer2,1,4);

    vector<vector<double> > blur_r(row,vector<double>(col));
    vector<vector<double> > blur_g(row,vector<double>(col));
    vector<vector<double> > blur_b(row,vector<double>(col));
    vector<vector<double> > detail_h_r(row,vector<double>(col));
    vector<vector<double> > detail_h_g(row,vector<double>(col));
    vector<vector<double> > detail_h_b(row,vector<double>(col));
    vector<vector<double> > detail_v_r(row,vector<double>(col));
    vector<vector<double> > detail_v_g(row,vector<double>(col));
    vector<vector<double> > detail_v_b(row,vector<double>(col));
    vector<vector<double> > detail_d_r(row,vector<double>(col));
    vector<vector<double> > detail_d_g(row,vector<double>(col));
    vector<vector<double> > detail_d_b(row,vector<double>(col));

       for (int i=0;i < row; i++){
               for (int j=0; j < col;j++){
            double temp_r = output_r[i*col + j];
            blur_r[i][j]= temp_r;
            double temp_g = output_g[i*col + j];
            blur_g[i][j]= temp_g;
            double temp_b = output_b[i*col + j];
            blur_b[i][j]= temp_b;
               }
       }

       for (int i=0;i < row; i++){
               for (int j=0; j < col;j++){
            double temp_r = output_r[row * col +i*col + j];
            detail_h_r[i][j]= temp_r;
            double temp_g = output_g[row* col+i*col + j];
            detail_h_g[i][j]= temp_g;
            double temp_b = output_b[row * col+i*col + j];
            detail_h_b[i][j]= temp_b;
               }
       }

       for (int i=0;i < row; i++){
               for (int j=0; j < col;j++){
            double temp_r = output_r[2 *row * col +i*col + j];
            detail_v_r[i][j]= temp_r;
            double temp_g = output_g[2 *row* col+i*col + j];
            detail_v_g[i][j]= temp_g;
            double temp_b = output_b[2 *row * col+i*col + j];
            detail_v_b[i][j]= temp_b;
               }
       }

       for (int i=0;i < row; i++){
               for (int j=0; j < col;j++){
            double temp_r = output_r[3 *row * col +i*col + j];
            detail_d_r[i][j]= temp_r;
            double temp_g = output_g[3 *row* col+i*col + j];
            detail_d_g[i][j]= temp_g;
            double temp_b = output_b[3 *row * col+i*col + j];
            detail_d_b[i][j]= temp_b;
               }
       }
       QImage blurimg(col,row,QImage::Format_RGB32);
       QImage detail_himg(col,row,QImage::Format_RGB32);
       QImage detail_vimg(col,row,QImage::Format_RGB32);
       QImage detail_dimg(col,row,QImage::Format_RGB32);

       double max_r,max_b,max_g;

       maxval(output_r,max_r);
       maxval(output_g,max_g);
       maxval(output_b,max_b);



       for (int i = 0; i < row; i++) {
           for (int j = 0; j < col; j++) {
               if ( blur_r[i][j] <= 0.0){
                   blur_r[i][j] = 0.0;
               }
               if ( blur_g[i][j] <= 0.0){
                   blur_g[i][j] = 0.0;
               }
               if ( blur_b[i][j] <= 0.0){
                   blur_b[i][j] = 0.0;
               }
           unsigned int temp_r, temp_g, temp_b;
           temp_r = (unsigned int) ((blur_r[i][j] / max_r) * 255.0);
           temp_g = (unsigned int) ((blur_g[i][j] / max_g) * 255.0);
           temp_b = (unsigned int) ((blur_b[i][j] / max_b) * 255.0);

           QRgb value = qRgb(temp_r,temp_g,temp_b);
           blurimg.setPixel(j,i,value);
           }
       }

       for (int i = 0; i < row; i++) {
           for (int j = 0; j < col; j++) {
               if ( detail_h_r[i][j] <= 0.0){
                   detail_h_r[i][j] = 0.0;
               }
               if ( detail_h_g[i][j] <= 0.0){
                   detail_h_g[i][j] = 0.0;
               }
               if ( detail_h_b[i][j] <= 0.0){
                   detail_h_b[i][j] = 0.0;
               }
               if ( detail_h_r[i][j] >= 255.0){
                   detail_h_r[i][j] = 255.0;
               }
               if ( detail_h_g[i][j] >= 255.0){
                   detail_h_g[i][j] = 255.0;
               }
               if ( detail_h_b[i][j] >= 255.0){
                   detail_h_b[i][j] = 255.0;
               }
           unsigned int temp_r, temp_g, temp_b;
           temp_r = (unsigned int) detail_h_r[i][j] ;
           temp_g = (unsigned int) detail_h_g[i][j];
           temp_b = (unsigned int) detail_h_b[i][j] ;

           QRgb value = qRgb(temp_r,temp_g,temp_b);
           detail_himg.setPixel(j,i,value);
           }
       }

       for (int i = 0; i < row; i++) {
           for (int j = 0; j < col; j++) {
               if ( detail_v_r[i][j] <= 0.0){
                   detail_v_r[i][j] = 0.0;
               }
               if ( detail_v_g[i][j] <= 0.0){
                   detail_v_g[i][j] = 0.0;
               }
               if ( detail_v_b[i][j] <= 0.0){
                   detail_v_b[i][j] = 0.0;
               }
               if ( detail_v_r[i][j] >= 255.0){
                   detail_v_r[i][j] = 255.0;
               }
               if ( detail_v_g[i][j] >= 255.0){
                   detail_v_g[i][j] = 255.0;
               }
               if ( detail_v_b[i][j] >= 255.0){
                   detail_v_b[i][j] = 255.0;
               }
           unsigned int temp_r, temp_g, temp_b;
           temp_r = (unsigned int) detail_v_r[i][j] ;
           temp_g = (unsigned int) detail_v_g[i][j];
           temp_b = (unsigned int) detail_v_b[i][j] ;

           QRgb value = qRgb(temp_r,temp_g,temp_b);
           detail_vimg.setPixel(j,i,value);
           }
       }

       for (int i = 0; i < row; i++) {
           for (int j = 0; j < col; j++) {
               if ( detail_d_r[i][j] <= 0.0){
                   detail_d_r[i][j] = 0.0;
               }
               if ( detail_d_g[i][j] <= 0.0){
                   detail_d_g[i][j] = 0.0;
               }
               if ( detail_d_b[i][j] <= 0.0){
                   detail_d_b[i][j] = 0.0;
               }
               if ( detail_d_r[i][j] >= 255.0){
                   detail_d_r[i][j] = 255.0;
               }
               if ( detail_d_g[i][j] >= 255.0){
                   detail_d_g[i][j] = 255.0;
               }
               if ( detail_d_b[i][j] >= 255.0){
                   detail_d_b[i][j] = 255.0;
               }
           unsigned int temp_r, temp_g, temp_b;
           temp_r = (unsigned int) detail_d_r[i][j] ;
           temp_g = (unsigned int) detail_d_g[i][j];
           temp_b = (unsigned int) detail_d_b[i][j] ;

           QRgb value = qRgb(temp_r,temp_g,temp_b);
           detail_dimg.setPixel(j,i,value);
           }
       }

       QLabel *label2 = new QLabel(QString("Approximated Image at Level %1").arg(J));
       QLabel *label3 = new QLabel(QString("Horizontal Details at Level %1").arg(J));
       QLabel *label4 = new QLabel(QString("Vertical Details at Level %1").arg(J));
       QLabel *label5 = new QLabel(QString("Diagonal Details at Level %1").arg(J));
       label2->setAlignment(Qt::AlignCenter);
       label3->setAlignment(Qt::AlignCenter);
       label4->setAlignment(Qt::AlignCenter);
       label5->setAlignment(Qt::AlignCenter);
       label2->setScaledContents(true);
       label3->setScaledContents(true);
       label4->setScaledContents(true);
       label5->setScaledContents(true);

       dwtimage = blurimg;

       QPixmap pixblur;

       pixblur.convertFromImage(blurimg);

       QLabel *labelblur = new QLabel(this);
       labelblur->setPixmap(pixblur);

       QPixmap pixdetail_h;

       pixdetail_h.convertFromImage(detail_himg);

       QLabel *labeldetail_h = new QLabel(this);
       labeldetail_h->setPixmap(pixdetail_h);

       QPixmap pixdetail_v;

       pixdetail_v.convertFromImage(detail_vimg);

       QLabel *labeldetail_v = new QLabel(this);
       labeldetail_v->setPixmap(pixdetail_v);

       QPixmap pixdetail_d;

       pixdetail_d.convertFromImage(detail_dimg);

       QLabel *labeldetail_d = new QLabel(this);
       labeldetail_d->setPixmap(pixdetail_d);

       labelblur->setScaledContents(true);
       labeldetail_d->setScaledContents(true);
       labeldetail_h->setScaledContents(true);
       labeldetail_v->setScaledContents(true);

       QPushButton *blurbutton = new QPushButton("View FullSize Image");
       QPushButton *hdetailbutton = new QPushButton("View FullSize Image");
       QPushButton *vdetailbutton = new QPushButton("View FullSize Image");
       QPushButton *ddetailbutton = new QPushButton("View FullSize Image");

       swtblur = blurimg;
       swth = detail_himg;
       swtv = detail_vimg;
       swtd = detail_dimg;

           signalMapper = new QSignalMapper(this);
           signalMapper->setMapping(blurbutton, 0);
           signalMapper->setMapping(hdetailbutton, 1);
           signalMapper->setMapping(vdetailbutton, 2);
           signalMapper->setMapping(ddetailbutton, 3);

           connect(blurbutton, SIGNAL(clicked()),
               signalMapper, SLOT (map()));
           connect(hdetailbutton, SIGNAL(clicked()),
               signalMapper, SLOT (map()));
           connect(vdetailbutton, SIGNAL(clicked()),
               signalMapper, SLOT (map()));
           connect(ddetailbutton, SIGNAL(clicked()),
               signalMapper, SLOT (map()));

           connect(signalMapper, SIGNAL(mapped(int )),this, SLOT(setSWTVAL(int )));



           glayout->addWidget(label2,1,2);
           glayout->addWidget(labelblur,2,2);
           glayout->addWidget(blurbutton,3,2);
           glayout->addWidget(label3,4,1);
           glayout->addWidget(label4,4,2);
           glayout->addWidget(label5,4,3);
           glayout->addWidget(labeldetail_h,5,1);
           glayout->addWidget(labeldetail_v,5,2);
           glayout->addWidget(labeldetail_d,5,3);
           glayout->addWidget(hdetailbutton,6,1);
           glayout->addWidget(vdetailbutton,6,2);
           glayout->addWidget(ddetailbutton,6,3);
           glayout->addItem(spacer,7,1);



       glayout->update();

}

void MainWindow::dispDWT_PER(vector<vector<double> > &output,int J,int row, int col){
    QLayoutItem *child;
    while ((child = glayout->takeAt(0)) != 0)
    {
    delete child->widget();
    delete child;
    }

    vspacer = new QSpacerItem( 10, 10, QSizePolicy::Minimum,
    QSizePolicy::Expanding );
    hspacer1 = new QSpacerItem( 10, 10, QSizePolicy::Expanding,
    QSizePolicy::Minimum );
    hspacer2 = new QSpacerItem( 10, 10, QSizePolicy::Expanding,
    QSizePolicy::Minimum );
    spacer = new QSpacerItem( 10, 10, QSizePolicy::Minimum,
    QSizePolicy::Expanding );

    QLabel *label1 = new QLabel("Original Image");
    label1->setAlignment(Qt::AlignCenter);
    label1->setScaledContents(true);


    QPixmap pix;

    pix.convertFromImage(image);

    QLabel *labelorig = new QLabel(this);
    labelorig->setPixmap(pix);
    labelorig->setScaledContents(true);


    glayout->addItem(vspacer,0,1);
    glayout->addItem(hspacer1,1,0);
    glayout->addWidget(label1,1,1);
    glayout->addWidget(labelorig,2,1);
    glayout->addItem(hspacer2,1,4);


    QImage dwt_image(col,row,QImage::Format_RGB32);
    double max;

    maxval2(output,max);


    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if ( output[i][j] <= 0.0){
                output[i][j] = 0.0;
            }
            unsigned int temp;
            if ( (i <= (row/pow(2.0,(double) J))) && (j <= (col/pow(2.0,(double) J)))) {
            temp = (unsigned int) ((output[i][j] / max) * 255.0);
        } else {
            temp = (unsigned int) output[i][j] ;
        }
            QRgb value = qRgb(temp,temp,temp);
            dwt_image.setPixel(j,i,value);
        }
    }

    dwtimage = dwt_image;

    QLabel *label2 = new QLabel(QString("DWT Output at Level %1").arg(J));
    label2->setAlignment(Qt::AlignCenter);

    QPixmap pixdwt;

    pixdwt.convertFromImage(dwt_image);

    QLabel *labeldwt = new QLabel(this);
    labeldwt->setPixmap(pixdwt);
    labeldwt->setScaledContents(true);


    QPushButton *dwtfullbutton = new QPushButton("View FullSize Image");
    connect(dwtfullbutton,SIGNAL(clicked()),this,SLOT(dwtFULLVIEW()));

    glayout->addWidget(label2,1,2);
    glayout->addWidget(labeldwt,2,2);

    glayout->addWidget(dwtfullbutton,3,2);


    glayout->addItem(spacer,4,1);

    glayout->update();

}

void MainWindow::dispDWT_PER_RGB(vector<vector<double> > &output_r,vector<vector<double> > &output_g,
                                 vector<vector<double> > &output_b,int J,int row, int col){
    QLayoutItem *child;
    while ((child = glayout->takeAt(0)) != 0)
    {
    delete child->widget();
    delete child;
    }

    vspacer = new QSpacerItem( 10, 10, QSizePolicy::Minimum,
    QSizePolicy::Expanding );
    hspacer1 = new QSpacerItem( 10, 10, QSizePolicy::Expanding,
    QSizePolicy::Minimum );
    hspacer2 = new QSpacerItem( 10, 10, QSizePolicy::Expanding,
    QSizePolicy::Minimum );
    spacer = new QSpacerItem( 10, 10, QSizePolicy::Minimum,
    QSizePolicy::Expanding );

    QLabel *label1 = new QLabel("Original Image");
    label1->setAlignment(Qt::AlignCenter);
    label1->setScaledContents(true);

    QPixmap pix;

    pix.convertFromImage(image);

    QLabel *labelorig = new QLabel(this);
    labelorig->setPixmap(pix);
    labelorig->setScaledContents(true);


    glayout->addItem(vspacer,0,1);
    glayout->addItem(hspacer1,1,0);
    glayout->addWidget(label1,1,1);
    glayout->addWidget(labelorig,2,1);
    glayout->addItem(hspacer2,1,3);


    QImage dwt_image(col,row,QImage::Format_RGB32);
    double max_r,max_g,max_b;

    maxval2(output_r,max_r);
    maxval2(output_g,max_g);
    maxval2(output_b,max_b);



    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if ( output_r[i][j] <= 0.0){
                output_r[i][j] = 0.0;
            }
            if ( output_g[i][j] <= 0.0){
                output_g[i][j] = 0.0;
            }
            if ( output_b[i][j] <= 0.0){
                output_b[i][j] = 0.0;
            }
            unsigned int temp_r,temp_g,temp_b;
            if ( (i <= (row/pow(2.0,(double) J))) && (j <= (col/pow(2.0,(double) J)))) {
            temp_r = (unsigned int) ((output_r[i][j] / max_r) * 255.0);
            temp_g = (unsigned int) ((output_g[i][j] / max_g) * 255.0);
            temp_b = (unsigned int) ((output_b[i][j] / max_b) * 255.0);
        } else {
            temp_r = (unsigned int) output_r[i][j] ;
            temp_g = (unsigned int) output_g[i][j] ;
            temp_b = (unsigned int) output_b[i][j] ;
        }
            QRgb value = qRgb(temp_r,temp_g,temp_b);
            dwt_image.setPixel(j,i,value);
        }
    }

    dwtimage = dwt_image;

    QLabel *label2 = new QLabel(QString("DWT Output at Level %1").arg(J));
    label2->setAlignment(Qt::AlignCenter);
    label2->setScaledContents(true);

    QPixmap pixdwt;

    pixdwt.convertFromImage(dwt_image);

    QLabel *labeldwt = new QLabel(this);
    labeldwt->setPixmap(pixdwt);
    labeldwt->setScaledContents(true);

    QPushButton *dwtfullbutton = new QPushButton("View FullSize Image");
    connect(dwtfullbutton,SIGNAL(clicked()),this,SLOT(dwtFULLVIEW()));

    glayout->addWidget(label2,1,2);
    glayout->addWidget(labeldwt,2,2);

    glayout->addWidget(dwtfullbutton,3,2);
    glayout->addItem(spacer,4,1);
    glayout->update();

}

void MainWindow::dispDWT_SYM(vector<double>  &output,int J ,vector<int> length) {
    QLayoutItem *child;
    while ((child = glayout->takeAt(0)) != 0)
    {
    delete child->widget();
    delete child;
    }

    vspacer = new QSpacerItem( 10, 10, QSizePolicy::Minimum,
    QSizePolicy::Expanding );
    hspacer1 = new QSpacerItem( 10, 10, QSizePolicy::Expanding,
    QSizePolicy::Minimum );
    hspacer2 = new QSpacerItem( 10, 10, QSizePolicy::Expanding,
    QSizePolicy::Minimum );
    spacer = new QSpacerItem( 10, 10, QSizePolicy::Minimum,
    QSizePolicy::Expanding );

    QLabel *label1 = new QLabel("Original Image");
    label1->setAlignment(Qt::AlignCenter);
    label1->setScaledContents(true);

    QPixmap pix;

    pix.convertFromImage(image);

    QLabel *labelorig = new QLabel(this);
    labelorig->setPixmap(pix);
    labelorig->setScaledContents(true);

    glayout->addItem(vspacer,0,1);
    glayout->addItem(hspacer1,1,0);
    glayout->addWidget(label1,1,1);
    glayout->addWidget(labelorig,2,1);
    glayout->addItem(hspacer2,1,3);


    double max;
    vector<int> length2;

    dwt_output_dim_sym(length,length2,J);

    int siz = length2.size();
    int rows_n=length2[siz-2];
    int cols_n = length2[siz-1];

    QImage dwt_image(cols_n,rows_n,QImage::Format_RGB32);


    vector<vector< double> > dwt_disp(rows_n, vector<double>(cols_n));
    dispDWT(output,dwt_disp, length ,length2, J);

    maxval2(dwt_disp,max);

    for (int i = 0; i < rows_n; i++) {
        for (int j = 0; j < cols_n; j++) {
            if ( dwt_disp[i][j] <= 0.0){
                dwt_disp[i][j] = 0.0;
            }
            unsigned int temp;
            if ( (i <= length2[0]) && (j <= length2[1])) {
            temp = (unsigned int) ((dwt_disp[i][j] / max) * 255.0);
        } else {
            temp = (unsigned int) dwt_disp[i][j] ;
        }
            QRgb value = qRgb(temp,temp,temp);
            dwt_image.setPixel(j,i,value);
        }
    }

    dwtimage = dwt_image;

    QLabel *label2 = new QLabel(QString("DWT Output at Level %1").arg(J));
    label2->setAlignment(Qt::AlignCenter);
    label2->setScaledContents(true);

    QPixmap pixdwt;

    pixdwt.convertFromImage(dwt_image);

    QLabel *labeldwt = new QLabel(this);
    labeldwt->setPixmap(pixdwt);
    labeldwt->setScaledContents(true);


    QPushButton *dwtfullbutton = new QPushButton("View FullSize Image");
    connect(dwtfullbutton,SIGNAL(clicked()),this,SLOT(dwtFULLVIEW()));

    QPushButton *expdwtbutton = new QPushButton("Expansive View");
    connect(expdwtbutton,SIGNAL(clicked()),this,SLOT(dwtEXPVIEW()));

    glayout->addWidget(label2,1,2);
    glayout->addWidget(labeldwt,2,2);

    glayout->addWidget(dwtfullbutton,3,2);
    glayout->addWidget(expdwtbutton,4,2);
    glayout->addItem(spacer,5,1);


    glayout->update();


}

void MainWindow::dispDWT_SYM_RGB(vector<double>  &output_r,vector<double>  &output_g,
                                 vector<double>  &output_b,int J ,vector<int> length) {
    QLayoutItem *child;
    while ((child = glayout->takeAt(0)) != 0)
    {
    delete child->widget();
    delete child;
    }

    vspacer = new QSpacerItem( 10, 10, QSizePolicy::Minimum,
    QSizePolicy::Expanding );
    hspacer1 = new QSpacerItem( 10, 10, QSizePolicy::Expanding,
    QSizePolicy::Minimum );
    hspacer2 = new QSpacerItem( 10, 10, QSizePolicy::Expanding,
    QSizePolicy::Minimum );
    spacer = new QSpacerItem( 10, 10, QSizePolicy::Minimum,
    QSizePolicy::Expanding );

    QLabel *label1 = new QLabel("Original Image");
    label1->setAlignment(Qt::AlignCenter);
    label1->setScaledContents(true);

    QPixmap pix;

    pix.convertFromImage(image);

    QLabel *labelorig = new QLabel(this);
    labelorig->setPixmap(pix);
    labelorig->setScaledContents(true);

    glayout->addItem(vspacer,0,1);
    glayout->addItem(hspacer1,1,0);
    glayout->addWidget(label1,1,1);
    glayout->addWidget(labelorig,2,1);
    glayout->addItem(hspacer2,1,3);

    vector<int> length2;

    dwt_output_dim_sym(length,length2,J);

    int siz = length2.size();
    int rows=length2[siz-2];
    int cols = length2[siz-1];

    QImage dwt_image(cols,rows,QImage::Format_RGB32);


    vector<vector< double> > dwt_disp_r(rows, vector<double>(cols));
    vector<vector< double> > dwt_disp_g(rows, vector<double>(cols));
    vector<vector< double> > dwt_disp_b(rows, vector<double>(cols));

    dispDWT(output_r,dwt_disp_r, length ,length2, J);
    dispDWT(output_g,dwt_disp_g, length ,length2, J);
    dispDWT(output_b,dwt_disp_b, length ,length2, J);

    double maxr,maxg,maxb;
    maxval2(dwt_disp_r,maxr);
    maxval2(dwt_disp_g,maxg);
    maxval2(dwt_disp_b,maxb);


    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if ( dwt_disp_r[i][j] <= 0.0){
                dwt_disp_r[i][j] = 0.0;
            }
            if ( dwt_disp_g[i][j] <= 0.0){
                dwt_disp_g[i][j] = 0.0;
            }
            if ( dwt_disp_b[i][j] <= 0.0){
                dwt_disp_b[i][j] = 0.0;
            }
            unsigned int temp_r, temp_g,temp_b;
            if ( (i <= length2[0]) && (j <= length2[1])) {
            temp_r = (unsigned int) ((dwt_disp_r[i][j] / maxr) * 255.0);
            temp_g = (unsigned int) ((dwt_disp_g[i][j] / maxg) * 255.0);
            temp_b = (unsigned int) ((dwt_disp_b[i][j] / maxb) * 255.0);

        } else {
            temp_r = (unsigned int) dwt_disp_r[i][j] ;
            temp_g = (unsigned int) dwt_disp_g[i][j] ;
            temp_b = (unsigned int) dwt_disp_b[i][j] ;

        }
            QRgb value = qRgb(temp_r,temp_g,temp_b);
            dwt_image.setPixel(j,i,value);

        }
    }

    dwtimage = dwt_image;

    QLabel *label2 = new QLabel(QString("DWT Output at Level %1").arg(J));
    label2->setAlignment(Qt::AlignCenter);
    label2->setScaledContents(true);

    QPixmap pixdwt;

    pixdwt.convertFromImage(dwt_image);

    QLabel *labeldwt = new QLabel(this);
    labeldwt->setPixmap(pixdwt);
    labeldwt->setScaledContents(true);

    QPushButton *dwtfullbutton = new QPushButton("View FullSize Image");
    connect(dwtfullbutton,SIGNAL(clicked()),this,SLOT(dwtFULLVIEW()));

  //  QPushButton *expdwtbutton = new QPushButton("Expansive View");
  //  connect(expdwtbutton,SIGNAL(clicked()),this,SLOT(dwtEXPVIEW()));

    glayout->addWidget(label2,1,2);
    glayout->addWidget(labeldwt,2,2);

    glayout->addWidget(dwtfullbutton,3,2);
   // glayout->addWidget(expdwtbutton,4,2);
    glayout->addItem(spacer,4,1);

    glayout->update();

    dwt_disp_r.clear();
    dwt_disp_r.clear();
    dwt_disp_r.clear();
}
void MainWindow::reportDWT() {
    QTextBrowser *report = new QTextBrowser();
    report->setReadOnly(true);
    report->setWindowTitle("DWT OUTPUT");
   // report->setText(QString("DWT Report \n\n"));
  //  report->setText(QString("Signal Length : "));
  //  QTextDocument *doc = new QTextDocument();
    vector<double> lp1,hp1,lp2,hp2;
    filtcoef(nm,lp1,hp1,lp2,hp2);

//    unsigned int sig_length = original_signal.size();
    QString nm2(nm.c_str());
    int oup_length;
    oup_length = dwt_coefficients.size();

    QString str;
    str = "DWT OUTPUT \n \n";
 //   str.append(QString("Length of Signal : %1 \n \n").arg(sig_length));
    str.append(QString("Wavelet Used : %1 \n \n").arg(nm2));
    str.append(QString("Decomposition Levels : %1 \n \n").arg(J));
    str.append(QString("DWT Execution Time ( in mSec) : %1 \n \n").arg(exec_time));


    report->setText(str);

    report->show();

}

void MainWindow::approximateSig2() {
    int Max_Iter,Max_Iter_sym;
    if (image.isNull()) {
        errormessage();
    }
    int sig_length = min(image.height(),image.width());
    Max_Iter = (int) floor(log( double(sig_length))/log (2.0)) - 1;
    Max_Iter_sym = (int) floor(log( double(sig_length))/log (2.0));

    dwtbutton->setEnabled(false);
    appxbutton->setEnabled(false);



    int width = image.width();
    int height = image.height();

    vector<vector<double> > vec(height,vector<double>(width));
    vector<vector<double> > vecred(height,vector<double>(width));
    vector<vector<double> > vecgreen(height,vector<double>(width));
    vector<vector<double> > vecblue(height,vector<double>(width));

    vector<vector<double> > idwt_output(height, vector<double>(width));
    vector<vector<double> > idwt_output_r(height, vector<double>(width));
    vector<vector<double> > idwt_output_g(height, vector<double>(width));
    vector<vector<double> > idwt_output_b(height, vector<double>(width));

    int form = image.format();

    if (form == 3) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            vec[i][j] = (double) (image.pixelIndex(j,i));
        }
    }
} else if ((form != 3) && (mode_color_appx == "GrayScale (Faster)")) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
    QRgb value = image.pixel(j,i);
    double temp1 = (double) (qRed(value));
    double temp2 = (double) (qGreen(value));
    double temp3 = (double) (qBlue(value));
    vec[i][j] =  0.59 * temp2 + 0.30 * temp1 + 0.11 * temp3;
    form = 3;
}
    }
} else {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            QRgb value = image.pixel(j,i);
            vecred[i][j] = (double) (qRed(value));
            vecgreen[i][j] = (double) (qGreen(value));
            vecblue[i][j] = (double) (qBlue(value));
        }
    }
}


  vector<double> flag,flag_r,flag_g,flag_b,dwt_output,dwt_output_r,dwt_output_g,dwt_output_b;
  int rr1,cc1;
  dwt_output_dim(vec, rr1, cc1 );
  vector<vector<double> >  dwt_output_per(rr1, vector<double>(cc1));
  vector<vector<double> >  dwt_output_per_r(rr1, vector<double>(cc1));
  vector<vector<double> >  dwt_output_per_g(rr1, vector<double>(cc1));
  vector<vector<double> >  dwt_output_per_b(rr1, vector<double>(cc1));

  vector<vector<double> >  idwt_output_per(rr1, vector<double>(cc1));
  vector<vector<double> >  idwt_output_per_r(rr1, vector<double>(cc1));
  vector<vector<double> >  idwt_output_per_g(rr1, vector<double>(cc1));
  vector<vector<double> >  idwt_output_per_b(rr1, vector<double>(cc1));
  vector<int> length,length_r,length_g,length_b;

  QTime cpu_time;

  // perform J-Level SWT/DWT
  if ( mode_appx == "dwt_per") {
     flag.clear();
     cpu_time.start();
     if ( form == 3) {
     dwt_2d(vec,Max_Iter, nm, dwt_output,flag,length );

     appx_coeff_sym(dwt_output);

     exec_time = cpu_time.elapsed();
     per_coeff_length = length;


 } else {

     dwt_2d(vecred,Max_Iter, nm, dwt_output_r,flag_r,length_r );
     dwt_2d(vecgreen,Max_Iter, nm, dwt_output_g,flag_g,length_g );
     dwt_2d(vecblue,Max_Iter, nm, dwt_output_b,flag_b,length_b );

     appx_coeff_sym(dwt_output_r);
     appx_coeff_sym(dwt_output_g);
     appx_coeff_sym(dwt_output_b);
     exec_time = cpu_time.elapsed();
     length = length_r;
     exec_time = cpu_time.elapsed();
     per_coeff_length = length;

 }

} else if (mode_appx == "dwt_sym") {
     flag.clear();
     cpu_time.start();
     if (form == 3) {
     dwt_2d_sym(vec,Max_Iter_sym,nm,dwt_output,flag,length,ext);
     appx_coeff_sym(dwt_output);
     exec_time = cpu_time.elapsed();
     sym_coeff_length = length;
 } else {
     dwt_2d_sym(vecred,Max_Iter_sym,nm,dwt_output_r,flag_r,length_r,ext);
     dwt_2d_sym(vecgreen,Max_Iter_sym,nm,dwt_output_g,flag_g,length_g,ext);
     dwt_2d_sym(vecblue,Max_Iter_sym,nm,dwt_output_b,flag_b,length_b,ext);

     appx_coeff_sym(dwt_output_r);
     appx_coeff_sym(dwt_output_g);
     appx_coeff_sym(dwt_output_b);
     length = length_r;
     exec_time = cpu_time.elapsed();
     sym_coeff_length = length;
 }
}

  if (mode_appx == "dwt_per") {
      if (form == 3) {

          idwt_2d(dwt_output,flag, nm, idwt_output,length);

          dispAPPX_PER(idwt_output);

      } else {

       idwt_2d(dwt_output_r,flag_r, nm, idwt_output_r,length_r);
       idwt_2d(dwt_output_g,flag_g, nm, idwt_output_g,length_g);
       idwt_2d(dwt_output_b,flag_b, nm, idwt_output_b,length_b);

       dispAPPX_PER_RGB(idwt_output_r,idwt_output_g,idwt_output_b);
      }
  } else if (mode_appx == "dwt_sym") {
      if (form == 3) {
       idwt_2d_sym( dwt_output,flag, nm, idwt_output,length);
       dispAPPX_PER(idwt_output);
      } else {
          idwt_2d_sym( dwt_output_r,flag_r, nm, idwt_output_r,length_r);
          idwt_2d_sym( dwt_output_g,flag_g, nm, idwt_output_g,length_g);
          idwt_2d_sym( dwt_output_b,flag_b, nm, idwt_output_b,length_b);

          dispAPPX_PER_RGB(idwt_output_r,idwt_output_g,idwt_output_b);

      }

  }

dwtbutton->setEnabled(true);
appxbutton->setEnabled(true);
}

void MainWindow::dispAPPX_PER(vector<vector<double> > &idwtop) {
    QLayoutItem *child;
    while ((child = glayout->takeAt(0)) != 0)
    {
    delete child->widget();
    delete child;
    }
    vspacer = new QSpacerItem( 10, 10, QSizePolicy::Minimum,
    QSizePolicy::Expanding );
    hspacer1 = new QSpacerItem( 10, 10, QSizePolicy::Expanding,
    QSizePolicy::Minimum );
    hspacer2 = new QSpacerItem( 10, 10, QSizePolicy::Expanding,
    QSizePolicy::Minimum );
    spacer = new QSpacerItem( 10, 10, QSizePolicy::Minimum,
    QSizePolicy::Expanding );

    QLabel *label1 = new QLabel("Original Image");
    label1->setAlignment(Qt::AlignCenter);
    label1->setScaledContents(true);


    QPixmap pix;

    pix.convertFromImage(image);

    QLabel *labelorig = new QLabel(this);
    labelorig->setPixmap(pix);
    labelorig->setScaledContents(true);

    glayout->addItem(vspacer,0,1);
    glayout->addItem(hspacer1,1,0);
    glayout->addWidget(label1,1,1);
    glayout->addWidget(labelorig,2,1);
    glayout->addItem(hspacer2,1,3);

    int r = image.height();
    int c = image.width();
    vector<vector<double> > dummy(r,vector<double>(c,0.0));

    zero_remove(dummy,idwtop);

    int row = idwtop.size();
    int col = idwtop[0].size();

    QImage appx_image(col,row,QImage::Format_RGB32);

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if ( idwtop[i][j] <= 0.0){
                idwtop[i][j] = 0.0;
            }

            unsigned int temp = (unsigned int) idwtop[i][j] ;

            QRgb value = qRgb(temp,temp,temp);
            appx_image.setPixel(j,i,value);
        }
    }
    approximatedimage = appx_image;
    appxoutbutton->setEnabled(true);
    QLabel *label2 = new QLabel(QString("Approximated Image using %1 \% Coefficients").arg(n_coef));
    label2->setAlignment(Qt::AlignCenter);
    label2->setScaledContents(true);

    QPixmap pix2;

    pix2.convertFromImage(appx_image);

    QLabel *labelappx = new QLabel(this);
    labelappx->setPixmap(pix2);
    labelappx->setScaledContents(true);

    QPushButton *appxfullbutton = new QPushButton("View FullSize Image");
    connect(appxfullbutton,SIGNAL(clicked()),this,SLOT(appxFULLVIEW()));

    glayout->addWidget(label2,1,2);
    glayout->addWidget(labelappx,2,2);

    glayout->addWidget(appxfullbutton,3,2);
    glayout->addItem(spacer,4,1);
    glayout->update();

}

void MainWindow::dispAPPX_PER_RGB(vector<vector<double> > &idwtop_r,vector<vector<double> > &idwtop_g,
                                  vector<vector<double> > &idwtop_b) {

    QLayoutItem *child;
    while ((child = glayout->takeAt(0)) != 0)
    {
    delete child->widget();
    delete child;
    }

    vspacer = new QSpacerItem( 10, 10, QSizePolicy::Minimum,
    QSizePolicy::Expanding );
    hspacer1 = new QSpacerItem( 10, 10, QSizePolicy::Expanding,
    QSizePolicy::Minimum );
    hspacer2 = new QSpacerItem( 10, 10, QSizePolicy::Expanding,
    QSizePolicy::Minimum );
    spacer = new QSpacerItem( 10, 10, QSizePolicy::Minimum,
    QSizePolicy::Expanding );

    QLabel *label1 = new QLabel("Original Image");
    label1->setAlignment(Qt::AlignCenter);
    label1->setScaledContents(true);


    QPixmap pix;

    pix.convertFromImage(image);

    QLabel *labelorig = new QLabel(this);
    labelorig->setPixmap(pix);
    labelorig->setScaledContents(true);

    glayout->addItem(vspacer,0,1);
    glayout->addItem(hspacer1,1,0);
    glayout->addWidget(label1,1,1);
    glayout->addWidget(labelorig,2,1);
    glayout->addItem(hspacer2,1,3);

    int r = image.height();
    int c = image.width();

    vector<vector<double> > dummy(r,vector<double>(c,0.0));
    zero_remove(dummy,idwtop_r);
    zero_remove(dummy,idwtop_g);
    zero_remove(dummy,idwtop_b);



    int row = idwtop_r.size();
    int col = idwtop_r[0].size();
    QImage appx_image(col,row,QImage::Format_RGB32);

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if ( idwtop_r[i][j] <= 0.0){
                idwtop_r[i][j] = 0.0;
            }
            if ( idwtop_g[i][j] <= 0.0){
                idwtop_g[i][j] = 0.0;
            }
            if ( idwtop_b[i][j] <= 0.0){
                idwtop_b[i][j] = 0.0;
            }

            unsigned int temp_r = (unsigned int) idwtop_r[i][j] ;
            unsigned int temp_g = (unsigned int) idwtop_g[i][j] ;
            unsigned int temp_b = (unsigned int) idwtop_b[i][j] ;


            QRgb value = qRgb(temp_r,temp_g,temp_b);
            appx_image.setPixel(j,i,value);
        }
    }

    approximatedimage = appx_image;
    appxoutbutton->setEnabled(true);


    QLabel *label2 = new QLabel(QString("Approximated Image using %1 \% Coefficients").arg(n_coef));
    label2->setAlignment(Qt::AlignCenter);
    label2->setScaledContents(true);

    QPixmap pix2;

    pix2.convertFromImage(appx_image);

    QLabel *labelappx = new QLabel(this);
    labelappx->setPixmap(pix2);
    labelappx->setScaledContents(true);


    QPushButton *appxfullbutton = new QPushButton("View FullSize Image");
    connect(appxfullbutton,SIGNAL(clicked()),this,SLOT(appxFULLVIEW()));

    glayout->addWidget(label2,1,2);
    glayout->addWidget(labelappx,2,2);

    glayout->addWidget(appxfullbutton,3,2);
    glayout->addItem(spacer,4,1);
    glayout->update();

}

void MainWindow::appx_coeff_per(vector<vector<double> > & dwtop) {
    double max;
    maxval2(dwtop,max);
    int rr1 = dwtop.size();
    int cc1 = dwtop[0].size();

    int num = floor(rr1 * cc1 * n_coef / 100);

    vector<double> temp1;

     for (int i =0; i < rr1; i++) {
             for (int j = 0; j < cc1; j++){
                     double tempval = abs(dwtop[i][j]);
                     temp1.push_back(tempval);
             }
     }
      double thresh1= 0.0;
      findthresh(temp1,num,thresh1);

      for (int i =0; i < rr1; i++) {
              for (int j = 0; j < cc1; j++){
                    double temp = abs(dwtop[i][j]);

                    if (temp < thresh1){
                            dwtop[i][j] = 0.0;

                    }
                }
              }

}

void MainWindow::appx_coeff_sym(vector<double>  &dwtop) {
    double max;
    maxval(dwtop,max);
    int rr1 = dwtop.size();

    int num = floor(rr1 * n_coef / 100);

    vector<double> temp1;

     for (int i =0; i < rr1; i++) {
                     double tempval = abs(dwtop[i]);
                     temp1.push_back(tempval);

     }
      double thresh1= 0.0;
      findthresh(temp1,num,thresh1);

      for (int i =0; i < rr1; i++) {
                    double temp = abs(dwtop[i]);

                    if (temp < thresh1){
                            dwtop.at(i) = 0.0;

                    }

              }

}


void MainWindow::findthresh(vector<double> vector1, int N, double& t){
        sort(vector1.begin(), vector1.end(), greater<double>());
        t = vector1.at(N-1);
}

void MainWindow::wavedisp() {
    vector<double> lp1,hp1,lp2,hp2;
    filtcoef(nm,lp1,hp1,lp2,hp2);

    vector<double> phi,psi,filt2,phi1,psi1,phi2,psi2;
    if (nm.compare(0,1,"d") == 0) {
    iterorth(lp2,phi,5,"l");
    altflip(lp2,filt2);
    iterorth(lp2,psi,5,"h");
    ORTHplot(phi,psi);
} else if (nm.compare(0,1,"b") == 0){
  iterbiorth(lp1,hp1,lp2,hp2,phi1,psi1,phi2,psi2,5);
  BIORTHplot(phi1,psi1,phi2,psi2);
} else if (nm.compare(0,1,"c") == 0) {
    iterorth(lp2,phi,5,"l");
    iterorth(lp2,psi,5,"h");
    ORTHplot(phi,psi);
} else if (nm.compare(0,1,"s") == 0) {
    iterorth(lp2,phi,5,"l");
    iterorth(lp2,psi,5,"h");
    ORTHplot(phi,psi);
}

}


void MainWindow::filtdisp() {

    vector<double> lp1,hp1,lp2,hp2;
    filtcoef(nm,lp1,hp1,lp2,hp2);

    QLayoutItem *child;
    while ((child = glayout->takeAt(0)) != 0)
    {
    delete child->widget();
    delete child;
    }

    QLabel *l1 = new QLabel("Decomposition Low Pass Filter");
    l1->setAlignment(Qt::AlignCenter);
    glayout->addWidget(l1,0,0);
    pointplot2(lp1,2,1);

    QLabel *l2 = new QLabel(QString("Decomposition High pass Filter"));
    l2->setAlignment(Qt::AlignCenter);
    glayout->addWidget(l2,2,0);
    pointplot2(hp1,2,3);

    QLabel *l3 = new QLabel("Reconstruction Low Pass Filter");
    l3->setAlignment(Qt::AlignCenter);
    glayout->addWidget(l3,4,0);
    pointplot2(lp2,2,5);

    QLabel *l4 = new QLabel(QString("Reconstruction High Pass Filter"));
    l4->setAlignment(Qt::AlignCenter);
    glayout->addWidget(l4,6,0);
    pointplot2(hp2,2,7);



}

void MainWindow::freqdisp2() {
    QLayoutItem *child;
    while ((child = glayout->takeAt(0)) != 0)
    {
    delete child->widget();

     }

    int height = image.height();
    int width = image.width();

    int form = image.format();


fftw_plan plan_image;
fftw_complex *inp_data, *oup_data;
inp_data = ( fftw_complex* ) fftw_malloc( sizeof( fftw_complex ) * height * width );
oup_data = ( fftw_complex* ) fftw_malloc( sizeof( fftw_complex ) * height * width );

if (form == 3) {
for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
        inp_data[i * width + j][0] = (double) (image.pixelIndex(j,i));
        inp_data[i * width + j][1] =0.0;
    }
}
} else {
for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
QRgb value = image.pixel(j,i);
double temp1 = (double) (qRed(value));
double temp2 = (double) (qGreen(value));
double temp3 = (double) (qBlue(value));
inp_data[i * width + j][0] =  0.59 * temp2 + 0.30 * temp1 + 0.11 * temp3;
inp_data[i * width + j][1] = 0.0;
}
}
}

plan_image  = fftw_plan_dft_2d( height,width, inp_data, oup_data, FFTW_FORWARD, FFTW_ESTIMATE );
fftw_execute(plan_image);
vector<double> fft_data;
for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
        double temp1 = oup_data[i*width+j][0];
        double temp2 = oup_data[i*width+j][1];
      double temp =  log(sqrt(pow(temp1,2.0) +pow(temp2,2.0))) ;
      fft_data.push_back(temp);

    }
    }
 double max;
 maxval(fft_data,max);

 QImage fft_image(width,height,QImage::Format_RGB32);
 vector<vector<double> > temp_fft(height,vector<double>(width));

 for (int i = 0; i < height; i++) {
     for (int j = 0; j < width; j++) {
       double temp =  fft_data[i*width+j] * 255.0 / max ;

     temp_fft[i][j] = temp;

     }
     }
 circshift2d(temp_fft,width/2,height/2);

 for (int i = 0; i < height; i++) {
     for (int j = 0; j < width; j++) {
       double temp =  temp_fft[i][j] ;

       QRgb value = qRgb(temp,temp,temp);
       fft_image.setPixel(j,i,value);

     }
     }

 vspacer = new QSpacerItem( 10, 10, QSizePolicy::Minimum,
 QSizePolicy::Expanding );
 hspacer1 = new QSpacerItem( 10, 10, QSizePolicy::Expanding,
 QSizePolicy::Minimum );
 hspacer2 = new QSpacerItem( 10, 10, QSizePolicy::Expanding,
 QSizePolicy::Minimum );
 spacer = new QSpacerItem( 10, 10, QSizePolicy::Minimum,
 QSizePolicy::Expanding );

 QLabel *label1 = new QLabel(QString("Input Image"));
 label1->setAlignment(Qt::AlignCenter);
 label1->setScaledContents(true);

 QLabel *labelorig = new QLabel(this);

 QPixmap pix;
 pix.convertFromImage(image);
 labelorig->setPixmap(pix);
 labelorig->setScaledContents(true);

 glayout->addItem(vspacer,0,1);
 glayout->addItem(hspacer1,1,0);
 glayout->addWidget(label1,1,1);
 glayout->addWidget(labelorig,2,1);
 glayout->addItem(hspacer2,1,3);

 QLabel *label2 = new QLabel(QString("Image FFT"));
 label2->setAlignment(Qt::AlignCenter);
 label2->setScaledContents(true);

 QPixmap pix2;

 pix2.convertFromImage(fft_image);

 QLabel *labelappx = new QLabel(this);
 labelappx->setPixmap(pix2);
 labelappx->setScaledContents(true);

 fftimage = fft_image;

 QPushButton *fftfullbutton = new QPushButton("View FullSize Image");
 connect(fftfullbutton,SIGNAL(clicked()),this,SLOT(fftFULLVIEW()));

 glayout->addWidget(label2,1,2);
 glayout->addWidget(labelappx,2,2);

 glayout->addWidget(fftfullbutton,3,2);
 glayout->addItem(spacer,4,1);
 glayout->update();


 fftw_destroy_plan(plan_image);
 fftw_free(inp_data);
 fftw_free(oup_data);

}

void MainWindow::imageFILTER2() {
    setimagebutton->setEnabled(true);
    resetimagebutton->setEnabled(true);
    filteroutbutton->setEnabled(true);
    vector<double> filter;
    if (im_filter == "Moving Average 3x3") {
        for (int i=0; i < 9; i++) {
            double temp = 1.0 / 9.0;
            filter.push_back(temp);
        }
        conv2dfft(filter,3,3);
    } else if (im_filter == "Moving Average 5x5") {
        for (int i=0; i < 25; i++) {
            double temp = 1.0 / 25.0;
            filter.push_back(temp);
        }
        conv2dfft(filter,5,5);

    } else if (im_filter == "Moving Average 7x7") {
        for (int i=0; i < 49; i++) {
            double temp = 1.0 / 49.0;
            filter.push_back(temp);
        }
        conv2dfft(filter,7,7);

    } else if (im_filter == "Median Filter") {
        int height = image.height();
        int width = image.width();
        vector<vector<double> > x2(height+2,vector<double> (width+2,0.0));
        vector<vector<double> > inp(height,vector<double> (width,0.0));
        vector<vector<double> > x2_red(height+2,vector<double> (width+2,0.0));
        vector<vector<double> > inp_red(height,vector<double> (width,0.0));
        vector<vector<double> > x2_green(height+2,vector<double> (width+2,0.0));
        vector<vector<double> > inp_green(height,vector<double> (width,0.0));
        vector<vector<double> > x2_blue(height+2,vector<double> (width+2,0.0));
        vector<vector<double> > inp_blue(height,vector<double> (width,0.0));

        int form = image.format();
        if (form ==3) {
        for (int i=1; i < height +1;i++) {
            for (int j=1; j < width+1;j++) {
                x2[i][j] = (double) (image.pixelIndex(j-1,i-1));

            }
        }
    } else if (mode_color_filt == "GrayScale (Faster)") {
        for (int i=1; i < height +1;i++) {
            for (int j=1; j < width+1;j++) {
        QRgb value = image.pixel(j-1,i-1);
        double temp1 = (double) (qRed(value));
        double temp2 = (double) (qGreen(value));
        double temp3 = (double) (qBlue(value));
        x2[i][j] =  0.59 * temp2 + 0.30 * temp1 + 0.11 * temp3;
    }
        }
        form = 3;
    } else {
        for (int i=1; i < height +1;i++) {
            for (int j=1; j < width+1;j++) {
        QRgb value = image.pixel(j-1,i-1);
        double temp1 = (double) (qRed(value));
        double temp2 = (double) (qGreen(value));
        double temp3 = (double) (qBlue(value));
        x2_red[i][j] = temp1  ;
        x2_green[i][j] = temp2;
        x2_blue[i][j] = temp3;
    }
        }

    }
    if (form == 3) {
    for (int i=1; i < height +1;i++) {
        for (int j=1; j < width+1;j++) {
            vector<double> vec;
            for (int ii=-1; ii < 2; ii++) {
                for (int jj=-1;jj <2; jj++) {
                    double temp = x2[i-ii][j-jj];
                    vec.push_back(temp);
                }
            }
            double val;
            median(vec,val);
            x2[i][j] = val;
        }
    }

    for (int i=0; i < height;i++) {
        for (int j=0;j < width;j++) {
            inp[i][j]=x2[i+1][j+1];

        }
    }

     dispMEDIAN(inp);
 } else {

     for (int i=1; i < height +1;i++) {
         for (int j=1; j < width+1;j++) {
             vector<double> vecr,vecg,vecb;
             for (int ii=-1; ii < 2; ii++) {
                 for (int jj=-1;jj <2; jj++) {
                     double tempr = x2_red[i-ii][j-jj];
                     vecr.push_back(tempr);
                     double tempg = x2_green[i-ii][j-jj];
                     vecg.push_back(tempg);
                     double tempb = x2_blue[i-ii][j-jj];
                     vecb.push_back(tempb);
                 }
             }
             double valr,valg,valb;
             median(vecr,valr);
             x2_red[i][j] = valr;
             median(vecg,valg);
             x2_green[i][j] = valg;
             median(vecb,valb);
             x2_blue[i][j] = valb;
         }
     }

     for (int i=0; i < height;i++) {
         for (int j=0;j < width;j++) {
             inp_red[i][j]=x2_red[i+1][j+1];
             inp_green[i][j]=x2_green[i+1][j+1];
             inp_blue[i][j]=x2_blue[i+1][j+1];


         }
     }

      dispMEDIAN_RGB(inp_red,inp_green,inp_blue);

 }

    } else if (im_filter == "Roberts Mask (H)") {
        double array[4]= {-1,0,0,1};
        for (int i=0;i < 4; i++) {
            double temp = array[i];
            filter.push_back(temp);
        }

        conv2dfft(filter,2,2);

    } else if (im_filter == "Roberts Mask (V)") {
        double array[4]= {0,-1,1,0};
        for (int i=0;i < 4; i++) {
            double temp = array[i];
            filter.push_back(temp);
        }

        conv2dfft(filter,2,2);

    } else if (im_filter == "Sobel Mask (H)") {
        double array[9]= {1,2,1,0,0,0,-1,-2,-1};
        for (int i=0;i < 9; i++) {
            double temp = array[i];
            filter.push_back(temp);
        }

        conv2dfft(filter,3,3);

    }  else if (im_filter == "Sobel Mask (V)") {
        double array[9]= {1,0,-1,2,0,-2,1,0,-1};
        for (int i=0;i < 9; i++) {
            double temp = array[i];
            filter.push_back(temp);
        }

        conv2dfft(filter,3,3);

    }  else if (im_filter == "Prewitt Mask (H)") {
        double array[9]= {1,1,1,0,0,0,-1,-1,-1};
        for (int i=0;i < 9; i++) {
            double temp = array[i];
            filter.push_back(temp);
        }

        conv2dfft(filter,3,3);

    } else if (im_filter == "Prewitt Mask (V)") {
        double array[9]= {1,0,-1,1,0,-1,1,0,-1};
        for (int i=0;i < 9; i++) {
            double temp = array[i];
            filter.push_back(temp);
        }

        conv2dfft(filter,3,3);

    } else if (im_filter == "LaPlacian") {
        double array[9]= {0,-1,0,-1,4,-1,0,-1,0};
        for (int i=0;i < 9; i++) {
            double temp = array[i];
            filter.push_back(temp);
        }

        conv2dfft(filter,3,3);

    } else if (im_filter == "LaPlacian Sharp") {
        double array[9]= {0,-1,0,-1,5,-1,0,-1,0};
        for (int i=0;i < 9; i++) {
            double temp = array[i];
            filter.push_back(temp);
        }

        conv2dfft(filter,3,3);

    } else if (im_filter == "Gaussian") {
        double t = floor(((double)gauss_size + 1.0) / 2.0);
        double sum=0.0;
        if (gauss_sigma == 0)  {
            gauss_sigma = 0.001;
        }
        for (int i=1;i <= gauss_size; i++) {
            for (int j= 0; j <= gauss_size;j++) {
            double temp = (1.0/(sqrt(2.0 * 3.14159) * gauss_sigma))* exp(-(pow((double)i-t,2)+pow((double)j-t,2))/(2.0*pow(gauss_sigma,2.0)));
            filter.push_back(temp);
            sum+=temp;
        }
        }
        transform(filter.begin(), filter.end(), filter.begin(),
                       bind1st(multiplies<double>(),1/sum));
        conv2dfft(filter,gauss_size,gauss_size);

    }



}

void MainWindow::conv2dfft(vector<double> &filt, int filt_ht, int filt_wd) {
    QLayoutItem *child;
    while ((child = glayout->takeAt(0)) != 0)
    {
    delete child->widget();

     }
    int image_ht = image.height();
    int image_wd = image.width();
    int height = image_ht+filt_ht-1;
    int width = image_wd+ filt_wd - 1;

    int form = image.format();
    QImage filt_image(image_wd,image_ht,QImage::Format_RGB32);



fftw_plan plan_image,plan_image_red,plan_image_green,plan_image_blue,plan_filt,plan_ifft,plan_ifft_red
        ,plan_ifft_green,plan_ifft_blue;
fftw_complex *inp_data, *oup_data,*inp_data_red, *oup_data_red,*inp_data_green, *oup_data_green,
             *inp_data_blue, *oup_data_blue,*inp_filt, *oup_filt,*temp_data,*temp_ifft,*temp_data_red,
             *temp_ifft_red,*temp_data_green,*temp_ifft_green,*temp_data_blue,*temp_ifft_blue;
inp_data = ( fftw_complex* ) fftw_malloc( sizeof( fftw_complex ) * height * width );
oup_data = ( fftw_complex* ) fftw_malloc( sizeof( fftw_complex ) * height * width );
inp_filt = ( fftw_complex* ) fftw_malloc( sizeof( fftw_complex ) * height * width );
oup_filt = ( fftw_complex* ) fftw_malloc( sizeof( fftw_complex ) * height * width );
temp_data = ( fftw_complex* ) fftw_malloc( sizeof( fftw_complex ) * height * width );
temp_ifft = ( fftw_complex* ) fftw_malloc( sizeof( fftw_complex ) * height * width );

inp_data_red = ( fftw_complex* ) fftw_malloc( sizeof( fftw_complex ) * height * width );
oup_data_red = ( fftw_complex* ) fftw_malloc( sizeof( fftw_complex ) * height * width );
inp_data_green = ( fftw_complex* ) fftw_malloc( sizeof( fftw_complex ) * height * width );
oup_data_green = ( fftw_complex* ) fftw_malloc( sizeof( fftw_complex ) * height * width );
inp_data_blue = ( fftw_complex* ) fftw_malloc( sizeof( fftw_complex ) * height * width );
oup_data_blue = ( fftw_complex* ) fftw_malloc( sizeof( fftw_complex ) * height * width );

temp_data_red = ( fftw_complex* ) fftw_malloc( sizeof( fftw_complex ) * height * width );
temp_ifft_red = ( fftw_complex* ) fftw_malloc( sizeof( fftw_complex ) * height * width );
temp_data_green = ( fftw_complex* ) fftw_malloc( sizeof( fftw_complex ) * height * width );
temp_ifft_green = ( fftw_complex* ) fftw_malloc( sizeof( fftw_complex ) * height * width );
temp_data_blue = ( fftw_complex* ) fftw_malloc( sizeof( fftw_complex ) * height * width );
temp_ifft_blue = ( fftw_complex* ) fftw_malloc( sizeof( fftw_complex ) * height * width );


if (form == 3) {
for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
        if ( (i < image_ht) && (j < image_wd) ) {
        inp_data[i * width + j][0] = (double) (image.pixelIndex(j,i));
        inp_data[i * width + j][1] =0.0;
    } else {
        inp_data[i * width + j][0] = 0.0;
        inp_data[i * width + j][1] =0.0;
    }
    }
}
} else if ( mode_color_filt == "GrayScale (Faster)") {
for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
QRgb value;
double temp1;
double temp2;
double temp3;
if ( (i < image_ht) && (j < image_wd) )  {
    value= image.pixel(j,i);
    temp1 = (double) (qRed(value));
    temp2 = (double) (qGreen(value));
    temp3 = (double) (qBlue(value));

inp_data[i * width + j][0] =  0.59 * temp2 + 0.30 * temp1 + 0.11 * temp3;
inp_data[i * width + j][1] = 0.0;
} else {
    inp_data[i * width + j][0] =  0.0;
    inp_data[i * width + j][1] = 0.0;
}
}
}
form =3;
} else {

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
    QRgb value;
    double temp1;
    double temp2;
    double temp3;
    if ( (i < image_ht) && (j < image_wd) )  {
        value= image.pixel(j,i);
        temp1 = (double) (qRed(value));
        temp2 = (double) (qGreen(value));
        temp3 = (double) (qBlue(value));

    inp_data_red[i * width + j][0] =  temp1;
    inp_data_red[i * width + j][1] = 0.0;
    inp_data_green[i * width + j][0] =  temp2;
    inp_data_green[i * width + j][1] = 0.0;
    inp_data_blue[i * width + j][0] =  temp3;
    inp_data_blue[i * width + j][1] = 0.0;
    } else {
        inp_data_red[i * width + j][0] =  0.0;
        inp_data_red[i * width + j][1] = 0.0;
        inp_data_green[i * width + j][0] =  0.0;
        inp_data_green[i * width + j][1] = 0.0;
        inp_data_blue[i * width + j][0] =  0.0;
        inp_data_blue[i * width + j][1] = 0.0;
    }
    }
    }

}

for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
        if ( (i < filt_ht) && (j < filt_wd) ) {
        inp_filt[i * width + j][0] = filt[i*filt_wd + j];
        inp_filt[i * width + j][1] =0.0;
    } else {
        inp_filt[i * width + j][0] = 0.0;
        inp_filt[i * width + j][1] =0.0;
    }
    }
}
if (form == 3) {

plan_image  = fftw_plan_dft_2d( height,width, inp_data, oup_data, FFTW_FORWARD, FFTW_ESTIMATE );
fftw_execute(plan_image);
plan_filt  = fftw_plan_dft_2d( height,width, inp_filt, oup_filt, FFTW_FORWARD, FFTW_ESTIMATE );
fftw_execute(plan_filt);

int sz = height * width;

for (int i =0; i < sz; i++){
     temp_data[i][0] = oup_data[i][0]*oup_filt[i][0] - oup_data[i][1]*oup_filt[i][1];

     temp_data[i][1] = oup_data[i][0]*oup_filt[i][1] + oup_data[i][1]*oup_filt[i][0];

}

plan_ifft  = fftw_plan_dft_2d( height,width, temp_data, temp_ifft, FFTW_BACKWARD, FFTW_ESTIMATE );
fftw_execute( plan_ifft);



vector<vector<double> > temp_f(height,vector<double>(width));

for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      double temp =  temp_ifft[i*width+j][0];

    temp_f[i][j] = temp/(double) (height * width);

    }
    }

double max;
maxval2(temp_f,max);

for (int i = (int) floor((double)filt_ht/2.0); i < image_ht +(int) floor((double)filt_ht/2.0); i++) {
    for (int j = (int) floor((double)filt_wd/2.0); j < image_wd + (int) floor((double)filt_wd/2.0); j++) {
        double temp;
        if (temp_f[i][j] <= 0) {
            temp =0.0;
        } else {
            temp =  (temp_f[i][j] * 255.0) / max ;
  }

      QRgb value = qRgb(temp,temp,temp);
      filt_image.setPixel(j-(int) floor((double)filt_wd/2.0),i-(int) floor((double)filt_ht/2.0),value);

    }
    }
fftw_destroy_plan(plan_image);
fftw_destroy_plan(plan_filt);
fftw_destroy_plan(plan_ifft);



} else {
    plan_image_red  = fftw_plan_dft_2d( height,width, inp_data_red, oup_data_red, FFTW_FORWARD, FFTW_ESTIMATE );
    fftw_execute(plan_image_red);
    plan_image_green  = fftw_plan_dft_2d( height,width, inp_data_green, oup_data_green, FFTW_FORWARD, FFTW_ESTIMATE );
    fftw_execute(plan_image_green);
    plan_image_blue  = fftw_plan_dft_2d( height,width, inp_data_blue, oup_data_blue, FFTW_FORWARD, FFTW_ESTIMATE );
    fftw_execute(plan_image_blue);
    plan_filt  = fftw_plan_dft_2d( height,width, inp_filt, oup_filt, FFTW_FORWARD, FFTW_ESTIMATE );
    fftw_execute(plan_filt);

    int sz = height * width;

    for (int i =0; i < sz; i++){
         temp_data_red[i][0] = oup_data_red[i][0]*oup_filt[i][0] - oup_data_red[i][1]*oup_filt[i][1];

         temp_data_red[i][1] = oup_data_red[i][0]*oup_filt[i][1] + oup_data_red[i][1]*oup_filt[i][0];

         temp_data_green[i][0] = oup_data_green[i][0]*oup_filt[i][0] - oup_data_green[i][1]*oup_filt[i][1];

         temp_data_green[i][1] = oup_data_green[i][0]*oup_filt[i][1] + oup_data_green[i][1]*oup_filt[i][0];

         temp_data_blue[i][0] = oup_data_blue[i][0]*oup_filt[i][0] - oup_data_blue[i][1]*oup_filt[i][1];

         temp_data_blue[i][1] = oup_data_blue[i][0]*oup_filt[i][1] + oup_data_blue[i][1]*oup_filt[i][0];

    }

    plan_ifft_red  = fftw_plan_dft_2d( height,width, temp_data_red, temp_ifft_red, FFTW_BACKWARD, FFTW_ESTIMATE );
    fftw_execute( plan_ifft_red);
    plan_ifft_green  = fftw_plan_dft_2d( height,width, temp_data_green, temp_ifft_green, FFTW_BACKWARD, FFTW_ESTIMATE );
    fftw_execute( plan_ifft_green);
    plan_ifft_blue  = fftw_plan_dft_2d( height,width, temp_data_blue, temp_ifft_blue, FFTW_BACKWARD, FFTW_ESTIMATE );
    fftw_execute( plan_ifft_blue);



    vector<vector<double> > temp_f_red(height,vector<double>(width));
    vector<vector<double> > temp_f_green(height,vector<double>(width));
    vector<vector<double> > temp_f_blue(height,vector<double>(width));


    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
          double temp1 =  temp_ifft_red[i*width+j][0];

        temp_f_red[i][j] = temp1/(double) (height * width);

        double temp2 =  temp_ifft_green[i*width+j][0];

        temp_f_green[i][j] = temp2/(double) (height * width);

        double temp3 =  temp_ifft_blue[i*width+j][0];

        temp_f_blue[i][j] = temp3/(double) (height * width);

        }
        }

    double maxr;
    maxval2(temp_f_red,maxr);
    double maxg;
    maxval2(temp_f_green,maxg);
    double maxb;
    maxval2(temp_f_blue,maxb);

    for (int i = (int) floor((double)filt_ht/2.0); i < image_ht +(int) floor((double)filt_ht/2.0); i++) {
        for (int j = (int) floor((double)filt_wd/2.0); j < image_wd + (int) floor((double)filt_wd/2.0); j++) {
            double temp1,temp2,temp3;
            if (temp_f_red[i][j] <= 0) {
                temp1 =0.0;
            } else {
                temp1 =  (temp_f_red[i][j] * 255.0) / maxr ;
      }
            if (temp_f_green[i][j] <= 0) {
                temp2 =0.0;
            } else {
                temp2 =  (temp_f_green[i][j] * 255.0) / maxg ;
      }
            if (temp_f_blue[i][j] <= 0) {
                temp3 =0.0;
            } else {
                temp3 =  (temp_f_blue[i][j] * 255.0) / maxb ;
      }

          QRgb value = qRgb(temp1,temp2,temp3);
          filt_image.setPixel(j-(int) floor((double)filt_wd/2.0),i-(int) floor((double)filt_ht/2.0),value);

        }
        }
    fftw_destroy_plan(plan_image_red);
    fftw_destroy_plan(plan_image_green);
    fftw_destroy_plan(plan_image_blue);

    fftw_destroy_plan(plan_filt);
    fftw_destroy_plan(plan_ifft_red);
    fftw_destroy_plan(plan_ifft_green);
    fftw_destroy_plan(plan_ifft_blue);

}

filteredimage = filt_image;

fftw_free(inp_data);
fftw_free(oup_data);
fftw_free(inp_data_red);
fftw_free(oup_data_red);
fftw_free(inp_data_green);
fftw_free(oup_data_green);
fftw_free(inp_data_blue);
fftw_free(oup_data_blue);
fftw_free(inp_filt);
fftw_free(oup_filt);
fftw_free(temp_data);
fftw_free(temp_ifft);
fftw_free(temp_data_red);
fftw_free(temp_ifft_red);
fftw_free(temp_data_green);
fftw_free(temp_ifft_green);
fftw_free(temp_data_blue);
fftw_free(temp_ifft_blue);

vspacer = new QSpacerItem( 10, 10, QSizePolicy::Minimum,
QSizePolicy::Expanding );
hspacer1 = new QSpacerItem( 10, 10, QSizePolicy::Expanding,
QSizePolicy::Minimum );
hspacer2 = new QSpacerItem( 10, 10, QSizePolicy::Expanding,
QSizePolicy::Minimum );
spacer = new QSpacerItem( 10, 10, QSizePolicy::Minimum,
QSizePolicy::Expanding );

QLabel *label1 = new QLabel(QString("Input Image"));
label1->setAlignment(Qt::AlignCenter);
label1->setScaledContents(true);

QLabel *labelorig = new QLabel(this);

QPixmap pix;
pix.convertFromImage(image);
labelorig->setPixmap(pix);
labelorig->setScaledContents(true);

glayout->addItem(vspacer,0,1);
glayout->addItem(hspacer1,1,0);
glayout->addWidget(label1,1,1);
glayout->addWidget(labelorig,2,1);
glayout->addItem(hspacer2,1,3);

QLabel *label2 = new QLabel(QString("Filtered Image"));
label2->setAlignment(Qt::AlignCenter);
label2->setScaledContents(true);

QPixmap pix2;

pix2.convertFromImage(filt_image);

QLabel *labelappx = new QLabel(this);
labelappx->setPixmap(pix2);
labelappx->setScaledContents(true);

QPushButton *filtfullbutton = new QPushButton("View FullSize Image");
connect(filtfullbutton,SIGNAL(clicked()),this,SLOT(filtFULLVIEW()));

glayout->addWidget(label2,1,2);
glayout->addWidget(labelappx,2,2);

glayout->addWidget(filtfullbutton,3,2);
glayout->addItem(spacer,4,1);
glayout->update();


}

void MainWindow::dispMEDIAN(vector<vector<double> > &x2) {
    QLayoutItem *child;
    while ((child = glayout->takeAt(0)) != 0)
    {
    delete child->widget();

     }
    int row = x2.size();
    int col = x2[0].size();
    QImage filt_image(col,row,QImage::Format_RGB32);
    double max;
    maxval2(x2,max);

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            double temp;
            if (x2[i][j] <= 0) {
                temp =0.0;
            } else {
                temp =  (x2[i][j] * 255.0) / max ;
      }

          QRgb value = qRgb(temp,temp,temp);
          filt_image.setPixel(j,i,value);

        }
        }
    filteredimage = filt_image;

    vspacer = new QSpacerItem( 10, 10, QSizePolicy::Minimum,
    QSizePolicy::Expanding );
    hspacer1 = new QSpacerItem( 10, 10, QSizePolicy::Expanding,
    QSizePolicy::Minimum );
    hspacer2 = new QSpacerItem( 10, 10, QSizePolicy::Expanding,
    QSizePolicy::Minimum );
    spacer = new QSpacerItem( 10, 10, QSizePolicy::Minimum,
    QSizePolicy::Expanding );

    QLabel *label1 = new QLabel(QString("Input Image"));
    label1->setAlignment(Qt::AlignCenter);
    label1->setScaledContents(true);

    QLabel *labelorig = new QLabel(this);

    QPixmap pix;
    pix.convertFromImage(image);
    labelorig->setPixmap(pix);
    labelorig->setScaledContents(true);

    glayout->addItem(vspacer,0,1);
    glayout->addItem(hspacer1,1,0);
    glayout->addWidget(label1,1,1);
    glayout->addWidget(labelorig,2,1);
    glayout->addItem(hspacer2,1,3);

    QLabel *label2 = new QLabel(QString("Filtered Image"));
    label2->setAlignment(Qt::AlignCenter);
    label2->setScaledContents(true);

    QPixmap pix2;

    pix2.convertFromImage(filt_image);

    QLabel *labelappx = new QLabel(this);
    labelappx->setPixmap(pix2);
    labelappx->setScaledContents(true);

    QPushButton *filtfullbutton = new QPushButton("View FullSize Image");
    connect(filtfullbutton,SIGNAL(clicked()),this,SLOT(filtFULLVIEW()));

    glayout->addWidget(label2,1,2);
    glayout->addWidget(labelappx,2,2);

    glayout->addWidget(filtfullbutton,3,2);
    glayout->addItem(spacer,4,1);
    glayout->update();




}

void MainWindow::dispMEDIAN_RGB(vector<vector<double> > &x2_r,vector<vector<double> > &x2_g,
                                vector<vector<double> > &x2_b) {
    QLayoutItem *child;
    while ((child = glayout->takeAt(0)) != 0)
    {
    delete child->widget();

     }
    int row = x2_r.size();
    int col = x2_r[0].size();
    QImage filt_image(col,row,QImage::Format_RGB32);
    double maxr;
    maxval2(x2_r,maxr);
    double maxg;
    maxval2(x2_g,maxg);
    double maxb;
    maxval2(x2_b,maxb);

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            double tempr,tempg,tempb;
            if (x2_r[i][j] <= 0) {
                tempr =0.0;
            } else {
                tempr =  (x2_r[i][j] * 255.0) / maxr ;
      }

            if (x2_g[i][j] <= 0) {
                tempg =0.0;
            } else {
                tempg =  (x2_g[i][j] * 255.0) / maxg ;
      }

            if (x2_b[i][j] <= 0) {
                tempb =0.0;
            } else {
                tempb =  (x2_b[i][j] * 255.0) / maxb ;
      }

          QRgb value = qRgb(tempr,tempg,tempb);
          filt_image.setPixel(j,i,value);

        }
        }
    filteredimage = filt_image;

    vspacer = new QSpacerItem( 10, 10, QSizePolicy::Minimum,
    QSizePolicy::Expanding );
    hspacer1 = new QSpacerItem( 10, 10, QSizePolicy::Expanding,
    QSizePolicy::Minimum );
    hspacer2 = new QSpacerItem( 10, 10, QSizePolicy::Expanding,
    QSizePolicy::Minimum );
    spacer = new QSpacerItem( 10, 10, QSizePolicy::Minimum,
    QSizePolicy::Expanding );

    QLabel *label1 = new QLabel(QString("Input Image"));
    label1->setAlignment(Qt::AlignCenter);
    label1->setScaledContents(true);

    QLabel *labelorig = new QLabel(this);

    QPixmap pix;
    pix.convertFromImage(image);
    labelorig->setPixmap(pix);
    labelorig->setScaledContents(true);

    glayout->addItem(vspacer,0,1);
    glayout->addItem(hspacer1,1,0);
    glayout->addWidget(label1,1,1);
    glayout->addWidget(labelorig,2,1);
    glayout->addItem(hspacer2,1,3);

    QLabel *label2 = new QLabel(QString("Filtered Image"));
    label2->setAlignment(Qt::AlignCenter);
    label2->setScaledContents(true);

    QPixmap pix2;

    pix2.convertFromImage(filt_image);

    QLabel *labelappx = new QLabel(this);
    labelappx->setPixmap(pix2);
    labelappx->setScaledContents(true);

    QPushButton *filtfullbutton = new QPushButton("View FullSize Image");
    connect(filtfullbutton,SIGNAL(clicked()),this,SLOT(filtFULLVIEW()));

    glayout->addWidget(label2,1,2);
    glayout->addWidget(labelappx,2,2);

    glayout->addWidget(filtfullbutton,3,2);
    glayout->addItem(spacer,4,1);
    glayout->update();




}

void MainWindow::freqdisp() {
    QLayoutItem *child;
    while ((child = glayout->takeAt(0)) != 0)
    {
    delete child->widget();
    delete child;
    }

    vector<double> freq_response;
    vector<double> signal;
    signal = original_signal;
    freq(signal,freq_response);

    QLabel *l3 = new QLabel("Input Signal");
    l3->setAlignment(Qt::AlignCenter);
    glayout->addWidget(l3,0,0);
    lineplotmod2(signal,1,1,double(0),(double)signal.size()-1);

    QLabel *l4 = new QLabel(QString("Two-Sided Frequency Response"));
    l4->setAlignment(Qt::AlignCenter);
    glayout->addWidget(l4,2,0);
    lineplotmod2(freq_response,1,3,-3.14,3.14);

    vector<double> freq_response1;

    freq_one(signal,freq_response1);

    QLabel *l5 = new QLabel(QString("One-Sided Frequency Response"));
    l5->setAlignment(Qt::AlignCenter);
    glayout->addWidget(l5,4,0);
    lineplotmod2(freq_response1,1,5,0,3.14);

}

void MainWindow::filtfreq2() {
    QLayoutItem *child;
    while ((child = glayout->takeAt(0)) != 0)
    {
    delete child->widget();
    delete child;
    }
    vector<double> lp1,hp1,lp2,hp2;
    filtcoef(nm,lp1,hp1,lp2,hp2);

    vector<double> lp1f;
    freq_one(lp1,lp1f);

    QLabel *l1 = new QLabel(QString("Analysis Low Pass Filter"));
    l1->setAlignment(Qt::AlignCenter);
    glayout->addWidget(l1,0,0);
    lineplot(lp1f,2,1,0.0,3.14);

    vector<double> hp1f;
    freq_one(hp1,hp1f);

    QLabel *l2 = new QLabel(QString("Analysis High Pass Filter"));
    l2->setAlignment(Qt::AlignCenter);
    glayout->addWidget(l2,2,0);
    lineplot(hp1f,2,3,0.0,3.14);

    vector<double> lp2f;
    freq_one(lp2,lp2f);

    QLabel *l3 = new QLabel(QString("Synthesis Low Pass Filter"));
    l3->setAlignment(Qt::AlignCenter);
    glayout->addWidget(l3,4,0);
    lineplot(lp2f,2,5,0.0,3.14);

    vector<double> hp2f;
    freq_one(hp2,hp2f);

    QLabel *l4 = new QLabel(QString("Synthesis High Pass Filter"));
    l4->setAlignment(Qt::AlignCenter);
    glayout->addWidget(l4,6,0);
    lineplot(hp2f,2,7,0.0,3.14);
}

void MainWindow::filtfreq() {
    QLayoutItem *child;
    while ((child = glayout->takeAt(0)) != 0)
    {
    delete child->widget();
    delete child;
    }
    vector<double> lp1,hp1,lp2,hp2;
    filtcoef(nm,lp1,hp1,lp2,hp2);

    vector<double> lp1f;
    freq_one(lp1,lp1f);

    QLabel *l1 = new QLabel(QString("Analysis Low Pass Filter"));
    l1->setAlignment(Qt::AlignCenter);
    glayout->addWidget(l1);
    lineplotmod(lp1f,2);

    vector<double> hp1f;
    freq_one(hp1,hp1f);

    QLabel *l2 = new QLabel(QString("Analysis High Pass Filter"));
    l2->setAlignment(Qt::AlignCenter);
    glayout->addWidget(l2);
    lineplotmod(hp1f,2);

    vector<double> lp2f;
    freq_one(lp2,lp2f);

    QLabel *l3 = new QLabel(QString("Synthesis Low Pass Filter"));
    l3->setAlignment(Qt::AlignCenter);
    glayout->addWidget(l3);
    lineplotmod(lp2f,2);

    vector<double> hp2f;
    freq_one(hp2,hp2f);

    QLabel *l4 = new QLabel(QString("Synthesis High Pass Filter"));
    l4->setAlignment(Qt::AlignCenter);
    glayout->addWidget(l4);
    lineplotmod(hp2f,2);
}



void MainWindow::altflip(vector<double> &c, vector<double> &d) {
    unsigned int j=c.size();
    int s=-1;
    for (unsigned int i = 0; i< j; i++){
        double temp;
        s= s * -1;
        temp = s * c[j-i-1];
        d.push_back(temp);
    }
}

void MainWindow::iterorth(vector<double> &filt,vector<double>& output, int num, string type) {

    unsigned int N = filt.size();
    unsigned int ini = N;
    vector<double> vect;
    if (type == "l") {
    vect= filt;
} else {
    altflip(filt,vect);
}

    for (int i=0; i < num; i++) {
     ini = 2*ini + (N - 2);
     vector<double> vect1;
     for (unsigned int j =0; j < N; j++) {
         vector<double> a,b;
         a = vect;
         upsamp(a,2,b);

         unsigned int jj = b.size();
         double temp = 2 *filt[j];
         b.erase(b.begin()+jj-1,b.end());

         b.insert(b.begin(),j,0);

         b.insert(b.end(),N-j-1,0);

         transform(b.begin(), b.end(), b.begin(),
                        bind1st(multiplies<double>(),temp));
         //transform (b.begin(), b.end(), vect1.begin(), vect1.begin(), op_sum);
         if (j==0){
             for (unsigned int iter=0; iter < b.size();iter++)
                 vect1.push_back(0.0);
         }
         vector<double> temp2;
         temp2 = vect1;

         vecsum(b,temp2,vect1);
     }
     vect=vect1;

    }
    output = vect;
}

void MainWindow::iterbiorth(vector<double> &h0,vector<double> &h1,vector<double> &f0,vector<double> &f1,
                            vector<double>& vecth0,vector<double>& vecth1,vector<double>& vectf0,
                            vector<double>& vectf1,int num) {

    unsigned int Nh0 = h0.size();// Low Pass Filter
    unsigned int Nh1 = h1.size();
    unsigned int Nf0 = f0.size();// Low Pass Filter
    unsigned int Nf1 = f1.size();
 //   unsigned int ini = N; // Use it to create grid later on

    vecth0=h0;
    vector<double> filt;
    for (int i=0; i < num; i++) {
   //  ini = 2*ini + (N - 2);
        filt = h0;
     vector<double> vect1;
     for (unsigned int j =0; j < Nh0; j++) {
         vector<double> a,b;
         a = vecth0;
         upsamp(a,2,b);

         unsigned int jj = b.size();
         double temp = 2 *filt[j];
         b.erase(b.begin()+jj-1,b.end());

         b.insert(b.begin(),j,0);

         b.insert(b.end(),Nh0-j-1,0);

         transform(b.begin(), b.end(), b.begin(),
                        bind1st(multiplies<double>(),temp));
         //transform (b.begin(), b.end(), vect1.begin(), vect1.begin(), op_sum);
         if (j==0){
             for (unsigned int iter=0; iter < b.size();iter++)
                 vect1.push_back(0.0);
         }
         vector<double> temp2;
         temp2 = vect1;

         vecsum(b,temp2,vect1);
     }
     vecth0=vect1;

    }

      vecth1 = h1;

    for (int i=0; i < num; i++) {
   //  ini = 2*ini + (N - 2);
        filt = h0;
     vector<double> vect1;
     for (unsigned int j =0; j < Nh0; j++) {
         vector<double> a,b;
         a = vecth1;
         upsamp(a,2,b);

         unsigned int jj = b.size();
         double temp = 2 *filt[j];
         b.erase(b.begin()+jj-1,b.end());

         b.insert(b.begin(),j,0);

         b.insert(b.end(),Nh1-j-1,0);

         transform(b.begin(), b.end(), b.begin(),
                        bind1st(multiplies<double>(),temp));
         //transform (b.begin(), b.end(), vect1.begin(), vect1.begin(), op_sum);
         if (j==0){
             for (unsigned int iter=0; iter < b.size();iter++)
                 vect1.push_back(0.0);
         }
         vector<double> temp2;
         temp2 = vect1;

         vecsum(b,temp2,vect1);
     }
     vecth1=vect1;

    }

    vectf0=f0;
    filt =f0;

    for (int i=0; i < num; i++) {
   //  ini = 2*ini + (N - 2);
     vector<double> vect1;
     for (unsigned int j =0; j < Nf0; j++) {
         vector<double> a,b;
         a = vectf0;
         upsamp(a,2,b);

         unsigned int jj = b.size();
         double temp = 2 *filt[j];
         b.erase(b.begin()+jj-1,b.end());

         b.insert(b.begin(),j,0);

         b.insert(b.end(),Nf0-j-1,0);

         transform(b.begin(), b.end(), b.begin(),
                        bind1st(multiplies<double>(),temp));
         //transform (b.begin(), b.end(), vect1.begin(), vect1.begin(), op_sum);
         if (j==0){
             for (unsigned int iter=0; iter < b.size();iter++)
                 vect1.push_back(0.0);
         }
         vector<double> temp2;
         temp2 = vect1;

         vecsum(b,temp2,vect1);
     }
     vectf0=vect1;

    }

    vectf1 = f1;
    filt=f0;

    for (int i=0; i < num; i++) {
   //  ini = 2*ini + (N - 2);
     vector<double> vect1;
     for (unsigned int j =0; j < Nf0; j++) {
         vector<double> a,b;
         a = vectf1;
         upsamp(a,2,b);

         unsigned int jj = b.size();
         double temp = 2 *filt[j];
         b.erase(b.begin()+jj-1,b.end());

         b.insert(b.begin(),j,0);

         b.insert(b.end(),Nf1-j-1,0);

         transform(b.begin(), b.end(), b.begin(),
                        bind1st(multiplies<double>(),temp));
         //transform (b.begin(), b.end(), vect1.begin(), vect1.begin(), op_sum);
         if (j==0){
             for (unsigned int iter=0; iter < b.size();iter++)
                 vect1.push_back(0.0);
         }
         vector<double> temp2;
         temp2 = vect1;

         vecsum(b,temp2,vect1);
     }
     vectf1=vect1;

    }

}


void MainWindow::signalDENOISE2() {
    if (image.isNull()) {
        errormessage();
    }

    int width = image.width();
    int height = image.height();

    vector<vector<double> > vec(height,vector<double>(width));
    vector<vector<double> > vecred(height,vector<double>(width));
    vector<vector<double> > vecgreen(height,vector<double>(width));
    vector<vector<double> > vecblue(height,vector<double>(width));

    vector<vector<double> > idwt_output(height, vector<double>(width));
    vector<vector<double> > idwt_output_r(height, vector<double>(width));
    vector<vector<double> > idwt_output_g(height, vector<double>(width));
    vector<vector<double> > idwt_output_b(height, vector<double>(width));


    int max_dec = (int) floor((double)log(min(width,height))/log(2.0)) - 1;
    if ( J_dn >= max_dec) {
        J_dn = max_dec;
    }

    int form = image.format();

    if (form == 3) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            vec[i][j] = (double) (image.pixelIndex(j,i));
        }
    }
} else if ((form != 3) && (mode_color_denoise == "GrayScale (Faster)")) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
    QRgb value = image.pixel(j,i);
    double temp1 = (double) (qRed(value));
    double temp2 = (double) (qGreen(value));
    double temp3 = (double) (qBlue(value));
    vec[i][j] =  0.59 * temp2 + 0.30 * temp1 + 0.11 * temp3;
    form = 3;
}
    }
} else {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            QRgb value = image.pixel(j,i);
            vecred[i][j] = (double) (qRed(value));
            vecgreen[i][j] = (double) (qGreen(value));
            vecblue[i][j] = (double) (qBlue(value));
        }
    }
}


  vector<double> flag,flag_r,flag_g,flag_b,dwt_output,dwt_output_r,dwt_output_g,dwt_output_b,signal;
  int rr1,cc1;
  dwt_output_dim(vec, rr1, cc1 );
  vector<vector<double> >  dwt_output_per(rr1, vector<double>(cc1));
  vector<vector<double> >  dwt_output_per_r(rr1, vector<double>(cc1));
  vector<vector<double> >  dwt_output_per_g(rr1, vector<double>(cc1));
  vector<vector<double> >  dwt_output_per_b(rr1, vector<double>(cc1));

  vector<vector<double> >  idwt_output_per(rr1, vector<double>(cc1));
  vector<vector<double> >  idwt_output_per_r(rr1, vector<double>(cc1));
  vector<vector<double> >  idwt_output_per_g(rr1, vector<double>(cc1));
  vector<vector<double> >  idwt_output_per_b(rr1, vector<double>(cc1));
  vector<int> length,length_r,length_g,length_b;

  if (dn_method == "visushrink") {

       if ( mode_denoise == "dwt_per") {
           if (form == 3) {
          flag.clear();
          dwt_2d(vec,J_dn, nm_dn, dwt_output,flag,length );

          unsigned int dwt_len = dwt_output.size();
          int siz = length.size();
          int l1 = length[siz-3];
          int l2 = length[siz -4];
          vector<double> dwt_med;
          for (unsigned int i= dwt_len - l1*l2; i < dwt_len;i++) {
              double temp = abs(dwt_output[i]);
              dwt_med.push_back(temp);
          }
          double sigma;
          median(dwt_med,sigma);

          double td;
          td = sqrt(2.0 * log(dwt_len)) * sigma / 0.6745;

          if (dn_thresh == "hard") {
              for (unsigned int iter=0; iter < dwt_len; iter++) {
                  if (abs(dwt_output[iter]) <= td) {
                      dwt_output.at(iter) = 0;
                  }
              }
          } else if (dn_thresh == "soft") {
              for (unsigned int iter=0; iter < dwt_len; iter++) {
                  if (abs(dwt_output[iter]) >= td) {
                      double temp;
                      temp = sgn(dwt_output[iter])*( abs(dwt_output[iter]) - td);
                      dwt_output.at(iter) = temp;
                  } else {
                      dwt_output.at(iter) = 0;
                  }
              }

          }

          idwt_2d( dwt_output,flag, nm_dn, idwt_output,length);
          dispDENOISE(idwt_output);

      } else {
          for (int col =0; col < 3; col++) {
          if (col ==0) {
              vec = vecred;
          } else if (col == 1) {
              vec = vecgreen;
          } else {
              vec = vecblue;
          }
          flag.clear();
          length.clear();
          dwt_output.clear();
          dwt_2d(vec,J_dn,nm_dn,dwt_output,flag,length);

          unsigned int dwt_len = dwt_output.size();
          int siz = length.size();
          int l1 = length[siz-3];
          int l2 = length[siz -4];
          vector<double> dwt_med;
          for (unsigned int i= dwt_len - l1*l2; i < dwt_len;i++) {
              double temp = abs(dwt_output[i]);
              dwt_med.push_back(temp);
          }
          double sigma;
          median(dwt_med,sigma);

          double td;
          td = sqrt(2.0 * log(dwt_len)) * sigma / 0.6745;
          if (dn_thresh == "hard") {
              for (unsigned int iter=0; iter < dwt_len; iter++) {
                  if (abs(dwt_output[iter]) <= td) {
                      dwt_output.at(iter) = 0;
                  }
              }
          } else if (dn_thresh == "soft") {
              for (unsigned int iter=0; iter < dwt_len; iter++) {
                  if (abs(dwt_output[iter]) >= td) {
                      double temp;
                      temp = sgn(dwt_output[iter])*( abs(dwt_output[iter]) - td);
                      dwt_output.at(iter) = temp;
                  } else {
                      dwt_output.at(iter) = 0;
                  }
              }

          }

          if (col ==0) {
              dwt_output_r = dwt_output;
              flag_r = flag;
              length_r = length;
          } else if (col == 1) {
              dwt_output_g = dwt_output;
              flag_g = flag;
              length_g = length;

          } else {
              dwt_output_b = dwt_output;
              flag_b = flag;
              length_b = length;
          }
      }

          idwt_2d( dwt_output_r,flag_r, nm_dn, idwt_output_r,length_r);
          idwt_2d( dwt_output_g,flag_g, nm_dn, idwt_output_g,length_g);
          idwt_2d( dwt_output_b,flag_b, nm_dn, idwt_output_b,length_b);
          dispDENOISE_RGB(idwt_output_r,idwt_output_g,idwt_output_b);

      }



    } else if (mode_denoise == "dwt_sym") {
        if (form == 3) {
         flag.clear();
         dwt_2d_sym(vec,J_dn,nm_dn,dwt_output,flag,length,ext_dn);

         unsigned int dwt_len = dwt_output.size();
         int siz = length.size();
         int l1 = length[siz-3];
         int l2 = length[siz -4];
         vector<double> dwt_med;
         for (unsigned int i= dwt_len - l1*l2; i < dwt_len;i++) {
             double temp = abs(dwt_output[i]);
             dwt_med.push_back(temp);
         }
         double sigma;
         median(dwt_med,sigma);

         double td;
         td = sqrt(2.0 * log(dwt_len)) * sigma / 0.6745;

         if (dn_thresh == "hard") {
             for (unsigned int iter=0; iter < dwt_len; iter++) {
                 if (abs(dwt_output[iter]) <= td) {
                     dwt_output.at(iter) = 0;
                 }
             }
         } else if (dn_thresh == "soft") {
             for (unsigned int iter=0; iter < dwt_len; iter++) {
                 if (abs(dwt_output[iter]) >= td) {
                     double temp;
                     temp = sgn(dwt_output[iter])*( abs(dwt_output[iter]) - td);
                     dwt_output.at(iter) = temp;
                 } else {
                     dwt_output.at(iter) = 0;
                 }
             }

         }

         idwt_2d_sym( dwt_output,flag, nm_dn, idwt_output,length);
         dispDENOISE(idwt_output);

     } else {
         for (int col =0; col < 3; col++) {
         if (col ==0) {
             vec = vecred;
         } else if (col == 1) {
             vec = vecgreen;
         } else {
             vec = vecblue;
         }
         flag.clear();
         length.clear();
         dwt_output.clear();
         dwt_2d_sym(vec,J_dn,nm_dn,dwt_output,flag,length,ext_dn);

         unsigned int dwt_len = dwt_output.size();
         int siz = length.size();
         int l1 = length[siz-3];
         int l2 = length[siz -4];
         vector<double> dwt_med;
         for (unsigned int i= dwt_len - l1*l2; i < dwt_len;i++) {
             double temp = abs(dwt_output[i]);
             dwt_med.push_back(temp);
         }
         double sigma;
         median(dwt_med,sigma);

         double td;
         td = sqrt(2.0 * log(dwt_len)) * sigma / 0.6745;
         if (dn_thresh == "hard") {
             for (unsigned int iter=0; iter < dwt_len; iter++) {
                 if (abs(dwt_output[iter]) <= td) {
                     dwt_output.at(iter) = 0;
                 }
             }
         } else if (dn_thresh == "soft") {
             for (unsigned int iter=0; iter < dwt_len; iter++) {
                 if (abs(dwt_output[iter]) >= td) {
                     double temp;
                     temp = sgn(dwt_output[iter])*( abs(dwt_output[iter]) - td);
                     dwt_output.at(iter) = temp;
                 } else {
                     dwt_output.at(iter) = 0;
                 }
             }

         }

         if (col ==0) {
             dwt_output_r = dwt_output;
             flag_r = flag;
             length_r = length;
         } else if (col == 1) {
             dwt_output_g = dwt_output;
             flag_g = flag;
             length_g = length;

         } else {
             dwt_output_b = dwt_output;
             flag_b = flag;
             length_b = length;
         }
     }

         idwt_2d_sym( dwt_output_r,flag_r, nm_dn, idwt_output_r,length_r);
         idwt_2d_sym( dwt_output_g,flag_g, nm_dn, idwt_output_g,length_g);
         idwt_2d_sym( dwt_output_b,flag_b, nm_dn, idwt_output_b,length_b);
         dispDENOISE_RGB(idwt_output_r,idwt_output_g,idwt_output_b);

     }
    }
  } else if (dn_method == "sureshrink") {

       if ( mode_denoise == "dwt_per") {
           if (form == 3) {
               flag.clear();
               dwt_2d(vec,J_dn,nm_dn,dwt_output,flag,length);
               int len = 0;

               for (int it = 0; it < J_dn; it++) {
                   vector<double> dwt_med;
                   vector<double> coef;
                   int dwt_len;
                   if (it == 0) {
                   for (int i= length[0] * length[1]; i < 4 * length[0] * length[1];i++) {
                       double temp = abs(dwt_output[i]);
                       double temp2 = dwt_output[i];
                       dwt_med.push_back(temp);
                       coef.push_back(temp2);
                   }
                   len= 4 * length[0] * length[1];
                   dwt_len = dwt_med.size();
               } else {
                    for (int i= len + 1; i < len + 3 * length[2 * it] * length[2 * it +1];i++) {
                        double temp = abs(dwt_output[i]);
                        double temp2 = dwt_output[i];
                        dwt_med.push_back(temp);
                        coef.push_back(temp2);
                    }
                   dwt_len = dwt_med.size();

               }
                   double sigma;
                   median(dwt_med,sigma);

                   double td;


               // td = sqrt(2.0 * log(dwt_len)) * sigma / 0.6745;

                   if ( sigma < 0.00000001) {
                       td = 0;
                   } else {
                       double tv;
                       tv = sqrt(2.0 * log(dwt_len));
                       double norm;
                       l2norm(coef,norm);
                       double te;
                       te =(pow(norm,2.0) - (double) dwt_len)/(double) dwt_len;
                       double ct;

                       ct = pow(log((double) dwt_len)/log(2.0),1.5)/sqrt((double) dwt_len);
                       if (te < ct) {
                           td = tv;
                       } else {
                           sort(dwt_med.begin(),dwt_med.end());
                           vector<double> x_sure;
                           double x_sum = 0.0;

                           for (unsigned int val =0; val < dwt_med.size();val++){
                               double temp;
                               temp = pow(dwt_med[val],2.0);
                               x_sure.push_back(temp);
                               x_sum+=temp;
                           }

                           vector<double> risk_vector;
                           for (int rk=0; rk < dwt_len; rk++) {
                               double temp = ((double)dwt_len + 1 - 2 * ((double)rk + 1) +x_sum + x_sure[rk]*((double)dwt_len - 1 -(double) rk))/(double)dwt_len;
                               risk_vector.push_back(temp);
                           }

                        int min_index;
                        minindex(risk_vector,min_index);
                        double thr;
                        thr = sqrt(x_sure[min_index]);

                        td = min(thr,tv);

                       }
                   }
                   td = td * sigma / 0.6745;


               if (dn_thresh == "hard") {
                   if (it == 0) {
                   for (int iter=length[0] * length[1]; iter < 4 * length[0] * length[1]; iter++) {
                       if (abs(dwt_output[iter]) <= td) {
                           dwt_output.at(iter) = 0;
                       }
                   }
               } else {
                   for (int iter=len + 1; iter < len + 3 * length[2 * it] * length[2 * it +1]; iter++) {
                       if (abs(dwt_output[iter]) <= td) {
                           dwt_output.at(iter) = 0;
                       }
                   }
               }
               } else if (dn_thresh == "soft") {
                   if (it == 0) {
                   for (int iter=length[0] * length[1]; iter < 4 * length[0] * length[1]; iter++) {
                       if (abs(dwt_output[iter]) >= td) {
                           double temp;
                           temp = sgn(dwt_output[iter])*( abs(dwt_output[iter]) - td);
                           dwt_output.at(iter) = temp;
                       } else {
                           dwt_output.at(iter) = 0;
                       }
                   }
               } else {
                   for (int iter=len + 1; iter < len + 3 * length[2 * it] * length[2 * it +1]; iter++) {
                       if (abs(dwt_output[iter]) >= td) {
                           double temp;
                           temp = sgn(dwt_output[iter])*( abs(dwt_output[iter]) - td);
                           dwt_output.at(iter) = temp;
                       } else {
                           dwt_output.at(iter) = 0;
                       }
                   }
               }


               }
               if ( it >= 1) {
                   len += 3 * length[2 * it] * length[2 * it +1];

               }
           }
               idwt_2d( dwt_output,flag, nm_dn, idwt_output,length);
               dispDENOISE(idwt_output);

           } else {

               for (int col =0; col < 3; col++) {
               if (col ==0) {
                   vec = vecred;
               } else if (col == 1) {
                   vec = vecgreen;
               } else {
                   vec = vecblue;
               }
               flag.clear();
               length.clear();
               dwt_output.clear();
               dwt_2d(vec,J_dn,nm_dn,dwt_output,flag,length);
               int len = 0;

               for (int it = 0; it < J_dn; it++) {
                   vector<double> dwt_med;
                   vector<double> coef;
                   int dwt_len;
                   if (it == 0) {
                   for (int i= length[0] * length[1]; i < 4 * length[0] * length[1];i++) {
                       double temp = abs(dwt_output[i]);
                       double temp2 = dwt_output[i];
                       dwt_med.push_back(temp);
                       coef.push_back(temp2);
                   }
                   len= 4 * length[0] * length[1];
                   dwt_len = dwt_med.size();
               } else {
                    for (int i= len + 1; i < len + 3 * length[2 * it] * length[2 * it +1];i++) {
                        double temp = abs(dwt_output[i]);
                        double temp2 = dwt_output[i];
                        dwt_med.push_back(temp);
                        coef.push_back(temp2);
                    }
                   dwt_len = dwt_med.size();

               }
                   double sigma;
                   median(dwt_med,sigma);

                   double td;


               // td = sqrt(2.0 * log(dwt_len)) * sigma / 0.6745;

                   if ( sigma < 0.00000001) {
                       td = 0;
                   } else {
                       double tv;
                       tv = sqrt(2.0 * log(dwt_len));
                       double norm;
                       l2norm(coef,norm);
                       double te;
                       te =(pow(norm,2.0) - (double) dwt_len)/(double) dwt_len;
                       double ct;

                       ct = pow(log((double) dwt_len)/log(2.0),1.5)/sqrt((double) dwt_len);
                       if (te < ct) {
                           td = tv;
                       } else {
                           sort(dwt_med.begin(),dwt_med.end());
                           vector<double> x_sure;
                           double x_sum = 0.0;

                           for (unsigned int val =0; val < dwt_med.size();val++){
                               double temp;
                               temp = pow(dwt_med[val],2.0);
                               x_sure.push_back(temp);
                               x_sum+=temp;
                           }

                           vector<double> risk_vector;
                           for (int rk=0; rk < dwt_len; rk++) {
                               double temp = ((double)dwt_len + 1 - 2 * ((double)rk + 1) +x_sum + x_sure[rk]*((double)dwt_len - 1 -(double) rk))/(double)dwt_len;
                               risk_vector.push_back(temp);
                           }

                        int min_index;
                        minindex(risk_vector,min_index);
                        double thr;
                        thr = sqrt(x_sure[min_index]);

                        td = min(thr,tv);

                       }
                   }
                   td = td * sigma / 0.6745;


               if (dn_thresh == "hard") {
                   if (it == 0) {
                   for (int iter=length[0] * length[1]; iter < 4 * length[0] * length[1]; iter++) {
                       if (abs(dwt_output[iter]) <= td) {
                           dwt_output.at(iter) = 0;
                       }
                   }
               } else {
                   for (int iter=len + 1; iter < len + 3 * length[2 * it] * length[2 * it +1]; iter++) {
                       if (abs(dwt_output[iter]) <= td) {
                           dwt_output.at(iter) = 0;
                       }
                   }
               }
               } else if (dn_thresh == "soft") {
                   if (it == 0) {
                   for (int iter=length[0] * length[1]; iter < 4 * length[0] * length[1]; iter++) {
                       if (abs(dwt_output[iter]) >= td) {
                           double temp;
                           temp = sgn(dwt_output[iter])*( abs(dwt_output[iter]) - td);
                           dwt_output.at(iter) = temp;
                       } else {
                           dwt_output.at(iter) = 0;
                       }
                   }
               } else {
                   for (int iter=len + 1; iter < len + 3 * length[2 * it] * length[2 * it +1]; iter++) {
                       if (abs(dwt_output[iter]) >= td) {
                           double temp;
                           temp = sgn(dwt_output[iter])*( abs(dwt_output[iter]) - td);
                           dwt_output.at(iter) = temp;
                       } else {
                           dwt_output.at(iter) = 0;
                       }
                   }
               }


               }
               if ( it >= 1) {
                   len += 3 * length[2 * it] * length[2 * it +1];

               }
           }
               if (col ==0) {
                   dwt_output_r = dwt_output;
                   flag_r = flag;
                   length_r = length;
               } else if (col == 1) {
                   dwt_output_g = dwt_output;
                   flag_g = flag;
                   length_g = length;

               } else {
                   dwt_output_b = dwt_output;
                   flag_b = flag;
                   length_b = length;
               }
           }

               idwt_2d( dwt_output_r,flag_r, nm_dn, idwt_output_r,length_r);
               idwt_2d( dwt_output_g,flag_g, nm_dn, idwt_output_g,length_g);
               idwt_2d( dwt_output_b,flag_b, nm_dn, idwt_output_b,length_b);
               dispDENOISE_RGB(idwt_output_r,idwt_output_g,idwt_output_b);


           }

 }  else if (mode_denoise == "dwt_sym") {
     if (form == 3) {
         flag.clear();
         dwt_2d_sym(vec,J_dn,nm_dn,dwt_output,flag,length,ext_dn);
         int len = 0;

         for (int it = 0; it < J_dn; it++) {
             vector<double> dwt_med;
             vector<double> coef;
             int dwt_len;
             if (it == 0) {
             for (int i= length[0] * length[1]; i < 4 * length[0] * length[1];i++) {
                 double temp = abs(dwt_output[i]);
                 double temp2 = dwt_output[i];
                 dwt_med.push_back(temp);
                 coef.push_back(temp2);
             }
             len= 4 * length[0] * length[1];
             dwt_len = dwt_med.size();
         } else {
              for (int i= len + 1; i < len + 3 * length[2 * it] * length[2 * it +1];i++) {
                  double temp = abs(dwt_output[i]);
                  double temp2 = dwt_output[i];
                  dwt_med.push_back(temp);
                  coef.push_back(temp2);
              }
             dwt_len = dwt_med.size();

         }
             double sigma;
             median(dwt_med,sigma);

             double td;


         // td = sqrt(2.0 * log(dwt_len)) * sigma / 0.6745;

             if ( sigma < 0.00000001) {
                 td = 0;
             } else {
                 double tv;
                 tv = sqrt(2.0 * log(dwt_len));
                 double norm;
                 l2norm(coef,norm);
                 double te;
                 te =(pow(norm,2.0) - (double) dwt_len)/(double) dwt_len;
                 double ct;

                 ct = pow(log((double) dwt_len)/log(2.0),1.5)/sqrt((double) dwt_len);
                 if (te < ct) {
                     td = tv;
                 } else {
                     sort(dwt_med.begin(),dwt_med.end());
                     vector<double> x_sure;
                     double x_sum = 0.0;

                     for (unsigned int val =0; val < dwt_med.size();val++){
                         double temp;
                         temp = pow(dwt_med[val],2.0);
                         x_sure.push_back(temp);
                         x_sum+=temp;
                     }

                     vector<double> risk_vector;
                     for (int rk=0; rk < dwt_len; rk++) {
                         double temp = ((double)dwt_len + 1 - 2 * ((double)rk + 1) +x_sum + x_sure[rk]*((double)dwt_len - 1 -(double) rk))/(double)dwt_len;
                         risk_vector.push_back(temp);
                     }

                  int min_index;
                  minindex(risk_vector,min_index);
                  double thr;
                  thr = sqrt(x_sure[min_index]);

                  td = min(thr,tv);

                 }
             }
             td = td * sigma / 0.6745;


         if (dn_thresh == "hard") {
             if (it == 0) {
             for (int iter=length[0] * length[1]; iter < 4 * length[0] * length[1]; iter++) {
                 if (abs(dwt_output[iter]) <= td) {
                     dwt_output.at(iter) = 0;
                 }
             }
         } else {
             for (int iter=len + 1; iter < len + 3 * length[2 * it] * length[2 * it +1]; iter++) {
                 if (abs(dwt_output[iter]) <= td) {
                     dwt_output.at(iter) = 0;
                 }
             }
         }
         } else if (dn_thresh == "soft") {
             if (it == 0) {
             for (int iter=length[0] * length[1]; iter < 4 * length[0] * length[1]; iter++) {
                 if (abs(dwt_output[iter]) >= td) {
                     double temp;
                     temp = sgn(dwt_output[iter])*( abs(dwt_output[iter]) - td);
                     dwt_output.at(iter) = temp;
                 } else {
                     dwt_output.at(iter) = 0;
                 }
             }
         } else {
             for (int iter=len + 1; iter < len + 3 * length[2 * it] * length[2 * it +1]; iter++) {
                 if (abs(dwt_output[iter]) >= td) {
                     double temp;
                     temp = sgn(dwt_output[iter])*( abs(dwt_output[iter]) - td);
                     dwt_output.at(iter) = temp;
                 } else {
                     dwt_output.at(iter) = 0;
                 }
             }
         }


         }
         if ( it >= 1) {
             len += 3 * length[2 * it] * length[2 * it +1];

         }
     }
         idwt_2d_sym( dwt_output,flag, nm_dn, idwt_output,length);
         dispDENOISE(idwt_output);

     } else {

         for (int col =0; col < 3; col++) {
         if (col ==0) {
             vec = vecred;
         } else if (col == 1) {
             vec = vecgreen;
         } else {
             vec = vecblue;
         }
         flag.clear();
         length.clear();
         dwt_output.clear();
         dwt_2d_sym(vec,J_dn,nm_dn,dwt_output,flag,length,ext_dn);
         int len = 0;

         for (int it = 0; it < J_dn; it++) {
             vector<double> dwt_med;
             vector<double> coef;
             int dwt_len;
             if (it == 0) {
             for (int i= length[0] * length[1]; i < 4 * length[0] * length[1];i++) {
                 double temp = abs(dwt_output[i]);
                 double temp2 = dwt_output[i];
                 dwt_med.push_back(temp);
                 coef.push_back(temp2);
             }
             len= 4 * length[0] * length[1];
             dwt_len = dwt_med.size();
         } else {
              for (int i= len + 1; i < len + 3 * length[2 * it] * length[2 * it +1];i++) {
                  double temp = abs(dwt_output[i]);
                  double temp2 = dwt_output[i];
                  dwt_med.push_back(temp);
                  coef.push_back(temp2);
              }
             dwt_len = dwt_med.size();

         }
             double sigma;
             median(dwt_med,sigma);

             double td;


         // td = sqrt(2.0 * log(dwt_len)) * sigma / 0.6745;

             if ( sigma < 0.00000001) {
                 td = 0;
             } else {
                 double tv;
                 tv = sqrt(2.0 * log(dwt_len));
                 double norm;
                 l2norm(coef,norm);
                 double te;
                 te =(pow(norm,2.0) - (double) dwt_len)/(double) dwt_len;
                 double ct;

                 ct = pow(log((double) dwt_len)/log(2.0),1.5)/sqrt((double) dwt_len);
                 if (te < ct) {
                     td = tv;
                 } else {
                     sort(dwt_med.begin(),dwt_med.end());
                     vector<double> x_sure;
                     double x_sum = 0.0;

                     for (unsigned int val =0; val < dwt_med.size();val++){
                         double temp;
                         temp = pow(dwt_med[val],2.0);
                         x_sure.push_back(temp);
                         x_sum+=temp;
                     }

                     vector<double> risk_vector;
                     for (int rk=0; rk < dwt_len; rk++) {
                         double temp = ((double)dwt_len + 1 - 2 * ((double)rk + 1) +x_sum + x_sure[rk]*((double)dwt_len - 1 -(double) rk))/(double)dwt_len;
                         risk_vector.push_back(temp);
                     }

                  int min_index;
                  minindex(risk_vector,min_index);
                  double thr;
                  thr = sqrt(x_sure[min_index]);

                  td = min(thr,tv);

                 }
             }
             td = td * sigma / 0.6745;


         if (dn_thresh == "hard") {
             if (it == 0) {
             for (int iter=length[0] * length[1]; iter < 4 * length[0] * length[1]; iter++) {
                 if (abs(dwt_output[iter]) <= td) {
                     dwt_output.at(iter) = 0;
                 }
             }
         } else {
             for (int iter=len + 1; iter < len + 3 * length[2 * it] * length[2 * it +1]; iter++) {
                 if (abs(dwt_output[iter]) <= td) {
                     dwt_output.at(iter) = 0;
                 }
             }
         }
         } else if (dn_thresh == "soft") {
             if (it == 0) {
             for (int iter=length[0] * length[1]; iter < 4 * length[0] * length[1]; iter++) {
                 if (abs(dwt_output[iter]) >= td) {
                     double temp;
                     temp = sgn(dwt_output[iter])*( abs(dwt_output[iter]) - td);
                     dwt_output.at(iter) = temp;
                 } else {
                     dwt_output.at(iter) = 0;
                 }
             }
         } else {
             for (int iter=len + 1; iter < len + 3 * length[2 * it] * length[2 * it +1]; iter++) {
                 if (abs(dwt_output[iter]) >= td) {
                     double temp;
                     temp = sgn(dwt_output[iter])*( abs(dwt_output[iter]) - td);
                     dwt_output.at(iter) = temp;
                 } else {
                     dwt_output.at(iter) = 0;
                 }
             }
         }


         }
         if ( it >= 1) {
             len += 3 * length[2 * it] * length[2 * it +1];

         }
     }
         if (col ==0) {
             dwt_output_r = dwt_output;
             flag_r = flag;
             length_r = length;
         } else if (col == 1) {
             dwt_output_g = dwt_output;
             flag_g = flag;
             length_g = length;

         } else {
             dwt_output_b = dwt_output;
             flag_b = flag;
             length_b = length;
         }
     }

         idwt_2d_sym( dwt_output_r,flag_r, nm_dn, idwt_output_r,length_r);
         idwt_2d_sym( dwt_output_g,flag_g, nm_dn, idwt_output_g,length_g);
         idwt_2d_sym( dwt_output_b,flag_b, nm_dn, idwt_output_b,length_b);
         dispDENOISE_RGB(idwt_output_r,idwt_output_g,idwt_output_b);


     }
    }

   } else if (dn_method == "bayesshrink") {
    if ( mode_denoise == "dwt_per") {
        if (form == 3) {

        flag.clear();
        dwt_2d(vec,J_dn,nm_dn,dwt_output,flag,length);
        int len = 0;

        int dwt_len = dwt_output.size();
        int siz = length.size();
        int l1 = length[siz-3];
        int l2 = length[siz -4];
        vector<double> hh_noise_vector;
        for (unsigned int i=(unsigned int) dwt_len - l1*l2; i < (unsigned int) dwt_len;i++) {
            double temp = abs(dwt_output[i]);
            hh_noise_vector.push_back(temp);
        }
        double sigmaN;
        median(hh_noise_vector,sigmaN);

        for (int it = 0; it < J_dn; it++) {
            vector<double> dwt_med_hh,dwt_med_hl,dwt_med_lh;
            if (it == 0) {
            for (int i= length[0] * length[1]; i < 2 * length[0] * length[1];i++) {
                double temp = abs(dwt_output[i]);
                dwt_med_lh.push_back(temp);
            }
            for (int i= 2 *length[0] * length[1]; i < 3 * length[0] * length[1];i++) {
                double temp = abs(dwt_output[i]);
                dwt_med_hl.push_back(temp);
            }
            for (int i= 3 *length[0] * length[1]; i < 4 * length[0] * length[1];i++) {
                double temp = abs(dwt_output[i]);
                dwt_med_hh.push_back(temp);
            }
            len= 4 * length[0] * length[1];
        } else {
             for (int i= len ; i < len + length[2 * it] * length[2 * it +1];i++) {
                 double temp = abs(dwt_output[i]);
                 dwt_med_lh.push_back(temp);
             }
             for (int i= len +length[2 * it] * length[2 * it +1]; i < len + 2 *length[2 * it] * length[2 * it +1];i++) {
                 double temp = abs(dwt_output[i]);
                 dwt_med_hl.push_back(temp);
             }
             for (int i= len + 2*length[2 * it] * length[2 * it +1]; i < len + 3 *length[2 * it] * length[2 * it +1];i++) {
                 double temp = abs(dwt_output[i]);
                 dwt_med_hh.push_back(temp);
             }

        }
        double sigmaW_hh;
        median(dwt_med_hh,sigmaW_hh);

        double sigmaW_hl;
        median(dwt_med_hl,sigmaW_hl);

        double sigmaW_lh;
        median(dwt_med_lh,sigmaW_lh);

        double sigmaS_hh,sigmaS_hl,sigmaS_lh;

        double td_hh,td_hl,td_lh;

        sigmaS_hh= max((pow(sigmaW_hh,2.0)-pow(sigmaN,2.0)),0.0);
        sigmaS_hl= max((pow(sigmaW_hl,2.0)-pow(sigmaN,2.0)),0.0);
        sigmaS_lh= max((pow(sigmaW_lh,2.0)-pow(sigmaN,2.0)),0.0);



        if ( sigmaS_hh < 0) {
            td_hh = 0;
        } else {
            td_hh = pow(sigmaN,2.0) /sqrt(sigmaS_hh);
        }
        if ( sigmaS_hl < 0) {
            td_hl = 0;
        }else {
            td_hl = pow(sigmaN,2.0) /sqrt(sigmaS_hl);
        }
        if ( sigmaS_lh < 0) {
            td_lh = 0;
        }else {
            td_lh = pow(sigmaN,2.0) /sqrt(sigmaS_lh);
        }




        if (dn_thresh == "hard") {
            if (it == 0) {
            for (int iter=length[0] * length[1]; iter < 2 * length[0] * length[1]; iter++) {
                if (abs(dwt_output[iter]) <= td_lh) {
                    dwt_output.at(iter) = 0;
                }
            }
            for (int iter=2 *length[0] * length[1]; iter < 3 * length[0] * length[1]; iter++) {
                if (abs(dwt_output[iter]) <= td_hl) {
                    dwt_output.at(iter) = 0;
                }
            }
            for (int iter=3 *length[0] * length[1]; iter < 4 * length[0] * length[1]; iter++) {
                if (abs(dwt_output[iter]) <= td_hh) {
                    dwt_output.at(iter) = 0;
                }
            }
        } else {
            for (int iter=len ; iter < len + length[2 * it] * length[2 * it +1]; iter++) {
                if (abs(dwt_output[iter]) <= td_lh) {
                    dwt_output.at(iter) = 0;
                }
            }
            for (int iter=len+length[2 * it] * length[2 * it +1]; iter < len + 2*length[2 * it] * length[2 * it +1]; iter++) {
                if (abs(dwt_output[iter]) <= td_hl) {
                    dwt_output.at(iter) = 0;
                }
            }
            for (int iter=len +2*length[2 * it] * length[2 * it +1]; iter < len + 3*length[2 * it] * length[2 * it +1]; iter++) {
                if (abs(dwt_output[iter]) <= td_hh) {
                    dwt_output.at(iter) = 0;
                }
            }
        }
        } else if (dn_thresh == "soft") {
            if (it == 0) {
            for (int iter=length[0] * length[1]; iter < 2 * length[0] * length[1]; iter++) {
                if (abs(dwt_output[iter]) >= td_lh) {
                    double temp;
                    temp = sgn(dwt_output[iter])*( abs(dwt_output[iter]) - td_lh);
                    dwt_output.at(iter) = temp;
                } else {
                    dwt_output.at(iter) = 0;
                }
            }
            for (int iter=2 *length[0] * length[1]; iter < 3 * length[0] * length[1]; iter++) {
                if (abs(dwt_output[iter]) >= td_hl) {
                    double temp;
                    temp = sgn(dwt_output[iter])*( abs(dwt_output[iter]) - td_hl);
                    dwt_output.at(iter) = temp;
                } else {
                    dwt_output.at(iter) = 0;
                }
            }
            for (int iter=3 *length[0] * length[1]; iter < 4 * length[0] * length[1]; iter++) {
                if (abs(dwt_output[iter]) >= td_hh) {
                    double temp;
                    temp = sgn(dwt_output[iter])*( abs(dwt_output[iter]) - td_hh);
                    dwt_output.at(iter) = temp;
                } else {
                    dwt_output.at(iter) = 0;
                }
            }
        } else {
            for (int iter=len ; iter < len + length[2 * it] * length[2 * it +1]; iter++) {
                if (abs(dwt_output[iter]) >= td_lh) {
                    double temp;
                    temp = sgn(dwt_output[iter])*( abs(dwt_output[iter]) - td_lh);
                    dwt_output.at(iter) = temp;
                } else {
                    dwt_output.at(iter) = 0;
                }
            }

        for (int iter=len +length[2 * it] * length[2 * it +1]; iter < len + 2 * length[2 * it] * length[2 * it +1]; iter++) {
            if (abs(dwt_output[iter]) >= td_hl) {
                double temp;
                temp = sgn(dwt_output[iter])*( abs(dwt_output[iter]) - td_hl);
                dwt_output.at(iter) = temp;
            } else {
                dwt_output.at(iter) = 0;
            }
        }

        for (int iter=len +length[2 * it] * length[2 * it +1]; iter < len + 3 * length[2 * it] * length[2 * it +1]; iter++) {
            if (abs(dwt_output[iter]) >= td_hh) {
                double temp;
                temp = sgn(dwt_output[iter])*( abs(dwt_output[iter]) - td_hh);
                dwt_output.at(iter) = temp;
            } else {
                dwt_output.at(iter) = 0;
            }
        }
       }
        }
        if ( it >= 1) {
            len += 3 * length[2 * it] * length[2 * it +1];

        }
    }
        idwt_2d( dwt_output,flag, nm_dn, idwt_output,length);
        dispDENOISE(idwt_output);
    } else {
        for (int col = 0; col < 3; col++) {
            if (col == 0) {
                vec = vecred;
            } else if (col == 1) {
                vec = vecgreen;
            } else {
                vec = vecblue;
            }

            flag.clear();
            length.clear();
            dwt_output.clear();
            dwt_2d(vec,J_dn,nm_dn,dwt_output,flag,length);
            int len = 0;

            int dwt_len = dwt_output.size();
            int siz = length.size();
            int l1 = length[siz-3];
            int l2 = length[siz -4];
            vector<double> hh_noise_vector;
            for (unsigned int i=(unsigned int) dwt_len - l1*l2; i < (unsigned int) dwt_len;i++) {
                double temp = abs(dwt_output[i]);
                hh_noise_vector.push_back(temp);
            }
            double sigmaN;
            median(hh_noise_vector,sigmaN);

            for (int it = 0; it < J_dn; it++) {
                vector<double> dwt_med_hh,dwt_med_hl,dwt_med_lh;
                if (it == 0) {
                for (int i= length[0] * length[1]; i < 2 * length[0] * length[1];i++) {
                    double temp = abs(dwt_output[i]);
                    dwt_med_lh.push_back(temp);
                }
                for (int i= 2 *length[0] * length[1]; i < 3 * length[0] * length[1];i++) {
                    double temp = abs(dwt_output[i]);
                    dwt_med_hl.push_back(temp);
                }
                for (int i= 3 *length[0] * length[1]; i < 4 * length[0] * length[1];i++) {
                    double temp = abs(dwt_output[i]);
                    dwt_med_hh.push_back(temp);
                }
                len= 4 * length[0] * length[1];
            } else {
                 for (int i= len ; i < len + length[2 * it] * length[2 * it +1];i++) {
                     double temp = abs(dwt_output[i]);
                     dwt_med_lh.push_back(temp);
                 }
                 for (int i= len +length[2 * it] * length[2 * it +1]; i < len + 2 *length[2 * it] * length[2 * it +1];i++) {
                     double temp = abs(dwt_output[i]);
                     dwt_med_hl.push_back(temp);
                 }
                 for (int i= len + 2*length[2 * it] * length[2 * it +1]; i < len + 3 *length[2 * it] * length[2 * it +1];i++) {
                     double temp = abs(dwt_output[i]);
                     dwt_med_hh.push_back(temp);
                 }

            }
            double sigmaW_hh;
            median(dwt_med_hh,sigmaW_hh);

            double sigmaW_hl;
            median(dwt_med_hl,sigmaW_hl);

            double sigmaW_lh;
            median(dwt_med_lh,sigmaW_lh);

            double sigmaS_hh,sigmaS_hl,sigmaS_lh;

            double td_hh,td_hl,td_lh;

            sigmaS_hh= max((pow(sigmaW_hh,2.0)-pow(sigmaN,2.0)),0.0);
            sigmaS_hl= max((pow(sigmaW_hl,2.0)-pow(sigmaN,2.0)),0.0);
            sigmaS_lh= max((pow(sigmaW_lh,2.0)-pow(sigmaN,2.0)),0.0);



            if ( sigmaS_hh < 0) {
                td_hh = 0;
            } else {
                td_hh = pow(sigmaN,2.0) /sqrt(sigmaS_hh);
            }
            if ( sigmaS_hl < 0) {
                td_hl = 0;
            }else {
                td_hl = pow(sigmaN,2.0) /sqrt(sigmaS_hl);
            }
            if ( sigmaS_lh < 0) {
                td_lh = 0;
            }else {
                td_lh = pow(sigmaN,2.0) /sqrt(sigmaS_lh);
            }




            if (dn_thresh == "hard") {
                if (it == 0) {
                for (int iter=length[0] * length[1]; iter < 2 * length[0] * length[1]; iter++) {
                    if (abs(dwt_output[iter]) <= td_lh) {
                        dwt_output.at(iter) = 0;
                    }
                }
                for (int iter=2 *length[0] * length[1]; iter < 3 * length[0] * length[1]; iter++) {
                    if (abs(dwt_output[iter]) <= td_hl) {
                        dwt_output.at(iter) = 0;
                    }
                }
                for (int iter=3 *length[0] * length[1]; iter < 4 * length[0] * length[1]; iter++) {
                    if (abs(dwt_output[iter]) <= td_hh) {
                        dwt_output.at(iter) = 0;
                    }
                }
            } else {
                for (int iter=len ; iter < len + length[2 * it] * length[2 * it +1]; iter++) {
                    if (abs(dwt_output[iter]) <= td_lh) {
                        dwt_output.at(iter) = 0;
                    }
                }
                for (int iter=len+length[2 * it] * length[2 * it +1]; iter < len + 2*length[2 * it] * length[2 * it +1]; iter++) {
                    if (abs(dwt_output[iter]) <= td_hl) {
                        dwt_output.at(iter) = 0;
                    }
                }
                for (int iter=len +2*length[2 * it] * length[2 * it +1]; iter < len + 3*length[2 * it] * length[2 * it +1]; iter++) {
                    if (abs(dwt_output[iter]) <= td_hh) {
                        dwt_output.at(iter) = 0;
                    }
                }
            }
            } else if (dn_thresh == "soft") {
                if (it == 0) {
                for (int iter=length[0] * length[1]; iter < 2 * length[0] * length[1]; iter++) {
                    if (abs(dwt_output[iter]) >= td_lh) {
                        double temp;
                        temp = sgn(dwt_output[iter])*( abs(dwt_output[iter]) - td_lh);
                        dwt_output.at(iter) = temp;
                    } else {
                        dwt_output.at(iter) = 0;
                    }
                }
                for (int iter=2 *length[0] * length[1]; iter < 3 * length[0] * length[1]; iter++) {
                    if (abs(dwt_output[iter]) >= td_hl) {
                        double temp;
                        temp = sgn(dwt_output[iter])*( abs(dwt_output[iter]) - td_hl);
                        dwt_output.at(iter) = temp;
                    } else {
                        dwt_output.at(iter) = 0;
                    }
                }
                for (int iter=3 *length[0] * length[1]; iter < 4 * length[0] * length[1]; iter++) {
                    if (abs(dwt_output[iter]) >= td_hh) {
                        double temp;
                        temp = sgn(dwt_output[iter])*( abs(dwt_output[iter]) - td_hh);
                        dwt_output.at(iter) = temp;
                    } else {
                        dwt_output.at(iter) = 0;
                    }
                }
            } else {
                for (int iter=len ; iter < len + length[2 * it] * length[2 * it +1]; iter++) {
                    if (abs(dwt_output[iter]) >= td_lh) {
                        double temp;
                        temp = sgn(dwt_output[iter])*( abs(dwt_output[iter]) - td_lh);
                        dwt_output.at(iter) = temp;
                    } else {
                        dwt_output.at(iter) = 0;
                    }
                }
            }
            for (int iter=len +length[2 * it] * length[2 * it +1]; iter < len + 2 * length[2 * it] * length[2 * it +1]; iter++) {
                if (abs(dwt_output[iter]) >= td_hl) {
                    double temp;
                    temp = sgn(dwt_output[iter])*( abs(dwt_output[iter]) - td_hl);
                    dwt_output.at(iter) = temp;
                } else {
                    dwt_output.at(iter) = 0;
                }
            }

            for (int iter=len +length[2 * it] * length[2 * it +1]; iter < len + 3 * length[2 * it] * length[2 * it +1]; iter++) {
                if (abs(dwt_output[iter]) >= td_hh) {
                    double temp;
                    temp = sgn(dwt_output[iter])*( abs(dwt_output[iter]) - td_hh);
                    dwt_output.at(iter) = temp;
                } else {
                    dwt_output.at(iter) = 0;
                }
            }

            }
            if ( it >= 1) {
                len += 3 * length[2 * it] * length[2 * it +1];

            }
            if (col ==0) {
                dwt_output_r = dwt_output;
                flag_r = flag;
                length_r = length;
            } else if (col == 1) {
                dwt_output_g = dwt_output;
                flag_g = flag;
                length_g = length;

            } else {
                dwt_output_b = dwt_output;
                flag_b = flag;
                length_b = length;
            }
        }
        }
            idwt_2d( dwt_output_r,flag_r, nm_dn, idwt_output_r,length_r);
            idwt_2d( dwt_output_g,flag_g, nm_dn, idwt_output_g,length_g);
            idwt_2d( dwt_output_b,flag_b, nm_dn, idwt_output_b,length_b);
            dispDENOISE_RGB(idwt_output_r,idwt_output_g,idwt_output_b);


    }


  } else if ( mode_denoise == "dwt_sym") {

      if (form == 3) {

      flag.clear();
      dwt_2d_sym(vec,J_dn,nm_dn,dwt_output,flag,length,ext_dn);
      int len = 0;

      int dwt_len = dwt_output.size();
      int siz = length.size();
      int l1 = length[siz-3];
      int l2 = length[siz -4];
      vector<double> hh_noise_vector;
      for (unsigned int i=(unsigned int) dwt_len - l1*l2; i < (unsigned int) dwt_len;i++) {
          double temp = abs(dwt_output[i]);
          hh_noise_vector.push_back(temp);
      }
      double sigmaN;
      median(hh_noise_vector,sigmaN);

      for (int it = 0; it < J_dn; it++) {
          vector<double> dwt_med_hh,dwt_med_hl,dwt_med_lh;
          if (it == 0) {
          for (int i= length[0] * length[1]; i < 2 * length[0] * length[1];i++) {
              double temp = abs(dwt_output[i]);
              dwt_med_lh.push_back(temp);
          }
          for (int i= 2 *length[0] * length[1]; i < 3 * length[0] * length[1];i++) {
              double temp = abs(dwt_output[i]);
              dwt_med_hl.push_back(temp);
          }
          for (int i= 3 *length[0] * length[1]; i < 4 * length[0] * length[1];i++) {
              double temp = abs(dwt_output[i]);
              dwt_med_hh.push_back(temp);
          }
          len= 4 * length[0] * length[1];
      } else {
           for (int i= len ; i < len + length[2 * it] * length[2 * it +1];i++) {
               double temp = abs(dwt_output[i]);
               dwt_med_lh.push_back(temp);
           }
           for (int i= len +length[2 * it] * length[2 * it +1]; i < len + 2 *length[2 * it] * length[2 * it +1];i++) {
               double temp = abs(dwt_output[i]);
               dwt_med_hl.push_back(temp);
           }
           for (int i= len + 2*length[2 * it] * length[2 * it +1]; i < len + 3 *length[2 * it] * length[2 * it +1];i++) {
               double temp = abs(dwt_output[i]);
               dwt_med_hh.push_back(temp);
           }

      }
      double sigmaW_hh;
      median(dwt_med_hh,sigmaW_hh);

      double sigmaW_hl;
      median(dwt_med_hl,sigmaW_hl);

      double sigmaW_lh;
      median(dwt_med_lh,sigmaW_lh);

      double sigmaS_hh,sigmaS_hl,sigmaS_lh;

      double td_hh,td_hl,td_lh;

      sigmaS_hh= max((pow(sigmaW_hh,2.0)-pow(sigmaN,2.0)),0.0);
      sigmaS_hl= max((pow(sigmaW_hl,2.0)-pow(sigmaN,2.0)),0.0);
      sigmaS_lh= max((pow(sigmaW_lh,2.0)-pow(sigmaN,2.0)),0.0);



      if ( sigmaS_hh < 0) {
          td_hh = 0;
      } else {
          td_hh = pow(sigmaN,2.0) /sqrt(sigmaS_hh);
      }
      if ( sigmaS_hl < 0) {
          td_hl = 0;
      }else {
          td_hl = pow(sigmaN,2.0) /sqrt(sigmaS_hl);
      }
      if ( sigmaS_lh < 0) {
          td_lh = 0;
      }else {
          td_lh = pow(sigmaN,2.0) /sqrt(sigmaS_lh);
      }




      if (dn_thresh == "hard") {
          if (it == 0) {
          for (int iter=length[0] * length[1]; iter < 2 * length[0] * length[1]; iter++) {
              if (abs(dwt_output[iter]) <= td_lh) {
                  dwt_output.at(iter) = 0;
              }
          }
          for (int iter=2 *length[0] * length[1]; iter < 3 * length[0] * length[1]; iter++) {
              if (abs(dwt_output[iter]) <= td_hl) {
                  dwt_output.at(iter) = 0;
              }
          }
          for (int iter=3 *length[0] * length[1]; iter < 4 * length[0] * length[1]; iter++) {
              if (abs(dwt_output[iter]) <= td_hh) {
                  dwt_output.at(iter) = 0;
              }
          }
      } else {
          for (int iter=len ; iter < len + length[2 * it] * length[2 * it +1]; iter++) {
              if (abs(dwt_output[iter]) <= td_lh) {
                  dwt_output.at(iter) = 0;
              }
          }
          for (int iter=len+length[2 * it] * length[2 * it +1]; iter < len + 2*length[2 * it] * length[2 * it +1]; iter++) {
              if (abs(dwt_output[iter]) <= td_hl) {
                  dwt_output.at(iter) = 0;
              }
          }
          for (int iter=len +2*length[2 * it] * length[2 * it +1]; iter < len + 3*length[2 * it] * length[2 * it +1]; iter++) {
              if (abs(dwt_output[iter]) <= td_hh) {
                  dwt_output.at(iter) = 0;
              }
          }
      }
      } else if (dn_thresh == "soft") {
          if (it == 0) {
          for (int iter=length[0] * length[1]; iter < 2 * length[0] * length[1]; iter++) {
              if (abs(dwt_output[iter]) >= td_lh) {
                  double temp;
                  temp = sgn(dwt_output[iter])*( abs(dwt_output[iter]) - td_lh);
                  dwt_output.at(iter) = temp;
              } else {
                  dwt_output.at(iter) = 0;
              }
          }
          for (int iter=2 *length[0] * length[1]; iter < 3 * length[0] * length[1]; iter++) {
              if (abs(dwt_output[iter]) >= td_hl) {
                  double temp;
                  temp = sgn(dwt_output[iter])*( abs(dwt_output[iter]) - td_hl);
                  dwt_output.at(iter) = temp;
              } else {
                  dwt_output.at(iter) = 0;
              }
          }
          for (int iter=3 *length[0] * length[1]; iter < 4 * length[0] * length[1]; iter++) {
              if (abs(dwt_output[iter]) >= td_hh) {
                  double temp;
                  temp = sgn(dwt_output[iter])*( abs(dwt_output[iter]) - td_hh);
                  dwt_output.at(iter) = temp;
              } else {
                  dwt_output.at(iter) = 0;
              }
          }
      } else {
          for (int iter=len ; iter < len + length[2 * it] * length[2 * it +1]; iter++) {
              if (abs(dwt_output[iter]) >= td_lh) {
                  double temp;
                  temp = sgn(dwt_output[iter])*( abs(dwt_output[iter]) - td_lh);
                  dwt_output.at(iter) = temp;
              } else {
                  dwt_output.at(iter) = 0;
              }
          }

      for (int iter=len +length[2 * it] * length[2 * it +1]; iter < len + 2 * length[2 * it] * length[2 * it +1]; iter++) {
          if (abs(dwt_output[iter]) >= td_hl) {
              double temp;
              temp = sgn(dwt_output[iter])*( abs(dwt_output[iter]) - td_hl);
              dwt_output.at(iter) = temp;
          } else {
              dwt_output.at(iter) = 0;
          }
      }

      for (int iter=len +length[2 * it] * length[2 * it +1]; iter < len + 3 * length[2 * it] * length[2 * it +1]; iter++) {
          if (abs(dwt_output[iter]) >= td_hh) {
              double temp;
              temp = sgn(dwt_output[iter])*( abs(dwt_output[iter]) - td_hh);
              dwt_output.at(iter) = temp;
          } else {
              dwt_output.at(iter) = 0;
          }
      }
     }
      }
      if ( it >= 1) {
          len += 3 * length[2 * it] * length[2 * it +1];

      }
  }
      idwt_2d_sym( dwt_output,flag, nm_dn, idwt_output,length);
      dispDENOISE(idwt_output);
  } else {
      for (int col = 0; col < 3; col++) {
          if (col == 0) {
              vec = vecred;
          } else if (col == 1) {
              vec = vecgreen;
          } else {
              vec = vecblue;
          }

          flag.clear();
          length.clear();
          dwt_output.clear();
          dwt_2d_sym(vec,J_dn,nm_dn,dwt_output,flag,length,ext_dn);
          int len = 0;

          int dwt_len = dwt_output.size();
          int siz = length.size();
          int l1 = length[siz-3];
          int l2 = length[siz -4];
          vector<double> hh_noise_vector;
          for (unsigned int i=(unsigned int) dwt_len - l1*l2; i < (unsigned int) dwt_len;i++) {
              double temp = abs(dwt_output[i]);
              hh_noise_vector.push_back(temp);
          }
          double sigmaN;
          median(hh_noise_vector,sigmaN);

          for (int it = 0; it < J_dn; it++) {
              vector<double> dwt_med_hh,dwt_med_hl,dwt_med_lh;
              if (it == 0) {
              for (int i= length[0] * length[1]; i < 2 * length[0] * length[1];i++) {
                  double temp = abs(dwt_output[i]);
                  dwt_med_lh.push_back(temp);
              }
              for (int i= 2 *length[0] * length[1]; i < 3 * length[0] * length[1];i++) {
                  double temp = abs(dwt_output[i]);
                  dwt_med_hl.push_back(temp);
              }
              for (int i= 3 *length[0] * length[1]; i < 4 * length[0] * length[1];i++) {
                  double temp = abs(dwt_output[i]);
                  dwt_med_hh.push_back(temp);
              }
              len= 4 * length[0] * length[1];
          } else {
               for (int i= len ; i < len + length[2 * it] * length[2 * it +1];i++) {
                   double temp = abs(dwt_output[i]);
                   dwt_med_lh.push_back(temp);
               }
               for (int i= len +length[2 * it] * length[2 * it +1]; i < len + 2 *length[2 * it] * length[2 * it +1];i++) {
                   double temp = abs(dwt_output[i]);
                   dwt_med_hl.push_back(temp);
               }
               for (int i= len + 2*length[2 * it] * length[2 * it +1]; i < len + 3 *length[2 * it] * length[2 * it +1];i++) {
                   double temp = abs(dwt_output[i]);
                   dwt_med_hh.push_back(temp);
               }

          }
          double sigmaW_hh;
          median(dwt_med_hh,sigmaW_hh);

          double sigmaW_hl;
          median(dwt_med_hl,sigmaW_hl);

          double sigmaW_lh;
          median(dwt_med_lh,sigmaW_lh);

          double sigmaS_hh,sigmaS_hl,sigmaS_lh;

          double td_hh,td_hl,td_lh;

          sigmaS_hh= max((pow(sigmaW_hh,2.0)-pow(sigmaN,2.0)),0.0);
          sigmaS_hl= max((pow(sigmaW_hl,2.0)-pow(sigmaN,2.0)),0.0);
          sigmaS_lh= max((pow(sigmaW_lh,2.0)-pow(sigmaN,2.0)),0.0);



          if ( sigmaS_hh < 0) {
              td_hh = 0;
          } else {
              td_hh = pow(sigmaN,2.0) /sqrt(sigmaS_hh);
          }
          if ( sigmaS_hl < 0) {
              td_hl = 0;
          }else {
              td_hl = pow(sigmaN,2.0) /sqrt(sigmaS_hl);
          }
          if ( sigmaS_lh < 0) {
              td_lh = 0;
          }else {
              td_lh = pow(sigmaN,2.0) /sqrt(sigmaS_lh);
          }




          if (dn_thresh == "hard") {
              if (it == 0) {
              for (int iter=length[0] * length[1]; iter < 2 * length[0] * length[1]; iter++) {
                  if (abs(dwt_output[iter]) <= td_lh) {
                      dwt_output.at(iter) = 0;
                  }
              }
              for (int iter=2 *length[0] * length[1]; iter < 3 * length[0] * length[1]; iter++) {
                  if (abs(dwt_output[iter]) <= td_hl) {
                      dwt_output.at(iter) = 0;
                  }
              }
              for (int iter=3 *length[0] * length[1]; iter < 4 * length[0] * length[1]; iter++) {
                  if (abs(dwt_output[iter]) <= td_hh) {
                      dwt_output.at(iter) = 0;
                  }
              }
          } else {
              for (int iter=len ; iter < len + length[2 * it] * length[2 * it +1]; iter++) {
                  if (abs(dwt_output[iter]) <= td_lh) {
                      dwt_output.at(iter) = 0;
                  }
              }
              for (int iter=len+length[2 * it] * length[2 * it +1]; iter < len + 2*length[2 * it] * length[2 * it +1]; iter++) {
                  if (abs(dwt_output[iter]) <= td_hl) {
                      dwt_output.at(iter) = 0;
                  }
              }
              for (int iter=len +2*length[2 * it] * length[2 * it +1]; iter < len + 3*length[2 * it] * length[2 * it +1]; iter++) {
                  if (abs(dwt_output[iter]) <= td_hh) {
                      dwt_output.at(iter) = 0;
                  }
              }
          }
          } else if (dn_thresh == "soft") {
              if (it == 0) {
              for (int iter=length[0] * length[1]; iter < 2 * length[0] * length[1]; iter++) {
                  if (abs(dwt_output[iter]) >= td_lh) {
                      double temp;
                      temp = sgn(dwt_output[iter])*( abs(dwt_output[iter]) - td_lh);
                      dwt_output.at(iter) = temp;
                  } else {
                      dwt_output.at(iter) = 0;
                  }
              }
              for (int iter=2 *length[0] * length[1]; iter < 3 * length[0] * length[1]; iter++) {
                  if (abs(dwt_output[iter]) >= td_hl) {
                      double temp;
                      temp = sgn(dwt_output[iter])*( abs(dwt_output[iter]) - td_hl);
                      dwt_output.at(iter) = temp;
                  } else {
                      dwt_output.at(iter) = 0;
                  }
              }
              for (int iter=3 *length[0] * length[1]; iter < 4 * length[0] * length[1]; iter++) {
                  if (abs(dwt_output[iter]) >= td_hh) {
                      double temp;
                      temp = sgn(dwt_output[iter])*( abs(dwt_output[iter]) - td_hh);
                      dwt_output.at(iter) = temp;
                  } else {
                      dwt_output.at(iter) = 0;
                  }
              }
          } else {
              for (int iter=len ; iter < len + length[2 * it] * length[2 * it +1]; iter++) {
                  if (abs(dwt_output[iter]) >= td_lh) {
                      double temp;
                      temp = sgn(dwt_output[iter])*( abs(dwt_output[iter]) - td_lh);
                      dwt_output.at(iter) = temp;
                  } else {
                      dwt_output.at(iter) = 0;
                  }
              }
          }
          for (int iter=len +length[2 * it] * length[2 * it +1]; iter < len + 2 * length[2 * it] * length[2 * it +1]; iter++) {
              if (abs(dwt_output[iter]) >= td_hl) {
                  double temp;
                  temp = sgn(dwt_output[iter])*( abs(dwt_output[iter]) - td_hl);
                  dwt_output.at(iter) = temp;
              } else {
                  dwt_output.at(iter) = 0;
              }
          }

          for (int iter=len +length[2 * it] * length[2 * it +1]; iter < len + 3 * length[2 * it] * length[2 * it +1]; iter++) {
              if (abs(dwt_output[iter]) >= td_hh) {
                  double temp;
                  temp = sgn(dwt_output[iter])*( abs(dwt_output[iter]) - td_hh);
                  dwt_output.at(iter) = temp;
              } else {
                  dwt_output.at(iter) = 0;
              }
          }

          }
          if ( it >= 1) {
              len += 3 * length[2 * it] * length[2 * it +1];

          }
          if (col ==0) {
              dwt_output_r = dwt_output;
              flag_r = flag;
              length_r = length;
          } else if (col == 1) {
              dwt_output_g = dwt_output;
              flag_g = flag;
              length_g = length;

          } else {
              dwt_output_b = dwt_output;
              flag_b = flag;
              length_b = length;
          }
      }
      }
          idwt_2d_sym( dwt_output_r,flag_r, nm_dn, idwt_output_r,length_r);
          idwt_2d_sym( dwt_output_g,flag_g, nm_dn, idwt_output_g,length_g);
          idwt_2d_sym( dwt_output_b,flag_b, nm_dn, idwt_output_b,length_b);
          dispDENOISE_RGB(idwt_output_r,idwt_output_g,idwt_output_b);


  }

  }


}
  denoiseoutbutton->setEnabled(true);
  denoisecoefbutton->setEnabled(true);
  //denoised_signal = output;
  denoising_coefficients = dwt_output;

}

void MainWindow::dispDENOISE(vector<vector<double> > &idwtop) {
    QLayoutItem *child;
    while ((child = glayout->takeAt(0)) != 0)
    {
    delete child->widget();
    delete child;
    }

    vspacer = new QSpacerItem( 10, 10, QSizePolicy::Minimum,
    QSizePolicy::Expanding );
    hspacer1 = new QSpacerItem( 10, 10, QSizePolicy::Expanding,
    QSizePolicy::Minimum );
    hspacer2 = new QSpacerItem( 10, 10, QSizePolicy::Expanding,
    QSizePolicy::Minimum );
    spacer = new QSpacerItem( 10, 10, QSizePolicy::Minimum,
    QSizePolicy::Expanding );

    QLabel *label1 = new QLabel("Original Image");
    label1->setAlignment(Qt::AlignCenter);
    label1->setScaledContents(true);

    QPixmap pix;

    pix.convertFromImage(image);

    QLabel *labelorig = new QLabel(this);
    labelorig->setPixmap(pix);
    labelorig->setScaledContents(true);

    glayout->addItem(vspacer,0,1);
    glayout->addItem(hspacer1,1,0);
    glayout->addWidget(label1,1,1);
    glayout->addWidget(labelorig,2,1);
    glayout->addItem(hspacer2,1,3);

    int r = image.height();
    int c = image.width();
    vector<vector<double> > dummy(r,vector<double>(c,0.0));

    zero_remove(dummy,idwtop);

    int row = idwtop.size();
    int col = idwtop[0].size();

    QImage den_image(col,row,QImage::Format_RGB32);

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if ( idwtop[i][j] <= 0.0){
                idwtop[i][j] = 0.0;
            }

            unsigned int temp = (unsigned int) idwtop[i][j] ;

            QRgb value = qRgb(temp,temp,temp);
            den_image.setPixel(j,i,value);
        }
    }


    denoisedimage = den_image;

    QLabel *label2 = new QLabel(QString("DeNoised Image"));
    label2->setAlignment(Qt::AlignCenter);
    label2->setScaledContents(true);

    QPixmap pix2;

    pix2.convertFromImage(den_image);

    QLabel *labelappx = new QLabel(this);
    labelappx->setPixmap(pix2);
    labelappx->setScaledContents(true);


    QPushButton *denoisefullbutton = new QPushButton("View FullSize Image");
    connect(denoisefullbutton,SIGNAL(clicked()),this,SLOT(denoiseFULLVIEW()));

    glayout->addWidget(label2,1,2);
    glayout->addWidget(labelappx,2,2);

    glayout->addWidget(denoisefullbutton,3,2);
    glayout->addItem(spacer,4,1);
    glayout->update();

}

void MainWindow::dispDENOISE_RGB(vector<vector<double> > &idwtop_r,vector<vector<double> > &idwtop_g,
                                  vector<vector<double> > &idwtop_b) {

    QLayoutItem *child;
    while ((child = glayout->takeAt(0)) != 0)
    {
    delete child->widget();
    delete child;
    }

    vspacer = new QSpacerItem( 10, 10, QSizePolicy::Minimum,
    QSizePolicy::Expanding );
    hspacer1 = new QSpacerItem( 10, 10, QSizePolicy::Expanding,
    QSizePolicy::Minimum );
    hspacer2 = new QSpacerItem( 10, 10, QSizePolicy::Expanding,
    QSizePolicy::Minimum );
    spacer = new QSpacerItem( 10, 10, QSizePolicy::Minimum,
    QSizePolicy::Expanding );

    QLabel *label1 = new QLabel("Original Image");
    label1->setAlignment(Qt::AlignCenter);
    label1->setScaledContents(true);

    QPixmap pix;

    pix.convertFromImage(image);

    QLabel *labelorig = new QLabel(this);
    labelorig->setPixmap(pix);
    labelorig->setScaledContents(true);

    glayout->addItem(vspacer,0,1);
    glayout->addItem(hspacer1,1,0);
    glayout->addWidget(label1,1,1);
    glayout->addWidget(labelorig,2,1);
    glayout->addItem(hspacer2,1,3);

    int r = image.height();
    int c = image.width();

    vector<vector<double> > dummy(r,vector<double>(c,0.0));
    zero_remove(dummy,idwtop_r);
    zero_remove(dummy,idwtop_g);
    zero_remove(dummy,idwtop_b);



    int row = idwtop_r.size();
    int col = idwtop_r[0].size();
    QImage den_image(col,row,QImage::Format_RGB32);

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if ( idwtop_r[i][j] <= 0.0){
                idwtop_r[i][j] = 0.0;
            }
            if ( idwtop_g[i][j] <= 0.0){
                idwtop_g[i][j] = 0.0;
            }
            if ( idwtop_b[i][j] <= 0.0){
                idwtop_b[i][j] = 0.0;
            }

            unsigned int temp_r = (unsigned int) idwtop_r[i][j] ;
            unsigned int temp_g = (unsigned int) idwtop_g[i][j] ;
            unsigned int temp_b = (unsigned int) idwtop_b[i][j] ;


            QRgb value = qRgb(temp_r,temp_g,temp_b);
            den_image.setPixel(j,i,value);
        }
    }

    denoisedimage = den_image;

    QLabel *label2 = new QLabel(QString("Denoised Image"));
    label2->setAlignment(Qt::AlignCenter);
    label2->setScaledContents(true);

    QPixmap pix2;

    pix2.convertFromImage(den_image);

    QLabel *labelappx = new QLabel(this);
    labelappx->setPixmap(pix2);
    labelappx->setScaledContents(true);


    QPushButton *denoisefullbutton = new QPushButton("View FullSize Image");
    connect(denoisefullbutton,SIGNAL(clicked()),this,SLOT(denoiseFULLVIEW()));

    glayout->addWidget(label2,1,2);
    glayout->addWidget(labelappx,2,2);

    glayout->addWidget(denoisefullbutton,3,2);
    glayout->addItem(spacer,4,1);
    glayout->update();

}

void MainWindow::appxFULLVIEW() {
    QPixmap pix;

    pix.convertFromImage(approximatedimage);

    QLabel *labelappx = new QLabel(this);
    labelappx->setPixmap(pix);
    QScrollArea *area = new QScrollArea;

    area->setWidget(labelappx);
    area->setWindowTitle("Approximated Image");
    int height = approximatedimage.height();
    int width = approximatedimage.width();

    if ( (width  < 600) && (height < 600)) {
        area->resize(width,height);
    } else if ((width  < 600) && (height > 600)) {
        area->resize(width,600);
    } else if ((width  > 600) && (height < 600)) {
        area->resize(600,height);
    } else {
        area->resize(600,600);
    }

    area->show();
}

void MainWindow::denoiseFULLVIEW() {
    QPixmap pix;

    pix.convertFromImage(denoisedimage);

    QLabel *labelappx = new QLabel(this);
    labelappx->setPixmap(pix);
    QScrollArea *area = new QScrollArea;

    area->setWidget(labelappx);
    area->setWindowTitle("Denoised Image");
    int height = denoisedimage.height();
    int width = denoisedimage.width();

    if ( (width  < 600) && (height < 600)) {
        area->resize(width,height);
    } else if ((width  < 600) && (height > 600)) {
        area->resize(width,600);
    } else if ((width  > 600) && (height < 600)) {
        area->resize(600,height);
    } else {
        area->resize(600,600);
    }

    area->show();
}

void MainWindow::filtFULLVIEW() {
    QPixmap pix;

    pix.convertFromImage(filteredimage);

    QLabel *labelappx = new QLabel(this);
    labelappx->setPixmap(pix);
    QScrollArea *area = new QScrollArea;

    area->setWidget(labelappx);
    area->setWindowTitle("Filtered Image");
    int height = filteredimage.height();
    int width = filteredimage.width();

    if ( (width  < 600) && (height < 600)) {
        area->resize(width,height);
    } else if ((width  < 600) && (height > 600)) {
        area->resize(width,600);
    } else if ((width  > 600) && (height < 600)) {
        area->resize(600,height);
    } else {
        area->resize(600,600);
    }

    area->show();
}

void MainWindow::fftFULLVIEW() {
    QPixmap pix;

    pix.convertFromImage(fftimage);

    QLabel *labelappx = new QLabel(this);
    labelappx->setPixmap(pix);
    QScrollArea *area = new QScrollArea;

    area->setWidget(labelappx);
    area->setWindowTitle("Image FFT");
    int height = fftimage.height();
    int width = fftimage.width();

    if ( (width  < 600) && (height < 600)) {
        area->resize(width,height);
    } else if ((width  < 600) && (height > 600)) {
        area->resize(width,600);
    } else if ((width  > 600) && (height < 600)) {
        area->resize(600,height);
    } else {
        area->resize(600,600);
    }

    area->show();
}

void MainWindow::dwtFULLVIEW() {
    QPixmap pix;

    pix.convertFromImage(dwtimage);

    QLabel *labelappx = new QLabel(this);
    labelappx->setPixmap(pix);
    QScrollArea *area = new QScrollArea;

    area->setWidget(labelappx);
    area->setWindowTitle("DWT Output");
    int height = dwtimage.height();
    int width = dwtimage.width();

    if ( (width  < 600) && (height < 600)) {
        area->resize(width,height);
    } else if ((width  < 600) && (height > 600)) {
        area->resize(width,600);
    } else if ((width  > 600) && (height < 600)) {
        area->resize(600,height);
    } else {
        area->resize(600,600);
    }

    area->show();
}

void MainWindow::dwtEXPVIEW() {
    QPixmap pix2;

    pix2.convertFromImage(expimage);

    QLabel *labelappx = new QLabel(this);
    labelappx->setPixmap(pix2);
    QScrollArea *area2 = new QScrollArea;

    area2->setWidget(labelappx);
    area2->setWindowTitle("Expansive DWT Output");
    int height = expimage.height();
    int width = expimage.width();

    if ( (width  < 600) && (height < 600)) {
        area2->resize(width,height);
    } else if ((width  < 600) && (height > 600)) {
        area2->resize(width,600);
    } else if ((width  > 600) && (height < 600)) {
        area2->resize(600,height);
    } else {
        area2->resize(600,600);
    }

    area2->show();
}

void MainWindow::setSWTVAL(int value) {

    switch (value) {
    case 0:
        dwtimage = swtblur;
        break;
    case 1:
        dwtimage = swth;
        break;
    case 2:
        dwtimage = swtv;
        break;
    case 3:
        dwtimage = swtd;
        break;
    default:
        cout << "NULL";
    }

  dwtFULLVIEW();

}

void MainWindow::l2norm(const vector<double> &V, double &oup) {
    oup = 0.0;
    for (unsigned int i=0; i < V.size();i++) {
        oup+= pow(V[i],2.0);
    }
    oup = sqrt(oup);

}

void MainWindow::median(vector<double> &dwt_m,double &sigma) {
    vector<double> dwt_med;
    dwt_med = dwt_m;
    sort(dwt_med.begin(),dwt_med.end());
    unsigned int size = dwt_med.size();
    if (size  % 2 == 0)
    {
        sigma = (dwt_med[size / 2 - 1] + dwt_med[size / 2]) / 2;
    }
    else
    {
        sigma = dwt_med[size / 2];
    }
}

int MainWindow::sgn(double X) {
    if ( X >=0) {
        return 1;
    }
    else {
        return -1;
    }
}

void MainWindow::saveDWT2() {

    QString fileName = QFileDialog::getSaveFileName(this,QObject::tr("Save File As"),
                    "../",tr("Image Files (*.png *.bmp *.jpg *.tiff *.tif)"));

    string file2;
    file2 =fileName.toStdString();
    const char *filename = file2.c_str();

    dwtimage.save(filename,0,-1);


}

void MainWindow::saveAPPX2() {
    QString fileName = QFileDialog::getSaveFileName(this,QObject::tr("Save File As"),
                    "../",tr("Image Files (*.png *.bmp *.jpg *.tiff *.tif)"));

    string file2;
    file2 =fileName.toStdString();
    const char *filename = file2.c_str();

   approximatedimage.save(filename,0,-1);


}

void MainWindow::saveAPPXCOEF() {
    QString fileName = QFileDialog::getSaveFileName(this,QObject::tr("Save File As"),
                    "../",tr("Text File(*.txt)"));

    string file2;
    file2 =fileName.toStdString();
    const char *filename = file2.c_str();

        ofstream approximation_coef (filename);
        for (unsigned int i = 0; i < approximation_coefficients.size(); i++){
                        approximation_coef << approximation_coefficients[i] << endl;
                }


}

void MainWindow::saveDENOISE2() {
    QString fileName = QFileDialog::getSaveFileName(this,QObject::tr("Save File As"),
                    "../",tr("Image Files (*.png *.bmp *.jpg *.tiff *.tif)"));

    string file2;
    file2 =fileName.toStdString();
    const char *filename = file2.c_str();

    denoisedimage.save(filename,0,-1);


}

void MainWindow::saveFILTER2() {
    QString fileName = QFileDialog::getSaveFileName(this,QObject::tr("Save File As"),
                    "../",tr("Image Files (*.png *.bmp *.jpg *.tiff *.tif)"));

    string file2;
    file2 =fileName.toStdString();
    const char *filename = file2.c_str();

    filteredimage.save(filename,0,-1);


}

void MainWindow::saveDENOISECOEF() {
    QString fileName = QFileDialog::getSaveFileName(this, QObject::tr("Save File As"),
                                                    "../", QObject::tr("Text (*.txt)"));
    string file2;
    file2 =fileName.toStdString();
    const char *filename = file2.c_str();

        ofstream denoising_coef (filename);
        for (unsigned int i = 0; i < denoising_coefficients.size(); i++){
                        denoising_coef << denoising_coefficients[i] << endl;
                }


}

void MainWindow::ORTHplot(vector<double> &phi, vector<double> &psi) {
    QLayoutItem *child;
    while ((child = glayout->takeAt(0)) != 0)
    {
    delete child->widget();
    delete child;
    }
    vector<double> lp1,hp1,lp2,hp2;
    filtcoef(nm,lp1,hp1,lp2,hp2);
    double sig_min = 0;
    double sig_max = (double) lp1.size() - 1.0;
    double temp = 1.0/4.0;
    transform(phi.begin(), phi.end(), phi.begin(),
                   bind1st(multiplies<double>(),temp));
    transform(psi.begin(), psi.end(), psi.begin(),
                   bind1st(multiplies<double>(),temp));
    QLabel *l1 = new QLabel("Scaling Function");
    l1->setAlignment(Qt::AlignCenter);
    glayout->addWidget(l1,0,0);
    lineplotmod2(phi,0,1,sig_min,sig_max);

    QLabel *l2 = new QLabel(QString("Wavelet Function"));
    l2->setAlignment(Qt::AlignCenter);
    glayout->addWidget(l2,2,0);
    lineplotmod2(psi,0,3,sig_min,sig_max);
}

void MainWindow::BIORTHplot(vector<double> &phi1, vector<double> &psi1,vector<double> &phi2,
                            vector<double> &psi2) {
    QLayoutItem *child;
    while ((child = glayout->takeAt(0)) != 0)
    {
    delete child->widget();
    delete child;
    }
    vector<double> lp1,hp1,lp2,hp2;
    filtcoef(nm,lp1,hp1,lp2,hp2);
    double sig_min = 0;
    double sig_max = (double) lp1.size() - 1.0;
    double temp = 1.0/4.0;
    transform(phi1.begin(), phi1.end(), phi1.begin(),
                   bind1st(multiplies<double>(),temp));
    transform(psi1.begin(), psi1.end(), psi1.begin(),
                   bind1st(multiplies<double>(),temp));
    transform(phi2.begin(), phi2.end(), phi2.begin(),
                   bind1st(multiplies<double>(),temp));
    transform(psi2.begin(), psi2.end(), psi2.begin(),
                   bind1st(multiplies<double>(),temp));
    QLabel *l1 = new QLabel("Decomposition Scaling Function");
    l1->setAlignment(Qt::AlignCenter);
    glayout->addWidget(l1,0,0);
    lineplotmod2(phi1,2,1,sig_min,sig_max);

    QLabel *l2 = new QLabel(QString("Decomposition Wavelet Function"));
    l2->setAlignment(Qt::AlignCenter);
    glayout->addWidget(l2,2,0);
    lineplotmod2(psi1,2,3,sig_min,sig_max);

    QLabel *l3 = new QLabel("Reconstruction Scaling Function");
    l3->setAlignment(Qt::AlignCenter);
    glayout->addWidget(l3,4,0);
    lineplotmod2(phi2,2,5,sig_min,sig_max);

    QLabel *l4 = new QLabel(QString("Reconstruction Wavelet Function"));
    l4->setAlignment(Qt::AlignCenter);
    glayout->addWidget(l4,6,0);
    lineplotmod2(psi2,2,7,sig_min,sig_max);
}

void* MainWindow::showmsg() {
    QMessageBox::critical(this,tr("Error!"),tr("No Signal loaded"));
    exit(1);
}

void MainWindow::SIGplot(vector<double> &sig){
    QLayoutItem *child;
    while ((child = glayout->takeAt(0)) != 0)
    {
    delete child->widget();
    delete child;
    }
    unsigned int temp2 = sig.size();
    scene = new QGraphicsScene();
    view = new QGraphicsView();
    QPointF points[temp2];
    QPolygonF poly;
    qreal sc = (qreal) view->width()/sig.size();
    double max,min;
    maxval(sig,max);
    minval(sig,min);
    double ht;
    double ht1 = max - min;
    ht = (double)view->height()/ ht1;


    for (unsigned int i=0; i < sig.size(); i++) {
       double y =-1 *  sig[i];
        points[i]=QPointF((double)i*sc,y*ht);
        poly << points[i];
    }
    QPainterPath path;
    path.addPolygon(poly);
    QPen pen(Qt::white, 1, Qt::SolidLine);

    scene->addPath(path, pen);
    QFont font;
    font.setPixelSize(20);
    font.setBold(false);
    font.setFamily("Times");

//     QPen pen2(Qt::red, 3, Qt::SolidLine);
    /*
    QGraphicsSimpleTextItem * io = scene->addSimpleText("Signal Display");
    io->setPos(70,-100);
    io->setFont(font);
    io->setBrush(QColor(255, 255, 255, 127));
*/
    scene->setBackgroundBrush(QColor(72,118,255));
    view->setScene(scene);

    view->viewport()->installEventFilter(this);
    view->viewport()->setMouseTracking(true);

    glayout->addWidget(view);
   // view->show();

}

void MainWindow::SWTplot(vector<double> &dwt_output,vector<double> &orig, int J, int temp2) {
    QLayoutItem *child;
    while ((child = glayout->takeAt(0)) != 0)
    {
    delete child->widget();
    delete child;
    }
    QLabel *l1 = new QLabel("Original Signal");
    l1->setAlignment(Qt::AlignCenter);
    glayout->addWidget(l1);
    lineplotmod(orig,J);

    for (int i=0; i < J+1; i++) {

        vector<double> sig;
        if (i ==0) {
            QLabel *l1 = new QLabel();
            QString str=QString("Approximation Coefficients at Level J = %1").arg(J-i,0,10);
            l1->setText(str);
            l1->setAlignment(Qt::AlignCenter);
            glayout->addWidget(l1);
        sig.assign(dwt_output.begin(),dwt_output.begin()+ temp2);

    } else {
        QLabel *l1 = new QLabel();
        QString str=QString("Detail Coefficients at Level J = %1").arg(J-i+1,0,10);
        l1->setText(str);
        l1->setAlignment(Qt::AlignCenter);
        glayout->addWidget(l1);
        sig.assign(dwt_output.begin()+ i * temp2 ,dwt_output.begin()+(i+1)*temp2);
    }
        lineplotmod(sig,J);

    }

}

void MainWindow::DWT_SYMplot(vector<double> &dwt_output,vector<double> &orig,  int J, vector<int> &length ) {
    QLayoutItem *child;
    while ((child = glayout->takeAt(0)) != 0)
    {
    delete child->widget();
    delete child;
    }
    QLabel *l1 = new QLabel("Original Signal");
    l1->setAlignment(Qt::AlignCenter);
    glayout->addWidget(l1);
    lineplotmod(orig,J);
   int temp = 0;
    for (int i=0; i < J+1; i++) {

        vector<double> sig;
       if (i == 0) {
        QLabel *l1 = new QLabel();
        QString str=QString("Approximation Coefficients at Level J = %1").arg(J-i,0,10);
        l1->setText(str);
        l1->setAlignment(Qt::AlignCenter);
        glayout->addWidget(l1);
        sig.assign(dwt_output.begin(),dwt_output.begin()+length[0]);

        } else {
            QLabel *l1 = new QLabel();
            QString str=QString("Detail Coefficients at Level J = %1").arg(J-i+1,0,10);
            l1->setText(str);
            l1->setAlignment(Qt::AlignCenter);
            glayout->addWidget(l1);
        sig.assign(dwt_output.begin()+ temp,dwt_output.begin()+temp+length[i]);
    }
        lineplotmod(sig,J);
        temp += length[i];

    }

}

void MainWindow::DWT_PERplot(vector<double> &dwt_output,vector<double> &orig,  int J) {
    QLayoutItem *child;
    while ((child = glayout->takeAt(0)) != 0)
    {
    delete child->widget();
    delete child;
    }
    QLabel *l1 = new QLabel("Original Signal");
    l1->setAlignment(Qt::AlignCenter);
    glayout->addWidget(l1);
    lineplotmod(orig,J);
    unsigned int app_len = dwt_output.size() / int(pow(2.0,J));

    for (int i=0; i<J+1;i++) {
        vector<double> sig;

        if ( i==0 ) {
            QLabel *l1 = new QLabel();
            QString str=QString("Approximation Coefficients at Level J = %1").arg(J-i,0,10);
            l1->setText(str);
            l1->setAlignment(Qt::AlignCenter);
            glayout->addWidget(l1);
            sig.assign(dwt_output.begin(),dwt_output.begin()+app_len);
        } else {
            QLabel *l1 = new QLabel();
            QString str=QString("Detail Coefficients at Level J = %1").arg(J-i+1,0,10);
            l1->setText(str);
            l1->setAlignment(Qt::AlignCenter);
            glayout->addWidget(l1);
            sig.assign(dwt_output.begin()+app_len, dwt_output.begin()+ 2* app_len);
            app_len = 2 * app_len;

        }
        lineplotmod(sig,J);
    }

}

void MainWindow::APPXplot(vector<double> &signal,vector<double> &output) {
    QLayoutItem *child;
    while ((child = glayout->takeAt(0)) != 0)
    {
    delete child->widget();
    delete child;
    }
    QLabel *l1 = new QLabel("Original Signal");
    l1->setAlignment(Qt::AlignCenter);
    glayout->addWidget(l1);
    lineplotmod(signal,0);

    QLabel *l2 = new QLabel(QString("Approximated Signal Using only %1 \% Coefficients").arg(n_coef));
    l2->setAlignment(Qt::AlignCenter);
    glayout->addWidget(l2);
    lineplotmod(output,0);

}

void MainWindow::DENOISEplot(vector<double> &signal,vector<double> &output) {
    QLayoutItem *child;
    while ((child = glayout->takeAt(0)) != 0)
    {
    delete child->widget();
    delete child;
    }
    QLabel *l1 = new QLabel("Original Signal");
    l1->setAlignment(Qt::AlignCenter);
    glayout->addWidget(l1);
    lineplotmod(signal,0);

    QLabel *l2 = new QLabel(QString("DeNoised Signal"));
    l2->setAlignment(Qt::AlignCenter);
    glayout->addWidget(l2);
    lineplotmod(output,0);

}

void MainWindow::lineplot(vector<double> &sig, int J_num ,int pl_num, double sig_min, double sig_max){

    int temp2 = sig.size();
    QPen pen(QColor(72,118,255), 1, Qt::SolidLine);
    QVector<double> xdata;
    QVector<double> qsig = QVector<double>::fromStdVector(sig);


    for (double i =sig_min; i <= sig_max; i+=(sig_max-sig_min)/(double)(temp2-1)){
        xdata.append((double) i);
    }
    QwtPlot *temp_plt = new QwtPlot(this);
    QwtPlotCurve *temp_curve = new QwtPlotCurve(QString("curve"));

    temp_curve->setSamples(xdata,qsig);
    temp_curve->setPen(pen);
    temp_curve->attach(temp_plt);
    temp_plt->setCanvasBackground(Qt::black);
   // temp_plt->setAxisScale(QwtPlot::xBottom,sig_min,sig_max,0);

    QwtPlotZoomer *zoomer = new QwtPlotZoomer(temp_plt->canvas());
    QwtPlotPanner *panner = new QwtPlotPanner(temp_plt->canvas());
    zoomer->setMousePattern(QwtEventPattern::MouseSelect2,
        Qt::RightButton, Qt::ControlModifier);
    zoomer->setMousePattern(QwtEventPattern::MouseSelect3,
        Qt::RightButton);
    temp_plt->replot();
    panner->setAxisEnabled(QwtPlot::yRight, false);
    panner->setMouseButton(Qt::MidButton);
    const QColor c(QColor(72,118,255));
    zoomer->setRubberBandPen(c);
    zoomer->setTrackerPen(c);
    glayout->addWidget(temp_plt,pl_num,0);
    glayout->update();
    xdata.clear();

}

void MainWindow::lineplotmod2(vector<double> &sig, int J_num, int pl_num,double sig_min, double sig_max){

    int temp2 = sig.size();
    QPen pen(QColor(72,118,255), 1, Qt::SolidLine);
    QVector<double> xdata;
    QVector<double> qsig = QVector<double>::fromStdVector(sig);


    for (double i =sig_min; i <= sig_max; i+=(sig_max-sig_min)/(double)(temp2-1)){
        xdata.append((double) i);
    }
    QwtPlot *temp_plt = new QwtPlot(this);
    QwtPlotCurve *temp_curve = new QwtPlotCurve(QString("curve"));

    temp_curve->setSamples(xdata,qsig);
    temp_curve->setPen(pen);
    temp_curve->attach(temp_plt);
    temp_plt->setCanvasBackground(Qt::black);

    QwtPlotZoomer *zoomer = new QwtPlotZoomer(temp_plt->canvas());
    QwtPlotPanner *panner = new QwtPlotPanner(temp_plt->canvas());
    zoomer->setMousePattern(QwtEventPattern::MouseSelect2,
        Qt::RightButton, Qt::ControlModifier);
    zoomer->setMousePattern(QwtEventPattern::MouseSelect3,
        Qt::RightButton);
    temp_plt->replot();
    panner->setAxisEnabled(QwtPlot::yRight, false);
    panner->setMouseButton(Qt::MidButton);
    const QColor c(QColor(72,118,255));
    zoomer->setRubberBandPen(c);
    zoomer->setTrackerPen(c);

    glayout->addWidget(temp_plt,pl_num,0);
    glayout->update();
}

void MainWindow::lineplotmod(vector<double> &sig, int J_num){

    int temp2 = sig.size();
    scene = new QGraphicsScene();
    view = new QGraphicsView();
    QPointF points[temp2];
    QPolygonF poly;

    QFont font;
    font.setPixelSize(10);
    font.setBold(false);
    font.setFamily("Times");

    /*
    QGraphicsSimpleTextItem * io = scene->addSimpleText("Signal Display");
    io->setPos(70,-100);
    io->setFont(font);
    io->setBrush(QColor(255, 255, 255, 127)); */

    scene->setBackgroundBrush(QColor(72,118,255));
    qreal sc = (qreal) view->width()/sig.size();
    double max,min;
    maxval(sig,max);
    minval(sig,min);
    double ht;
    double ht1 = max - min;
    if (max == min) {
        ht = (double)view->height()/ max;
    } else {
     ht = (double)view->height()/ ht1;
    }
    ht = ht / (J_num+2);

    QRectF rect = view->contentsRect();

    QPen pen2(QColor(25,63,178), 0, Qt::SolidLine);
    if ( (max > 0) & (min < 0)) {
    scene->addLine(rect.left() ,0.0,rect.right(),0.0,pen2);
}
    scene->addLine(0.0 ,max * ht ,0.0,min * ht,pen2);

    QPen pen3(QColor(25,63,178), 0, Qt::DotLine);
    qreal gr_y= (rect.right() - rect.left()) / 8.0;

    unsigned int num_y =8;
    QFont newFont("Times",(int) 10);
    if ( J_num <= 1) {
     newFont.setPixelSize(10);
 }
    if ( (J_num > 1) & (J_num < 3)) {
     newFont.setPixelSize(9);
 }
    if ( (J_num >= 3) & (J_num < 5)) {
        newFont.setPixelSize(8);
    }
    if ( (J_num >= 5) & (J_num < 8)) {
        newFont.setPixelSize(8);
    }
    if (J_num >= 8) {
        newFont.setPixelSize(7);

    }

    for (unsigned int iter =0; iter < num_y; iter++) {
        scene->addLine(gr_y *(iter+1) ,max * ht ,gr_y *(iter+1) ,min * ht,pen3);
        QString disp;
        disp = disp.setNum(temp2 - temp2 *(qreal) iter/(qreal) num_y);
        QGraphicsTextItem *text = scene->addText(disp, newFont);
        text->setPos((temp2 - temp2 *(qreal) iter/(qreal) num_y) * sc,min*ht);
        text->scale(1,-1);

    }
    int num_x=5;
    for (int iter = 0; iter <= num_x; iter++) {
        scene->addLine(rect.left() ,max*ht - ht *ht1 * iter/num_x,rect.right(),max*ht - ht*ht1 * iter/num_x,pen3);
        QString disp;
        disp = disp.setNum(max - ht1 * iter /num_x);
        QGraphicsTextItem *text = scene->addText(disp, newFont);
        text->setPos(rect.left() ,max*ht - ht *ht1 * iter/num_x);
        text->scale(1,-1);
    }


    for (unsigned int i=0; i < sig.size(); i++) {
       double y =sig[i];
        points[i]=QPointF((double)i * sc,y *ht );
        poly << points[i];
    }
    QPainterPath path;
    path.addPolygon(poly);
    QPen pen(Qt::white, 1, Qt::SolidLine);

    scene->addPath(path, pen);



    view->setScene(scene);
    view->scale(1,-1);


    view->viewport()->installEventFilter(this);
    view->viewport()->setMouseTracking(true);


    vlayout2->addWidget(view);
    vlayout2->update();
}


void MainWindow::pointplot2(vector<double> &filt, int J_num, int pl_num) {
    int temp2 = filt.size();

    QPen pen(QColor(72,118,255), 1, Qt::SolidLine);
    QBrush brush(Qt::white);

    QVector<double> xdata;
    QVector<double> qsig = QVector<double>::fromStdVector(filt);


    for (int i =0; i < temp2; i++){
        xdata.append((double) i);
    }
    QwtPlot *temp_plt = new QwtPlot(this);
    QSize elpse_size(6,6);

    QwtSymbol *elpse = new QwtSymbol(QwtSymbol::Ellipse,brush,pen, elpse_size);

    QwtPlotCurve *temp_curve = new QwtPlotCurve();
    temp_curve->setStyle(QwtPlotCurve::Sticks);
    temp_curve->setSamples(xdata,qsig);
    temp_curve->setSymbol(elpse);
    temp_curve->setPen(pen);

    temp_curve->attach(temp_plt);
    temp_plt->setCanvasBackground(Qt::black);

    QwtPlotZoomer *zoomer = new QwtPlotZoomer(temp_plt->canvas());
    QwtPlotPanner *panner = new QwtPlotPanner(temp_plt->canvas());
    zoomer->setMousePattern(QwtEventPattern::MouseSelect2,
        Qt::RightButton, Qt::ControlModifier);
    zoomer->setMousePattern(QwtEventPattern::MouseSelect3,
        Qt::RightButton);
    temp_plt->replot();
    panner->setAxisEnabled(QwtPlot::yRight, false);
    panner->setMouseButton(Qt::MidButton);
    const QColor c(QColor(72,118,255));
    zoomer->setRubberBandPen(c);
    zoomer->setTrackerPen(c);
    glayout->addWidget(temp_plt,pl_num,0);
    glayout->update();
    xdata.clear();


}

void* MainWindow::maxval(const vector<double> &arr, double &max){
        max = -10000;
        for (unsigned int i =0; i < arr.size(); i++) {
                if (max <= arr[i]){
                        max = arr[i];
                }

        }
        return 0;
}

void* MainWindow::maxval2(vector<vector<double> > &arr, double &max){
        max = -10000;
        for (unsigned int i =0; i < arr.size(); i++) {
                for (unsigned int j =0; j < arr[0].size(); j++) {
                        if (max <= arr[i][j]){
                                max = arr[i][j];
                        }
                }
        }
        return 0;
}

void* MainWindow::minval2(vector<vector<double> > &arr, double &min){
        min = 10000;
        for (unsigned int i =0; i < arr.size(); i++) {
                for (unsigned int j =0; j < arr[0].size(); j++) {
                        if (min >= arr[i][j]){
                                min = arr[i][j];
                        }
                }
        }
        return 0;
}

void* MainWindow::minval(const vector<double> &arr, double &min){
        min = 10000;
        for (unsigned int i =0; i < arr.size(); i++) {
                if (min >= arr[i]){
                        min = arr[i];
                }

        }
        return 0;
}


void MainWindow::minindex(const vector<double> &arr, int &minind){
        double min;
        min = 10000000.0;
        for (unsigned int i =0; i < arr.size(); i++) {
                if (min >= arr[i]){
                        min = arr[i];
                        minind = i;
                }

        }
}

void MainWindow::createStatusBar()
 {
     statusBar()->showMessage(tr("Status Bar"));
 }


bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
  if (event->type() == QEvent::MouseMove)
  {
    QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
    QPointF pos = view->mapToScene(mouseEvent->pos());
    statusBar()->showMessage(QString("Mouse move (%1,%2)").arg(pos.x()).arg(pos.y()));
  }
  return false;
}

void* MainWindow::freq_one(vector<double> &sig, vector<double> &freq_resp) {
         unsigned int K = sig.size();
            unsigned int N = (unsigned int) pow(2.0,ceil(log10(K)/log10(2)));
            if ( N < 64) {
                N = 64;
            }
            vector<complex<double> > fft_oup;
            for (unsigned int i =0; i < sig.size(); i++) {
                 double temp = sig[i];
                 fft_oup.push_back(complex<double>(temp,0));
            }
            fft(fft_oup,1,N);
            cout << "OK" << endl;
            for (unsigned int i = 0; i < N/2 - 1; i++){
                double temp = abs(fft_oup[i]);
                freq_resp.push_back(temp);
            }


            return 0;
}



