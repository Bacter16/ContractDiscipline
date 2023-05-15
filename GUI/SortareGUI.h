#pragma once
#include "../Services/Service_Discipline.h"
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QListWidget>

class SortareGUI: public QWidget {
private:
    Service *service;

    QListWidget *lst;

    QPushButton* sortButtonDenumire = new QPushButton{"Sortare Denumire"};
    QPushButton* sortButtonTip = new QPushButton{"Sortare Tip"};
    QPushButton* sortButtonOre = new QPushButton{"Sortare Ore"};

    void initSortGUI(QWidget *widget);

    void conect();

    void sortareDenumire();

    void sortareTip();

    void sortareNrOre();

    void loadData();

public:
    explicit SortareGUI(Service *serv,QListWidget *l);

};
