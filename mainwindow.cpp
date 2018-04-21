#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "nannbp.h"

NLayer oLayer;
NANNBP bp;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    oLayer.RndInit(1,2);
    bp.Init(2,3,1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    vector<float> inputs;
    inputs.push_back(ui->doubleSpinBox->value());
    inputs.push_back(ui->doubleSpinBox_2->value());
    ui->doubleSpinBox_3->setValue(oLayer.Run(inputs)[0]);
}

void Learn(float i1, float i2, float o){
    vector<float> inputs;
    vector<float> outputs;

    inputs.push_back(i1);
    inputs.push_back(i2);
    outputs.push_back(o);
    oLayer.LearnOutput(inputs,outputs);
    bp.Learn(inputs,outputs);
}

void Ask(float i1, float i2){
    vector<float> inputs = {i1,i2};
    //auto res = oLayer.Run(inputs);
    auto res = bp.Run(inputs);
    cout<<"I:"<<i1<<","<<i2;
    cout<<"\tO:";
    foreach(auto r , res){
        cout<<r<<endl;
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    int n = 1000;
    while(n>0){
        Learn(0,0,0);
        Learn(0,1,1);
        Learn(1,0,1);
        Learn(1,1,0);
        n--;
    }
    //oLayer.Print();
    bp.Print();
}

void MainWindow::on_btnGetAskTest_clicked()
{
    Ask(0,0);
    Ask(1,0);
    Ask(0,1);
    Ask(1,1);
}
