#pragma once
#include <string>
#include "Disciplina.h"


class Validare {
private:
    Disciplina disciplina;

    static void validare_denumire(std::string denumire);

    static void validare_tip(const std::string& tip);

    static void validare_nr_ore(int nr_ore);

    static void validare_cadru_didactic(std::string nume);

public:
    explicit Validare(Disciplina &d);

    int validare_disciplina();
};


class ValidareException : public std::exception
{
private:
    std::string msg;

public:
    explicit ValidareException(std::string  m);

    [[nodiscard]] const char* what() const noexcept override
    {
        return msg.c_str();
    }
};
