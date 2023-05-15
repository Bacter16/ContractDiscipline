

#include <sstream>
#include "ContractStudiuGUI.h"

ContractStudiuGUI::ContractStudiuGUI(Service_Contract *serv, std::vector<Disciplina> *dis): serviceC{serv}, discipline{dis}{
    initContractGUI(this);
}

void ContractStudiuGUI::initContractGUI(QWidget *widget) {

    auto mainContractLayout = new QVBoxLayout(widget);

    auto rawLayout = new QFormLayout;
    rawLayout->addRow(randomAndSaveLine);
    mainContractLayout->addLayout(rawLayout);

    auto listsLayout = new QHBoxLayout;
    listsLayout->addWidget(lstDiscipline);
    listsLayout->addWidget(lstContract);
    mainContractLayout->addLayout(listsLayout);

//    auto rawLayout = new QFormLayout;
//    rawLayout->addRow("Denumire", denumire);
//    rawLayout->addRow("Tip", tip);
//    rawLayout->addRow("Cadru", cadru);
//    rawLayout->addRow("Nr Ore", nrOre);
//    midLayout->addLayout(rawLayout);

    auto buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(addButton);
    buttonsLayout->addWidget(delButton);
    buttonsLayout->addWidget(randomAddButton);
    buttonsLayout->addWidget(saveButton);
    buttonsLayout->addWidget(exitButton);
    mainContractLayout->addLayout(buttonsLayout);

    connectContract();
    loadData(discipline, lstDiscipline);
    loadData(serviceC->get_contract_service(), lstContract);

    widget->show();
}

void ContractStudiuGUI::connectContract() {
    QObject::connect(addButton,&QPushButton::clicked,this, &ContractStudiuGUI::addDisciplinaContractGUI);

    QObject::connect(delButton,&QPushButton::clicked,this, &ContractStudiuGUI::delDisciplinaContractGUI);

    QObject::connect(randomAddButton,&QPushButton::clicked,this, &ContractStudiuGUI::randDisciplinaContractGUI);

    QObject::connect(saveButton,&QPushButton::clicked,this, &ContractStudiuGUI::saveDisciplinaContractGUI);

    QObject::connect(exitButton,&QPushButton::clicked,[&](){
        close();
    });

    QObject::connect(lstDiscipline, &QListWidget::itemSelectionChanged, [&]() {
//        if (lstDiscipline->selectedItems().isEmpty()) {
//            denumire->setText("");
//            tip->setText("");
//            cadru->setText("");
//            nrOre->setText("");
//            return;
//        }
        QListWidgetItem* selItem = lstDiscipline->selectedItems().at(0);
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
        nrOre->setText(QString::fromStdString(word));
    });

}

void ContractStudiuGUI::loadData(std::vector<Disciplina> *dis, QListWidget *lst) {
    lst->clear();
    for(const Disciplina& disciplina: *dis){
        lst->addItem(QString::fromStdString(disciplina.getDenumire()) + " " + QString::fromStdString(disciplina.getTip())
                     + " " + QString::fromStdString(disciplina.getCadruDidactic()) + " " + QString::fromStdString(std::to_string(disciplina.getNrOre())));
    }
}

void ContractStudiuGUI::addDisciplinaContractGUI() {
    auto _denumire = denumire->text().toStdString();
    auto _tip = tip->text().toStdString();
    auto _cadru = cadru->text().toStdString();
    auto _ore = nrOre->text().toInt();
    if(!(_denumire.empty() or _tip.empty() or _cadru.empty())){
        try{
            serviceC->add_contract_service(_denumire, _tip, _cadru, _ore);
            loadData(serviceC->get_contract_service(), lstContract);
        }catch(ValidareException &exception){
            QMessageBox::warning(nullptr,"Warning",exception.what());
        }catch(ServiceContractException &exception){
            QMessageBox::warning(nullptr,"warning",exception.what());
        }catch(ContractException &exception){
            QMessageBox::warning(nullptr,"warning",exception.what());
        }
    }
    else{
        QMessageBox::warning(nullptr,"warning","Nothing selected!");
    }
}

void ContractStudiuGUI::delDisciplinaContractGUI() {
    serviceC->delete_contract_service();
    loadData(serviceC->get_contract_service(), lstContract);
}

void ContractStudiuGUI::randDisciplinaContractGUI() {
    if(randomAndSaveLine->text().toInt() > 0){
        try{
            serviceC->random_generator(randomAndSaveLine->text().toInt(), discipline);
            loadData(serviceC->get_contract_service(), lstContract);
        }catch (ServiceContractException &exception){
            QMessageBox::warning(nullptr,"warning",exception.what());
        }
    }
    else
        QMessageBox::warning(nullptr,"warning","Invalid number!");
}

void ContractStudiuGUI::saveDisciplinaContractGUI() {
    if(!randomAndSaveLine->text().toStdString().empty())
        serviceC->save_contract_service(randomAndSaveLine->text().toStdString());
    else
        QMessageBox::warning(nullptr,"warning","Field empty!");
}
