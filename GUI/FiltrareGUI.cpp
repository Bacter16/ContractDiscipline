
#include "FiltrareGUI.h"


FiltrareGUI::FiltrareGUI(Service *serv): service{serv} {
    initFiltrareGUI(this);
}

void FiltrareGUI::initFiltrareGUI(QWidget *widget) {

//    widget->resize(200,150);

    auto filterLayout = new QVBoxLayout(widget);
    filterLayout->addWidget(filterField);
    filterLayout->addWidget(lst);

    auto buttonsFilterLayout = new QHBoxLayout;
    buttonsFilterLayout->addWidget(filterDenumire);
    buttonsFilterLayout->addWidget(filterNrOre);
    buttonsFilterLayout->addWidget(exitButton);

    filterLayout->addLayout(buttonsFilterLayout);


    connectFiltrareGUI();

    widget->show();
}

void FiltrareGUI::loadDataFiltrareGUI(const std::vector<Disciplina>& discipline) {
    lst->clear();
    for(const Disciplina& disciplina: discipline ){
        lst->addItem(QString::fromStdString(disciplina.getDenumire()) + " " + QString::fromStdString(disciplina.getTip())
                     + " " + QString::fromStdString(disciplina.getCadruDidactic()) + " " + QString::fromStdString(std::to_string(disciplina.getNrOre())));
    }
}

void FiltrareGUI::connectFiltrareGUI() {
    QObject::connect(filterDenumire,&QPushButton::clicked, this, &FiltrareGUI::filterByDenumire);

    QObject::connect(filterNrOre,&QPushButton::clicked, this, &FiltrareGUI::filterByNrOre);

    QObject::connect(exitButton,&QPushButton::clicked,[this](){
        close();
    });

}

void FiltrareGUI::filterByDenumire() {
    auto _denumire = filterField->text().toStdString();
    vector<Disciplina> discipline = service->filtrare_discipline_service_cadru_didactic(_denumire);
    if(discipline.empty())
        QMessageBox::information(nullptr,"Warning","Nu exista cadrul didactic");
    else
        loadDataFiltrareGUI(discipline);
}

void FiltrareGUI::filterByNrOre() {
    auto nrOre = filterField->text().toInt();
    vector<Disciplina> discipline = service->filtrare_discipline_service_nr_ore(nrOre);
    if(discipline.empty())
        QMessageBox::information(nullptr,"Warning","Nu exista o disiplina cu acest numar de ore");
    else
        loadDataFiltrareGUI(discipline);
}
