#include "client.h"
#include "ui_client.h"
#include<QDebug>
#include<QHostAddress>
#include<QMessageBox>
#include<QSqlDatabase>
#include<QSqlQuery>
Client::Client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Client)
{
    cSocket = new QTcpSocket(this);
    ui->setupUi(this);
    this->setWindowTitle("ChatClient");
    ui->disconnBtn->setEnabled(false);
    connect(cSocket,&QTcpSocket::connected,this,[=](){
        ui->msgHisLine->append("连接服务器成功!");
        QString msg = ui->username->text()+"进入服务器!";
        cSocket->write(msg.toUtf8());
    });
    connect(cSocket,&QTcpSocket::disconnected,this,[=](){
        ui->msgHisLine->append("已退出服务器!");
    });
    connect(cSocket,&QTcpSocket::readyRead,[=](){
        QByteArray msglist = cSocket->readAll();
        ui->msgHisLine->append(msglist);
    });
}

Client::~Client()
{
    delete ui;
}

void Client::on_quitLoginBtn_clicked()
{
    cSocket->close();
    emit this->back();
}

void Client::getusername(QString username)
{
    QSqlDatabase db = QSqlDatabase::database("conn");
    QSqlQuery *query = new QSqlQuery(db);
    QString sql = QString("select * from userinfo where username = '%1'").arg(username);
    query->exec(sql);
    while (query->next()) {
        fileinfo = QFileInfo(query->value("usericon").toString());
        ui->iconLable->setPixmap(QPixmap(fileinfo.absoluteFilePath()));
        ui->iconLable->setScaledContents(true);
        ui->username->setText(username);
    }
}

void Client::on_connServerBtn_clicked()
{
    if(ui->portLine->text().isNull()){
        QMessageBox::warning(this,"Warning","请输入端口号!");
    }
    else{
        cSocket->connectToHost(QHostAddress("192.168.31.53"),ui->portLine->text().toInt());
        ui->portLine->setEnabled(false);
        ui->connServerBtn->setEnabled(false);
        ui->disconnBtn->setEnabled(true);
    }
}


void Client::on_disconnBtn_clicked()
{
    QString msg = ui->username->text()+"退出服务器!";
    cSocket->write(msg.toUtf8());
    cSocket->close();
    ui->portLine->setEnabled(true);
    ui->connServerBtn->setEnabled(true);
    ui->disconnBtn->setEnabled(false);
}


void Client::on_sendMsgBtn_clicked()
{
    if(ui->msgLine->text().isNull()){
        QMessageBox::warning(this,"Warning","发送信息不可为空!");
    }
    else{
        QString msg = ui->username->text()+": "+ui->msgLine->text();
        cSocket->write(msg.toUtf8());
        ui->msgHisLine->append(msg);
        ui->msgLine->clear();
    }
}

