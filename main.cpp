#include <QApplication>

#include "widget.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QCoreApplication::setApplicationName("加密解密的应用");
  QCoreApplication::setOrganizationName("xwwwb");
  Widget w;
  w.show();
  return a.exec();
}
