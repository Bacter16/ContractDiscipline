#include <QApplication>
#include "GUI.h"

int main(int argc, char *argv[]) {
//    testRepo();
//    testsService();
    QApplication a(argc, argv);
    QApplication::setFont(QFont{"Arial", 15});
    Repository repo;
    Service service{&repo};
    GUI app{&service};
    app.show();
    return QApplication::exec();
}
