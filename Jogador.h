#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <memory>
#include <ctime>

#include "Carta.h"
class RodadasController;

class Jogador 
{
protected:
    int NumeroJogador;
    std::string Nome;
    std::unique_ptr<Carta> mao[3];
    bool CartaUsada[3];
    StatusJogador status;
    bool Bot;
    bool PodePedirTruco;
    RodadasController* MesaDaRodada;

public:
    Jogador(int numero, std::string nome,bool bot) : NumeroJogador(numero), Nome(nome), status(EsperandoCartas),Bot(bot), PodePedirTruco(true){}

    std::string ObtemNome() const
    {
        return Nome;
    };

    int ObtemNumeroJogador()
    {
        return NumeroJogador;
    };

    bool PodeTrucar() { return PodePedirTruco; }
    void JaPodePedirTruco() { PodePedirTruco = true; }
    void NaoPodeMaisPedirTruco() { PodePedirTruco = false; }
    bool EhUmBot() const { return Bot; };

    void RecebeCartas(const Carta& carta1, const Carta& carta2, const Carta& carta3);
    void OrdenaCartas();

    const Carta* PrimeiraCartaNaMao() const 
    {
        return mao[0].get(); // Retorna o ponteiro para o primeiro elemento do array
    }

    const Carta* SegundaCartaNaMao() const 
    {
        return mao[1].get(); // Retorna o ponteiro para o segundo elemento do array
    }

    const Carta* TerceiraCartaNaMao() const 
    {
        return mao[2].get(); // Retorna o ponteiro para o segundo elemento do array
    }

    const Carta* getjogadabot(int jogadasbot) const
    {
        return mao[jogadasbot].get(); 
    }

    StatusJogador GetStatus() const 
    {
        return status;
    }

    virtual void InicializaRodada(RodadasController* mesaDaRodada)
    {
        MesaDaRodada = mesaDaRodada;
        OrdenaCartas();
    }

    virtual bool AceitarTruco() 
    {
        srand(static_cast<unsigned int>(time(nullptr)));
        return (rand() % 2 == 1);
    }

   virtual bool PedeTruco()
    {
        srand(static_cast<unsigned int>(time(nullptr)));
        if(PodePedirTruco)
            return (rand() % 5 == 1);
        return false;
    }

   virtual const Carta* FazerUmaJogada()
   {
       return nullptr;
   }

};
