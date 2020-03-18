#include "mainwindow.hh"
#include "./ui_mainwindow.h"
#include <QLabel>
#include <QSpinBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_canvas = qobject_cast<PaintWidget*>(ui->widget);
    setUpDock();
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

    QHBoxLayout* fontLayout = new QHBoxLayout;
    QLabel* fontLabel       = new QLabel("Font: ", dockParent);
    m_fontComboBox          = new BetterFontCB(dockParent);
    fontLayout->addWidget(fontLabel);
    fontLayout->addWidget(m_fontComboBox);
    topLayout->addLayout(fontLayout);
    m_canvas->setFont(m_fontComboBox->getFile(m_fontComboBox->currentIndex()));

    QHBoxLayout* sizeLayout = new QHBoxLayout;
    QLabel* sizeLabel       = new QLabel("Size: ", dockParent);
    QSpinBox* sizeSpinBox   = new QSpinBox(dockParent);
    sizeSpinBox->setMaximum(200);
    sizeSpinBox->setValue(20);
    m_canvas->setFontSize(20);
    sizeLayout->addWidget(sizeLabel);
    sizeLayout->addWidget(sizeSpinBox);
    topLayout->addLayout(sizeLayout);

    connect(sizeSpinBox,
            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            m_canvas,
            &PaintWidget::setFontSize);
    connect(m_fontComboBox,
            static_cast<void (BetterFontCB::*)(int)>(&BetterFontCB::currentIndexChanged),
            this,
            &MainWindow::fontChanged);

    dockParent->setLayout(topLayout);
    dock->setWidget(dockParent);
}

void
MainWindow::fontChanged(int index)
{
    m_canvas->setFont(m_fontComboBox->getFile(index));
}
