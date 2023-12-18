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
    Carta PegarCartaDoTopo();
    void ConstruirBaralhoTrucoPaulista();
};