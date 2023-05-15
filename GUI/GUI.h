#pragma once
#include "../Services/Service_Discipline.h"
#include "RapoarteGUI.h"
#include "SortareGUI.h"
#include "FiltrareGUI.h"
#include "ContractStudiuGUI.h"
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QFormLayout>
#include <QApplication>
#include <qdebug.h>


class GUI: public QWidget{
public:

    explicit GUI(Service* service, Service_Contract* servC);

private:
    Service *service;
    Service_Contract *serviceC;

    RapoarteGUI *rapoarte{};

    SortareGUI *sortare{};

    FiltrareGUI *filtrare{};

    ContractStudiuGUI *contractGui{};

    vector<Disciplina> *discipline = new vector<Disciplina>;

    QLineEdit *denumire = new QLineEdit;
    QLineEdit *tip = new QLineEdit;
    QLineEdit *cadru = new QLineEdit;
    QLineEdit *ore = new QLineEdit;

    QListWidget* lst = new QListWidget;

    QPushButton* addButton = new QPushButton{"Adauga"};
    QPushButton* delButton = new QPushButton{"Sterge"};
    QPushButton* modButton = new QPushButton{"Modifica"};
    QPushButton* exitButton = new QPushButton{"Exit"};

    QPushButton *contractBut = new QPushButton("Contract");
    QPushButton *undoButton = new QPushButton("Undo");
    QPushButton* sortButton = new QPushButton{"Sortare"};
    QPushButton* filterButton = new QPushButton{"Filtrare"};
    QPushButton* raport = new QPushButton{"Rapoarte"};

    void initGUI(QWidget *widget);

    void loadData();

    void initConnect();

    void addDisciplinaGUI();

    void delDisciplinaGUI();

    int selectedIndex();

    void windowRapoarte();

    void windowSort();

    void windowFilter();

    void undoMain();

    void windowContract();
};
