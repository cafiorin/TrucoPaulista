#pragma once
#include "Jogador.h"
#include "Enums.h"
#include "Carta.h"

#include <utility>
#include <map>
#include <vector>
#include <algorithm>
#include <cstdlib>

class BotJogaSozinho : public Jogador
{
public:
	BotJogaSozinho(int numero, std::string nome);
	~BotJogaSozinho();

	const Carta* FazerUmaJogadaRebatendo();
	const Carta* FazerUmaJogadaComecando();

	virtual void InicializaRodada(RodadasController* mesaDaRodada);
	virtual bool AceitarTruco();
	virtual bool PedeTruco();
	virtual const Carta* FazerUmaJogada();

	ValorDasCartasNaMao AnalisarMaoDeCartas();
	void CalcularQualidadeDasCartas(int valor, int& otimas, int& medias, int& ruims);
	ValorDasCartasNaMao AnalisarValorFinal(int otimas, int medias, int ruims);
	ValorDasCartasNaMao QualidadeDasCartasNaRodada;
	bool CalcularSeDeveTrucarOuCorrerOuAceitar(ProbabilidadeDeTrucarOuCorrerOuAceitar probabilidade);
	const Carta* PrimeiraCartaMaiorNaMao(const Carta* cartaDoAdversario);
	bool TemCartaMaiorNaMao(const Carta* cartaDoAdversario);
	const Carta* PegaAMelhorOuPiorCartaNaMao(bool melhor);

//
//private:
//	ValorDasCartasNaMao AnalisarMaoDeCartas();
//	void PreencherValorFinalCartas(const Carta* carta, std::map<ValorDasCartasNaMao, int>& valor_final);
//	ValorDasCartasNaMao AnalisarValorFinal(std::map<ValorDasCartasNaMao, int>& valor_final);
//	void JogarRodadaNormal(PosicaoNaDuplaParaJogar posicao, bool adversario_esta_trucando, std::pair<const Carta*, bool> carta_mais_alta_rodada, int valor_da_rodada_atual);
//	void JogarRodadaMelando(PosicaoNaDuplaParaJogar posicao, bool adversario_esta_trucando, std::pair<const Carta*, bool> carta_mais_alta_rodada, int valor_da_rodada_atual);
//	void JogarComoPrimeiroEComAdversarioTrucando(std::pair<const Carta*, bool> carta_mais_alta_rodada, int valor_da_rodada_atual);
//	void JogarComoPrimeiroEComAdversarioNaoTrucando(std::pair<const Carta*, bool> carta_mais_alta_rodada, int valor_da_rodada_atual);
//	void JogarComoPeEComAdversarioTrucando(std::pair<const Carta*, bool> carta_mais_alta_rodada, int valor_da_rodada_atual);
//	void JogarComoPeEComAdversarioNaoTrucando(std::pair<const Carta*, bool> carta_mais_alta_rodada, int valor_da_rodada_atual);
//	std::vector<const Carta*> OrdenarCartasDaMao();
//


};

