#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "betterfontcb.hh"
#include "paintwidget.hh"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    private:
    void setUpDock();
    void fontChanged(int index);

    private:
    Ui::MainWindow* ui;
    PaintWidget* m_canvas;
    BetterFontCB* m_fontComboBox;
};
#endif // MAINWINDOW_HH
