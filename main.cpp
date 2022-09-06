/*
  Dialog101
  Copyright (C) 2019-2022 Anthony Tibbs <anthony@tibbs.ca>

  This program is free software; you can redistribute itand /or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA 02110 - 1301 USA.
*/

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
