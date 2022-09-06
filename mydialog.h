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
