#pragma once
#include "../Domain/Disciplina.h"
#include <utility>
#include <vector>
#include <cassert>
#include <iostream>
#include <exception>
#include <cstring>
#include <fstream>

class Repository {
private:
    std::vector<Disciplina> *discipline;
public:

    Repository();

    void add(Disciplina &disciplina);

    std::vector<Disciplina> *getAll();

    void remove(Disciplina& disciplina);

    void modify_denumire(int poz, const string& new_denumire);

    void modify_tip(int poz, const string& new_tip);

    void modify_cadru(int poz, const string& new_cadru);

    void modify_ore(int poz, int new_ore);

    void read();

    void overwrite();

    ~Repository();

    void modifyOverAll(int poz, const string &new_denumire, const string &new_tip, const string &new_cadru, int new_ore);
};

class RepoException : public std::exception
{
private:
    string msg;

public:
    explicit RepoException(string  m);

    [[nodiscard]] const char* what() const noexcept override
    {
        return msg.c_str();
    }
};

void testRepo();
