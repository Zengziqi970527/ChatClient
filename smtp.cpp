#include "smtp.h"
Smtp::Smtp(QByteArray username, QByteArray pwd)
{
    if(username.contains("@163")){
        this->username = username;
        this->pwd = pwd;
    }
    else{

    }
}

Smtp::~Smtp()
{
    delete this->cSocket;
}

void Smtp::send(QByteArray recvaddr, QString subject, QString content)
{
    this->recvaddr = recvaddr;
    this->subject = subject;
    this->content = content;
    QByteArray usernametmp = this->username;
    QByteArray recvaddrtmp = this->recvaddr;
    cSocket = new QTcpSocket();
    this->cSocket->connectToHost("smtp.163.com",25,QTcpSocket::ReadWrite);
    this->cSocket->waitForConnected(1000);
    this->cSocket->waitForReadyRead(1000);
    recvdata = cSocket->readAll();
    qDebug()<<recvdata;
    this->cSocket->write("helo smtp.163.com\r\n");
    this->cSocket->waitForReadyRead(1000);
    recvdata = cSocket->readAll();
    this->cSocket->write("auth login\r\n");
    this->cSocket->waitForReadyRead(1000);
    recvdata = cSocket->readAll();
    qDebug()<<recvdata;
    this->cSocket->write(username.toBase64().append("\r\n"));
    this->cSocket->waitForReadyRead(1000);
    recvdata = cSocket->readAll();
    qDebug()<<username.toBase64();
    qDebug()<<recvdata;

    this->cSocket->write(pwd.toBase64().append("\r\n"));
    this->cSocket->waitForReadyRead(1000);
    recvdata = cSocket->readAll();
    qDebug()<<pwd.toBase64();
    qDebug()<<recvdata;

    this->cSocket->write(mailfrom.append(usernametmp.append(">\r\n")));
    this->cSocket->waitForReadyRead(1000);
    recvdata = cSocket->readAll();
    qDebug()<<recvdata;

    this->cSocket->write(rcptto.append(recvaddrtmp.append(">\r\n")));
    this->cSocket->waitForReadyRead(1000);
    recvdata = cSocket->readAll();
    qDebug()<<recvdata;

    this->cSocket->write("data\r\n");
    this->cSocket->waitForReadyRead(1000);
    recvdata = cSocket->readAll();
    usernametmp = this->username;
    recvaddrtmp = this->recvaddr;
    this->cSocket->write(prefrom.append(usernametmp.append("\r\n")));
    this->cSocket->write(preto.append(recvaddrtmp.append("\r\n")));
    this->cSocket->write(presubject.append(subject.toLocal8Bit().append("\r\n")));
    this->cSocket->write("\r\n");
    this->cSocket->write(content.toLocal8Bit().append("\r\n"));
    this->cSocket->write(".\r\n");
    this->cSocket->waitForReadyRead(1000);
    recvdata = cSocket->readAll();
    this->cSocket->write("quit\r\n");
    this->cSocket->waitForReadyRead(1000);
    recvdata = cSocket->readAll();
    qDebug()<<recvdata;
}
