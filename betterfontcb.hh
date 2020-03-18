#ifndef BETTERFONTCB_H
#define BETTERFONTCB_H

#include <QComboBox>

class BetterFontCB : public QComboBox {
    Q_OBJECT
    public:
    BetterFontCB(QWidget* parent = nullptr);
    QString getFile(int index);

    private:
    QVector<QString> m_fontNames;
    QVector<QString> m_fontFiles;
};

#endif // BETTERFONTCB_H
