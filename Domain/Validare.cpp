#include "Validare.h"

Validare::Validare(Disciplina &d):disciplina{d} {}

void Validare::validare_denumire(std::string denumire) {
    if (denumire.empty()) {
        throw ValidareException("Denumire invalida!\n");
    }
    char first_char = denumire[0];
    if(!isalpha(first_char) or !isupper(first_char))
        throw ValidareException("Denumire invalida!\n");
}

void Validare::validare_tip(const std::string& tip) {
    if(tip != "seminar" && tip != "laborator" && tip != "curs" && tip != "Seminar" && tip != "Laborator" && tip != "Curs")
        throw ValidareException("Tip invalid!\n");
}

void Validare::validare_nr_ore(int nr_ore) {
    if(nr_ore % 2 == 1)
        throw ValidareException("Numar de ore invalid!\n");
}

void Validare::validare_cadru_didactic(std::string nume) {
    if (nume.empty()) {
        throw ValidareException("Nume invalid!\n");
    }
    char first_char = nume[0];
    if(!isalpha(first_char) or !isupper(first_char))
        throw ValidareException("Nume invalid!\n");
}

int Validare::validare_disciplina() {
    validare_denumire(disciplina.getDenumire());
    validare_tip(disciplina.getTip());
    validare_cadru_didactic(disciplina.getCadruDidactic());
    validare_nr_ore(disciplina.getNrOre());
    return 0;
}

ValidareException::ValidareException(std::string m):msg{std::move(m)}{}
