#ifndef MD5_H
#define MD5_H

#include <QWidget>

namespace Ui {
class MD5;
}

class MD5 : public QWidget
{
    Q_OBJECT

public:
    explicit MD5(QWidget *parent = nullptr);
    ~MD5();

private:
    Ui::MD5 *ui;

private slots:
    void handleTextChange(const QString &text);
};

#endif // MD5_H
