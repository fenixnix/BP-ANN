#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "nannbp.h"

NAnnBp bp;

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  vector<int> layerNums = {2,5,1};
  bp.Init(layerNums);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::Ask(QString json)
{
  QJsonDocument j = QJsonDocument::fromJson(json.toLatin1());
  vector<float> iArray;
  auto ijArray = j["I"].toArray();

  for(int i = 0;i<ijArray.size();i++){
      iArray.push_back(ijArray[i].toDouble());
    }
  auto result = bp.Run(iArray);
  QString r = json + " result:";
  for(int i = 0;i<result.size();i++){
      r += QString::number(result[i]) + ",";
    }
  ui->resultEdit->append(r);
}

void Learn(QString json){
  //qDebug()<<json;
  QJsonDocument j = QJsonDocument::fromJson(json.toLatin1());
  vector<float> iArray,oArray;
  auto ijArray = j["I"].toArray();
  auto ojArray = j["O"].toArray();

  for(int i = 0;i<ijArray.size();i++){
      iArray.push_back(ijArray[i].toDouble());
    }

  for(int i = 0;i<ojArray.size();i++){
      oArray.push_back(ojArray[i].toDouble());
    }
  bp.Learn(iArray,oArray);
}

void MainWindow::on_btnGetAskTest_clicked()
{
  Ask("{\"I\":[0,0]}");
  Ask("{\"I\":[0,1]}");
  Ask("{\"I\":[1,0]}");
  Ask("{\"I\":[1,1]}");
}

void MainWindow::on_btnTeachTest_clicked()
{
  for(int i = 0;i<1000;i++){
      Learn("{\"I\":[0,0],\"O\":[0]}");
      Learn("{\"I\":[0,1],\"O\":[0]}");
      Learn("{\"I\":[1,0],\"O\":[0]}");
      Learn("{\"I\":[1,1],\"O\":[1]}");
    }
}

void MainWindow::on_btnTeachSumIn10_clicked()
{
//  int n = 1000;
//  while(n>0){
//      for(int i = 0;i<5;i++){
//          for(int j = 0;j<5;j++){
//              Learn(i*0.1,j*0.1,(i+j)*0.1);
//            }
//        }
//      n--;
//    }
//  qDebug()<<QString::fromStdString(bp.Print());
}

void MainWindow::on_btnAskSumIn10_clicked()
{
//  for(int i = 0;i<5;i++){
//      for(int j = 0;j<5;j++){
//          Ask(i*0.1,j*0.1);
//        }
//    }
}

void MainWindow::on_iniBtn_clicked()
{
  auto p = ui->bpAnnParam->text().split(",");
  vector<int> params;
  foreach(QString t, p){
      params.push_back(t.toInt());
    }
  bp.Init(params);
  ui->resultEdit->append(QString::fromStdString(bp.Print()));
}

void MainWindow::on_trainBtn_clicked()
{
  auto jList = ui->trainEdit->toPlainText().split("\n");
  foreach(auto js, jList){
      Learn(js);
    }
}
/*
{"I":[0,0],"O":[0]}
{"I":[0,1],"O":[0]}
{"I":[1,0],"O":[0]}
{"I":[1,1],"O":[1]}
*/

void MainWindow::on_askBtn_clicked()
{
  Ask(ui->askEdit->text());
}
