#pragma once
#include "Jogador.h"
#include "Enums.h"
#include "Carta.h"

#include <utility>
#include <map>
#include <vector>
#include <algorithm>
#include <cstdlib>

class Bot : public Jogador
{
public:
	Bot(int numero, std::string nome);
	~Bot();

	/**
	* Esse metodo eh usado para passar todas as informacoes necessarias para o bot poder fazer uma jogada.
	* Com esse metodo, o bot pode jogar cartas e tomar a decisao de pedir um truco
	* Inputs da funcao e valores possiveis:
	*	1. tipo_rodada: { PrimeiraRodada, SegundaRodada, TerceiraRodada, Melando, MaoDeOnze }
	*	2. posicao: { Primeiro, Pe }
	*	3. adversario_esta_trucando: { true, false }
	*	4. carta_mais_alta_rodada: { Carta, eh_da_sua_dupla [true/false] }
	*	5. valor_da_rodada_atual: { 1, 3, 6, 9, 12 }
	* Caso o Bot decida pedir um truco, o resultado da decisao vai ficar guardado em deve_pedir_truco_ e deve ser lido atraves do metodo Bot::PedeTruco()
	*/
	void FazerUmaJogada(NumeroDaRodadaAtual tipo_rodada, PosicaoNaDuplaParaJogar posicao, bool adversario_esta_trucando, std::pair<const Carta*, bool> carta_mais_alta_rodada, int valor_da_rodada_atual);

	/**
	* Esse metodo eh usado para fazer o Bot decidir se deve aceitar ou correr de um truco que foi pedido pelo adversario
	* Inputs da funcao e valores possiveis:
	*	1. tipo_rodada: { PrimeiraRodada, SegundaRodada, TerceiraRodada, Melando }
	*	2. posicao: { Primeiro, Pe }
	*	4. carta_mais_alta_rodada: { Carta, eh_da_sua_dupla [true/false] }
	*	5. dupla_esta_ganhando_ou_empatado: [true/false]
	* O resultado da decisao do Bot vai ficar guardado em deve_aceitar_o_truco_ e deve ser lido atraves do metodo Bot::AceitarTruco()
	*/
	void VerificarSeDeveAceitarOuCorrer(NumeroDaRodadaAtual tipo_rodada, PosicaoNaDuplaParaJogar posicao, std::pair<const Carta*, bool> carta_mais_alta_rodada, bool dupla_esta_ganhando_ou_empatado);

	/**
	* Esses metodos sao usados para ler o valor da decisao tomada pelo bot, se deve pedir truco ou se deve aceitar/correr de um truco
	*/
	bool AceitarTruco();
	bool PedeTruco();

private:
	ValorDasCartasNaMao AnalisarMaoDeCartas();
	void PreencherValorFinalCartas(const Carta* carta, std::map<ValorDasCartasNaMao, int>& valor_final);
	ValorDasCartasNaMao AnalisarValorFinal(std::map<ValorDasCartasNaMao, int>& valor_final);
	void JogarRodadaNormal(PosicaoNaDuplaParaJogar posicao, bool adversario_esta_trucando, std::pair<const Carta*, bool> carta_mais_alta_rodada, int valor_da_rodada_atual);
	void JogarRodadaMelando(PosicaoNaDuplaParaJogar posicao, bool adversario_esta_trucando, std::pair<const Carta*, bool> carta_mais_alta_rodada, int valor_da_rodada_atual);
	void JogarComoPrimeiroEComAdversarioTrucando(std::pair<const Carta*, bool> carta_mais_alta_rodada, int valor_da_rodada_atual);
	void JogarComoPrimeiroEComAdversarioNaoTrucando(std::pair<const Carta*, bool> carta_mais_alta_rodada, int valor_da_rodada_atual);
	void JogarComoPeEComAdversarioTrucando(std::pair<const Carta*, bool> carta_mais_alta_rodada, int valor_da_rodada_atual);
	void JogarComoPeEComAdversarioNaoTrucando(std::pair<const Carta*, bool> carta_mais_alta_rodada, int valor_da_rodada_atual);
	std::vector<const Carta*> OrdenarCartasDaMao();
	bool CalcularSeDeveTrucarOuCorrerOuAceitar(ProbabilidadeDeTrucarOuCorrerOuAceitar probabilidade);
	void LimparDecisoesDoBot();
	void SetAceitarTruco(bool decisao);
	void SetPedeTruco(bool decisao);

	void VerificarSeDeveAceitarPrimeiraRodada(PosicaoNaDuplaParaJogar posicao, std::pair<const Carta*, bool> carta_mais_alta_rodada);
	void VerificarSeDeveAceitarSegundaRodada(PosicaoNaDuplaParaJogar posicao, std::pair<const Carta*, bool> carta_mais_alta_rodada, bool dupla_esta_ganhando_ou_empatado);

	bool deve_aceitar_o_truco_;
	bool deve_pedir_truco_;
};

