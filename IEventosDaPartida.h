#pragma once
#include "Jogador.h"

class IEventosDaPartida 
{
public:
    virtual ~IEventosDaPartida() {}

    virtual void onInicioDaPartida() = 0;
    virtual void onFimDaPartida(Jogador* ganhou) = 0;

    virtual void onInicioDaRodada(int numeroRodada) = 0;
    virtual void onFimDaRodada(int numeroRodada, Jogador *JogadorQueGanhou) = 0;

    virtual void onAcabouARodada(Jogador* JogadorQueGanhou) = 0;

    virtual void solicitaJogadorJogar(Jogador* jogador) = 0;
    virtual void onBotJogouACarta(int NumeroDaRodada, Jogador* jogadorAjogar, const Carta* cartaJogada, bool cartaCoberta) = 0;
    virtual void onPedeTruco(Jogador* jogador) = 0;
    virtual void onAceitouTruco(Jogador* jogador)=0;
    virtual void onCartaJogada(int NumeroDaRodada, Jogador* jogador, const Carta* carta, bool cartaCoberta) = 0;

    // TODO:
    // Outros eventos, como jogadas, truco, etc...
    // Adicione aqui métodos conforme o necessário
};

