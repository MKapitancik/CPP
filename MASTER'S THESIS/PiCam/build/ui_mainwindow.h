/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *img;
    QTabWidget *tabWidget;
    QWidget *tab;
    QSpinBox *RedBalancespinBox;
    QComboBox *SceneModecomboBox;
    QComboBox *ColorEffectscomboBox;
    QLabel *label_6;
    QCheckBox *ManualISOcheckBox;
    QSpinBox *BrightspinBox;
    QSpinBox *ExposureTimespinBox;
    QSpinBox *ContrspinBox;
    QSlider *BrightSlider;
    QSlider *ExposureTimehorizontalSlider;
    QLabel *label_3;
    QLabel *label_9;
    QLabel *label_10;
    QComboBox *AutoExpBiascomboBox;
    QLabel *label_4;
    QSlider *BlueBalancehorizontalSlider;
    QLabel *label_2;
    QSlider *ContrSlider;
    QSlider *RedBalanceSlider;
    QComboBox *WhiteBalanceAPcomboBox;
    QComboBox *ExposureMeteringcomboBox;
    QSpinBox *BlueBalancespinBox;
    QCheckBox *ManualExposurecheckBox;
    QLabel *label_7;
    QComboBox *IsoSensitivitycomboBox;
    QSpinBox *SaturationspinBox;
    QLabel *label_5;
    QSlider *SaturationSlider;
    QLabel *label;
    QLabel *label_8;
    QPushButton *DefaultSettingsBtn;
    QWidget *tab_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1300, 650);
        MainWindow->setMaximumSize(QSize(1500, 650));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        img = new QLabel(centralWidget);
        img->setObjectName(QStringLiteral("img"));
        img->setGeometry(QRect(490, 0, 800, 600));
        img->setMaximumSize(QSize(800, 600));
        img->setStyleSheet(QStringLiteral(""));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 0, 471, 461));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        RedBalancespinBox = new QSpinBox(tab);
        RedBalancespinBox->setObjectName(QStringLiteral("RedBalancespinBox"));
        RedBalancespinBox->setGeometry(QRect(170, 210, 50, 31));
        RedBalancespinBox->setMinimum(1);
        RedBalancespinBox->setMaximum(7999);
        SceneModecomboBox = new QComboBox(tab);
        SceneModecomboBox->setObjectName(QStringLiteral("SceneModecomboBox"));
        SceneModecomboBox->setGeometry(QRect(260, 340, 141, 29));
        ColorEffectscomboBox = new QComboBox(tab);
        ColorEffectscomboBox->setObjectName(QStringLiteral("ColorEffectscomboBox"));
        ColorEffectscomboBox->setGeometry(QRect(20, 340, 151, 29));
        label_6 = new QLabel(tab);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(50, 310, 101, 21));
        ManualISOcheckBox = new QCheckBox(tab);
        ManualISOcheckBox->setObjectName(QStringLiteral("ManualISOcheckBox"));
        ManualISOcheckBox->setGeometry(QRect(250, 250, 141, 26));
        BrightspinBox = new QSpinBox(tab);
        BrightspinBox->setObjectName(QStringLiteral("BrightspinBox"));
        BrightspinBox->setGeometry(QRect(170, 30, 50, 31));
        BrightspinBox->setMaximum(100);
        BrightspinBox->setValue(50);
        ExposureTimespinBox = new QSpinBox(tab);
        ExposureTimespinBox->setObjectName(QStringLiteral("ExposureTimespinBox"));
        ExposureTimespinBox->setGeometry(QRect(410, 30, 50, 31));
        ExposureTimespinBox->setMinimum(1);
        ExposureTimespinBox->setMaximum(10000);
        ContrspinBox = new QSpinBox(tab);
        ContrspinBox->setObjectName(QStringLiteral("ContrspinBox"));
        ContrspinBox->setGeometry(QRect(170, 90, 50, 31));
        ContrspinBox->setMaximum(100);
        BrightSlider = new QSlider(tab);
        BrightSlider->setObjectName(QStringLiteral("BrightSlider"));
        BrightSlider->setGeometry(QRect(10, 30, 160, 26));
        BrightSlider->setMinimum(0);
        BrightSlider->setMaximum(100);
        BrightSlider->setSliderPosition(50);
        BrightSlider->setOrientation(Qt::Horizontal);
        ExposureTimehorizontalSlider = new QSlider(tab);
        ExposureTimehorizontalSlider->setObjectName(QStringLiteral("ExposureTimehorizontalSlider"));
        ExposureTimehorizontalSlider->setEnabled(false);
        ExposureTimehorizontalSlider->setGeometry(QRect(250, 30, 160, 26));
        ExposureTimehorizontalSlider->setMinimum(1);
        ExposureTimehorizontalSlider->setMaximum(10000);
        ExposureTimehorizontalSlider->setOrientation(Qt::Horizontal);
        label_3 = new QLabel(tab);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(60, 130, 81, 21));
        label_9 = new QLabel(tab);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(277, 310, 101, 21));
        label_10 = new QLabel(tab);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(240, 120, 181, 21));
        AutoExpBiascomboBox = new QComboBox(tab);
        AutoExpBiascomboBox->setObjectName(QStringLiteral("AutoExpBiascomboBox"));
        AutoExpBiascomboBox->setGeometry(QRect(260, 90, 141, 29));
        label_4 = new QLabel(tab);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(50, 190, 101, 21));
        BlueBalancehorizontalSlider = new QSlider(tab);
        BlueBalancehorizontalSlider->setObjectName(QStringLiteral("BlueBalancehorizontalSlider"));
        BlueBalancehorizontalSlider->setGeometry(QRect(10, 270, 160, 26));
        BlueBalancehorizontalSlider->setMinimum(1);
        BlueBalancehorizontalSlider->setMaximum(7999);
        BlueBalancehorizontalSlider->setOrientation(Qt::Horizontal);
        label_2 = new QLabel(tab);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(60, 60, 68, 21));
        ContrSlider = new QSlider(tab);
        ContrSlider->setObjectName(QStringLiteral("ContrSlider"));
        ContrSlider->setGeometry(QRect(10, 90, 160, 26));
        ContrSlider->setMinimum(0);
        ContrSlider->setMaximum(100);
        ContrSlider->setSliderPosition(50);
        ContrSlider->setOrientation(Qt::Horizontal);
        RedBalanceSlider = new QSlider(tab);
        RedBalanceSlider->setObjectName(QStringLiteral("RedBalanceSlider"));
        RedBalanceSlider->setGeometry(QRect(10, 210, 160, 26));
        RedBalanceSlider->setMinimum(1);
        RedBalanceSlider->setMaximum(7999);
        RedBalanceSlider->setOrientation(Qt::Horizontal);
        WhiteBalanceAPcomboBox = new QComboBox(tab);
        WhiteBalanceAPcomboBox->setObjectName(QStringLiteral("WhiteBalanceAPcomboBox"));
        WhiteBalanceAPcomboBox->setGeometry(QRect(260, 220, 141, 29));
        ExposureMeteringcomboBox = new QComboBox(tab);
        ExposureMeteringcomboBox->setObjectName(QStringLiteral("ExposureMeteringcomboBox"));
        ExposureMeteringcomboBox->setGeometry(QRect(260, 150, 141, 29));
        BlueBalancespinBox = new QSpinBox(tab);
        BlueBalancespinBox->setObjectName(QStringLiteral("BlueBalancespinBox"));
        BlueBalancespinBox->setGeometry(QRect(170, 270, 50, 31));
        BlueBalancespinBox->setMinimum(1);
        BlueBalancespinBox->setMaximum(7999);
        ManualExposurecheckBox = new QCheckBox(tab);
        ManualExposurecheckBox->setObjectName(QStringLiteral("ManualExposurecheckBox"));
        ManualExposurecheckBox->setGeometry(QRect(250, 0, 161, 26));
        label_7 = new QLabel(tab);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(260, 60, 141, 21));
        IsoSensitivitycomboBox = new QComboBox(tab);
        IsoSensitivitycomboBox->setObjectName(QStringLiteral("IsoSensitivitycomboBox"));
        IsoSensitivitycomboBox->setEnabled(false);
        IsoSensitivitycomboBox->setGeometry(QRect(260, 280, 141, 29));
        SaturationspinBox = new QSpinBox(tab);
        SaturationspinBox->setObjectName(QStringLiteral("SaturationspinBox"));
        SaturationspinBox->setGeometry(QRect(170, 150, 50, 31));
        SaturationspinBox->setMaximum(100);
        label_5 = new QLabel(tab);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(50, 250, 101, 21));
        SaturationSlider = new QSlider(tab);
        SaturationSlider->setObjectName(QStringLiteral("SaturationSlider"));
        SaturationSlider->setGeometry(QRect(10, 150, 160, 26));
        SaturationSlider->setMaximum(100);
        SaturationSlider->setOrientation(Qt::Horizontal);
        label = new QLabel(tab);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 10, 68, 21));
        label_8 = new QLabel(tab);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(240, 190, 191, 21));
        DefaultSettingsBtn = new QPushButton(tab);
        DefaultSettingsBtn->setObjectName(QStringLiteral("DefaultSettingsBtn"));
        DefaultSettingsBtn->setGeometry(QRect(140, 380, 151, 31));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tabWidget->addTab(tab_2, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1300, 27));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        img->setText(QString());
        label_6->setText(QApplication::translate("MainWindow", "Color Effects", 0));
        ManualISOcheckBox->setText(QApplication::translate("MainWindow", "Manual ISO", 0));
        label_3->setText(QApplication::translate("MainWindow", "Saturation", 0));
        label_9->setText(QApplication::translate("MainWindow", "Scene Mode", 0));
        label_10->setText(QApplication::translate("MainWindow", "Exposure Metering Mode", 0));
        label_4->setText(QApplication::translate("MainWindow", "Red Balance", 0));
        label_2->setText(QApplication::translate("MainWindow", "Contrast", 0));
        ManualExposurecheckBox->setText(QApplication::translate("MainWindow", "Manual Exposure", 0));
        label_7->setText(QApplication::translate("MainWindow", "Auto Exposure Bias", 0));
        label_5->setText(QApplication::translate("MainWindow", "Blue Balance", 0));
        label->setText(QApplication::translate("MainWindow", "Brightness", 0));
        label_8->setText(QApplication::translate("MainWindow", "White Balance Auto Preset", 0));
        DefaultSettingsBtn->setText(QApplication::translate("MainWindow", "Default Settings", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Camp Parameters", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Preprocesing", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
