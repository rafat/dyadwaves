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
static int n_coef = 25;
static vector<double> original_signal;
static string mode_appx = "dwt_per";
static string mode_denoise = "swt";
static string nm_dn = "db1";
static int J_dn = 1;
static string dn_thresh = "soft";
static string dn_method = "visushrink";
static vector<double> dwt_coefficients;
static vector<double> approximated_signal;
static vector<double> approximation_coefficients;
static vector<double> denoised_signal;
static vector<double> denoising_coefficients;
static int exec_time;
static vector<int> sym_coeff_length;
static vector<int> per_coeff_length;

static QVector<QwtPlot *> plt;
static QVector<QwtPlotCurve *> plt_curve;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    createActions();
    createMenus();
    createToolBars();
    DWTdialog();
    DISPdialog();
    APPXdialog();
    DENOISEdialog();
    OUTPUTconsole();
    defaultSIG();

    dwtdial = new QWidget();
    dwtdial->setLayout(vlayout);

    QWidget *mw = new QWidget(this);

    scene = new QGraphicsScene();

  //  QGraphicsEllipseItem *ellipse= new QGraphicsEllipseItem(-10,-10,120,50);
    QPen pen(QColor(73,118,255), 1, Qt::SolidLine);
    QFont font;
    font.setPixelSize(30);
    font.setBold(false);
    font.setFamily("Georgia");

//    QGraphicsSimpleTextItem * io = scene->addSimpleText("WAVELET GUI");
//    io->setFont(font);
//    io->setBrush(QColor(73,118,255));

    scene->setBackgroundBrush(Qt::black);
 //   scene->installEventFilter(this);
    setMouseTracking(TRUE);
    createStatusBar();

    view = new QGraphicsView();
    view->setScene(scene);


    QImage sig_img;
    sig_img.load(":/images/sig.bmp");

    QPixmap pix_sig;
    pix_sig.convertFromImage(sig_img);
    QGraphicsPixmapItem* item_sig = scene->addPixmap(pix_sig);
    item_sig->setPos(40,0);

    QImage l1_img;
    l1_img.load(":/images/l1.bmp");

    QPixmap pix_l1;
    pix_l1.convertFromImage(l1_img);
    QGraphicsPixmapItem* item_l1 = scene->addPixmap(pix_l1);
    item_l1->setPos(40,150);

    scene->addLine(165,56 ,165,150,pen);

    QImage h1_img;
    h1_img.load(":/images/h1.bmp");

    QPixmap pix_h1;
    pix_h1.convertFromImage(h1_img);
    QGraphicsPixmapItem* item_h1 = scene->addPixmap(pix_h1);
    item_h1->setPos(340,150);

    scene->addLine(165,56 ,415,150,pen);

    QImage l2_img;
    l2_img.load(":/images/l2.bmp");

    QPixmap pix_l2;
    pix_l2.convertFromImage(l2_img);
    QGraphicsPixmapItem* item_l2 = scene->addPixmap(pix_l2);
    item_l2->setPos(40,300);

    scene->addLine(165,206,165,300,pen);


    QImage h2_img;
    h2_img.load(":/images/h2.bmp");

    QPixmap pix_h2;
    pix_h2.convertFromImage(h2_img);
    QGraphicsPixmapItem* item_h2 = scene->addPixmap(pix_h2);
    item_h2->setPos(340,300);
    scene->addLine(165,206 ,415,300,pen);


 //   view->viewport()->installEventFilter(this);
 //   view->viewport()->setMouseTracking(true);

    vlayout2 = new QVBoxLayout;
    vlayout2->addWidget(view);

//    QImage img("lena512.bmp");
//    QPixmap pix;
//    pix.convertFromImage(img);

//    QLabel *labelpix = new QLabel(this);
//    labelpix->setPixmap(pix);

//    vlayout2->addWidget(labelpix);

    denoisedial = new QWidget();
    denoisedial->setLayout(vlayout3);

    mwlay = new QHBoxLayout;
    mw->setLayout(mwlay);
    mwlay->addWidget(dwtdial);
    mwlay->addLayout(vlayout2);
    mwlay->addWidget(denoisedial);

    setCentralWidget(mw);

}

void MainWindow::createActions() {
  exitAct =new QAction(tr("E&xit"),this);
  exitAct->setShortcut(tr("Ctrl+Q"));
  connect(exitAct,SIGNAL(triggered()),this,SLOT(close()));

  openAct= new QAction(tr("O&pen"),this);
  openAct->setShortcut(tr("Ctrl+O"));
  connect(openAct,SIGNAL(triggered()),this,SLOT(openFile()));

  aboutAct = new QAction(tr("A&bout"),this);
  connect(aboutAct,SIGNAL(triggered()),this,SLOT(about()));

  regular2Act= new QAction(tr("Piecewise Regular Signal- 2048"),this);
  connect(regular2Act,SIGNAL(triggered()),this,SLOT(loadreg2()));

  regularAct= new QAction(tr("Piecewise Regular Signal- 256"),this);
  connect(regularAct,SIGNAL(triggered()),this,SLOT(loadreg()));

  polyAct= new QAction(tr("Piecewise Polynomial Signal- 1024"),this);
  connect(polyAct,SIGNAL(triggered()),this,SLOT(loadpoly()));

  heavisineAct = new QAction(tr("Heavisine Signal- 512"),this);
  connect(heavisineAct,SIGNAL(triggered()),this,SLOT(loadheavisine()));

  noisyheavisineAct = new QAction(tr("Noisy Heavisine Signal- 8 dB"),this);
  connect(noisyheavisineAct,SIGNAL(triggered()),this,SLOT(loadnoisyheavisine()));

  noisybumpsAct = new QAction(tr("Noisy Bumps Signal- 20 dB"),this);
  connect(noisybumpsAct,SIGNAL(triggered()),this,SLOT(loadnoisybumps()));

  ecgAct = new QAction(tr("ECG Signal- 5400"),this);
  connect(ecgAct,SIGNAL(triggered()),this,SLOT(loadecg()));

  appxAct= new QAction(tr("Signal Approximation"), this);
//  connect(appxAct,SIGNAL(triggered()),this,SLOT())

}

void MainWindow::createMenus(){
fileMenu=menuBar()->addMenu(tr("&File"));
fileMenu->addAction(openAct);
fileMenu->addAction(exitAct);

signalMenu=menuBar()->addMenu(tr("&Test Signals"));
signalMenu->addAction(regular2Act);
signalMenu->addAction(regularAct);
signalMenu->addAction(polyAct);
signalMenu->addAction(heavisineAct);
signalMenu->addAction(noisyheavisineAct);
signalMenu->addAction(noisybumpsAct);
signalMenu->addAction(ecgAct);

//appMenu=menuBar()->addMenu(tr("&Applications"));
//appMenu->addAction(appxAct);

helpMenu=menuBar()->addMenu(tr("&Help"));
helpMenu->addAction(aboutAct);

}

void MainWindow::createToolBars() {
    fileToolBar = addToolBar(tr("File"));
}

void MainWindow::openFile() {

    QString filename = QFileDialog::getOpenFileName(0,
                     QObject::tr("Open Signal File"), "../", QObject::tr("Text Files (*.txt)"));

    if (!filename.isEmpty())
        loadFile(filename);
         setCurrentFile(filename);
}

void MainWindow::loadreg2() {
    QFile::copy(":/signal/pieceregular2048.txt","regular2048.txt");
    QFileInfo dir("regular2048.txt");
    QString filename = dir.absoluteFilePath();

    loadFile(filename);
    setCurrentFile(filename);
}

void MainWindow::loadreg() {
    QFile::copy(":/signal/pieceregular.txt","regular.txt");
    QFileInfo dir("regular.txt");
    QString filename = dir.absoluteFilePath();

    loadFile(filename);
    setCurrentFile(filename);
}

