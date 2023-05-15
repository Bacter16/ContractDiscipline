#include "SortareGUI.h"

SortareGUI::SortareGUI(Service *serv,QListWidget *l): service{serv}, lst{l} {
    initSortGUI(this);
}

void SortareGUI::loadData() {
    lst->clear();
    for(const Disciplina& disciplina: *service->getAllService()){
        lst->addItem(QString::fromStdString(disciplina.getDenumire()) + " " + QString::fromStdString(disciplina.getTip())
                     + " " + QString::fromStdString(disciplina.getCadruDidactic()) + " " + QString::fromStdString(std::to_string(disciplina.getNrOre())));
    }
}

void SortareGUI::initSortGUI(QWidget *widget) {

    widget->resize(200,150);

    auto sortButtons = new QVBoxLayout(widget);
    sortButtons->addWidget(sortButtonDenumire);
    sortButtons->addWidget(sortButtonTip);
    sortButtons->addWidget(sortButtonOre);

    conect();

    widget->show();
}

void SortareGUI::conect() {
    QObject::connect(sortButtonDenumire,&QPushButton::clicked, this, &SortareGUI::sortareDenumire);

    QObject::connect(sortButtonTip,&QPushButton::clicked, this, &SortareGUI::sortareTip);

    QObject::connect(sortButtonOre,&QPushButton::clicked, this, &SortareGUI::sortareNrOre);

}

void SortareGUI::sortareDenumire(){
    service->discipline_sortate_dupa_denumire();
    loadData();
    close();
}

void SortareGUI::sortareTip() {
    service->discipline_sortate_dupa_cadru_tip();
    loadData();
    close();
}

void SortareGUI::sortareNrOre() {
    service->discipline_sortate_dupa_nr_ore();
    loadData();
    close();
}