#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
     static QString getHtml(QString url);
    ~Widget();
private slots:
    void work();
    void updatepro1(int k);
    void updatepro2(int k);
private:

    Ui::Widget *ui;
    int top,aver;
    int XCB[7][3];
    int BH[10][3];
};

#endif // WIDGET_H
