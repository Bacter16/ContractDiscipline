#ifndef CONTRACTDISCIPLINE_FILTRAREGUI_H
#define CONTRACTDISCIPLINE_FILTRAREGUI_H

#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QMessageBox>
#include "../Services/Service_Discipline.h"

class FiltrareGUI: public QWidget  {
private:

    Service *service;

    QLineEdit *filterField = new QLineEdit;

    QListWidget *lst = new QListWidget;

    QPushButton *filterDenumire = new QPushButton("Filtrare dupa denumire");
    QPushButton *filterNrOre = new QPushButton("Filtrare dupa nr. ore");
    QPushButton* exitButton = new QPushButton{"Exit"};

    void initFiltrareGUI(QWidget *widget);

    void connectFiltrareGUI();

    void loadDataFiltrareGUI(const std::vector<Disciplina>& discipline);

    void filterByDenumire();

    void filterByNrOre();

public:

    explicit FiltrareGUI(Service *serv);

};


#endif //CONTRACTDISCIPLINE_FILTRAREGUI_H
