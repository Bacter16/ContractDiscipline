#pragma once
#include <vector>
#include "../Domain/Disciplina.h"
#include <fstream>
#include <utility>
#include <cassert>

class Repository_Contract {
private:
    std::vector<Disciplina> *contract;

public:
    Repository_Contract();

    std::vector<Disciplina> *get_contract();

    void add_contract(const Disciplina& disciplina);

    void delete_contract();

    ~Repository_Contract();

    void save_contract(const string &nume);

    void remove(const Disciplina& d);
};

class ContractException : public std::exception
{
private:
    string msg;

public:
    explicit ContractException(string  m);

    [[nodiscard]] const char* what() const noexcept override
    {
    return msg.c_str();
    }
};

void tests_contract();