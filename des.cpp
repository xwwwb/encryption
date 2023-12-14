#include "des.h"
#include "ui_des.h"
#include <iostream>
#include <openssl/des.h>
#include <string>
DES::DES(QWidget *parent) : QWidget(parent), ui(new Ui::DES) {
  ui->setupUi(this);
  this->setWindowTitle("DES加密解密");
  connect(ui->pushButton, &QAbstractButton::clicked, this,
          &DES::handleDESEncode);
  connect(ui->pushButton_2, &QAbstractButton::clicked, this,
          &DES::handleDESDecode);
}

DES::~DES() { delete ui; }

QString DES::EncodeDES(QString input, QString keystring) {
  using namespace std;
  string input_ = input.toStdString();
  unsigned char *input__ = (unsigned char *)input_.c_str();
  string keystring_ = keystring.toStdString();
  unsigned char *keystring__ = (unsigned char *)keystring_.c_str();

  unsigned char *result = core(input__, keystring__, 1);

  return char2string(result);
}
QString DES::DecodeDES(QString input, QString keystring) {
  using namespace std;
  unsigned char *tmp = string2char(input);
  string keystring_ = keystring.toStdString();
  unsigned char *keystring__ = (unsigned char *)keystring_.c_str();
  unsigned char *result = core(tmp, keystring__, 0);
  delete[] tmp;
  return QString((char *)result);
}

// 1是加密 0是解密
unsigned char *DES::core(unsigned char *input, unsigned char *keystring,
                         int mode = 1) {

  DES_cblock key;
  DES_key_schedule key_schedule;

  // 生成一个 key
  DES_string_to_key((const char *)keystring, &key);
  if (DES_set_key_checked(&key, &key_schedule) != 0) {
    printf("convert to key_schedule failed.\n");
    return (unsigned char *)"convert to key_schedule failed.\n";
  }

  // 需要加密的字符串 input已经准备好了
  size_t len = (sizeof(input) + 7) / 8 * 8;
  unsigned char *output = new unsigned char[len + 1];
  // IV
  DES_cblock ivec;

  if (mode == 1) {
    // 加密
    memset((char *)&ivec, 0, sizeof(ivec));
    DES_ncbc_encrypt(input, output, sizeof(input), &key_schedule, &ivec,
                     DES_ENCRYPT);
    // 输出加密以后的内容

    return output;
  } else {
    // 解密
    memset((char *)&ivec, 0, sizeof(ivec));
    DES_ncbc_encrypt(input, output, len, &key_schedule, &ivec, DES_DECRYPT);
    return output;
  }
}

// 将char中的十进制数转成16进制字符串
QString DES::char2string(unsigned char *text) {
  using namespace std;
  string result;
  for (int i = 0; i < strlen((char *)text); i++) {
    string hex;
    char bit;
    int deci = text[i];
    do {
      if (deci % 16 < 10)
        bit = deci % 16 + '0';
      else
        bit = deci % 16 + 'A' - 10;
      hex.insert(hex.begin(), bit);
      deci /= 16;
    } while (deci);
    if (hex.length() < 2) {
      hex.insert(hex.begin(), '0');
    }
    result += hex;
  }
  return QString::fromStdString(result);
}

// 将16进制字符串转成十进制数字的数组
unsigned char *DES::string2char(QString text) {
  int length = text.length();
  unsigned char *result = new unsigned char[length / 2];
  using namespace std;
  for (int i = 0; i < length; i += 2) {
    char *tmp = new char[2];
    tmp[0] = text[i].toLatin1();
    tmp[1] = text[i + 1].toLatin1();
    int n = strtol(tmp, NULL, 16);
    result[i / 2] = n;
    delete[] tmp;
  }

  return result;
}

void DES::handleDESEncode() {
  QString text = ui->plainTextEdit->toPlainText();
  QString key = ui->plainTextEdit_3->toPlainText();
  ui->plainTextEdit_2->setPlainText(EncodeDES(text, key));
}

void DES::handleDESDecode() {
  QString text = ui->plainTextEdit_2->toPlainText();
  QString key = ui->plainTextEdit_3->toPlainText();

  ui->plainTextEdit->setPlainText(DecodeDES(text, key));
}
