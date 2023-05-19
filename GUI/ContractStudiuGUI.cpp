

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
    listsLayout->addWidget(tableContract);
    mainContractLayout->addLayout(listsLayout);

    auto buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(addButton);
    buttonsLayout->addWidget(delButton);
    buttonsLayout->addWidget(randomAddButton);
    buttonsLayout->addWidget(saveButton);
    buttonsLayout->addWidget(exitButton);
    mainContractLayout->addLayout(buttonsLayout);

    connectContract();
    loadData(discipline, lstDiscipline);
    loadTableContract();

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
            loadTableContract();
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
    loadTableContract();
}

void ContractStudiuGUI::randDisciplinaContractGUI() {
    if(randomAndSaveLine->text().toInt() > 0){
        try{
            serviceC->random_generator(randomAndSaveLine->text().toInt(), discipline);
            loadTableContract();
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

void ContractStudiuGUI::loadTableContract() {
    tableContract->clear();
    tableContract->setMinimumSize(404,100);
    tableContract->setColumnCount(4);
    tableContract->setRowCount(static_cast<int>(serviceC->get_contract_service()->size()));
    tableContract->verticalHeader()->setVisible(false);
    tableContract->horizontalHeader()->setVisible(false);
    int i = 0;
    for(const auto& el:*serviceC->get_contract_service()){
        tableContract->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(el.getDenumire())));
        tableContract->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(el.getTip())));
        tableContract->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(el.getCadruDidactic())));
        tableContract->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(std::to_string(el.getNrOre()))));
        i++;
    }
}

