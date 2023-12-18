#pragma once
#include <string>

class Carta 
{
public:
    int valor;
    std::string nome;
    std::string naipe;

    Carta(int _valor, std::string _nome, std::string _naipe) : valor(_valor), nome(_nome),naipe(_naipe)
    {
    }
};
