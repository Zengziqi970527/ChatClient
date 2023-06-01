#ifndef REGISTER_H
#define REGISTER_H
#include<QPoint>
#include <QWidget>
#include<QSqlDatabase>
#include<QFileInfo>
#include<QMouseEvent>
namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();
//    QSqlDatabase db;
//    bool databaseConn(QSqlDatabase db);
    QString url;
    QFileInfo fileinfo;
    int num;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    bool ispresswid;
    QPoint last;
signals:
    void back();
private slots:
    void on_backBtn_clicked();
    void on_smallBtn_clicked();
    void on_closeBtn_clicked();
    void on_registerBtn_clicked();
    void on_iconchooseBtn_clicked();
    void on_pushButton_clicked();
private:
    Ui::Register *ui;
};

#endif // REGISTER_H
