#include "widget.h"
#include "ui_widget.h"
#include"register.h"
#include"client.h"
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QMessageBox>
#include<QDebug>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::WindowStaysOnTopHint,false);
    this->setWindowFlag(Qt::FramelessWindowHint);
    ui->smallBtn->setIcon(QIcon(":/icon/small.png"));
    ui->closeBtn->setIcon(QIcon(":/icon/closeBtn.png"));
    ui->userIcon->setPixmap(QPixmap(":/icon/login.png"));
    ui->userIcon->setScaledContents(true);
    //系统托盘设置
    sysicon = new QSystemTrayIcon(this);
    sysicon->setIcon(QIcon(":/icon/logo.ico"));
    sysicon->setToolTip("ChatClient");
    sysicon->show();
    menu = new QMenu(this);
    actopen = new QAction("显示程序");
    actclose = new QAction("关闭程序");
    menu->addAction(actopen);
    menu->addAction(actclose);
    sysicon->setContextMenu(menu);
    connect(actopen,SIGNAL(triggered(bool)),this,SLOT(showwin()));
    connect(actclose,SIGNAL(triggered(bool)),this,SLOT(closewin()));
    //优化登录界面图标
    QAction *actlogin = new QAction(ui->usernumLine);
    QAction *actpwd = new QAction(ui->pwdLine);
    QAction *actkey = new QAction(ui->pwdLine);
    actlogin->setIcon(QIcon(":/icon/login.png"));
    actpwd->setIcon(QIcon(":/icon/lock.png"));
    actkey->setIcon(QIcon(":/icon/keyboard.png"));
    ui->usernumLine->addAction(actlogin,QLineEdit::LeadingPosition);
    ui->pwdLine->addAction(actpwd,QLineEdit::LeadingPosition);
    ui->pwdLine->addAction(actkey,QLineEdit::TrailingPosition);
    //注册页面的打开和返回
    Register *rewin = new Register;
    connect(ui->registerBtn,&QPushButton::clicked,[=](){
        rewin->show();
        this->hide();
    });
    connect(rewin,&Register::back,[=](){
        rewin->close();
        this->show();
    });
    //登录后的页面的显示与返回
    Client *client = new Client;
    void(Widget::*logsucc)(QString) = &Widget::loginsuccess;
    void(Client::*getuser)(QString) = &Client::getusername;
    connect(this,logsucc,client,getuser);
    connect(this,logsucc,client,[=](){
        this->close();
        client->show();
    });
    connect(client,&Client::back,this,[=](){
        client->close();
        this->show();
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    ispresswid = true;
    last = event->globalPos();
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if(ispresswid){
        int dx = event->globalX()-last.x();
        int dy = event->globalY()-last.y();
        last = event->globalPos();
        move(x()+dx,y()+dy);
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    int dx = event->globalX()-last.x();
    int dy = event->globalY()-last.y();
    move(x()+dx,y()+dy);
    ispresswid = false;
}

void Widget::on_smallBtn_clicked()
{
    this->hide();
}


void Widget::on_closeBtn_clicked()
{
    this->close();
    qApp->exit(0);
}

void Widget::showwin()
{
    this->show();
}

void Widget::closewin()
{
    this->close();
    qApp->exit(0);
}


void Widget::on_loginBtn_clicked()
{
    QSqlDatabase db = QSqlDatabase::database("conn");
    QSqlQuery *query = new QSqlQuery(db);
    query->exec("select * from userinfo");
    bool flag = false;
    query->setForwardOnly(true);
    while(query->next()){
        if(query->value("username").toString()==ui->usernumLine->text()){
            flag = true;
            if(query->value("password").toString()==ui->pwdLine->text()){
                emit this->loginsuccess(query->value("username").toString());
            }
            else{
                QMessageBox::warning(this,"Warning","用户名或密码错误!");
            }
        }
    }
    query->exec("select * from userinfo");
    while (query->next()) {
        if(query->value("email").toString()==ui->usernumLine->text()){
            flag = true;
            if(query->value("password").toString()==ui->pwdLine->text()){
                emit this->loginsuccess(query->value("username").toString());
            }
            else{
                QMessageBox::warning(this,"Warning","邮箱或密码错误!");
            }
        }
    }
    if(!flag){
        QMessageBox::warning(this,"Warning","用户名或邮箱不存在!");
    }
}

