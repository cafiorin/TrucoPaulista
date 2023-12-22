#pragma once
#include <string>
#include "Enums.h"

class Carta 
{
public:
    int id;
    int valor;
    std::string nome;
    Naipes naipe;

    Carta(int _id, int _valor, std::string _nome, Naipes _naipe) : id(_id), valor(_valor), nome(_nome),naipe(_naipe)
    {
    }

    Carta(Carta *carta)
    {
        id = carta->id;
        valor = carta->valor;
        nome = carta->nome;
        naipe = carta->naipe;
    }

};
