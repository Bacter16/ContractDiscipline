
#ifndef CONTRACTDISCIPLINE_CONTRACTSTUDIUGUI_H
#define CONTRACTDISCIPLINE_CONTRACTSTUDIUGUI_H
#include "../Services/Service_Contract.h"
#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QMessageBox>

class GUI;

class ContractStudiuGUI: public QWidget{
private:

    Service_Contract *serviceC;
    std::vector<Disciplina> *discipline;

    QListWidget *lstDiscipline = new QListWidget;
    QListWidget *lstContract = new QListWidget;

    QPushButton *addButton = new QPushButton("Adauga");
    QPushButton *delButton = new QPushButton("Sterge contract");
    QPushButton *randomAddButton = new QPushButton("Adauga random");
    QPushButton *saveButton = new QPushButton("Save");
    QPushButton *exitButton = new QPushButton("Exit");

    QLineEdit *denumire = new QLineEdit;
    QLineEdit *tip = new QLineEdit;
    QLineEdit *cadru = new QLineEdit;
    QLineEdit *nrOre = new QLineEdit;
    QLineEdit *randomAndSaveLine = new QLineEdit;

    void initContractGUI(QWidget *widget);

    void connectContract();

    static void loadData(std::vector<Disciplina> *discipline, QListWidget *lst);

public:

    explicit ContractStudiuGUI(Service_Contract *serv, std::vector<Disciplina> *dis);

    void addDisciplinaContractGUI();

    void delDisciplinaContractGUI();

    void randDisciplinaContractGUI();

    void saveDisciplinaContractGUI();
};


#endif //CONTRACTDISCIPLINE_CONTRACTSTUDIUGUI_H
