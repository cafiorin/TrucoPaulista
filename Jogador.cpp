#include "pch.h"
#include "Jogador.h"
#include "RodadasController.h"
#include <random>
#include <algorithm> 

void Jogador::RecebeCartas(const Carta& carta1, const Carta& carta2, const Carta& carta3) 
{
    // Atribui as cartas ordenadas aos elementos do array mao
    mao[0] = std::make_unique<Carta>(carta1);
    mao[1] = std::make_unique<Carta>(carta2);
    mao[2] = std::make_unique<Carta>(carta3);

    CartaUsada[0] = false;
    CartaUsada[1] = false;
    CartaUsada[2] = false;

    status = EsperandoJogada;
}


void Jogador::OrdenaCartas()
{
    Carta tempMao[] = { *mao[0], *mao[1], *mao[2] };

    std::sort(std::begin(tempMao), std::end(tempMao),
        [this](const Carta& a, const Carta& b)
        {
            return (MesaDaRodada->MaiorCarta(&a, &b) == 1); 
        });

    *mao[0] = tempMao[0];
    *mao[1] = tempMao[1];
    *mao[2] = tempMao[2];
}


