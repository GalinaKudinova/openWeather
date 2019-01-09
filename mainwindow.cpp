#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    netManager=new QNetworkAccessManager(this);
    connect(netManager, SIGNAL(finished(QNetworkReply*)),
            this,SLOT(replyFinished(QNetworkReply*)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Get_clicked()
{
    QString qsTemp = ui->lineEdit_adress->text();
    ui->textBrowser->append("URL:"+qsTemp);
    QUrl adress;
    //adress.setUrl("http://qt-project.org");
    adress.setUrl("http://samples.openweathermap.org/data/2.5/weather?q=Tallinn&appid=399269c624268cee650d57493b1e0835");


    netManager->get(QNetworkRequest(adress));
}

void MainWindow::replyFinished(QNetworkReply *reply)
{
   ui->textBrowser->append("We got replay");
   qDebug()<<"Reply from URL "<<reply->url().toString();
   if(reply->error()!=QNetworkReply::NoError){
       qWarning()<<"Error no"<<reply->error()<<"for url:"<< reply->url();
       qDebug()<<"Request failed, "<<reply->errorString();
       qDebug()<< "Headers:"<< reply->rawHeaderList()<<"connect"<<reply->readAll();
       return;
   }

   qDebug()<<"reply from URL"<<reply->url().toString();
   //QString qsTemp=reply->readAll();
   //ui->textBrowser->append(qsTemp);
}
