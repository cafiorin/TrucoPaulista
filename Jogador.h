#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <memory>
#include <ctime>
#include <vector>
#include "Enums.h"

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
    int NumeroDaDupla;
    bool MostraCartaDistribuida;

public:
    Jogador(int numero, std::string nome, int numeroDaDupla, bool bot, bool mostraCartaDistribuida) : NumeroJogador(numero), Nome(nome), 
        status(EsperandoCartas), NumeroDaDupla(numeroDaDupla), Bot(bot), PodePedirTruco(true), MostraCartaDistribuida(mostraCartaDistribuida){}
    bool PodeMostrarAsCartas() { return MostraCartaDistribuida; }
    std::string ObtemNome() const { return Nome; }
    int ObtemNumeroJogador() { return NumeroJogador; }
    int ObtemNumeroDaDupla() { return NumeroDaDupla; }
    bool PodeTrucar() { return PodePedirTruco; }
    void JaPodePedirTruco() { PodePedirTruco = true; }
    void NaoPodeMaisPedirTruco() { PodePedirTruco = false; }
    bool EhUmBot() const { return Bot; }

    void RecebeCartas(const Carta& carta1, const Carta& carta2, const Carta& carta3);
    void RecebeCartas(const Carta& carta1, bool carta1Jogada, const Carta& carta2, bool carta2Jogada, const Carta& carta3, bool carta3Jogada);
    void OrdenaCartas();

    const std::vector<std::tuple<Carta*, bool>> GetCartasDoJogador() {
        std::vector<std::tuple<Carta*, bool>> cartasDoJogador;

        for (int i = 0; i < 3; i++)
            cartasDoJogador.push_back(std::make_tuple(mao[i].get(), CartaUsada[i]));

        return cartasDoJogador;
    }

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

   virtual void InicializaRodada(RodadasController* mesaDaRodada);
   virtual bool AceitarTruco();
   virtual bool PedeTruco();
   virtual const Carta* FazerUmaJogada()
   {
       return nullptr;
   }


   ValorDasCartasNaMao AnalisarMaoDeCartas();
   void CalcularQualidadeDasCartas(int valor, int& otimas, int& medias, int& ruims);
   ValorDasCartasNaMao AnalisarValorFinal(int otimas, int medias, int ruims);
   ValorDasCartasNaMao QualidadeDasCartasNaRodada;
   bool CalcularSeDeveTrucarOuCorrerOuAceitar(ProbabilidadeDeTrucarOuCorrerOuAceitar probabilidade);
   bool CalcularSeDeveFazerAcao(ProbabilidadeDeTrucarOuCorrerOuAceitar probabilidade);
   const Carta* PrimeiraCartaMaiorNaMao(const Carta* cartaDoAdversario);
   bool TemCartaMaiorNaMao(const Carta* cartaDoAdversario);
   const Carta* PegaAMelhorOuPiorCartaNaMao(bool melhor);
   void CartaQueFoiUsada(const Carta* cartaUsada);
};
