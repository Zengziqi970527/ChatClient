#ifndef SMTP_H
#define SMTP_H
#include<QByteArray>
#include<QTcpSocket>
class Smtp
{
public:
    Smtp(QByteArray username,QByteArray pwd);
    ~Smtp();
    void send(QByteArray recvaddr,QString subject,QString content);
private:
    QTcpSocket *cSocket;
    QByteArray username;
    QByteArray pwd;
    QByteArray recvaddr;
    QByteArray mailfrom = "mail from:<";
    QByteArray rcptto = "rcpt to:<";
    QByteArray prefrom = "from:";
    QByteArray preto = "to:";
    QByteArray presubject = "subject:";
    QString subject;
    QString content;
    QByteArray recvdata;
};

#endif // SMTP_H
