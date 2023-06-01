#include "register.h"
#include "ui_register.h"
#include"smtp.h"
#include<QDebug>
#include<QMessageBox>
#include<QSqlQuery>
#include<QHostInfo>
#include<QFileDialog>
Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    ui->icon->setPixmap(QPixmap(":/icon/login.png"));
    ui->icon->setScaledContents(true);
    this->setWindowFlags(Qt::SplashScreen|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    this->setWindowFlag(Qt::WindowStaysOnTopHint,false);
    ui->smallBtn->setIcon(QIcon(":/icon/small.png"));
    ui->closeBtn->setIcon(QIcon(":/icon/closeBtn.png"));
//    db = QSqlDatabase::addDatabase("QMYSQL");
//    if(databaseConn(db)){
//        qDebug()<<"database success connect";
//    }
//    else{
//        QMessageBox::warning(this,"Warning","数据库链接失败!");
//    }
}

Register::~Register()
{
    delete ui;
}

//bool Register::databaseConn(QSqlDatabase db)
//{
//    db.setHostName("localhost");
//    db.setUserName("root");
//    db.setPassword("root");
//    db.setDatabaseName("chatuserinfo");
//    db.setPort(3306);
//    return db.open();
//}

void Register::mousePressEvent(QMouseEvent *event)
{
    ispresswid = true;
    last = event->globalPos();
}

void Register::mouseMoveEvent(QMouseEvent *event)
{
    if(ispresswid){
        int dx = event->globalX()-last.x();
        int dy = event->globalY()-last.y();
        last = event->globalPos();
        move(x()+dx,y()+dy);
    }

}

void Register::mouseReleaseEvent(QMouseEvent *event)
{
    int dx = event->globalX()-last.x();
    int dy = event->globalY()-last.y();
    move(x()+dx,y()+dy);
    ispresswid = false;
}

void Register::on_backBtn_clicked()
{
    emit this->back();
}


void Register::on_smallBtn_clicked()
{
    this->hide();
}


void Register::on_closeBtn_clicked()
{
    this->close();
    qApp->exit(0);
}



void Register::on_registerBtn_clicked()
{
    QSqlDatabase db = QSqlDatabase::database("conn");
    QSqlQuery *query = new QSqlQuery(db);
    if(ui->usernameLine->text().isEmpty()||ui->passwordLine->text().isEmpty()||ui->confirmpwdLine->text().isEmpty()){
        QMessageBox::warning(this,"Warning","请输入用户名或密码!");
    }
    else{
        bool flag = true;
        query->exec("select * from userinfo");
        while (query->next()) {
            if(query->value("username").toString()==ui->usernameLine->text()){
                QMessageBox::warning(this,"Warning","用户名已被注册!");
                flag = false;
            }
        }
        if(flag){
            if(ui->passwordLine->text()!=ui->confirmpwdLine->text()){
                QMessageBox::warning(this,"Warning","两次输入的密码不相同，请重新输入!");
            }
            else{
                int input = ui->numLine->text().toInt();
                if(input==num){
                    QPixmap icon;
                    icon.load(fileinfo.absoluteFilePath());
                    QString filename = QCoreApplication::applicationDirPath();
                    filename = filename + QString("//..//UserFile//%1").arg(ui->usernameLine->text());
                    QDir *file = new QDir;
                    bool flag = file->exists(filename);
                    if(flag){
                        url = filename+QString("//%1.png").arg(ui->usernameLine->text());
                        icon.save(url);
                        QHostInfo info = QHostInfo::fromName(QHostInfo::localHostName());
                        QList<QHostAddress>list = info.addresses();
                        QString sql = "insert into userinfo values('%1','%2','%3','%4','%5')";
                        query->exec(sql.arg(ui->usernameLine->text()).arg(ui->passwordLine->text()).arg(list.at(1).toString()).arg(url).arg(ui->postLine->text()));
                        QMessageBox::information(this,"注册成功","注册成功，将返回登录界面!");
                        emit this->back();
                    }
                    else{
                        bool create = file->mkpath(filename);
                        if(create){
                            url = filename+QString("//%1.png").arg(ui->usernameLine->text());
                            icon.save(url);
                            QHostInfo info = QHostInfo::fromName(QHostInfo::localHostName());
                            QList<QHostAddress>list = info.addresses();
                            QString sql = "insert into userinfo values('%1','%2','%3','%4','%5')";
                            query->exec(sql.arg(ui->usernameLine->text()).arg(ui->passwordLine->text()).arg(list.at(1).toString()).arg(url).arg(ui->postLine->text()));
                            QMessageBox::information(this,"注册成功","注册成功，将返回登录界面!");
                            emit this->back();
                        }
                        else{
                            QMessageBox::warning(this,"Warning","创建文件夹失败!");
                        }
                    }

                }
                else{
                    QMessageBox::warning(this,"Warning","验证码不正确!");
                }
            }
        }
    }

}


void Register::on_iconchooseBtn_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,"选择头像",QDir::currentPath(),"Image Flie(*.jpg *.png *.ico)");
    fileinfo = QFileInfo(filename);
    ui->icon->setPixmap(QPixmap(fileinfo.absoluteFilePath()));
}


void Register::on_pushButton_clicked()
{
    QSqlDatabase db = QSqlDatabase::database("conn");
    QSqlQuery *query = new QSqlQuery(db);
    bool flag = true;
    query->exec("select * from userinfo");
    while (query->next()) {
        if(query->value("email").toString()==ui->postLine->text()){
            QMessageBox::warning(this,"Warning","邮箱已被注册!");
            flag = false;
        }
    }
    if(flag){
        QByteArray email = ui->postLine->text().toUtf8();
        num = rand()%(9999-1000)+1000;
        QString a = QString::number(num);
        qDebug()<<a;
        Smtp smtp("zengziqi0527@163.com","RIWAMKXCTGSKUOXY");
        smtp.send(email,"验证码",a);
    }
}

