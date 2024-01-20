#pragma once
#include "Carta.h"
#include "Rodada.h"
#include "Placar.h"
#include "Baralho.h"
#include "Partida.h"

class PersistenciaController
{
public:
	const std::string nomeArquivo = "trucoPaulista.json";

	PersistenciaController(Jogador* quemComecaRodada, 
						   Jogador* ultimoJogadorAJogar,
						   Placar* placar,
						   Jogador* dupla1[2],
						   Jogador* dupla2[2],
						   RodadasController* rodadas,
						   Carta* vira,
						   Partida* jogo);
	~PersistenciaController();

	bool ContinuarJogoPausado();

	void CriarArquivo();

	void RemoverArquivo();

	void AtualizarArquivo();

private:
	Jogador* QuemComecaRodada;
	Jogador* UltimoJogadorAJogar;

	Placar* PlacarDaPartida;

	Jogador* Dupla1[2];
	Jogador* Dupla2[2];

	RodadasController* Rodadas;
	Baralho* BaralhoMesa;
	Carta* Vira;

	Partida* Jogo;

	std::string MontarJSON();
	void PersistirJSON(std::string &json);

	const Json::Value GetCarta(Carta* carta);
	const Json::Value GetRodada();
	const Json::Value GetTimes();
	const Json::Value GetJogadores();
	const Json::Value GetTime(int pontosDoTime, int partidasVencidas);
	const Json::Value GetMao(std::vector<Carta*> mao);
};