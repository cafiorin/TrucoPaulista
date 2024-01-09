#pragma once

class IEventosDaPartida 
{
public:
    virtual ~IEventosDaPartida() {}

    virtual void onInicioDaPartida() = 0;
    virtual void onFimDaPartida() = 0;

    virtual void onInicioDaRodada(int numeroRodada) = 0;
    virtual void onFimDaRodada(int numeroRodada, Jogador *JogadorQueGanhou) = 0;

    virtual void solicitaJogadorJogar(Jogador* jogador) = 0;
    // Outros eventos, como jogadas, truco, etc...
    // Adicione aqui métodos conforme o necessário
};

