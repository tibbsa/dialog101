#include "mydialog.h"
#include <qcoreapplication.h>
#include <QtWidgets/QApplication>
#include <qtranslator.h>
#include <qinputdialog.h>
#include <qmessagebox.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QLocale locale;

    QStringList items;
    items << QObject::tr("French") << QObject::tr("English");

    bool ok;
    QString language = QInputDialog::getItem(
      nullptr, 
      QObject::tr("Select your language"), 
      QObject::tr("Language:"), 
      items, 
      0, 
      false, 
      &ok);

    if (!ok)
      return 1;


    if (!language.compare(QObject::tr("French"))) {
      QString langPath = QApplication::applicationDirPath().append("/Dialog101_fr-CA.qm");

      QTranslator* translator = new QTranslator;
      if (translator->load(langPath)) {
        QCoreApplication::installTranslator(translator);
      }
    }

    MyDialog w;
    w.show();
    return a.exec();
}
