#include "staticforfans.h"
#include "ui_staticforfans.h"
#include <QDebug>

staticForFans::staticForFans(QString session, QString team_1, QString team_2, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::staticForFans)
{
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());                     // 禁止拖动窗口大小
    map = new QMap<QString, QString>;
    map->insert("澳大利亚","image/australia");
    map->insert("比利时","image/belgium");
    map->insert("巴西", "image/brazil");
    map->insert("哥伦比亚", "image/colombia");
    map->insert("哥斯达黎加", "image/costa-rica");
    map->insert("丹麦","image/denmark");
    map->insert("埃及", "image/egypt");
    map->insert("英格兰", "image/england");
    map->insert("法国", "image/france");
    map->insert("德国", "image/germany");
    map->insert("冰岛", "image/iceland");
    map->insert("伊朗", "image/iran");
    map->insert("日本", "image/japan");
    map->insert("摩洛哥", "image/monaco");
    map->insert("巴拿马", "image/panama");
    map->insert("秘鲁", "image/peru");
    map->insert("波兰", "image/poland");
    map->insert("葡萄牙", "image/portugal");
    map->insert("俄罗斯", "image/russian");
    map->insert("韩国", "image/south-korea");
    map->insert("西班牙", "image/spain");
    map->insert("瑞典", "image/sweden");
    map->insert("乌拉圭","image/uruguay");

    setTeam(team_1, team_2);
    QSqlQuery query;
    query.prepare("select 主队进球, 客队进球 from match_score where 场次 = ?");
    query.addBindValue(session);
    query.exec();
    if(query.next()){
        ui->goal_1->setText(query.value(0).toString());
        ui->goal_2->setText(query.value(1).toString());
    }

    query.exec(QObject::tr("select 球队, 球员, 进球时间 from scorer where 场次 = '%1';").arg(session));

    while (query.next()) {
        qDebug() << query.value(0).toString();
        if(team_1 == query.value(0).toString()){
            ui->textBrowser->append(query.value(1).toString() + " " + query.value(2).toString() + "'");
        }
        if(team_2 == query.value(0).toString()){
            ui->textBrowser_2->append(query.value(1).toString() + " " + query.value(2).toString() + "'");
        }
    }
}

void staticForFans::setTeam(QString team_1, QString team_2){
    // 设置两队图标
    QString pix_1 = (*map)[team_1];
    if(NULL != pix_1){
        QPixmap pixmap1(pix_1);
        ui->team_1->setPixmap(pixmap1);

    }
    else
        ui->team_1->setText(team_1);

    QString pix_2 = (*map)[team_2];
    if(NULL != pix_2){
        QPixmap pixmap2(pix_2);
        ui->team_2->setPixmap(pixmap2);
    }
    else
        ui->team_2->setText(team_2);
}

staticForFans::~staticForFans()
{
    delete ui;
}
