#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>

#include <opencv2/opencv.hpp>

using namespace cv;

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


  void TestCellularAutomation1D();
  void TestCellularAutomation2D();

  Mat CA2D(Mat src);

private slots:

  void on_btnGetAskTest_clicked();

  void on_btnTeachTest_clicked();

  void on_iniBtn_clicked();

  void on_trainBtn_clicked();

  void on_askBtn_clicked();

  void on_actionTest_2D_triggered();

  void on_actionLearn_Conway_LifeGame_triggered();

private:
  Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
