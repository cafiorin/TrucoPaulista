#include "pch.h"
#include "Carta.h"

#define IDB_BITMAP_BASE  183


Carta::Carta(int _id, int _valor, std::string _nome, Naipes _naipe) : id(_id), valor(_valor), nome(_nome), naipe(_naipe)
{
    idResource = (IDB_BITMAP_BASE - 1) + id + ((int)naipe - 1) * 13;
}

Carta::Carta(Carta* carta)
{
    id = carta->id;
    valor = carta->valor;
    nome = carta->nome;
    naipe = carta->naipe;

    idResource = (IDB_BITMAP_BASE - 1) + id + ((int)naipe - 1) * 13;
}

int Carta::ObtemValor(const Carta* vira) const
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

