#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include<QPoint>
#include<QMenu>
#include<QMouseEvent>
#include<QSystemTrayIcon>
#include<QSqlDatabase>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:

    bool ispresswid;
    QPoint last;
    QSystemTrayIcon *sysicon;
    QMenu *menu;
    QAction *actopen;
    QAction *actclose;
    QSqlDatabase db;
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
signals:
    void loginsuccess(QString);
private slots:
    void on_smallBtn_clicked();
    void on_closeBtn_clicked();
    void showwin();
    void closewin();
    void on_loginBtn_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