void MainWindow::loadpoly() {
    QFile::copy(":/signal/piecepoly.txt","poly.txt");
    QFileInfo dir2("poly.txt");
    QString filename = dir2.absoluteFilePath();

    loadFile(filename);
    setCurrentFile(filename);
}

void MainWindow::loadheavisine() {
    QFile::copy(":/signal/heavisine.txt","heavisine.txt");
    QFileInfo dir3("heavisine.txt");
    QString filename = dir3.absoluteFilePath();

    loadFile(filename);
    setCurrentFile(filename);
}

void MainWindow::loadnoisyheavisine() {
    QFile::copy(":/signal/noisyheavisine.txt","noisyheavisine.txt");
    QFileInfo dir4("noisyheavisine.txt");
    QString filename = dir4.absoluteFilePath();

    loadFile(filename);
    setCurrentFile(filename);
}

void MainWindow::defaultSIG() {

    QFile::copy(":/signal/noisyheavisine.txt","defaultsig.txt");
    QFileInfo dir44("defaultsig.txt");
    QString filename = dir44.absoluteFilePath();

    original_signal.clear();
    string inp2;
    inp2 = filename.toStdString();
    char *inp = (char*)inp2.c_str();

    ifstream sig_inp(inp);
 if ( !sig_inp.good()){
        cout << "The File doesn't exist"<< endl;
 }
    while (sig_inp) {
        double temp;
        sig_inp >> temp;
        original_signal.push_back(temp);
    }
    original_signal.pop_back();
    vector<double> sig;
    sig = original_signal;
    setCurrentFile(filename);

}

void MainWindow::loadnoisybumps() {
    QFile::copy(":/signal/noisybumps.txt","noisybumps.txt");
    QFileInfo dir5("noisybumps.txt");
    QString filename = dir5.absoluteFilePath();

    loadFile(filename);
    setCurrentFile(filename);
}

void MainWindow::loadecg() {
    QFile::copy(":/signal/ecg.txt","ecg.txt");
    QFileInfo dir6("ecg.txt");
    QString filename = dir6.absoluteFilePath();

    loadFile(filename);
    setCurrentFile(filename);
}

void MainWindow::about() {
    QMessageBox msgBox;
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setText("DyadWaves : Wavelet Software");
    msgBox.setInformativeText("(c) 2011,    Rafat Hussain");
    msgBox.exec();
}


void MainWindow::loadFile(const QString &fileName){
    original_signal.clear();
    string inp2;
    inp2 = fileName.toStdString();
    char *inp = (char*)inp2.c_str();
  /*  char *inp=new char[inp2.size()+1];
    inp[inp2.size()]=0;
    memcpy(inp,inp2.c_str(),inp2.size());*/

   // vector<double> sig;
    ifstream sig_inp(inp);
 if ( !sig_inp.good()){
        cout << "The File doesn't exist"<< endl;
 }
    while (sig_inp) {
        double temp;
        sig_inp >> temp;
        original_signal.push_back(temp);
    }
    original_signal.pop_back();
    vector<double> sig;
    sig = original_signal;
  //  qwtlineplot(sig,1,0);
    SIGplot(sig);

  //  cout << sig.size() << endl;
  //  system("pause");
  //  computeDWT(sig);
}

void MainWindow::setCurrentFile(const QString &filename){
    curFile = filename;
}

void MainWindow::DWTdialog() {
    QLabel *dwthead = new QLabel("DWT Dashboard");
    dwthead->setStyleSheet("QLabel {background-color : black; color : #4876FF; font : bold 12px}");
    dwthead->setAlignment(Qt::AlignCenter);
    QHBoxLayout *hdwthead =  new QHBoxLayout;
    hdwthead->addWidget(dwthead);

    QHBoxLayout *hlayout = new QHBoxLayout;
    wave = new QComboBox();
    QLabel *label = new QLabel("Choose Wavelet Family");
    QPushButton *inpbutton = new QPushButton(QObject::tr("Load Signal"));
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
    QObject::connect(inpbutton, SIGNAL(clicked()),this, SLOT(openFile()));
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
    modes << "dwt_sym" << "swt" << "dwt_per" ;

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


    dwtbutton = new QPushButton(QObject::tr("Perform DWT"));
//    idwtbutton = new QPushButton(QObject::tr("Perform IDWT"));
//    idwtbutton->setEnabled(false);
    idwtbutton = new QCheckBox("Perform IDWT");
    idwtbutton->setChecked(false);

    QObject::connect(dwtbutton, SIGNAL(clicked()),this, SLOT(computeDWT()));
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
    vlayout->addWidget(idwtbutton);
    vlayout->addWidget(dwtbutton);
    vlayout->addWidget(reportbutton);

}
void MainWindow::APPXdialog(){
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

    vlayout->addLayout(happxhead);
    vlayout->addLayout(hdwtappx);
    vlayout->addLayout(happxlabel);
 //   vlayout->addWidget(appxinp);

    appxbutton = new QPushButton(QObject::tr("Approximate Signal"));
    vlayout->addWidget(appxbutton);

    QObject::connect(appxinp, SIGNAL(activated(int)),this, SLOT(setAppxCoef(int)));
    QObject::connect(appxbutton, SIGNAL(clicked()),this, SLOT(approximateSig()));

}

void MainWindow::DISPdialog() {
    QLabel *disphead = new QLabel("Display Dashboard");
    disphead->setStyleSheet("QLabel {background-color : black; color : #4876FF; font : bold 12px}");
    disphead->setAlignment(Qt::AlignCenter);



    filtdispbutton = new QPushButton(QObject::tr("Display Wavelet Filters"));
    wavedispbutton = new QPushButton(QObject::tr("Display Wavelets"));
    freqdispbutton = new QPushButton(QObject::tr("Signal Frequency Response"));
    filtfreqbutton = new QPushButton(QObject::tr("Filters Frequency Response"));

    QObject::connect(filtdispbutton, SIGNAL(clicked()),this, SLOT(filtdisp()));
    QObject::connect(wavedispbutton, SIGNAL(clicked()),this, SLOT(wavedisp()));
    QObject::connect(freqdispbutton, SIGNAL(clicked()),this, SLOT(freqdisp()));
    QObject::connect(filtfreqbutton, SIGNAL(clicked()),this, SLOT(filtfreq()));

    vlayout->addWidget(disphead);
    vlayout->addWidget(filtdispbutton);
    vlayout->addWidget(wavedispbutton);
    vlayout->addWidget(freqdispbutton);
    vlayout->addWidget(filtfreqbutton);

}

void MainWindow::DENOISEdialog() {
    vlayout3 = new QVBoxLayout;
    QLabel *denoisehead = new QLabel("Wavelet DeNoising");
    denoisehead->setStyleSheet("QLabel {background-color : black; color : #4876FF;  font : bold 12px}");
    denoisehead->setAlignment(Qt::AlignCenter);

    QHBoxLayout *hlayoutdnmethod = new QHBoxLayout;

    QStringList denoisemethod;
    denoisemethod << "visushrink" << "sureshrink";

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
    denoisemodes << "swt" << "dwt_per" << "dwt_sym";

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

    denoisebutton = new QPushButton(QObject::tr("DeNoise Signal"));
    QObject::connect(denoisebutton, SIGNAL(clicked()),this, SLOT(signalDENOISE()));

    vlayout3->addWidget(denoisehead);
    vlayout3->addLayout(hlayoutdnmethod);
    vlayout3->addLayout(hlayoutdnthresh);
    vlayout3->addLayout(hlayoutdn1);
    vlayout3->addLayout(hlayoutdn2);
    vlayout3->addLayout(hlayoutdn3);
    vlayout3->addWidget(denoisebutton);

}

