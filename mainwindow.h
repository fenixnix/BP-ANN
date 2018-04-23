#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:

  void on_btnGetAskTest_clicked();

  void on_btnTeachTest_clicked();

  void on_btnTeachSumIn10_clicked();

  void on_btnAskSumIn10_clicked();

private:
  Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
