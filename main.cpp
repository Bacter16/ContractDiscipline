#include <QApplication>
#include "GUI/GUI.h"

int main(int argc, char *argv[]) {
//    testRepo();
//    testsService();
    QApplication a(argc, argv);
    QApplication::setFont(QFont{"Arial", 15});
    Repository_Contract repo2;
    Repository repo1;
    Service_Contract service2{&repo2};
    Service service1{&repo1};
    GUI app{&service1, &service2};
    app.show();
    return QApplication::exec();
}
