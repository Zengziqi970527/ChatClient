#include "friendlist.h"
#include "ui_friendlist.h"
#include<QSqlDatabase>
#include<QSqlQuery>
Friendlist::Friendlist(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Friendlist)
{
    ui->setupUi(this);
    this->setWindowTitle("好友列表");
}

Friendlist::~Friendlist()
{
    delete ui;
}

void Friendlist::getusername(QString username)
{
    ui->userLabel->setText(username);
    QSqlDatabase db = QSqlDatabase::database("conn");
    QSqlQuery *query = new QSqlQuery(db);
    QString url;
    QString sql = QString("select usericon from userinfo where username = '%1'").arg(username);
    query->exec(sql);
    while (query->next()) {
        url = query->value("usericon").toString();
    }
    fileinfo = QFileInfo(url);
    ui->iconLabel->setPixmap(QPixmap(fileinfo.absoluteFilePath()));
    ui->iconLabel->setScaledContents(true);
    sql = QString("select friendname from friend where username = '%1").arg(username);
    query->exec(sql);
    while(query->next()){
    }
}
