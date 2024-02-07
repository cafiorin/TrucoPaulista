#pragma once

#include <vector>
#include <memory>

#include "Carta.h"

class Baralho 
{
private:
    std::shared_ptr<std::vector<Carta>> cartas;

public:
    Baralho();
    void Embaralhar();
    void EmbaralharMetade(int inicio, int fim);
    Carta PegarCartaDoTopo();
    void ConstruirBaralhoTrucoPaulista();
};