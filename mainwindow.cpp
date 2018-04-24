#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "nannbp.h"

NAnnBp bp;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    vector<int> layerNums = {2,5,3,1};
    bp.Init(layerNums);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void Learn(float i1, float i2, float o){

    vector<float> inputs = {i1,i2};
    vector<float> outputs = {o};

    bp.Learn(inputs,outputs);
}

void Ask(float i1, float i2){
    vector<float> inputs = {i1,i2};
    auto res = bp.Run(inputs);
    cout<<"I:";
    foreach(auto r , inputs){
        cout<<r<<",";
    }
    cout<<"\tO:";
    foreach(auto r , res){
        cout<<r<<",";
    }
    cout<<endl;
}

void MainWindow::on_btnGetAskTest_clicked()
{
    Ask(0,0);
    Ask(1,0);
    Ask(0,1);
    Ask(1,1);
}

void MainWindow::on_btnTeachTest_clicked()
{
    int n = 1000;
    while(n>0){
        Learn(0,0,0);
        Learn(0,1,0);
        Learn(1,0,0);
        Learn(1,1,1);
        n--;
    }
    ui->label->setText(QString::fromStdString(bp.Print()));
}

void MainWindow::on_btnTeachSumIn10_clicked()
{
    int n = 1000;
    while(n>0){
        for(int i = 0;i<5;i++){
            for(int j = 0;j<5;j++){
                Learn(i*0.1,j*0.1,(i+j)*0.1);
            }
        }
        n--;
    }
    qDebug()<<QString::fromStdString(bp.Print());
}

void MainWindow::on_btnAskSumIn10_clicked()
{
    for(int i = 0;i<5;i++){
        for(int j = 0;j<5;j++){
            Ask(i*0.1,j*0.1);
        }
    }
}
