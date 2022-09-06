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

#pragma once

#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupbox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QCheckbox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QPushButton>
#include <qbuttongroup.h>

class MyDialog : public QDialog
{
    Q_OBJECT

public:
    MyDialog(QWidget *parent = nullptr);
    ~MyDialog();

private slots:
  void handleSaveButtonPressed();

private:
  QGroupBox* createQ1group();
  QGroupBox* createQ2group();
  QGroupBox* createQ3group();
  QGroupBox* createQ4group();
  QGroupBox* createQ5group();
  QGroupBox* createQ6group();

  QLineEdit* q1_editbox;
  QButtonGroup* q2_group;
  std::vector<QRadioButton*> q2_options;
  std::vector<QCheckBox*> q3_options;
  std::vector<QCheckBox*> q4_options;
  QComboBox* q5_combobox;
  QLineEdit* q6_editbox;
  QPushButton* saveButton;

};
