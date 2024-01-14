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
	*	3. carta_mais_alta_rodada: { Carta, eh_da_sua_dupla [true/false] }
	*	4. vira: { Carta }
	* Caso o Bot decida pedir um truco, o resultado da decisao vai ficar guardado em deve_pedir_truco_ e deve ser lido atraves do metodo Bot::PedeTruco()
	* Caso o Bot escolha uma carta para jogar e não peça truco, a carta deve ser lida atraves do metodo Bot::GetJogadaBot()
	*/
	void FazerUmaJogada(NumeroDaRodadaAtual tipo_rodada, PosicaoNaDuplaParaJogar posicao, std::pair<const Carta*, bool> carta_mais_alta_rodada, const Carta* vira);

	/**
	* Esse metodo eh usado para fazer o Bot decidir se deve aceitar ou correr de um truco que foi pedido pelo adversario
	* Inputs da funcao e valores possiveis:
	*	1. tipo_rodada: { PrimeiraRodada, SegundaRodada, TerceiraRodada, Melando }
	*	2. posicao: { Primeiro, Pe }
	*	3. carta_mais_alta_rodada: { Carta, eh_da_sua_dupla [true/false] }
	*	4. dupla_esta_ganhando_ou_empatado: [true/false]
	*	5. vira: { Carta }
	* O resultado da decisao do Bot vai ficar guardado em deve_aceitar_o_truco_ e deve ser lido atraves do metodo Bot::AceitarTruco()
	*/
	void VerificarSeDeveAceitarOuCorrer(NumeroDaRodadaAtual tipo_rodada, PosicaoNaDuplaParaJogar posicao, std::pair<const Carta*, bool> carta_mais_alta_rodada, bool dupla_esta_ganhando_ou_empatado, const Carta* vira);

	/**
	* Esses metodos sao usados para ler o valor da decisao tomada pelo bot, se deve pedir truco ou se deve aceitar/correr de um truco e também a carta escolhida
	*/
	bool AceitarTruco();
	bool PedeTruco();
	const Carta* GetJogadaBot();

private:
	ValorDasCartasNaMao AnalisarMaoDeCartas();
	void PreencherValorFinalCartas(const Carta* carta, std::map<ValorDasCartasNaMao, int>& valor_final);
	ValorDasCartasNaMao AnalisarValorFinal(std::map<ValorDasCartasNaMao, int>& valor_final);

	void JogarRodadaNormal(PosicaoNaDuplaParaJogar posicao, std::pair<const Carta*, bool> carta_mais_alta_rodada, const Carta* vira);
	void JogarRodadaMelando(PosicaoNaDuplaParaJogar posicao, std::pair<const Carta*, bool> carta_mais_alta_rodada, const Carta* vira);
	void JogarComoPrimeiro(std::pair<const Carta*, bool> carta_mais_alta_rodada, const Carta* vira);
	void JogarComoPe(std::pair<const Carta*, bool> carta_mais_alta_rodada, const Carta* vira);

	std::vector<const Carta*> OrdenarCartasDaMao(const Carta* vira);
	bool CalcularSeDeveTrucarOuCorrerOuAceitar(ProbabilidadeDeTrucarOuCorrerOuAceitar probabilidade);
	void LimparDecisoesDoBot();
	void SetAceitarTruco(bool decisao);
	void SetPedeTruco(bool decisao);
	void SetJogadaBot(const Carta* carta_escolhida);

	void VerificarSeDeveAceitarPrimeiraRodada(PosicaoNaDuplaParaJogar posicao, std::pair<const Carta*, bool> carta_mais_alta_rodada, const Carta* vira);
	void VerificarSeDeveAceitarSegundaRodada(PosicaoNaDuplaParaJogar posicao, std::pair<const Carta*, bool> carta_mais_alta_rodada, bool dupla_esta_ganhando_ou_empatado, const Carta* vira);

	bool deve_aceitar_o_truco_;
	bool deve_pedir_truco_;
	const Carta* jogada_bot_;
};

