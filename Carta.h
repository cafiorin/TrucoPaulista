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

    int ObtemValor(const Carta* vira) const
    {
        if (valor == vira->valor + 1)
        {
            switch (naipe)
            {
            case Ouro:
                return valor + 10;
            case Espadas:
                return valor + 11;
            case Copas:
                return valor + 12;
            case Paus:
                return valor + 13;
            }
        }
        
        return valor;
    }
};
