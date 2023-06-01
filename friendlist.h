#ifndef FRIENDLIST_H
#define FRIENDLIST_H

#include <QWidget>
#include<QFileInfo>
namespace Ui {
class Friendlist;
}

class Friendlist : public QWidget
{
    Q_OBJECT
signals:
    void back();
public:
    explicit Friendlist(QWidget *parent = nullptr);
    ~Friendlist();
public:
    QFileInfo fileinfo;
public slots:
    void getusername(QString username);
private:
    Ui::Friendlist *ui;
};

#endif // FRIENDLIST_H