void MainWindow::OUTPUTconsole() {
    QLabel *outputhead = new QLabel("Save Output(s)");
    outputhead->setStyleSheet("QLabel {background-color : black; color : #4876FF;  font : bold 12px}");
    outputhead->setAlignment(Qt::AlignCenter);

    dwtoutbutton = new QPushButton(QObject::tr("Save DWT Output"));
    QObject::connect(dwtoutbutton, SIGNAL(clicked()),this, SLOT(saveDWT()));

    dwtoutbutton->setEnabled(false);

    fullgraphbutton = new QPushButton(QObject::tr("Save Decomposition Graph"));
    QObject::connect(fullgraphbutton, SIGNAL(clicked()),this, SLOT(fullPLOT()));

    fullgraphbutton->setEnabled(false);

    appxoutbutton = new QPushButton(QObject::tr("Save Approximated Signal"));
    QObject::connect(appxoutbutton, SIGNAL(clicked()),this, SLOT(saveAPPX()));

    appxoutbutton->setEnabled(false);

    appxcoefbutton = new QPushButton(QObject::tr("Save Approximation Coeffs"));
    QObject::connect(appxcoefbutton, SIGNAL(clicked()),this, SLOT(saveAPPXCOEF()));

    appxcoefbutton->setEnabled(false);

    denoiseoutbutton = new QPushButton(QObject::tr("Save Denoised Signal"));
    QObject::connect(denoiseoutbutton, SIGNAL(clicked()),this, SLOT(saveDENOISE()));

    denoiseoutbutton->setEnabled(false);

    denoisecoefbutton = new QPushButton(QObject::tr("Save Denoising Coeffs"));
    QObject::connect(denoisecoefbutton, SIGNAL(clicked()),this, SLOT(saveDENOISECOEF()));

    denoisecoefbutton->setEnabled(false);

    vlayout3->addWidget(outputhead);
    vlayout3->addWidget(dwtoutbutton);
   // vlayout3->addWidget(fullgraphbutton);
    vlayout3->addWidget(appxoutbutton);
    vlayout3->addWidget(appxcoefbutton);
    vlayout3->addWidget(denoiseoutbutton);
    vlayout3->addWidget(denoisecoefbutton);


}

void MainWindow::setDecom(int index){
    J = index + 1;

}

void MainWindow::setDenoiseDecom(int ind){
    J_dn = ind + 1;

}

