#include "widget.h"
#include <QMessageBox>

#include "./ui_widget.h"
#include "des.h"
#include "md5.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);
  this->setWindowTitle("数据加密及解密");
  connect(ui->pushButton, &QAbstractButton::clicked, this,
          &Widget::onMd5Clicked, Qt::UniqueConnection);
  connect(ui->pushButton_2, &QAbstractButton::clicked, this,
          &Widget::onDesClicked, Qt::UniqueConnection);
  connect(ui->pushButton_4, &QAbstractButton::clicked, this,
          &Widget::onAboutClicked, Qt::UniqueConnection);
}

Widget::~Widget() { delete ui; }

void Widget::onMd5Clicked() {
  MD5 *handleMD5 = new MD5();
  handleMD5->show();
}

void Widget::onDesClicked() {
  DES *handleDES = new DES();
  handleDES->show();
}
void Widget::onAboutClicked() {
  QMessageBox::about(NULL, "关于", "由计科2004 徐文博542010010220开发");
}
