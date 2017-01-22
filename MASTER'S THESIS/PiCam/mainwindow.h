#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "im2label.h"
#include "picam.h"

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
    //Display video frame in player UI
    void updatePlayerUI(QImage img);

    void on_BrightSlider_sliderMoved(int position);

    void on_BrightspinBox_valueChanged(const QString &arg1);

    void on_ContrSlider_valueChanged(int value);

    void on_ContrspinBox_valueChanged(const QString &arg1);

    void on_SaturationSlider_sliderMoved(int position);

    void on_SaturationspinBox_valueChanged(const QString &arg1);

    void on_RedBalanceSlider_sliderMoved(int position);

    void on_RedBalancespinBox_valueChanged(const QString &arg1);

    void on_BlueBalancehorizontalSlider_sliderMoved(int position);

    void on_BlueBalancespinBox_valueChanged(const QString &arg1);

    void on_ColorEffectscomboBox_currentIndexChanged(int index);

    void on_ExposureTimehorizontalSlider_sliderMoved(int position);

    void on_ManualExposurecheckBox_stateChanged(int arg1);

    void on_ExposureTimespinBox_valueChanged(int arg1);

    void on_AutoExpBiascomboBox_currentIndexChanged(int index);

    void on_WhiteBalanceAPcomboBox_currentIndexChanged(int index);

    void on_ManualISOcheckBox_stateChanged(int arg1);

    void on_IsoSensitivitycomboBox_currentIndexChanged(int index);

    void on_SceneModecomboBox_currentIndexChanged(int index);

    void on_ExposureMeteringcomboBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    Im2Label *myIm2label;
    Picam camParameter;
};

#endif // MAINWINDOW_H
