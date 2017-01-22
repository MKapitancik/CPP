#include <libv4l2.h>
#include <sys/ioctl.h>
#include <QtGui>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "picam.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),camParameter("/dev/video0")
{
    myIm2label = new Im2Label();

    QObject::connect(myIm2label, SIGNAL(processedImage(QImage)), this, SLOT(updatePlayerUI(QImage)));
    myIm2label->play();
    ui->setupUi(this);
    camParameter.getAllSetings();

    const QMetaObject &mo = Picam::staticMetaObject;
    int index = mo.indexOfEnumerator("colEffect");
    QMetaEnum metaEnum = mo.enumerator(index);

    // ***ComboBox definitions
    //Color efects
    for(int n=0; n <= metaEnum.keyCount(); n++)
    {
        ui->ColorEffectscomboBox->addItem(metaEnum.valueToKey(n));
    }
    //Auto exposure bias
    ui->AutoExpBiascomboBox->addItem("-4000");
    ui->AutoExpBiascomboBox->addItem("-3667");
    ui->AutoExpBiascomboBox->addItem("-3333");
    ui->AutoExpBiascomboBox->addItem("-3000");
    ui->AutoExpBiascomboBox->addItem("-2667");
    ui->AutoExpBiascomboBox->addItem("-2333");
    ui->AutoExpBiascomboBox->addItem("-2000");
    ui->AutoExpBiascomboBox->addItem("-1667");
    ui->AutoExpBiascomboBox->addItem("-1333");
    ui->AutoExpBiascomboBox->addItem("-1000");
    ui->AutoExpBiascomboBox->addItem("-667");
    ui->AutoExpBiascomboBox->addItem("-333");
    ui->AutoExpBiascomboBox->addItem("0");
    ui->AutoExpBiascomboBox->addItem("333");
    ui->AutoExpBiascomboBox->addItem("667");
    ui->AutoExpBiascomboBox->addItem("1000");
    ui->AutoExpBiascomboBox->addItem("1333");
    ui->AutoExpBiascomboBox->addItem("1667");
    ui->AutoExpBiascomboBox->addItem("2000");
    ui->AutoExpBiascomboBox->addItem("2333");
    ui->AutoExpBiascomboBox->addItem("2667");
    ui->AutoExpBiascomboBox->addItem("3000");
    ui->AutoExpBiascomboBox->addItem("3333");
    ui->AutoExpBiascomboBox->addItem("3667");
    ui->AutoExpBiascomboBox->addItem("4000");

    //White balance auto preset combobox
    ui->WhiteBalanceAPcomboBox->addItem("Manual");
    ui->WhiteBalanceAPcomboBox->addItem("Auto");
    ui->WhiteBalanceAPcomboBox->addItem("Incandescent");
    ui->WhiteBalanceAPcomboBox->addItem("Fluorescent");
    ui->WhiteBalanceAPcomboBox->addItem("Fluorescent H");
    ui->WhiteBalanceAPcomboBox->addItem("Horizon");
    ui->WhiteBalanceAPcomboBox->addItem("Daylight");
    ui->WhiteBalanceAPcomboBox->addItem("Flash");
    ui->WhiteBalanceAPcomboBox->addItem("Cloudy");
    ui->WhiteBalanceAPcomboBox->addItem("Shade");

    //ISO sensititivty combobox
    ui->IsoSensitivitycomboBox->addItem("0");
    ui->IsoSensitivitycomboBox->addItem("100");
    ui->IsoSensitivitycomboBox->addItem("200");
    ui->IsoSensitivitycomboBox->addItem("400");
    ui->IsoSensitivitycomboBox->addItem("800");

    //Scene mode combobox
    ui->SceneModecomboBox->addItem("None");
    ui->SceneModecomboBox->addItem("Night");
    ui->SceneModecomboBox->addItem("Sports");

    // Exposure Metering mode combobox
    ui->ExposureMeteringcomboBox->addItem("Average");
    ui->ExposureMeteringcomboBox->addItem("Center Weighted");
    ui->ExposureMeteringcomboBox->addItem("Spot");

    // end of combobox definitions

    // ***Signal definitions
        //Bright slider with brightbox and vice versa
        QObject::connect(ui->BrightSlider,SIGNAL(valueChanged(int)),ui->BrightspinBox,SLOT(setValue(int)));
        QObject::connect(ui->BrightspinBox,SIGNAL(valueChanged(int)),ui->BrightSlider,SLOT(setValue(int)));

        //Contra slider with contrabox and vice versa
        QObject::connect(ui->ContrSlider,SIGNAL(valueChanged(int)),ui->ContrspinBox,SLOT(setValue(int)));
        QObject::connect(ui->ContrspinBox,SIGNAL(valueChanged(int)),ui->ContrSlider,SLOT(setValue(int)));

        //Saturation slider with contrabox and vice versa
        QObject::connect(ui->SaturationSlider,SIGNAL(valueChanged(int)),ui->SaturationspinBox,SLOT(setValue(int)));
        QObject::connect(ui->SaturationspinBox,SIGNAL(valueChanged(int)),ui->SaturationSlider,SLOT(setValue(int)));

        //Blue balance signal with contrabox and vice versa
        QObject::connect(ui->BlueBalancehorizontalSlider,SIGNAL(valueChanged(int)),ui->BlueBalancespinBox,SLOT(setValue(int)));
        QObject::connect(ui->BlueBalancespinBox,SIGNAL(valueChanged(int)),ui->BlueBalancehorizontalSlider,SLOT(setValue(int)));

        //Red balance signal with contrabox and vice versa
        QObject::connect(ui->RedBalanceSlider,SIGNAL(valueChanged(int)),ui->RedBalancespinBox,SLOT(setValue(int)));
        QObject::connect(ui->RedBalancespinBox,SIGNAL(valueChanged(int)),ui->RedBalanceSlider,SLOT(setValue(int)));

    // end signal definitions
}

