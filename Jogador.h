#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <memory>

#include "Carta.h"

class Jogador 
{
private:
    int NumeroJogador;
    std::string Nome;
    std::unique_ptr<Carta> mao[3];
    StatusJogador status;
    bool Bot;

public:
    Jogador(int numero, std::string nome,bool bot) : NumeroJogador(numero), Nome(nome), status(EsperandoCartas),Bot(bot) {}

    void RecebeCartas(const Carta& carta1, const Carta& carta2, const Carta& carta3) {
        mao[0] = std::make_unique<Carta>(carta1);
        mao[1] = std::make_unique<Carta>(carta2);
        mao[2] = std::make_unique<Carta>(carta3);

        status = EsperandoJogada;
    }

    bool EhUmBot() const { return Bot; };

    std::string ObtemNome() const { return Nome; };


    const Carta* PrimeiraCartaNaMao() const {
        return mao[0].get(); // Retorna o ponteiro para o primeiro elemento do array
    }

    const Carta* SegundaCartaNaMao() const {
        return mao[1].get(); // Retorna o ponteiro para o segundo elemento do array
    }

    const Carta* TerceiraCartaNaMao() const {
        return mao[2].get(); // Retorna o ponteiro para o segundo elemento do array
    }

    const Carta* getjogadabot(int jogadasbot) const {
       
        return mao[jogadasbot].get(); // Retorna o ponteiro random carta
    }
    StatusJogador GetStatus() const {
        return status;
    }
};
