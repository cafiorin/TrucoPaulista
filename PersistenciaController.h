#pragma once
#include "Carta.h"
#include "Rodada.h"
#include "Placar.h"
#include "Baralho.h"
#include "Partida.h"
#include "Bot.h"
#include "BotJogaSozinho.h"
#include "json\include\json.h"

class PersistenciaController
{
public:
	PersistenciaController(Partida* jogo);
	~PersistenciaController();

	bool TemJogoSalvo();

	void RemoverArquivo();

	void AtualizarArquivo();

	Partida* RecriarPartida();

private:
	const std::string nomeArquivo = "_trucoPaulista.json";

	Placar* PlacarDaPartida;
	Jogador* Dupla1[2];
	Jogador* Dupla2[2];
	RodadasController* Rodadas;
	Carta* Vira;
	Jogador* JogadorAtual;
	int NumeroJogadores;
	bool MultiplasInstancias;

	void InicializarPersistencia(Partida* jogo);
	
	// Write
	std::string MontarJSON();
	void PersistirJSON(std::string &json);
	Json::Value GetCarta(Carta* carta);
	Json::Value GetRodada();
	Json::Value GetTimes();
	Json::Value GetJogadores(Jogador* dupla[2]);
	Json::Value GetTime(Jogador* dupla[2], int pontosDoTime, int partidasVencidas);
	Json::Value GetMao(Carta* mao[3]);
	Json::Value GetConfiguracoes();

	//Read
	Partida* MontarPartida(std::string json);
	Carta* CriarCarta(Json::Value cartaVirada);
	RodadasController* CriarRodadaController(Json::Value rodadaAtual, std::vector<Jogador*> jogadores, Placar* placar, Carta* vira);
	Partida* CriarPartida(Json::Value json);
};