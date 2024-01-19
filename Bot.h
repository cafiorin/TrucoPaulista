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

	// overrides Jogador.h
	// Esse metodo eh usado para fazer o Bot decidir se deve aceitar ou correr de um truco que foi pedido pelo adversario
	bool AceitarTruco() override;

	// Esse metodo eh usado para fazer o Bot decidir se deve pedir um truco
	bool PedeTruco() override;

	// Esse metodo eh usado para fazer o Bot escolher uma carta
	const Carta* FazerUmaJogada() override;

private:
	const Carta* JogarRodadaNormal();
	const Carta* JogarRodadaMelando();
	const Carta* JogarComoPrimeiro();
	const Carta* JogarComoPe();

	std::vector<const Carta*> OrdenarCartasDaMao(const Carta* vira);
	bool CalcularSeDeveTrucarOuCorrerOuAceitar(ProbabilidadeDeTrucarOuCorrerOuAceitar probabilidade);

	bool VerificarSeDeveAceitarPrimeiraRodada(std::pair<const Carta*, bool> carta_mais_alta_rodada, const Carta* vira);
	bool VerificarSeDeveAceitarSegundaRodada(std::pair<const Carta*, bool> carta_mais_alta_rodada, bool dupla_esta_ganhando_ou_empatado, const Carta* vira);
};

