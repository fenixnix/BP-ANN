#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  void Ask(QString json);

private slots:

  void on_btnGetAskTest_clicked();

  void on_btnTeachTest_clicked();

  void on_btnTeachSumIn10_clicked();

  void on_btnAskSumIn10_clicked();

  void on_iniBtn_clicked();

  void on_trainBtn_clicked();

  void on_askBtn_clicked();

private:
  Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
