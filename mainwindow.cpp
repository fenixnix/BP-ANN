#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "nannbp.h"

NANNBP bp;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    bp.Init(2,3,1);
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
        Learn(0,1,1);
        Learn(1,0,1);
        Learn(1,1,0);
        n--;
    }
    bp.Print();
}
