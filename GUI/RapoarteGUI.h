#pragma once
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include "../Services/Service_Discipline.h"

class RapoarteGUI: public QWidget {
private:

    Service *service;

    QPushButton* raportCursuri = new QPushButton{"Curs"};
    QPushButton* raportSeminare = new QPushButton{"Seminar"};
    QPushButton* raportLaboratoare = new QPushButton{"Laborator"};

    void initGUI(QWidget *widget);

    void conect();

public:

    explicit RapoarteGUI(Service *serv);

    void raportCursuriGUI();

    void raportSeminarGUI();

    void raportLaboratorGUI();
};

