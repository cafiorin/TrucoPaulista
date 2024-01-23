#pragma once
#include "Carta.h"
#include "Rodada.h"
#include "Placar.h"
#include "Baralho.h"
#include "Partida.h"
#include "json\include\json.h"

class PersistenciaController
{
public:
	PersistenciaController(Partida* jogo);
	~PersistenciaController();

	bool TemJogoSalvo();

	void RemoverArquivo();

	void AtualizarArquivo();

private:
	const std::string nomeArquivo = "_trucoPaulista.json";

	Placar* PlacarDaPartida;

	Jogador* Dupla1[2];
	Jogador* Dupla2[2];

	RodadasController* Rodadas;
	Carta* Vira;

	Partida* Jogo;

	std::string MontarJSON();
	void PersistirJSON(std::string &json);

	const Json::Value GetCarta(Carta* carta);
	const Json::Value GetRodada();
	const Json::Value GetTimes();
	const Json::Value GetJogadores(Jogador* dupla[2]);
	const Json::Value GetTime(Jogador* dupla[2], int pontosDoTime, int partidasVencidas);
	const Json::Value GetMao(std::vector<Carta*> mao);
};