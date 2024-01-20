#include "pch.h"
#include "json\include\json.h"
#include "PersistenciaController.h"
#include <fstream>

PersistenciaController::PersistenciaController(Jogador* quemComecaRodada,
											   Jogador* ultimoJogadorAJogar,
											   Placar* placar,
											   Jogador* dupla1[2],
											   Jogador* dupla2[2],
											   RodadasController* rodadas,
											   Carta* vira, 
											   Partida* jogo) {
	QuemComecaRodada = quemComecaRodada;
	UltimoJogadorAJogar = ultimoJogadorAJogar;
	PlacarDaPartida = placar;
	
	Dupla1[0] = dupla1[0];
	Dupla1[1] = dupla1[1];

	Dupla2[0] = dupla2[0];
	Dupla2[1] = dupla1[1];

	Rodadas = rodadas;
	Vira = vira;

	Jogo = jogo;
}

PersistenciaController::~PersistenciaController() {
	delete QuemComecaRodada;
	delete UltimoJogadorAJogar;
	delete PlacarDaPartida;
	delete Dupla1[0];
	delete Dupla1[1];
	delete Dupla2[0];
	delete Dupla2[1];
	delete Rodadas;
	delete Vira;
	delete Jogo;
}

bool PersistenciaController::ContinuarJogoPausado() {
	std::ofstream arquivoTruco(nomeArquivo, std::ios::out);

	if (!arquivoTruco)
		return false;

	if (arquivoTruco.is_open())
	{
		// Solicitar ao usuário se ele deseja continuar

		arquivoTruco.close();
	}

	return false;
}

void PersistenciaController::CriarArquivo() {
	std::ofstream arquivoTruco(nomeArquivo);
}

void PersistenciaController::AtualizarArquivo() {
	std::string json = MontarJSON();
	PersistirJSON(json);
}

void PersistenciaController::RemoverArquivo() {
	std::remove(nomeArquivo.c_str());
}

void PersistenciaController::PersistirJSON(std::string& json) {
	std::ofstream trucoArquivo(nomeArquivo.c_str(), std::ios::out | std::ios::trunc);

	if (trucoArquivo.is_open()) {
		trucoArquivo << json;
		trucoArquivo.close();
	}
}

Json::Value const PersistenciaController::GetCarta(Carta* carta) {

	Json::Value cartaViradaObject;
	cartaViradaObject["id"] = carta->id;
	cartaViradaObject["valor"] = carta->valor;
	cartaViradaObject["nome"] = carta->nome;
	cartaViradaObject["naipe"] = carta->naipe;

	return cartaViradaObject;
}

Json::Value const PersistenciaController::GetRodada() {
	Rodada* rodadaAtual = Rodadas->PegarRodadaAtual();

	Json::Value rodada;

	rodada["numeroDaRodada"] = Rodadas->QualRodadaEsta();

	Json::Value cartasDaMesa;

	for (int i = 0; i < 4; i++)
	{
		CartaDaRodada* cartaDaRodada = rodadaAtual->cartas[i];

		if (cartaDaRodada == nullptr)
			break;

		Json::Value carta;
		carta["cartaCoberta"] = cartaDaRodada->CartaCoberta;
		carta["idJogador"] = cartaDaRodada->JogadorDaCarta->ObtemNumeroJogador();

		Json::Value cartaJogada;
		cartaJogada["id"] = cartaDaRodada->CartaJogadaNaRodada->id;
		cartaJogada["valor"] = cartaDaRodada->CartaJogadaNaRodada->valor;
		cartaJogada["nome"] = cartaDaRodada->CartaJogadaNaRodada->nome;
		cartaJogada["naipe"] = cartaDaRodada->CartaJogadaNaRodada->naipe;
		carta["cartaJogada"] = cartaJogada;
		cartasDaMesa.append(carta);

		delete cartaDaRodada;
	}

	rodada["cartasDaMesa"] = cartasDaMesa;
	int valorDaPartida = Rodadas->QuantoEstaValendoARodada();
	rodada["valorDaRodada"] = valorDaPartida;

	if (valorDaPartida > 1) // Se valor da partida for maior que 1 alguém pediu truco
		rodada["idJogadorPediuTruco"] = Jogo->GetJogadorAtual()->ObtemNumeroJogador();
	
	delete rodadaAtual;

	return rodada;
}

Json::Value const PersistenciaController::GetMao(std::vector<Carta*> mao) {
	Json::Value maoDoJogador;

	int numCartas = std::count_if(mao.begin(), mao.end(), [](Carta* carta) {
		return carta != nullptr;
	});

	for (int i = 0; i < numCartas; i++)
		maoDoJogador.append(GetCarta(mao[i]));

	return maoDoJogador;
}

Json::Value const PersistenciaController::GetJogadores() {
	Json::Value jogadores;

	for (int i = 0; i < 2; i++)
	{
		Json::Value jogador;

		jogador["id"] = Dupla1[i]->ObtemNumeroJogador();
		jogador["bot"] = Dupla1[i]->EhUmBot();
		bool estaNaVezDeJogar = Jogo->GetJogadorAtual()->ObtemNumeroJogador() == Dupla1[i]->ObtemNumeroJogador();
		jogador["vezDeJogar"] = estaNaVezDeJogar;

		jogador["mao"] = GetMao(Dupla1[i]->GetCartasNaoJogadas());

		jogadores.append(jogador);
	}

	return jogadores;
}

Json::Value const PersistenciaController::GetTime(int pontosDoTime, int partidasVencidas) {
	Json::Value time;

	time["pontosDoTime"] = pontosDoTime;
	time["partidasVencidas"] = partidasVencidas;

	time["jogadores"] = GetJogadores();

	return time;
}

Json::Value const PersistenciaController::GetTimes() {
	Json::Value times;

	times.append(GetTime(PlacarDaPartida->PontosDaDupla1, PlacarDaPartida->PartidasVencidasDaDupla1));
	times.append(GetTime(PlacarDaPartida->PontosDaDupla2, PlacarDaPartida->PartidasVencidasDaDupla2));

	return times;
}

std::string PersistenciaController::MontarJSON() {
	Json::Value json;

	json["cartaVirada"] = GetCarta(Vira);
	json["rodadaAtual"] = GetRodada();
	json["times"] = GetTimes();

	Json::StreamWriterBuilder writer;
	return Json::writeString(writer, json);
}

/*  [JSON]
{
	[OK]CartaVirada<Carta>
	{
		Id<int>,
		Valor<int>,
		Nome<string>,
		Naipe<int>
	},
	[OK]Rodada<Rodada>
	{
		NumeroRodada<int>,
		CartasDaMesa<CartaDaRodade[4]>
		{
			[CartaCoberta<bool>, IdJogador<int>, CartaJogada<Carta> ],
			[...],
			[...],
			[...]
		},
		ValorRodada<int>,
		IdJogadorQuePediuTruco<int>
	},
	Time<Partida[2]>
	{
		[
			Jogador<Jogador[2]>
			{
				[
					Id<int>,
					Mão<Mão[3]>
					{
						[Id<int>, Valor<int>, Nome<string>, Naipe<string>],
						[...],
						[...]
					},
					Bot<bool>,
					Vez<bool>
				],
				[ ... ]
			},
			Pontos<int>
		],
		[...]
	}
}

*/