void MainWindow::setExt(int index){
    ext = index ;

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

void MainWindow::enableIDWT(){
    idwtbutton->setEnabled(true);
}


void MainWindow::computeDWT() {
    dwtbutton->setEnabled(false);
  /*  string inp2;
    inp2 = curFile.toStdString();
    char *inp = (char*)inp2.c_str();

    vector<double> sig;
    ifstream sig_inp(inp);
 if ( !sig_inp.good()){
        cout << "The File doesn't exist"<< endl;
        showmsg();
 }
    while (sig_inp) {
        double temp;
        sig_inp >> temp;
        sig.push_back(temp);
    }
    sig.pop_back();*/

    plt.clear();
    plt_curve.clear();
    int sig_size = original_signal.size();
    int max_dec = (int) floor((double)log(sig_size)/log(2.0)) - 1;
    if ( J >= max_dec) {
        J = max_dec;
    }

  vector<double> dwt_output, flag;
  vector<int> length;
  vector<double> signal;
  QTime cpu_time;

  // perform J-Level SWT/DWT
  if (mode == "swt"){
      int len;
      signal = original_signal;
      vector<double> sig2;
     sig2=original_signal;
     // dyadic_zpad_1d(sig2);
     cpu_time.start();
      swt(signal, J, nm, dwt_output,len );
      exec_time = cpu_time.elapsed();
      SWTplot(dwt_output,sig2,J,len);
      signal.clear();
 } else if ( mode == "dwt_per") {
     dwt_output.clear();
     flag.clear();
     signal = original_signal;
     vector<double> sig2;
     sig2=original_signal;
     cpu_time.start();
     dwt(signal,J, nm, dwt_output,flag,length );
     per_coeff_length= length;
     J=(int) flag[1];
     exec_time = cpu_time.elapsed();
     DWT_SYMplot(dwt_output,sig2, J,length);
     signal.clear();
} else if (mode == "dwt_sym") {
     dwt_output.clear();
     flag.clear();
     signal = original_signal;
     vector<double> sig;
     sig = original_signal;
     cpu_time.start();
     dwt_sym (signal, J,nm, dwt_output, flag,length, ext);
     J=(int) flag[1];
     exec_time = cpu_time.elapsed();
     DWT_SYMplot(dwt_output,sig,J,length);
     sym_coeff_length = length;
     signal.clear();
}
  vector<double> output;
  dwt_coefficients = dwt_output;

  if (idwtbutton->isChecked()) {
      if (mode == "swt") {
          iswt(dwt_output,J, nm,output);
      } else if (mode == "dwt_per") {
          idwt(dwt_output, flag,nm,output,length);
  }  else if (mode == "dwt_sym"){
          idwt_sym(dwt_output,flag,nm,output,length);
  }
  }
  dwtbutton->setEnabled(true);
  dwtoutbutton->setEnabled(true);
  reportbutton->setEnabled(true);

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

    unsigned int sig_length = original_signal.size();
    QString nm2(nm.c_str());
    int oup_length;
    oup_length = dwt_coefficients.size();

    QString str;
    str = "DWT OUTPUT \n \n";
    str.append(QString("Length of Signal : %1 \n \n").arg(sig_length));
    str.append(QString("Wavelet Used : %1 \n \n").arg(nm2));
    str.append(QString("Decomposition Levels : %1 \n \n").arg(J));
    str.append(QString("DWT Execution Time ( in mSec) : %1 \n \n").arg(exec_time));
    str.append(QString("Coefficient File : See \"Save DWT Output\" \n \n"));
    if ( mode == "swt") {
        QString modex = "Stationary Wavelet Transform";
        str.append(QString("DWT Mode : %1 \n \n").arg(modex));
        str.append(QString("Length of Coefficient Vector : %1 \n \n").arg(oup_length));
        str.append(QString("Coefficient File Key : All Coefficients are of same length %1 Coefficients \n ").arg(sig_length));
        str.append(QString("First %1 Coefficients are Approximation coefficients at level %2 \n").arg(sig_length).arg(J));
        str.append(QString("Second %1 Coefficients are Detail coefficients at level %2 \n").arg(sig_length).arg(J));
        str.append(QString(".......................................................... \n"));
        str.append(QString("Last %1 Coefficients are Detail coefficients at level %2 \n").arg(sig_length).arg(1));

    }    else if (mode == "dwt_per") {
        QString modex = "Discrete Wavelet Transform ( Decimated with Periodic Extension)";
        str.append(QString("DWT Mode : %1 \n \n").arg(modex));
        str.append(QString("Length of Coefficient Vector : %1 \n \n").arg(oup_length));
        str.append(QString("Coefficient File Key : All Coefficients are of different Lengths  \n "));
        str.append(QString("Coefficients are stored in following format [A(J) D(J) D(J-1) ..... D(1)] \n"));
        str.append(QString(", where A(J) is the approximation coefficient vector at the Jth level while \n "));
        str.append(QString("D(n) are the detail coefficient vectors at the nth level. \n"));
        unsigned int size_coeff = per_coeff_length.size();
        for (unsigned i = 0; i < size_coeff - 1; i++) {
            int temp;
            temp = per_coeff_length[i];
            str.append(QString("%1  \t").arg(temp));
        }
        str.append(QString(" ] \n"));
    } else {
        QString modex = "Discrete Wavelet Transform ( Decimated with Symmetric Extension)";
        str.append(QString("DWT Mode : %1 \n \n").arg(modex));
        str.append(QString("Length of Coefficient Vector : %1 \n \n").arg(oup_length));
        str.append(QString("Coefficient File Key : All Coefficients are of different Lengths  \n "));
        str.append(QString("Coefficients are stored in following format [A(J) D(J) D(J-1) ..... D(1)] \n"));
        str.append(QString(", where A(J) is the approximation coefficient vector at the Jth level while \n "));
        str.append(QString("D(n) are the detail coefficient vectors at the nth level. \n"));
        str.append(QString("Coefficient Length Vector : [ \t "));
        unsigned int size_coeff = sym_coeff_length.size();
        for (unsigned i = 0; i < size_coeff - 1; i++) {
            int temp;
            temp = sym_coeff_length[i];
            str.append(QString("%1  \t").arg(temp));
        }
        str.append(QString(" ] \n"));
    }

    report->setText(str);

    report->show();

}

void MainWindow::approximateSig() {
    vector<double> output;
    int Max_Iter,Max_Iter_sym;
    int sig_length = original_signal.size();
    vector<double> dwt_output, flag;
    Max_Iter = (int) floor(log( double(sig_length))/log (2.0)) - 1;
    Max_Iter_sym = (int) floor(log( double(sig_length))/log (2.0));

    vector<double> sig;
    sig = original_signal;

    if (mode_appx == "dwt_per") {
    vector<int> length1;

    dwt(sig, Max_Iter, nm, dwt_output,flag,length1 );

    int num_coef =(int) floor( (double) n_coef *sig_length/(double) 100);
    double thresh = 0.0;
    vector<double> temp_dwtoutput;
    for (unsigned int i =0; i < dwt_output.size();i++){
        double temp = abs(dwt_output[i]);
        temp_dwtoutput.push_back(temp);
    }

    findthresh(temp_dwtoutput,num_coef, thresh);

    for (unsigned int i = 0; i < dwt_output.size();i++){
        double temp = abs(dwt_output[i]);
        if (temp < thresh){
                dwt_output.at(i) = 0.0;

        }
    }

    idwt(dwt_output, flag,nm,output,length1);

    vector<double> signal = original_signal;
    APPXplot(signal,output);
} else {
    vector<int> length1;

    int ext=2;
    dwt_sym(sig, Max_Iter_sym, nm, dwt_output,flag, length1,ext );
    int num_coef =(int) floor( (double) n_coef *sig_length/(double) 100);

    double thresh = 0.0;

    vector<double> temp_dwtoutput;
    for (unsigned int i =0; i < dwt_output.size();i++){
        double temp = abs(dwt_output[i]);
        temp_dwtoutput.push_back(temp);
    }
    findthresh(temp_dwtoutput,num_coef, thresh);

    for (unsigned int i = 0; i < dwt_output.size();i++){
        double temp = abs(dwt_output[i]);
        if (temp < thresh){
                dwt_output.at(i) = 0.0;

        }
    }

    idwt_sym(dwt_output, flag,nm,output, length1);
    vector<double> signal = original_signal;
    APPXplot(signal,output);
}
approximated_signal = output;
approximation_coefficients = dwt_output;
appxoutbutton->setEnabled(true);
appxcoefbutton->setEnabled(true);

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
    while ((child = vlayout2->takeAt(0)) != 0)
    {
    delete child->widget();
    delete child;
    }

    QLabel *l1 = new QLabel("Decomposition Low Pass Filter");
    l1->setAlignment(Qt::AlignCenter);
    vlayout2->addWidget(l1);
    pointplot(lp1,2);

    QLabel *l2 = new QLabel(QString("Decomposition High pass Filter"));
    l2->setAlignment(Qt::AlignCenter);
    vlayout2->addWidget(l2);
    pointplot(hp1,2);

    QLabel *l3 = new QLabel("Reconstruction Low Pass Filter");
    l3->setAlignment(Qt::AlignCenter);
    vlayout2->addWidget(l3);
    pointplot(lp2,2);

    QLabel *l4 = new QLabel(QString("Reconstruction High Pass Filter"));
    l4->setAlignment(Qt::AlignCenter);
    vlayout2->addWidget(l4);
    pointplot(hp2,2);



}

void MainWindow::freqdisp() {
    QLayoutItem *child;
    while ((child = vlayout2->takeAt(0)) != 0)
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
    vlayout2->addWidget(l3);
    lineplotmod(signal,1);

    QLabel *l4 = new QLabel(QString("Two-Sided Frequency Response"));
    l4->setAlignment(Qt::AlignCenter);
    vlayout2->addWidget(l4);
    lineplot(freq_response,1, - 3.14, 3.14);

    vector<double> freq_response1;

    freq_one(signal,freq_response1);

    QLabel *l5 = new QLabel(QString("One-Sided Frequency Response"));
    l5->setAlignment(Qt::AlignCenter);
    vlayout2->addWidget(l5);
    lineplot(freq_response1,1,0,3.14);

}

void MainWindow::filtfreq() {
    QLayoutItem *child;
    while ((child = vlayout2->takeAt(0)) != 0)
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
    vlayout2->addWidget(l1);
    lineplot(lp1f,2,0,3.14);

    vector<double> hp1f;
    freq_one(hp1,hp1f);

    QLabel *l2 = new QLabel(QString("Analysis High Pass Filter"));
    l2->setAlignment(Qt::AlignCenter);
    vlayout2->addWidget(l2);
    lineplot(hp1f,2,0,3.14);

    vector<double> lp2f;
    freq_one(lp2,lp2f);

    QLabel *l3 = new QLabel(QString("Synthesis Low Pass Filter"));
    l3->setAlignment(Qt::AlignCenter);
    vlayout2->addWidget(l3);
    lineplot(lp2f,2,0,3.14);

    vector<double> hp2f;
    freq_one(hp2,hp2f);

    QLabel *l4 = new QLabel(QString("Synthesis High Pass Filter"));
    l4->setAlignment(Qt::AlignCenter);
    vlayout2->addWidget(l4);
    lineplot(hp2f,2,0,3.14);
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


void MainWindow::signalDENOISE(){

    int sig_size = original_signal.size();
    int max_dec = (int) floor((double)log(sig_size)/log(2.0)) - 1;
    if ( J_dn >= max_dec) {
        J_dn = max_dec;
    }

  vector<double> dwt_output, flag,output;
  vector<int> length;
  vector<double> signal;
  if (dn_method == "visushrink") {

      if (mode_denoise == "swt"){
          dwt_output.clear();
          int len;
          signal = original_signal;
          vector<double> sig2;
          sig2=original_signal;
          swt(signal, J_dn, nm_dn, dwt_output,len );
          unsigned int dwt_len = dwt_output.size();
          vector<double> dwt_med;
          for (unsigned int i=0; i < dwt_len;i++) {
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

          iswt(dwt_output,J_dn, nm_dn,output);
          DENOISEplot(sig2,output);

     //     SWTplot(dwt_output,sig2,J,len);
            signal.clear();
     } else if ( mode_denoise == "dwt_per") {
         dwt_output.clear();
         flag.clear();
         signal = original_signal;
         vector<double> sig2;
         sig2=original_signal;
         dwt(signal,J_dn, nm_dn, dwt_output,flag,length );

         unsigned int dwt_len = dwt_output.size();
         vector<double> dwt_med;
         for (unsigned int i=0; i < dwt_len;i++) {
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

         idwt(dwt_output, flag,nm_dn,output,length);
         DENOISEplot(sig2,output);
      //   DWT_PERplot(dwt_output,sig2, J);
           signal.clear();

    } else if (mode_denoise == "dwt_sym") {
         dwt_output.clear();
         flag.clear();
         signal = original_signal;
         vector<double> sig;
         sig = original_signal;
         dwt_sym (signal, J_dn,nm_dn, dwt_output, flag,length, ext);

         unsigned int dwt_len = dwt_output.size();
         vector<double> dwt_med;
         for (unsigned int i=0; i < dwt_len;i++) {
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

         idwt_sym(dwt_output,flag,nm_dn,output,length);
         DENOISEplot(sig,output);

     //    DWT_SYMplot(dwt_output,sig,J,length);
           signal.clear();
    }
  } else if (dn_method == "sureshrink") {

      if (mode_denoise == "swt"){
          dwt_output.clear();
          int len;
          signal = original_signal;
          vector<double> sig2;
          sig2=original_signal;
          swt(signal, J_dn, nm_dn, dwt_output,len );
          double td;

          for (int it = 0; it < J_dn; it++) {
              vector<double> dwt_med;
              vector<double> coef;
              for (int i=0; i < len;i++) {
                  double temp = abs(dwt_output[len * (it+1) + i]);
                  double temp2 = dwt_output[len * (it+1) + i];
                  dwt_med.push_back(temp);
                  coef.push_back(temp2);
              }
              double sigma;
              median(dwt_med,sigma);
              unsigned int dwt_len = len;

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
                      for (unsigned int rk=0; rk < dwt_len; rk++) {
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
              for (unsigned int iter=0; iter < dwt_len; iter++) {
                  if (abs(dwt_output[len * (it+1) + iter]) <= td) {
                      dwt_output.at(len * (it+1) + iter) = 0;
                  }
              }
          } else if (dn_thresh == "soft") {
              for (unsigned int iter=0; iter < dwt_len; iter++) {
                  if (abs(dwt_output[len * (it+1) + iter]) >= td) {
                      double temp;
                      temp = sgn(dwt_output[len * (it+1) + iter])*( abs(dwt_output[len * (it+1) + iter]) - td);
                      dwt_output.at(len * (it+1) + iter) = temp;
                  } else {
                      dwt_output.at(len * (it+1) + iter) = 0;
                  }
              }

          }

      }
          iswt(dwt_output,J_dn, nm_dn,output);
          DENOISEplot(sig2,output);

     //     SWTplot(dwt_output,sig2,J,len);
            signal.clear();
     } else if ( mode_denoise == "dwt_per") {
         dwt_output.clear();
         flag.clear();
         signal = original_signal;
         vector<double> sig2;
         sig2=original_signal;
         dyadic_zpad_1d(sig2);
         dwt(signal,J_dn, nm_dn, dwt_output,flag,length );

         unsigned int len = dwt_output.size() / int(pow(2.0,J_dn));
         for (int it = 0; it < J_dn; it++) {
             vector<double> dwt_med;
             vector<double> coef;
             for (unsigned int i=0; i < len;i++) {
                 double temp = abs(dwt_output[len  + i]);
                 double temp2 = dwt_output[len + i];
                 dwt_med.push_back(temp);
                 coef.push_back(temp2);
             }
             double sigma;
             median(dwt_med,sigma);
             unsigned int dwt_len = len;

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
                     for (unsigned int rk=0; rk < dwt_len; rk++) {
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
             for (unsigned int iter=0; iter < dwt_len; iter++) {
                 if (abs(dwt_output[len + iter]) <= td) {
                     dwt_output.at(len + iter) = 0;
                 }
             }
         } else if (dn_thresh == "soft") {
             for (unsigned int iter=0; iter < dwt_len; iter++) {
                 if (abs(dwt_output[len + iter]) >= td) {
                     double temp;
                     temp = sgn(dwt_output[len + iter])*( abs(dwt_output[len + iter]) - td);
                     dwt_output.at(len + iter) = temp;
                 } else {
                     dwt_output.at(len + iter) = 0;
                 }
             }

         }
         len = 2 * len;

     }
         idwt(dwt_output, flag,nm_dn,output,length);
         DENOISEplot(sig2,output);
      //   DWT_PERplot(dwt_output,sig2, J);
           signal.clear();

    } else if (mode_denoise == "dwt_sym") {
         dwt_output.clear();
         flag.clear();
         signal = original_signal;
         vector<double> sig;
         sig = original_signal;
         dwt_sym (signal, J_dn,nm_dn, dwt_output, flag,length, ext);

         unsigned int len = length[0];
         for (int it = 0; it < J_dn; it++) {
             vector<double> dwt_med;
             vector<double> coef;
             for (int i=0; i < length[it+1];i++) {
                 double temp = abs(dwt_output[len  + i]);
                 double temp2 = dwt_output[len + i];
                 dwt_med.push_back(temp);
                 coef.push_back(temp2);
             }
             double sigma;
             median(dwt_med,sigma);
             unsigned int dwt_len = length[it+1];

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
                     for (unsigned int rk=0; rk < dwt_len; rk++) {
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
             for (unsigned int iter=0; iter < dwt_len; iter++) {
                 if (abs(dwt_output[len + iter]) <= td) {
                     dwt_output.at(len + iter) = 0;
                 }
             }
         } else if (dn_thresh == "soft") {
             for (unsigned int iter=0; iter < dwt_len; iter++) {
                 if (abs(dwt_output[len + iter]) >= td) {
                     double temp;
                     temp = sgn(dwt_output[len + iter])*( abs(dwt_output[len + iter]) - td);
                     dwt_output.at(len + iter) = temp;
                 } else {
                     dwt_output.at(len + iter) = 0;
                 }
             }

         }
         len = len+length[it+1];

     }
         idwt_sym(dwt_output,flag,nm_dn,output,length);
         DENOISEplot(sig,output);

     //    DWT_SYMplot(dwt_output,sig,J,length);
           signal.clear();
    }
}
  denoiseoutbutton->setEnabled(true);
  denoisecoefbutton->setEnabled(true);
  denoised_signal = output;
  denoising_coefficients = dwt_output;

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
    sort(dwt_med.begin(),dwt_med.end(),greater<double>());
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

void MainWindow::saveDWT() {

    QString fileName = QFileDialog::getSaveFileName(this, QObject::tr("Save File As"),
                                                    "../",QObject::tr("Text File(*.txt)"));
        string file2;
        file2 =fileName.toStdString();
        const char *filename = file2.c_str();
        ofstream dwtcoeffs(filename);
        for (unsigned int i = 0; i < dwt_coefficients.size(); i++){
                        dwtcoeffs << dwt_coefficients[i] << endl;
                }


}

void MainWindow::saveAPPX() {
    QString fileName = QFileDialog::getSaveFileName(this,QObject::tr("Save File As"),
                    "../",tr("Text File(*.txt)"));

    string file2;
    file2 =fileName.toStdString();
    const char *filename = file2.c_str();

        ofstream approximated_sig (filename);
        for (unsigned int i = 0; i < approximated_signal.size(); i++){
                        approximated_sig << approximated_signal[i] << endl;
                }


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

void MainWindow::saveDENOISE() {
    QString fileName = QFileDialog::getSaveFileName(this, QObject::tr("Save File As"),
                                                    "../", QObject::tr("Text (*.txt)"));
    string file2;
    file2 =fileName.toStdString();
    const char *filename = file2.c_str();

        ofstream denoised_sig (filename);
        for (unsigned int i = 0; i < denoised_signal.size(); i++){
                        denoised_sig << denoised_signal[i] << endl;
                }


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
    while ((child = vlayout2->takeAt(0)) != 0)
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
    vlayout2->addWidget(l1);
    lineplot(phi,0,sig_min,sig_max);

    QLabel *l2 = new QLabel(QString("Wavelet Function"));
    l2->setAlignment(Qt::AlignCenter);
    vlayout2->addWidget(l2);
    lineplot(psi,0,sig_min,sig_max);
}

void MainWindow::BIORTHplot(vector<double> &phi1, vector<double> &psi1,vector<double> &phi2,
                            vector<double> &psi2) {
    QLayoutItem *child;
    while ((child = vlayout2->takeAt(0)) != 0)
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
    vlayout2->addWidget(l1);
    lineplot(phi1,2,sig_min,sig_max);

    QLabel *l2 = new QLabel(QString("Decomposition Wavelet Function"));
    l2->setAlignment(Qt::AlignCenter);
    vlayout2->addWidget(l2);
    lineplot(psi1,2,sig_min,sig_max);

    QLabel *l3 = new QLabel("Reconstruction Scaling Function");
    l3->setAlignment(Qt::AlignCenter);
    vlayout2->addWidget(l3);
    lineplot(phi2,2,sig_min,sig_max);

    QLabel *l4 = new QLabel(QString("Reconstruction Wavelet Function"));
    l4->setAlignment(Qt::AlignCenter);
    vlayout2->addWidget(l4);
    lineplot(psi2,2,sig_min,sig_max);
}

void* MainWindow::showmsg() {
    QMessageBox::critical(this,tr("Error!"),tr("No Signal loaded"));
    exit(1);
}

void MainWindow::SIGplot(vector<double> &sig){
    QLayoutItem *child;
    while ((child = vlayout2->takeAt(0)) != 0)
    {
    delete child->widget();
    delete child;
    }

    lineplotmod(sig,1);

}

void MainWindow::SWTplot(vector<double> &dwt_output,vector<double> &orig, int J, int temp2) {
    QLayoutItem *child;
    while ((child = vlayout2->takeAt(0)) != 0)
    {
    delete child->widget();
    delete child;
    }
    QFont font;
    if (J >= 5)    {
    font = QFont("Helvetica",6);
} else {
     font = QFont("Helvetica",7);
}    QLabel *l1 = new QLabel("Original Signal");
    l1->setAlignment(Qt::AlignCenter);
    l1->setFont(font);
    vlayout2->addWidget(l1);
 //   lineplotmod(orig,J);
    qwtlineplot(orig,J,0);


    for (int i=0; i < J+1; i++) {

        vector<double> sig;
        if (i ==0) {
            QLabel *l1 = new QLabel();
            QString str=QString("Approximation Coefficients at Level J = %1").arg(J-i,0,10);
            l1->setText(str);
            l1->setAlignment(Qt::AlignCenter);
            l1->setFont(font);
            vlayout2->addWidget(l1);
        sig.assign(dwt_output.begin(),dwt_output.begin()+ temp2);
        qwtlineplot(sig,J,1);


    } else {
        QLabel *l1 = new QLabel();
        QString str=QString("Detail Coefficients at Level J = %1").arg(J-i+1,0,10);
        l1->setText(str);
        l1->setAlignment(Qt::AlignCenter);
        l1->setFont(font);
        vlayout2->addWidget(l1);
        sig.assign(dwt_output.begin()+ i * temp2 ,dwt_output.begin()+(i+1)*temp2);
        qwtlineplot(sig,J,i+1);

    }
       // lineplotmod(sig,J);

    }

}

void MainWindow::DWT_SYMplot(vector<double> &dwt_output,vector<double> &orig,  int J, vector<int> &length ) {
    QLayoutItem *child;
    while ((child = vlayout2->takeAt(0)) != 0)
    {
    delete child->widget();
    delete child;
    }
    QFont font;
    if (J >= 5)    {
    font = QFont("Helvetica",6);
} else {
     font = QFont("Helvetica",7);
}

    QLabel *l1 = new QLabel("Original Signal");
    l1->setAlignment(Qt::AlignCenter);
    l1->setFont(font);
    vlayout2->addWidget(l1);
   // lineplotmod(orig,J);
    qwtlineplot(orig,J,0);
   int temp = 0;
    for (int i=0; i < J+1; i++) {

        vector<double> sig;
       if (i == 0) {
        QLabel *l1 = new QLabel();
        QString str=QString("Approximation Coefficients at Level J = %1").arg(J-i,0,10);
        l1->setText(str);
        l1->setAlignment(Qt::AlignCenter);
        l1->setFont(font);
        vlayout2->addWidget(l1);
        sig.assign(dwt_output.begin(),dwt_output.begin()+length[0]);
    //    sig.erase(sig.begin(),sig.begin()+ext);
    //    sig.erase(sig.end()-ext,sig.end());
        qwtlineplot(sig,J,1);


        } else {
            QLabel *l1 = new QLabel();
            QString str=QString("Detail Coefficients at Level J = %1").arg(J-i+1,0,10);
            l1->setText(str);
            l1->setAlignment(Qt::AlignCenter);
            l1->setFont(font);
            vlayout2->addWidget(l1);
        sig.assign(dwt_output.begin()+ temp,dwt_output.begin()+temp+length[i]);
    //    sig.erase(sig.begin(),sig.begin()+ext);
     //   sig.erase(sig.end()-ext,sig.end());
        qwtlineplot(sig,J,i+1);

    }
       // lineplotmod(sig,J);
        temp += length[i];

    }

}

void MainWindow::DWT_PERplot(vector<double> &dwt_output,vector<double> &orig,  int J) {
    QLayoutItem *child;
    while ((child = vlayout2->takeAt(0)) != 0)
    {
    delete child->widget();
    delete child;
    }
    QFont font;
    if (J >= 5)    {
    font = QFont("Helvetica",6);
} else {
     font = QFont("Helvetica",7);
}
    QLabel *l1 = new QLabel("Original Signal");
    l1->setAlignment(Qt::AlignCenter);
    l1->setFont(font);

    vlayout2->addWidget(l1);
    //lineplotmod(orig,J);
    qwtlineplot(orig,J,0);

    unsigned int app_len = dwt_output.size() / int(pow(2.0,J));

    for (int i=0; i<J+1;i++) {
        vector<double> sig;

        if ( i==0 ) {
            QLabel *l1 = new QLabel();
            QString str=QString("Approximation Coefficients at Level J = %1").arg(J-i,0,10);
            l1->setText(str);
            l1->setAlignment(Qt::AlignCenter);
            l1->setFont(font);

            vlayout2->addWidget(l1);
            sig.assign(dwt_output.begin(),dwt_output.begin()+app_len);
            qwtlineplot(sig,J,1);

        } else {
            QLabel *l1 = new QLabel();
            QString str=QString("Detail Coefficients at Level J = %1").arg(J-i+1,0,10);
            l1->setText(str);
            l1->setAlignment(Qt::AlignCenter);
            l1->setFont(font);

            vlayout2->addWidget(l1);
            sig.assign(dwt_output.begin()+app_len, dwt_output.begin()+ 2* app_len);
            app_len = 2 * app_len;
            qwtlineplot(sig,J,i+1);


        }
       // lineplotmod(sig,J);
    }

}

void MainWindow::APPXplot(vector<double> &signal,vector<double> &output) {
    QLayoutItem *child;
    while ((child = vlayout2->takeAt(0)) != 0)
    {
    delete child->widget();
    delete child;
    }
    QLabel *l1 = new QLabel("Original Signal");
    l1->setAlignment(Qt::AlignCenter);
    vlayout2->addWidget(l1);
    lineplotmod(signal,0);

    QLabel *l2 = new QLabel(QString("Approximated Signal Using only %1 \% Coefficients").arg(n_coef));
    l2->setAlignment(Qt::AlignCenter);
    vlayout2->addWidget(l2);
    lineplotmod(output,0);

}

void MainWindow::DENOISEplot(vector<double> &signal,vector<double> &output) {
    QLayoutItem *child;
    while ((child = vlayout2->takeAt(0)) != 0)
    {
    delete child->widget();
    delete child;
    }
    QLabel *l1 = new QLabel("Original Signal");
    l1->setAlignment(Qt::AlignCenter);
    vlayout2->addWidget(l1);
    lineplotmod(signal,0);

    QLabel *l2 = new QLabel(QString("DeNoised Signal"));
    l2->setAlignment(Qt::AlignCenter);
    vlayout2->addWidget(l2);
    lineplotmod(output,0);

}

void MainWindow::lineplot(vector<double> &sig, int J_num , double sig_min, double sig_max){

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
    const QColor c(Qt::white);
    zoomer->setRubberBandPen(c);
    zoomer->setTrackerPen(c);
  //  curve.append(temp_curve);
  //  plt.append(temp_plt);
    vlayout2->addWidget(temp_plt);
    xdata.clear();

}

void MainWindow::lineplotmod(vector<double> &sig, int J_num){

    int temp2 = sig.size();

    QPen pen(QColor(72,118,255), 1, Qt::SolidLine);
    QVector<double> xdata;
    QVector<double> qsig = QVector<double>::fromStdVector(sig);


    for (int i =0; i < temp2; i++){
        xdata.append((double) i);
    }
    QwtPlot *temp_plt = new QwtPlot(this);
    QwtPlotCurve *temp_curve = new QwtPlotCurve(QString("curve"));

    temp_curve->setSamples(xdata,qsig);
    temp_curve->setPen(pen);
    temp_curve->attach(temp_plt);
    temp_plt->setCanvasBackground(Qt::black);
  //  temp_plt->setAxisTitle(QwtPlot::yLeft, " Coefficients");

    QwtPlotZoomer *zoomer = new QwtPlotZoomer(temp_plt->canvas());
    QwtPlotPanner *panner = new QwtPlotPanner(temp_plt->canvas());
    zoomer->setMousePattern(QwtEventPattern::MouseSelect2,
        Qt::RightButton, Qt::ControlModifier);
    zoomer->setMousePattern(QwtEventPattern::MouseSelect3,
        Qt::RightButton);
    temp_plt->replot();
    temp_plt->updateAxes();
    panner->setAxisEnabled(QwtPlot::yRight, false);
    panner->setMouseButton(Qt::MidButton);
    const QColor c(Qt::white);
    zoomer->setRubberBandPen(c);
    zoomer->setTrackerPen(c);
  //  curve.append(temp_curve);
  //  plt.append(temp_plt);
    vlayout2->addWidget(temp_plt);
    xdata.clear();

}

void MainWindow::pointplot(vector<double> &filt, int J_num) {
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
    const QColor c(Qt::white);
    zoomer->setRubberBandPen(c);
    zoomer->setTrackerPen(c);
  //  curve.append(temp_curve);
  //  plt.append(temp_plt);
    vlayout2->addWidget(temp_plt);
    xdata.clear();

}

void MainWindow::qwtlineplot(vector<double> &sig, int J_num, int num){
    int temp2 = sig.size();

    QPen pen(QColor(72,118,255), 1, Qt::SolidLine);
    QVector<double> xdata;
    QVector<double> qsig = QVector<double>::fromStdVector(sig);


    for (int i =0; i < temp2; i++){
        xdata.append((double) i);
    }
    QwtPlot *temp_plt = new QwtPlot(this);
    QwtPlotCurve *temp_curve = new QwtPlotCurve(QString("VIEW #%1").arg(num));

    temp_curve->setSamples(xdata,qsig);
    temp_curve->setPen(pen);
    temp_curve->attach(temp_plt);
    temp_plt->setCanvasBackground(Qt::black);
    temp_plt->setAxisScale(QwtPlot::xBottom,0,temp2-1,0);
  //  temp_plt->setTitle(QString("Coefficents"));
  //  temp_plt->setAxisTitle(QwtPlot::yLeft, " Coefficients");
    if ((J_num >= 3) & (J_num < 5)) {
        temp_plt->setAxisMaxMajor(QwtPlot::yLeft,3);
        temp_plt->setAxisFont(QwtPlot::xBottom,QFont("Helvetica",7));
    } else if (J_num >= 5) {
        temp_plt->setAxisMaxMajor(QwtPlot::yLeft,3);
        temp_plt->setAxisFont(QwtPlot::xBottom,QFont("Helvetica",6));
    }
    plt_curve.append(temp_curve);
    QwtPlotZoomer *zoomer = new QwtPlotZoomer(temp_plt->canvas());
    QwtPlotPanner *panner = new QwtPlotPanner(temp_plt->canvas());
    zoomer->setMousePattern(QwtEventPattern::MouseSelect2,
        Qt::RightButton, Qt::ControlModifier);
    zoomer->setMousePattern(QwtEventPattern::MouseSelect3,
        Qt::RightButton);
    temp_plt->replot();
    temp_plt->updateAxes();
    plt.append(temp_plt);

    QwtLegend* legend = new QwtLegend( temp_plt );
    legend->setItemMode(QwtLegend::CheckableItem);
    temp_plt->insertLegend( legend, QwtPlot::RightLegend );


//    QwtLegend* legend2 = new QwtLegend(plt[num]);
//    legend2->setItemMode(QwtLegend::ReadOnlyItem);
//    plt[num]->insertLegend( legend2, QwtPlot::RightLegend );

   fullgraphbutton->setEnabled(true);

    panner->setAxisEnabled(QwtPlot::yRight, false);
    panner->setMouseButton(Qt::MidButton);
    const QColor c(Qt::white);
    zoomer->setRubberBandPen(c);
    zoomer->setTrackerPen(c);
  //  curve.append(temp_curve);
  //  plt.append(temp_plt);
    vlayout2->addWidget(temp_plt);
    newPlot(plt_curve[num],false);

    connect(temp_plt, SIGNAL(legendChecked(QwtPlotItem *,bool)),
        this,SLOT(newPlot(QwtPlotItem *, bool)));
    xdata.clear();

}

void MainWindow::newPlot(QwtPlotItem *curve, bool on) {
    if (on == true) {
      curve->setVisible(on);
      QWidget *sec = new QWidget;
      QVBoxLayout *vlt = new QVBoxLayout;
     // curve->setTitle("Print View");

      QwtPlot *temp_plt2 = new QwtPlot(sec);

      curve->attach(temp_plt2);
  //    QPen pen(Qt::white, 1, Qt::SolidLine);

      temp_plt2->setCanvasBackground(Qt::black);
      QwtPlotZoomer *zoomer = new QwtPlotZoomer(temp_plt2->canvas());
      QwtPlotPanner *panner = new QwtPlotPanner(temp_plt2->canvas());

      zoomer->setMousePattern(QwtEventPattern::MouseSelect2,
          Qt::RightButton, Qt::ControlModifier);
      zoomer->setMousePattern(QwtEventPattern::MouseSelect3,
          Qt::RightButton);

//          QwtLegend* legend2 = new QwtLegend(temp_plt2);
//          legend2->setItemMode(QwtLegend::CheckableItem);
//          temp_plt2->insertLegend( legend2, QwtPlot::RightLegend );

      panner->setAxisEnabled(QwtPlot::yRight, false);
      panner->setMouseButton(Qt::MidButton);
      const QColor c(Qt::white);
      zoomer->setRubberBandPen(c);
      zoomer->setTrackerPen(c);

      temp_plt2->replot();
      temp_plt2->updateAxes();

      QPushButton *printbutton = new QPushButton("Printable View");
      QPushButton *button2 = new QPushButton("Save as Image");
      QPushButton *pdfbutton2 = new QPushButton("Save as PDF/SVG");

      QHBoxLayout *hzt = new QHBoxLayout;
      hzt->addWidget(printbutton,0,0);
      hzt->addWidget(button2,0,0);
      hzt->addWidget(pdfbutton2,0,0);

      connect(printbutton,SIGNAL(clicked()),this,SLOT(newPlot_print()));
      connect(button2,SIGNAL(clicked()),this,SLOT(savePLOT2()));
      connect(pdfbutton2,SIGNAL(clicked()),this,SLOT(savePLOTPDF2()));
      printplot2 = temp_plt2;

      vlt->addWidget(temp_plt2);
      vlt->addLayout(hzt);


      sec->setLayout(vlt);
      sec->resize(500,400);
      QwtText qtext = curve->title();
      QString txt;
      txt = qtext.text();
      sec->setWindowTitle(txt);


      sec->show();
    //  newPlot_print(curve,false);
      printcurve = curve;
   //   connect(temp_plt2, SIGNAL(legendChecked(QwtPlotItem *,bool)),
      //    this,SLOT(newPlot_print(QwtPlotItem *, bool)));

  }
}

    void MainWindow::newPlot_print() {
          QwtPlotItem* curve;
          curve= printcurve;
          QWidget *tri = new QWidget;
          QVBoxLayout *vlt = new QVBoxLayout;
         // curve->setTitle("Print View");

          QwtPlot *temp_plt2 = new QwtPlot(tri);

          curve->attach(temp_plt2);
      //    QPen pen(Qt::white, 1, Qt::SolidLine);

          temp_plt2->setCanvasBackground(Qt::white);
          QwtPlotZoomer *zoomer = new QwtPlotZoomer(temp_plt2->canvas());
          QwtPlotPanner *panner = new QwtPlotPanner(temp_plt2->canvas());

          zoomer->setMousePattern(QwtEventPattern::MouseSelect2,
              Qt::RightButton, Qt::ControlModifier);
          zoomer->setMousePattern(QwtEventPattern::MouseSelect3,
              Qt::RightButton);


          panner->setAxisEnabled(QwtPlot::yRight, false);
          panner->setMouseButton(Qt::MidButton);
          const QColor c(Qt::black);
          zoomer->setRubberBandPen(c);
          zoomer->setTrackerPen(c);

          temp_plt2->replot();

          temp_plt2->updateAxes();

          vlt->addWidget(temp_plt2);
          QPushButton *button = new QPushButton("Save as Image");
          QPushButton *pdfbutton = new QPushButton("Save as PDF/SVG");

          QHBoxLayout *hzt = new QHBoxLayout;
          hzt->addWidget(button,0,0);
          hzt->addWidget(pdfbutton,0,0);

          vlt->addLayout(hzt);
          connect(button,SIGNAL(clicked()),this,SLOT(savePLOT()));
          connect(pdfbutton,SIGNAL(clicked()),this,SLOT(savePLOTPDF()));
          printplot = temp_plt2;

          tri->setLayout(vlt);
          tri->resize(500,400);
          QwtText qtext = curve->title();
          QString txt;
          txt = qtext.text();
          tri->setWindowTitle(txt);

          tri->show();

    }

    void MainWindow::savePLOT() {

        QString fileName;
        fileName = QFileDialog::getSaveFileName(this,QObject::tr("Save File As"),
                                                 "../",tr("Image(*.jpg *.bmp *.tif *.tiff *.png)"));
        if(!fileName.isEmpty())
        {
        QPixmap picture;
        picture = QPixmap::grabWidget(printplot);
        picture.save(fileName);
        }
    }

    void MainWindow::savePLOTPDF() {

        QString fileName;
        fileName = QFileDialog::getSaveFileName(this,QObject::tr("Save File As"),
                       "../",tr("All Files(*);;PDF(*.pdf);;SVG(*.svg);;Image(*.jpg *.bmp *.tif *.tiff *.png)"));
        if(!fileName.isEmpty())
        {
        QwtPlotRenderer renderer;
        renderer.renderDocument(printplot, fileName,QSizeF(300, 200), 85);

        }
    }

    void MainWindow::savePLOT2() {

        QString fileName;
        fileName = QFileDialog::getSaveFileName(this,QObject::tr("Save File As"),
                                                 "../",tr("Image(*.jpg *.bmp *.tif *.tiff *.png)"));
        if(!fileName.isEmpty())
        {
        QPixmap picture;
        picture = QPixmap::grabWidget(printplot2);
        picture.save(fileName);
        }
    }

    void MainWindow::savePLOTPDF2() {

        QString fileName;
        fileName = QFileDialog::getSaveFileName(this,QObject::tr("Save File As"),
                       "../",tr("All Files(*);;PDF(*.pdf);;SVG(*.svg);;Image(*.jpg *.bmp *.tif *.tiff *.png)"));
        if(!fileName.isEmpty())
        {
        QwtPlotRenderer renderer;
        renderer.renderDocument(printplot2, fileName,QSizeF(300, 200), 85);

        }
    }

    void MainWindow::fullPLOT() {
        int N = plt_curve.size();
        QwtPlot *fullplot = new QwtPlot();


        for (int i=0; i <N; i++) {
            QPen pen;
            if (i==0) {
                pen.setColor(QColor(255,0,0));
                pen.setWidth(1);
                pen.setStyle(Qt::SolidLine);
            plt_curve[i]->setTitle(QString("Original Signal"));
        } else if (i ==1) {
            plt_curve[i]->setTitle(QString("Approximation, Level %1").arg(N-2));
            pen.setColor(QColor(0,0,0));
            pen.setWidth(1);
            pen.setStyle(Qt::SolidLine);
        } else {
            pen.setColor(QColor(73+(i-2)*8,118+(i-2)*5,255-(i-2)*10));
            pen.setWidth(1);
            pen.setStyle(Qt::SolidLine);
            plt_curve[i]->setTitle(QString("Detail Level %1").arg(i-1));

        }
            plt_curve[i]->attach(fullplot);
            plt_curve[i]->setPen(pen);
            fullplot->setCanvasBackground(Qt::white);

            QwtLegend* legend = new QwtLegend( fullplot );
            legend->setItemMode(QwtLegend::ReadOnlyItem);
            fullplot->insertLegend( legend, QwtPlot::RightLegend );

        }

        QString fileName;
        fileName = QFileDialog::getSaveFileName(this,QObject::tr("Save File As"),
                       "../",tr("All Files(*);;PDF(*.pdf);;SVG(*.svg);;Image(*.jpg *.bmp *.tif *.tiff *.png)"));
        if(!fileName.isEmpty())
        {
        QwtPlotRenderer renderer;
        renderer.renderDocument(fullplot, fileName,QSizeF(300, 200), 85);

        }

    }

void* MainWindow::maxval(const vector<double> &arr, double &max){
        max = 0;
        for (unsigned int i =0; i < arr.size(); i++) {
                if (max <= arr[i]){
                        max = arr[i];
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


bool MainWindow::eventFilter(QObject *o, QEvent *event)
{
    bool filterEvent = false;

//      switch(event->type()) {

//          case QEvent::MouseButtonPress:
//          {
//            QMouseEvent * mouseEvent = static_cast<QMouseEvent *>(event);
//            origin = mouseEvent->pos();
//            active = true;
//            break;
//          }


//          case QEvent::MouseButtonRelease:
//          {
//            if (active) {
//              QMouseEvent * mouseEvent = static_cast<QMouseEvent *>(event);
//              QPoint end = mouseEvent->pos();

//              view = static_cast<QGraphicsView *>(o->parent());
//              QRectF zoomRectInScene = QRectF(view->mapToScene(origin),
//                                              view->mapToScene(end));
//              qDebug() << origin << " " << end;
//              view->fitInView(zoomRectInScene, Qt::KeepAspectRatio);
//              active = false;
//            }
//            break;
//          }
//      }

      return filterEvent;
}

void MainWindow::mousePressEvent(QGraphicsSceneMouseEvent  *event) {
    if (event->button() == Qt::LeftButton) {

       QPointF originf = event->pos();
       origin = originf.toPoint();
        if (!rubberband)
            rubberband = new QRubberBand(QRubberBand::Rectangle, this);
        rubberband->setGeometry(QRect(origin, QSize()));
        rubberband->show();
    }

}

void MainWindow::mouseMoveEvent(QGraphicsSceneMouseEvent  *event)
 {
     rubberband->setGeometry(QRect(origin,(QPoint) (event->pos()).toPoint()).normalized());
 }

 void MainWindow::mouseReleaseEvent(QGraphicsSceneMouseEvent  *event)
 {
     rubberband->hide();

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


