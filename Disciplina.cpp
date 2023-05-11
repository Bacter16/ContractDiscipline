#include "Disciplina.h"
#include <utility>

Disciplina::Disciplina(string d, string t,  string c, int n):
        denumire{std::move(d)},tip{std::move(t)},cadruDidactic{std::move(c)},nrOre{n}{}


string Disciplina::getDenumire() const{
    return denumire;
}

string Disciplina::getTip() const{
    return tip;
}

string Disciplina::getCadruDidactic() const{
    return cadruDidactic;
}

int Disciplina::getNrOre() const{
    return nrOre;
}

void Disciplina::set_denumire(string new_denumire) {
    denumire = std::move(new_denumire);
}

void Disciplina::set_tip(string new_tip) {
    tip = std::move(new_tip);
}

void Disciplina::set_cadru(string new_cadru) {
    cadruDidactic = std::move(new_cadru);
}

void Disciplina::set_ora(int new_ore) {
    nrOre = new_ore;
}

Disciplina::Disciplina(const Disciplina &d) = default;