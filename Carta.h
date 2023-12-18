#pragma once
#include <string>

enum Naipes { Espadas, Paus, Ouro, Copas };

class Carta 
{
public:
    int valor;
    std::string nome;
    Naipes naipe;

    Carta(int _valor, std::string _nome, Naipes _naipe) : valor(_valor), nome(_nome),naipe(_naipe)
    {
    }
};
