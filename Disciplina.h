#pragma once

#include <string>
#include <utility>

using std::string;

class Disciplina {
private:
    string denumire;
    string tip;
    string cadruDidactic;
    int nrOre{};

public:
    Disciplina() = default;

    Disciplina(string d, string t,  string c, int n);

    [[nodiscard]] string getDenumire() const;

    [[nodiscard]] string getTip() const;

    [[nodiscard]] string getCadruDidactic() const;

    [[nodiscard]] int getNrOre() const;

    Disciplina(const Disciplina &d);

    void set_denumire(string new_denumire);

    void set_tip(string new_tip);

    void set_cadru(string new_cadru);

    void set_ora(int new_ore);
};


