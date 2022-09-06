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
#include <QtWidgets/QFormLayout>
#include <QTranslator>
#include <qmessagebox.h>
#include <iostream>
#include <qinputdialog.h>
#include <qstandardpaths.h>
#include <qfile.h>

MyDialog::MyDialog(QWidget *parent) : QDialog(parent)
{
  QGridLayout *layout = new QGridLayout;
  layout->addWidget(createQ1group(), 0, 0, 1, 2);
  layout->addWidget(createQ2group(), 1, 0);
  layout->addWidget(createQ3group(), 1, 1);
  layout->addWidget(createQ4group(), 2, 0);
  layout->addWidget(createQ5group(), 2, 1);
  layout->addWidget(createQ6group(), 3, 0);

  saveButton = new QPushButton(tr("Save your answers"), this);
  saveButton->setStyleSheet("padding: 20px;");
  connect(saveButton, &QPushButton::released, this, &MyDialog::handleSaveButtonPressed);

  layout->addWidget(saveButton, 3, 1, Qt::AlignBottom | Qt::AlignRight);

  setLayout(layout);

  q1_editbox->setFocus();


}

MyDialog::~MyDialog()
{
  delete saveButton;
  delete q6_editbox;
  delete q5_combobox;
  for (auto p : q4_options) delete p;
  for (auto p : q3_options) delete p;
  delete q2_group;
  for (auto p : q2_options) delete p;
  delete q1_editbox;
}

QGroupBox* MyDialog::createQ1group()
{
  q1_editbox = new QLineEdit;
  QFormLayout* layout = new QFormLayout;
  layout->addRow(tr("Response:"), q1_editbox);

  QGroupBox* group = new QGroupBox(tr("Give one example of a toggle command that you learned this week"));
  group->setLayout(layout);
  return group;
}

QGroupBox* MyDialog::createQ2group()
{
  q2_options.push_back(new QRadioButton(tr("Insert+F12")));
  q2_options.push_back(new QRadioButton(tr("Insert+F12 twice quickly")));
  q2_options.push_back(new QRadioButton(tr("Insert+T")));

  q2_group = new QButtonGroup();
  
  QVBoxLayout* layout = new QVBoxLayout;
  for (QRadioButton* btn : q2_options) {
    layout->addWidget(btn);
    q2_group->addButton(btn);
  }

  QGroupBox* group = new QGroupBox(tr("What is the Jaws command to read the time on the system tray?"));
  group->setLayout(layout);
  return group;
}

QGroupBox* MyDialog::createQ3group()
{
  q3_options.push_back(new QCheckBox(tr("Settings Centre")));
  q3_options.push_back(new QCheckBox(tr("Quick Settings")));
  q3_options.push_back(new QCheckBox(tr("Task bar")));

  QVBoxLayout* layout = new QVBoxLayout;
  for (QCheckBox* btn : q3_options) {
    layout->addWidget(btn);
  }

  QGroupBox* group = new QGroupBox(tr("In which of the following places can you change Jaws settings for a specific program?"));
  group->setLayout(layout);
  return group;
}

QGroupBox* MyDialog::createQ4group()
{
  q4_options.push_back(new QCheckBox(tr("Restore settings when JAWS restarts")));
  q4_options.push_back(new QCheckBox(tr("Restore settings when focus changes")));
  q4_options.push_back(new QCheckBox(tr("Save the settings permanently")));

  QVBoxLayout* layout = new QVBoxLayout;
  for (QCheckBox* btn : q4_options) {
    layout->addWidget(btn);
  }

  QGroupBox* group = new QGroupBox(tr("In quick settings, which of the following is possible?"));
  group->setLayout(layout);
  return group;
}

QGroupBox* MyDialog::createQ5group()
{
  q5_combobox = new QComboBox();
  q5_combobox->addItem(tr("Insert+Up Arrow or Insert+I"));
  q5_combobox->addItem(tr("Insert+Down Arrow or Insert+K"));
  q5_combobox->addItem(tr("Tab key"));
  q5_combobox->setEditable(true);
  q5_combobox->setCurrentText("");

  QVBoxLayout* layout = new QVBoxLayout;
  layout->addWidget(q5_combobox, 0, Qt::AlignTop);
  
  QGroupBox* group = new QGroupBox(tr("What is the command to read the current line with JAWS?"));
  group->setLayout(layout);
  
  return group;
}

QGroupBox* MyDialog::createQ6group()
{
  q6_editbox = new QLineEdit;
  QFormLayout* layout = new QFormLayout;
  layout->addRow(tr("Response:"), q6_editbox);

  QGroupBox* group = new QGroupBox(tr("What Jaws command will read the title bar to confirm your location?"));
  group->setLayout(layout);
  return group;
}

void MyDialog::handleSaveButtonPressed()
{
  QString report;
  QTextStream rs(&report);

  if (q1_editbox->text().isEmpty()) {
    QMessageBox::warning(this, tr("Information Incomplete"), tr("You have not answered all of the questions!"), QMessageBox::Ok);
    q1_editbox->setFocus();
    return;
  }

  rs << "Q1: " << q1_editbox->text() << Qt::endl << Qt::endl;
    
  QAbstractButton* sel = q2_group->checkedButton();
  if (!sel) {
    QMessageBox::warning(this, tr("Information Incomplete"), tr("You have not answered all of the questions!"), QMessageBox::Ok);
    q2_options[0]->setFocus();
    return;
  }
  
  rs << "Q2: " << sel->text() << Qt::endl << Qt::endl;

  rs << "Q3: " << Qt::endl;
  for (QCheckBox *option : q3_options) {
    if (option->isChecked())
      rs << "  - Checked: ";
    else
      rs << "  - Not checked: ";

    rs << option->text() << Qt::endl;
  }
  rs << Qt::endl;
  
  rs << "Q4: " << Qt::endl;
  for (QCheckBox* option : q4_options) {
    if (option->isChecked())
      rs << "  - Checked: ";
    else
      rs << "  - Not checked: ";

    rs << option->text() << Qt::endl;
  }
  rs << Qt::endl;

  if (q5_combobox->currentText().isEmpty()) {
    QMessageBox::warning(this, tr("Information Incomplete"), tr("You have not answered all of the questions!"), QMessageBox::Ok);
    q5_combobox->setFocus();
    return;
  }

  rs << "Q5: " << q5_combobox->currentText() << Qt::endl << Qt::endl;

  if (q6_editbox->text().isEmpty()) {
    QMessageBox::warning(this, tr("Information Incomplete"), tr("You have not answered all of the questions!"), QMessageBox::Ok);
    q6_editbox->setFocus();
    return;
  }

  rs << "Q6: " << q6_editbox->text() << Qt::endl << Qt::endl;

  QString defaultUsername = qEnvironmentVariable("USER");
  if (defaultUsername.isEmpty()) {
    defaultUsername = qEnvironmentVariable("USERNAME");
  }

  bool ok = false;
  QString name = QInputDialog::getText(
    this,
    tr("Save your answers"),
    "Please enter your name:",
    QLineEdit::Normal,
    defaultUsername,
    &ok
  );

  if (!ok || name.isEmpty())
    return;

  if (ok) {
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString filename = desktopPath + "\\Dialog101-Responses(" + name + ").txt";
    QFile f(filename);
    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)) {
      QMessageBox::warning(
        this, 
        tr("Save your answers"), 
        tr("Unable to save your answers to '%1'. Please ask for assistance.").arg(filename)
      );
      
      return;
    }
    QTextStream ft(&f);
    ft << report;
    f.close();

    
    accept();
  }
}