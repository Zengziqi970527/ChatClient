#ifndef CLIENT_H
#define CLIENT_H
#include<QSqlQuery>
#include <QWidget>
#include<QTcpSocket>
#include<QFileInfo>
namespace Ui {
class Client;
}

class Client : public QWidget
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = nullptr);
    ~Client();
public:
    QFileInfo fileinfo;
signals:
    void back();
public slots:
    void getusername(QString);
private slots:
    void on_quitLoginBtn_clicked();
    void on_connServerBtn_clicked();

    void on_disconnBtn_clicked();

    void on_sendMsgBtn_clicked();

private:
    Ui::Client *ui;
    QTcpSocket *cSocket;

};

#endif // CLIENT_H
