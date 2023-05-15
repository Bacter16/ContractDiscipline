#include "RapoarteGUI.h"


RapoarteGUI::RapoarteGUI(Service *serv):service{serv} {
    initGUI(this);
}

void RapoarteGUI::initGUI(QWidget *widget) {

    widget->resize(200, 150);

    auto *raportsLayout = new QVBoxLayout(widget);
    raportsLayout->addWidget(raportCursuri);
    raportsLayout->addWidget(raportSeminare);
    raportsLayout->addWidget(raportLaboratoare);

    conect();

    widget->show();
}

void RapoarteGUI::conect() {

    QObject::connect(raportCursuri,&QPushButton::clicked, this, &RapoarteGUI::raportCursuriGUI);

    QObject::connect(raportSeminare,&QPushButton::clicked, this, &RapoarteGUI::raportSeminarGUI);

    QObject::connect(raportLaboratoare,&QPushButton::clicked, this, &RapoarteGUI::raportLaboratorGUI);
}

void RapoarteGUI::raportCursuriGUI() {
    int nrCursuri = service->rapoarteCursuri();
    QMessageBox::information(nullptr,"Information",QString::fromStdString(std::to_string(nrCursuri)));
}

void RapoarteGUI::raportSeminarGUI() {
    int nrSeminarii = service->rapoarteSeminare();
    QMessageBox::information(nullptr,"Information",QString::fromStdString(std::to_string(nrSeminarii)));
}

void RapoarteGUI::raportLaboratorGUI() {
    int nrLaboratoare = service->rapoarteLaboratoare();
    QMessageBox::information(nullptr,"Information",QString::fromStdString(std::to_string(nrLaboratoare)));
}