#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    lab = ui->label;
    lab2 = ui->label_2;
    lab3 = ui->label_3;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    sendRequest();
}

void MainWindow::sendRequest(){
    QEventLoop eventLoop;
    QNetworkAccessManager manager;


    QObject::connect(&manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QNetworkRequest req( QUrl( QString("http://127.0.0.1/cppJsonTest.php") ) );
    QNetworkReply *reply = manager.get(req);

    eventLoop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        QString strReply = (QString)reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jsonObj = jsonResponse.object();

        userName = jsonObj["FirstName"].toString();
        userName.append(" ");
        userName.append(jsonObj["LastName"].toString());
        userName.append("\n");
        userName.append(QString::number(jsonObj["Age"].toInt()));
        lab->setText(userName);

        lab2->setText(jsonObj["Phone number"].toString());

        QJsonObject jsonAdd = jsonObj["Address"].toObject();
        address = "Street: ";
        address.append(jsonAdd["Street"].toString());
        address.append("\nCity: ");
        address.append(jsonAdd["City"].toString());
        address.append("\nCountry: ");
        address.append(jsonAdd["Country"].toString());
        lab3->setText(address);

        delete reply;
    }else{
        QMessageBox::information(this, "Error!", reply->errorString());
        qDebug() << "Failure" << reply->errorString();
        delete reply;
    }
}
