#include "md5.h"

#include <QCryptographicHash>

#include "ui_md5.h"

MD5::MD5(QWidget *parent) : QWidget(parent), ui(new Ui::MD5) {
  ui->setupUi(this);
  this->setWindowTitle("MD5");
  connect(ui->lineEdit, &QLineEdit::textChanged, this, &MD5::handleTextChange);
}

MD5::~MD5() { delete ui; }

void MD5::handleTextChange(const QString &text) {
  if (text.length() > 0) {
    QCryptographicHash *handler =
        new QCryptographicHash(QCryptographicHash::Md5);
    QByteArray _text = text.toUtf8();
    handler->addData(_text);
    ui->lineEdit_2->setText(handler->result().toHex());
    delete handler;
  } else {
    ui->lineEdit_2->setText("");
  }
}
