#include <QApplication>
#include "view/MainWindow.h"
#include "data/DataManager.h"
#include "model/RadarModelDAO.h"
#include "model/JammerModelDAO.h"
#include "model/TargetModelDAO.h"
#include "model/RcsDataDAO.h"
int main(int argc, char *argv[])
{
    //先连接数据库
    DataManager::getInstance().connect();
    QApplication app(argc, argv);
    // 注册自定义类型
    qRegisterMetaType<RadarModel>("RadarModel");
    qRegisterMetaType<JammerModel>("JammerModel");
    qRegisterMetaType<TargetModel>("TargetModel");
    qRegisterMetaType<RcsData>("RcsData");
    MainWindow w;
    w.show();
    return app.exec();
}
