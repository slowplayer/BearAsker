#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QtAlgorithms>
#include <QMessageBox>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setLayout(ui->verticalLayout);

    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(work()));
    ui->comboBox->addItem(tr("普通"));
    ui->comboBox->addItem(tr("英雄"));
    ui->comboBox->addItem(tr("史诗"));
    ui->comboBox_2->addItem(tr("普通"));
    ui->comboBox_2->addItem(tr("英雄"));
    ui->comboBox_2->addItem(tr("史诗"));
    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(updatepro1(int)));
    connect(ui->comboBox_2,SIGNAL(currentIndexChanged(int)),this,SLOT(updatepro2(int)));
}
void Widget::work()
{
    QString url="http://www.battlenet.com.cn/api/wow/character/";
    url+=ui->lineEdit_2->text();
    url+="/";
    url+=ui->lineEdit->text();
    QString url1=url+"?fields=items";
    QString url2=url+"?fields=progression";
    QString html=Widget::getHtml(url1);
    if(html=="{\"status\":\"nok\", \"reason\": \"Character not found.\"}")
    {
        QMessageBox message(QMessageBox::NoIcon, "警告", "未查找到该角色！");
        message.exec();
        return;
    }
    while(html=="{\"status\":\"nok\", \"reason\": \"Internal server error.\"}")
        html=Widget::getHtml(url1);
    qDebug()<<html;
    QStringList cmd=html.split(",");
    qDebug()<<cmd.count();
    qDebug()<<cmd[11];
    qDebug()<<cmd[12];
    QString topstr="\"items\":{\"averageItemLevel\":";
    top=cmd[11].remove(topstr).toInt();
    QString averstr="\"averageItemLevelEquipped\":";
    aver=cmd[12].remove(averstr).toInt();
    html=Widget::getHtml(url2);
    while(html=="{\"status\":\"nok\", \"reason\": \"Internal server error.\"}")
        html=Widget::getHtml(url2);
    cmd=html.split(",");
    qDebug()<<html;
    QString pp="\"normalKills\":";
    QString hh="\"heroicKills\":";
    QString mm="\"mythicKills\":";
    for(int i=0;i<7;i++)
    {
       XCB[i][0]=cmd[1075+0+i*10].remove(pp).toInt();
       XCB[i][1]=cmd[1075+2+i*10].remove(hh).toInt();
       XCB[i][2]=cmd[1075+4+i*10].remove(mm).toInt();
    }
    qDebug()<<cmd[1072];
    qDebug()<<cmd[1075];
    qDebug()<<cmd[1243];
    for(int i=0;i<10;i++)
    {
       BH[i][0]=cmd[1151+0+i*10].remove(pp).toInt();
       BH[i][1]=cmd[1151+2+i*10].remove(hh).toInt();
       BH[i][2]=cmd[1151+4+i*10].remove(mm).toInt();
    }
    ui->lcdNumber->display(top);
    ui->lcdNumber_2->display(aver);

    int k=ui->comboBox->currentIndex();
    ui->lcdNumber_3->display(XCB[0][k]);
    ui->lcdNumber_4->display(XCB[1][k]);
    ui->lcdNumber_5->display(XCB[2][k]);
    ui->lcdNumber_6->display(XCB[3][k]);
    ui->lcdNumber_7->display(XCB[4][k]);
    ui->lcdNumber_8->display(XCB[5][k]);
    ui->lcdNumber_9->display(XCB[6][k]);

    k=ui->comboBox_2->currentIndex();
    ui->lcdNumber_10->display(BH[0][k]);
    ui->lcdNumber_11->display(BH[1][k]);
    ui->lcdNumber_12->display(BH[2][k]);
    ui->lcdNumber_13->display(BH[3][k]);
    ui->lcdNumber_14->display(BH[4][k]);
    ui->lcdNumber_15->display(BH[5][k]);
    ui->lcdNumber_16->display(BH[6][k]);
    ui->lcdNumber_17->display(BH[7][k]);
    ui->lcdNumber_18->display(BH[8][k]);
    ui->lcdNumber_19->display(BH[9][k]);

}
void Widget::updatepro1(int k)
{
    ui->lcdNumber_3->display(XCB[0][k]);
    ui->lcdNumber_4->display(XCB[1][k]);
    ui->lcdNumber_5->display(XCB[2][k]);
    ui->lcdNumber_6->display(XCB[3][k]);
    ui->lcdNumber_7->display(XCB[4][k]);
    ui->lcdNumber_8->display(XCB[5][k]);
    ui->lcdNumber_9->display(XCB[6][k]);
}
void Widget::updatepro2(int k)
{
    ui->lcdNumber_10->display(BH[0][k]);
    ui->lcdNumber_11->display(BH[1][k]);
    ui->lcdNumber_12->display(BH[2][k]);
    ui->lcdNumber_13->display(BH[3][k]);
    ui->lcdNumber_14->display(BH[4][k]);
    ui->lcdNumber_15->display(BH[5][k]);
    ui->lcdNumber_16->display(BH[6][k]);
    ui->lcdNumber_17->display(BH[7][k]);
    ui->lcdNumber_18->display(BH[8][k]);
    ui->lcdNumber_19->display(BH[9][k]);
}

QString Widget::getHtml(QString url)
{
    QNetworkAccessManager *manager=new QNetworkAccessManager();
    QNetworkReply *reply=manager->get(QNetworkRequest(QUrl(url)));
    QByteArray responseData;
    QEventLoop eventloop;
    connect(manager,SIGNAL(finished(QNetworkReply*)),&eventloop,SLOT(quit()));
    eventloop.exec();
    responseData=reply->readAll();
    return QString(responseData);
}

Widget::~Widget()
{
    delete ui;
}
