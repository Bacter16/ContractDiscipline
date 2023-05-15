#pragma once
#include "../Repos/Repository_Contract.h"
#include "../Domain/Validare.h"
#include <random>

class UndoActionContract {
public:
    virtual void doUndo() = 0;
    virtual ~UndoActionContract()= default;
};

class UndoAddContract: public UndoActionContract{
    Disciplina d;
    Repository_Contract &repo;
public:

    UndoAddContract(Repository_Contract &r,const Disciplina &dis);

    void doUndo() override;

};

class UndoDeleteContract: public UndoActionContract{
    std::vector<Disciplina> discipline;
    Repository_Contract &repo;
public:

    UndoDeleteContract(Repository_Contract &r,const std::vector<Disciplina>& d);

    void doUndo() override;

};

class Service_Contract {
private:

    Repository_Contract *repo;

    std::vector<UndoActionContract*> undoActions;

public:

    explicit Service_Contract(Repository_Contract *rep);

    void add_contract_service(const string& denumire, const string& tip, const string& cadru, int ore);

    void delete_contract_service();

    std::vector<Disciplina> *get_contract_service();

    void save_contract_service(const string& nume);

    void random_generator(int n, std::vector<Disciplina> *discipline);

    void undo_service();

    std::vector<int> raports_service();
};

class ServiceContractException : public std::exception{
private:
    string msg;
public:
    explicit ServiceContractException(string m);

    [[nodiscard]] const char* what() const noexcept override
    {
        return msg.c_str();
    }
};
