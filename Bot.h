#pragma once
#include "Jogador.h"
#include "Enums.h"
#include "Carta.h"

#include <utility>
#include <map>
#include <vector>
#include <algorithm>
#include <cstdlib>

class Bot : public Jogador {
public:
	Bot(int numero, std::string nome);
	~Bot();

	void FazerUmaJogada(NumeroDaRodada tipo_rodada, PosicaoNaDuplaParaJogar posicao, bool adversario_esta_trucando, std::pair<const Carta*, bool> carta_mais_alta_rodada);

private:
	ValorDasCartasNaMao AnalisarMaoDeCartas();
	void PreencherValorFinalCartas(const Carta* carta, std::map<ValorDasCartasNaMao, int>& valor_final);
	ValorDasCartasNaMao AnalisarValorFinal(std::map<ValorDasCartasNaMao, int>& valor_final);
	void JogarPrimeiraRodada(PosicaoNaDuplaParaJogar posicao, bool adversario_esta_trucando, std::pair<const Carta*, bool> carta_mais_alta_rodada, ValorDasCartasNaMao& valor_mao);
	void JogarComoPrimeiroEComAdversarioTrucando(std::pair<const Carta*, bool> carta_mais_alta_rodada, ValorDasCartasNaMao& valor_mao);
	void JogarComoPrimeiroEComAdversarioNaoTrucando(std::pair<const Carta*, bool> carta_mais_alta_rodada, ValorDasCartasNaMao& valor_mao);
	void JogarComoPeEComAdversarioTrucando(std::pair<const Carta*, bool> carta_mais_alta_rodada, ValorDasCartasNaMao& valor_mao);
	void JogarComoPeEComAdversarioNaoTrucando(std::pair<const Carta*, bool> carta_mais_alta_rodada, ValorDasCartasNaMao& valor_mao);
	std::vector<const Carta*> OrdenarCartasDaMao();
	bool CalcularSeDeveTrucarOuCorrerOuAceitar(ProbabilidadeDeTrucarOuCorrerOuAceitar probabilidade);
};