void MainWindow::updatePlayerUI(QImage img){
    if (!img.isNull())
    {
        ui->img->setAlignment(Qt::AlignHCenter);
        ui->img->setPixmap(QPixmap::fromImage(img).scaled(ui->img->size(),Qt::KeepAspectRatio, Qt::FastTransformation));
    }
}

MainWindow::~MainWindow()
{
    delete myIm2label;
    delete ui;
}

void MainWindow::on_BrightSlider_sliderMoved(int position)
{
    position = ui->BrightSlider->sliderPosition();
    //myIm2label->setCamParam(CV_CAP_PROP_BRIGHTNESS, (double)(position)/100);
    camParameter.set(V4L2_CID_BRIGHTNESS,position);
}

void MainWindow::on_BrightspinBox_valueChanged(const QString &arg1)
{
    int value = ui->BrightspinBox->value();
 //   myIm2label->setCamParam(CV_CAP_PROP_BRIGHTNESS, (double)(value)/100);
    camParameter.set(V4L2_CID_BRIGHTNESS,value);
}

void MainWindow::on_ContrSlider_valueChanged(int value)
{
    value = ui->ContrSlider->sliderPosition();
    //myIm2label->setCamParam(CV_CAP_PROP_CONTRAST, (double)(value)/100);
    camParameter.set(V4L2_CID_CONTRAST,value);
}

void MainWindow::on_ContrspinBox_valueChanged(const QString &arg1)
{
    int value = ui->ContrspinBox->value();
    //myIm2label->setCamParam(CV_CAP_PROP_CONTRAST, (double)(value)/100);
    camParameter.set(V4L2_CID_CONTRAST,value);
}

void MainWindow::on_SaturationSlider_sliderMoved(int position)
{
    position = ui->SaturationSlider->sliderPosition();
    camParameter.set(V4L2_CID_SATURATION,position);
}

void MainWindow::on_SaturationspinBox_valueChanged(const QString &arg1)
{
    int value = ui->SaturationspinBox->value();
    camParameter.set(V4L2_CID_SATURATION,value);
}

void MainWindow::on_RedBalanceSlider_sliderMoved(int position)
{
    position = ui->RedBalanceSlider->sliderPosition();
    camParameter.set(V4L2_CID_RED_BALANCE,position);
}

void MainWindow::on_RedBalancespinBox_valueChanged(const QString &arg1)
{
    int value = ui->RedBalancespinBox->value();
    camParameter.set(V4L2_CID_RED_BALANCE,value);
}

void MainWindow::on_BlueBalancehorizontalSlider_sliderMoved(int position)
{
    position = ui->BlueBalancehorizontalSlider->sliderPosition();
    camParameter.set(V4L2_CID_BLUE_BALANCE,position);
}

void MainWindow::on_BlueBalancespinBox_valueChanged(const QString &arg1)
{
    int value = ui->BlueBalancespinBox->value();
    camParameter.set(V4L2_CID_BLUE_BALANCE,value);
}

void MainWindow::on_ColorEffectscomboBox_currentIndexChanged(int index)
{
    camParameter.set(V4L2_CID_COLORFX,index);

}

void MainWindow::on_ManualExposurecheckBox_stateChanged(int arg1)
{
    if(arg1 > 0)
    {
        camParameter.set(V4L2_CID_EXPOSURE_AUTO,1);
        ui->ExposureTimehorizontalSlider->setEnabled(true);
        ui->ExposureTimespinBox->setEnabled(true);

    }
    else
    {
        camParameter.set(V4L2_CID_EXPOSURE_AUTO,0);
        ui->ExposureTimehorizontalSlider->setEnabled(false);
        ui->ExposureTimespinBox->setEnabled(false);
    }
}

void MainWindow::on_ExposureTimehorizontalSlider_sliderMoved(int position)
{
    camParameter.set(V4L2_CID_EXPOSURE_ABSOLUTE,position);
}

void MainWindow::on_ExposureTimespinBox_valueChanged(int arg1)
{
    camParameter.set(V4L2_CID_EXPOSURE_ABSOLUTE,arg1);
}

void MainWindow::on_AutoExpBiascomboBox_currentIndexChanged(int index)
{
    camParameter.set(V4L2_CID_AUTO_EXPOSURE_BIAS,index);
}

void MainWindow::on_WhiteBalanceAPcomboBox_currentIndexChanged(int index)
{
    camParameter.set(V4L2_CID_AUTO_N_PRESET_WHITE_BALANCE,index);
}

void MainWindow::on_ManualISOcheckBox_stateChanged(int arg1)
{
    if(arg1 > 0)
    {
        camParameter.set(V4L2_CID_ISO_SENSITIVITY_AUTO,1);
        ui->IsoSensitivitycomboBox->setEnabled(true);
    }
    else
    {
        camParameter.set(V4L2_CID_ISO_SENSITIVITY_AUTO,0);
        ui->IsoSensitivitycomboBox->setEnabled(false);
    }
}

void MainWindow::on_IsoSensitivitycomboBox_currentIndexChanged(int index)
{
    camParameter.set(V4L2_CID_ISO_SENSITIVITY,index);
}

void MainWindow::on_SceneModecomboBox_currentIndexChanged(int index)
{
    switch(index){
    case 0: index = 0; break;
    case 1: index = 8; break;
    case 2: index = 11; break;
    }
    camParameter.set(V4L2_CID_SCENE_MODE,index);
}

void MainWindow::on_ExposureMeteringcomboBox_currentIndexChanged(int index)
{
    camParameter.set(V4L2_CID_EXPOSURE_METERING,index);
}
