#include "GUI.h"


GUI::GUI(Service* serv):service{serv} {
    this->initGUI(this);
}

void GUI::loadData() {
    lst->clear();
    discipline = service->getAllService();
    for(const Disciplina& disciplina: *discipline){
        lst->addItem(QString::fromStdString(disciplina.getDenumire()) + " " + QString::fromStdString(disciplina.getTip())
        + " " + QString::fromStdString(disciplina.getCadruDidactic()) + " " + QString::fromStdString(std::to_string(disciplina.getNrOre())));
    }
}

void GUI::initGUI(QWidget *widget){

    widget->resize(500, 300);

    auto mainLayout = new QHBoxLayout;
    setLayout(mainLayout);

//    setStyleSheet("background-color:black;");

//    filter->setPlaceholderText("Cautare");
//    filter->setFixedHeight(36);
//    mainLayout->addWidget(filter);

    auto leftLayout = new QVBoxLayout;
    auto rightLayout = new QVBoxLayout;

    auto formLayout = new QFormLayout;
    formLayout->addRow("Denumire", denumire);
    formLayout->addRow("Tip", tip);
    formLayout->addRow("Nume Profesor", cadru);
    formLayout->addRow("Nr. ore", ore);
    rightLayout->addLayout(formLayout);

    auto buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(addButton);
    buttonsLayout->addWidget(delButton);
    buttonsLayout->addWidget(modButton);
    buttonsLayout->addWidget(exitButton);
    rightLayout->addLayout(buttonsLayout);

    leftLayout->addWidget(lst);

    auto underListButtonsLayout = new QHBoxLayout;
    underListButtonsLayout->addWidget(raport);
    underListButtonsLayout->addWidget(sortButtonDenumire);
    underListButtonsLayout->addWidget(sortButtonTip);
    underListButtonsLayout->addWidget(sortButtonOre);
    leftLayout->addLayout(underListButtonsLayout);

    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);

    loadData();
    initConnect();

}

void GUI::initConnect() {
    QObject::connect(exitButton,&QPushButton::clicked,&QApplication::quit);

    QObject::connect(addButton,&QPushButton::clicked,this,&GUI::addDisciplinaGUI);

    QObject::connect(delButton,&QPushButton::clicked,this,&GUI::delDisciplinaGUI);

    QObject::connect(this->modButton,
                     &QPushButton::clicked, [this]() {
                int index = this->selectedIndex();
                if (index == -1) {
                    QMessageBox::information(this, "Nothing selected", "Nothing selected");
                    return;
                }
                auto element = this->discipline->at(index);

                auto _denumire = this->denumire->text().toStdString();
                auto _tip = this->tip->text().toStdString();
                auto _cadru = this->cadru->text().toStdString();
                auto _ore = this->ore->text().toInt();

                if (_denumire.empty() || _tip.empty() || _cadru.empty() || _ore % 2 != 0) {
                    QMessageBox::information(this, "Something went wrong", "Something went wrong");
                    return;
                }

                this->service->modifyDisciplina(index, _denumire, _tip, _cadru, _ore);

                this->denumire->clear();
                this->tip->clear();
                this->cadru->clear();
                this->ore->clear();

                loadData();
            });

    QObject::connect(lst, &QListWidget::itemSelectionChanged, [&]() {
        if (lst->selectedItems().isEmpty()) {
            denumire->setText("");
            tip->setText("");
            cadru->setText("");
            ore->setText("");
            return;
        }
        QListWidgetItem* selItem = lst->selectedItems().at(0);
        std::string sentence = selItem->text().toStdString();
        std::istringstream iss(sentence);

        string word;
        iss >> word;
        denumire->setText(QString::fromStdString(word));
        iss >> word;
        tip->setText(QString::fromStdString(word));
        iss >> word;
        cadru->setText(QString::fromStdString(word));
        iss >> word;
        ore->setText(QString::fromStdString(word));
    });

    QObject::connect(sortButtonDenumire,&QPushButton::clicked, this, &GUI::sortareDenumire);

    QObject::connect(sortButtonTip,&QPushButton::clicked, this, &GUI::sortareTip);

    QObject::connect(sortButtonOre,&QPushButton::clicked, this, &GUI::sortareNrOre);

    QObject::connect(raport,&QPushButton::clicked, this, &GUI::windowRapoarte);

    QObject::connect(raportCursuri,&QPushButton::clicked, this, &GUI::raportCursuriGUI);

    QObject::connect(raportSeminare,&QPushButton::clicked, this, &GUI::raportSeminarGUI);

    QObject::connect(raportLaboratoare,&QPushButton::clicked, this, &GUI::raportLaboratorGUI);

//    QObject::connect(this->filter,
//                     &QLineEdit::textChanged,
//                     [this](const QString &text) {
//                         auto stringText = text.toStdString();
//                         auto filtered = service->filtrare_discipline_service_cadru_didactic(stringText);
//                         loadData(filtered);
//                     });
}

void GUI::addDisciplinaGUI() {
    auto _denumire = denumire->text().toStdString();
    auto _tip = tip->text().toStdString();
    auto _cadru = cadru->text().toStdString();
    auto _ore = ore->text().toInt();
    try{
        service->add_service(_denumire,_tip,_cadru,_ore);
    }catch(ValidareException &exception){
        QMessageBox::warning(nullptr,"Warning",exception.what());
    }catch(RepoException &exception){
        QMessageBox::warning(nullptr,"warning",exception.what());
    }catch(ServiceException &exception){
        QMessageBox::warning(nullptr,"warning",exception.what());
    }
    loadData();
}

void GUI::delDisciplinaGUI() {
    auto _denumire = denumire->text().toStdString();
    auto _tip = tip->text().toStdString();
    auto _cadru = cadru->text().toStdString();
    auto _ore = ore->text().toInt();
    try{
        service->remove_service(_denumire,_tip,_cadru,_ore);
    }catch(ValidareException &exception){
        QMessageBox::warning(nullptr,"Warning",exception.what());
    }catch(RepoException &exception){
        QMessageBox::warning(nullptr,"warning",exception.what());
    }catch(ServiceException &exception){
        QMessageBox::warning(nullptr,"warning",exception.what());
    }
    loadData();
}

int GUI::selectedIndex() {
    auto index = this->lst->selectionModel()->currentIndex();
    return index.row();
}

void GUI::sortareDenumire(){
    service->discipline_sortate_dupa_denumire();
    loadData();
}

void GUI::sortareTip() {
    service->discipline_sortate_dupa_cadru_tip();
    loadData();
}

void GUI::sortareNrOre() {
    service->discipline_sortate_dupa_nr_ore();
    loadData();
}

void GUI::windowRapoarte() {

    auto *windowRaports = new QWidget;
    windowRaports->close();
    auto *raportsLayout = new QVBoxLayout(windowRaports);
    raportsLayout->addWidget(raportCursuri);
    raportsLayout->addWidget(raportSeminare);
    raportsLayout->addWidget(raportLaboratoare);

    windowRaports->show();

}

void GUI::raportCursuriGUI() {
    int nrCursuri = service->rapoarteCursuri();
    QMessageBox::information(nullptr,"Information",QString::fromStdString(std::to_string(nrCursuri)));
}

void GUI::raportSeminarGUI() {
    int nrSeminarii = service->rapoarteSeminare();
    QMessageBox::information(nullptr,"Information",QString::fromStdString(std::to_string(nrSeminarii)));
}

void GUI::raportLaboratorGUI() {
    int nrLaboratoare = service->rapoarteLaboratoare();
    QMessageBox::information(nullptr,"Information",QString::fromStdString(std::to_string(nrLaboratoare)));
}

