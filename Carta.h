#pragma once
#include <string>

enum Naipes { Espadas, Paus, Ouro, Copas };

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
};
