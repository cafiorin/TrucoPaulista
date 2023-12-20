#include "pch.h"
#include <iostream>
#include <random>

#include "Baralho.h"


Baralho::Baralho()
{
    cartas = std::make_shared<std::vector<Carta>>();
    ConstruirBaralhoTrucoPaulista();
    Embaralhar();
}

void Baralho::Embaralhar()
{
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::shuffle(cartas->begin(), cartas->end(), rng);
}

Carta Baralho::PegarCartaDoTopo()
{
    if (cartas->empty())
    {
        throw std::out_of_range("Baralho vazio. Não é possível pegar mais cartas.");
    }
    Carta carta = cartas->back();
    cartas->pop_back();
    return carta;
}

void Baralho::ConstruirBaralhoTrucoPaulista()
{
    cartas->clear();
    
    int id = 1;
    for (int valor = 4; valor <= 13; ++valor)
    {
        std::string nome;

        switch (valor)
        {
        case 8:
            id = 12;
            nome = "Q";
            break;

        case 9:
            id = 11;
            nome = "J";
            break;

        case 10:
            id = 13;
            nome = "K";
            break;

        case 11:
            id = 1;
            nome = "A";
            break;

        case 12:
            id = 2;
            nome = "2";
            break;

        case 13:
            id = 3;
            nome = "3";
            break;

        default:
            id = valor;
            nome = std::to_string(valor);
            break;
        }

        for (int naipes=1; naipes<=4; naipes++)
        {
            cartas->push_back(Carta(id, valor, nome, (Naipes) naipes));
        }
    }
}