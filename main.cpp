#include "widget.h"
#include"register.h"
#include <QApplication>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QDebug>
#include<QSqlError>
void createdbconn(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL","conn");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("root");
    db.setDatabaseName("chatuserinfo");
    db.setPort(3306);
    if(!db.open()){
        qDebug()<<db.lastError().text();
    }
    else{
        qDebug()<<"database success connect";
    }
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    createdbconn();
    w.show();
    return a.exec();
}
