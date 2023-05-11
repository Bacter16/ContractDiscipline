#include "Service_Discipline.h"
#include <QtWidgets>
#include <qdebug.h>


class GUI: public QWidget{
public:

    explicit GUI(Service* service);

private:
    Service *service;

    vector<Disciplina> *myList = new vector<Disciplina>;

    QLineEdit *denumire = new QLineEdit;
    QLineEdit *tip = new QLineEdit;
    QLineEdit *cadru = new QLineEdit;
    QLineEdit *ore = new QLineEdit;

    QListWidget* lst = new QListWidget;

    QPushButton* addButton = new QPushButton{"Adauga"};
    QPushButton* delButton = new QPushButton{"Sterge"};
    QPushButton* modButton = new QPushButton{"Modifica"};
    QPushButton* exitButton = new QPushButton{"Exit"};

    QPushButton* sortButtonDenumire = new QPushButton{"Sortare Denumire"};
    QPushButton* sortButtonTip = new QPushButton{"Sortare Tip"};
    QPushButton* sortButtonOre = new QPushButton{"Sortare Nr. Ore"};

    void initGUI(QWidget *widget);

    void loadData();

    void initConnect();

    void addDisciplinaGUI();

    void delDisciplinaGUI();

    int selectedIndex();

    void sortareDenumire();

    void sortareTip();

    void sortareNrOre();
};
