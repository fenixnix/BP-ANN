#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "nannbp.h"
#include "cellularautomation1d.h"
#include "cellularautomation2d.h"
#include "int2binary.h"

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

void MainWindow::TestCellularAutomation1D()
{
  vector<int> layerNums = {3,5,1};
  bp.Init(layerNums);
  CellularAutomation1D ca;
  ca.Init(18);
  for(int i = 0;i<10000;i++){
      for(int j = 0;j<8;j++){
          bp.Learn(Int2Bin::Int2BinFloat(j),vector<float>{(float)ca.RunCell(j)});
        }
    }
  qDebug()<<"result:";
  for(int j = 0;j<8;j++){
      qDebug()<<(bp.Run(Int2Bin::Int2BinFloat(j))[0]>0.5?1:0);
    }
}

void MainWindow::TestCellularAutomation2D()
{
  bp.Init(vector<int>{9,36,18,1});
  CellularAutomation2D ca;
  ca.Init(vector<int>{2,3},vector<int>{3});
  for(int i = 0;i<1000;i++){
      for(int j = 0;j<512;j++){
          float caVal = ca.RunCell(Int2Bin::Int2BinFloat(j,9));
          bp.Learn(Int2Bin::Int2BinFloat(j,9),
                   vector<float>{caVal});
        }
    }
  qDebug()<<"Learn CA s23b3 Result:";
  int falseCnt = 0;
  for(int j = 0;j<512;j++){
      float bpVal = bp.Run(Int2Bin::Int2BinFloat(j,9))[0];
      float caVal = ca.RunCell(Int2Bin::Int2BinFloat(j,9));
      if(abs(bpVal-caVal)>0.05){
          falseCnt++;
        }
    }
  qDebug()<<"false Rate:"<<(float)falseCnt/512.0f<<"*"<<falseCnt;
}

inline int roundVal(int v, int T){
  return (v+T)%T;
}

float GetPixelVal(Mat src, int x, int y){
  int rx = roundVal(x,src.cols);
  int ry = roundVal(y,src.rows);
  return src.at<float>(ry,rx);
}

vector<float> GetPixelGrid(Mat src, int x, int y){
  vector<float> datas;
  datas.push_back(GetPixelVal(src,x-1,y-1));
  datas.push_back(GetPixelVal(src,x,y-1));
  datas.push_back(GetPixelVal(src,x+1,y-1));
  datas.push_back(GetPixelVal(src,x-1,y));
  datas.push_back(GetPixelVal(src,x,y));
  datas.push_back(GetPixelVal(src,x+1,y));
  datas.push_back(GetPixelVal(src,x-1,y+1));
  datas.push_back(GetPixelVal(src,x,y+1));
  datas.push_back(GetPixelVal(src,x+1,y+1));
  return datas;
}

Mat MainWindow::CA2D(Mat src)
{
  Mat next = src;
  for (int y = 0; y < src.rows; y++)
    {
      for (int x = 0; x < src.cols; x++)
        {
          next.at<float>(y,x) = bp.Run(GetPixelGrid(src,x,y))[0];
        }
    }

  return next;
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



void MainWindow::on_actionTest_2D_triggered()
{
  RNG rng(123);
  Mat src = Mat(64,64,CV_32F,Scalar::all(0));
  rng.fill(src,RNG::NORMAL,0,1.0);
  imshow("CA2D",src);

  int k = -1;
  while(k == -1){
      src = CA2D(src);
      Mat large;
      cv::resize(src,large,Size(src.cols*8,src.rows*8),0,0,cv::INTER_NEAREST);
      imshow("CA2D",large);
      k = waitKey(100);
    }
}

void MainWindow::on_actionLearn_Conway_LifeGame_triggered()
{
  TestCellularAutomation2D();
}
