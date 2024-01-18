#pragma once
#include <string>
#include "Enums.h"

class Carta 
{
public:
    int idResource;
    int id;
    int valor;
    std::string nome;
    Naipes naipe;

    Carta(int _id, int _valor, std::string _nome, Naipes _naipe);
    Carta(Carta* carta);
    int ObtemValor(const Carta* vira) const;

    // Sobrecarga do operador de igualdade
    bool operator==(const Carta& outraCarta) const 
    {
        return idResource == outraCarta.idResource;
    }

    // Sobrecarga do operador de desigualdade
    bool operator!=(const Carta& outraCarta) const 
    {
        return !(*this == outraCarta);
    }

};
