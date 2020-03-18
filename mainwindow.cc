#include "mainwindow.hh"
#include "./ui_mainwindow.h"
#include "betterfontcb.hh"
#include <QLabel>
#include <QSpinBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setUpDock();

    m_canvas = qobject_cast<PaintWidget*>(ui->widget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void
MainWindow::setUpDock()
{
    QDockWidget* dock      = ui->dockWidget;
    QWidget* dockParent    = new QWidget(dock);
    QVBoxLayout* topLayout = new QVBoxLayout(dockParent);

    QHBoxLayout* fontLayout    = new QHBoxLayout;
    QLabel* fontLabel          = new QLabel("Font: ", dockParent);
    BetterFontCB* fontComboBox = new BetterFontCB(dockParent);
    fontLayout->addWidget(fontLabel);
    fontLayout->addWidget(fontComboBox);
    topLayout->addLayout(fontLayout);
    m_canvas->setFont(fontComboBox->getFile(fontComboBox->currentIndex()));

    QHBoxLayout* sizeLayout = new QHBoxLayout;
    QLabel* sizeLabel       = new QLabel("Size: ", dockParent);
    QSpinBox* sizeSpinBox   = new QSpinBox(dockParent);
    sizeSpinBox->setMaximum(200);
    sizeSpinBox->setValue(20);
    m_canvas->setFontSize(20);
    sizeLayout->addWidget(sizeLabel);
    sizeLayout->addWidget(sizeSpinBox);
    topLayout->addLayout(sizeLayout);

    dockParent->setLayout(topLayout);
    dock->setWidget(dockParent);
}
