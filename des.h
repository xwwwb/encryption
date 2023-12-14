#ifndef DES_H
#define DES_H

#include <QWidget>

namespace Ui {
class DES;
}

class DES : public QWidget
{
    Q_OBJECT

public:
    explicit DES(QWidget *parent = nullptr);
    ~DES();

private:
    Ui::DES *ui;
    unsigned char* core(unsigned char*,unsigned char*,int);

    QString char2string(unsigned char*);
    unsigned char* string2char(QString);
    QString DecodeDES(QString ,QString );
    QString EncodeDES(QString ,QString );
private slots:
    void handleDESEncode();
    void handleDESDecode();
};

#endif // DES_H

