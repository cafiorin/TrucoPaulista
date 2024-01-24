#include "pch.h"
#include "PersistenciaController.h"
#include <fstream>

PersistenciaController::PersistenciaController(Partida* jogo) 
{

	PlacarDaPartida = jogo->GetPlacar();
	
	Dupla1[0] = jogo->ObtemJogadorHumano1();
	Dupla1[1] = jogo->ObtemJogadorHumano2();

	Dupla2[0] = jogo->ObtemJogadorBot1();
	Dupla2[1] = jogo->ObtemJogadorBot2();

	Rodadas = jogo->GetRodada();
	Vira = jogo->ObtemVira();
}

PersistenciaController::~PersistenciaController() 
{
}

bool PersistenciaController::TemJogoSalvo() 
{
	std::ofstream arquivoTruco(nomeArquivo, std::ios::out);

	if (!arquivoTruco)
		return false;

	arquivoTruco.seekp(0, std::ios::end);

	if (arquivoTruco.is_open() && arquivoTruco.tellp() != 0)
	{
		// Solicitar ao usuário se ele deseja continuar

		arquivoTruco.close();
		return true;
	}

	arquivoTruco.close();

	return false;
}

void PersistenciaController::AtualizarArquivo() 
{
	std::string json = MontarJSON();
	PersistirJSON(json);
}

void PersistenciaController::RemoverArquivo() 
{
	std::remove(nomeArquivo.c_str());
}

void PersistenciaController::PersistirJSON(std::string& json) 
{
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
	Json::Value rodada;

	rodada["numeroDaRodada"] = Rodadas->QualRodadaEsta();

	Json::Value cartasDaMesa;

	for (int i = 0; i < 4; i++)
	{
		if (Rodadas->PegarRodadaAtual()->cartas[i] == nullptr) {
			break;
		}

		Json::Value carta;
		carta["cartaCoberta"] = Rodadas->PegarRodadaAtual()->cartas[i]->CartaCoberta;
		carta["idJogador"] = Rodadas->PegarRodadaAtual()->cartas[i]->JogadorDaCarta->ObtemNumeroJogador();

		Json::Value cartaJogada;
		cartaJogada["id"] = Rodadas->PegarRodadaAtual()->cartas[i]->CartaJogadaNaRodada->id;
		cartaJogada["valor"] = Rodadas->PegarRodadaAtual()->cartas[i]->CartaJogadaNaRodada->valor;
		cartaJogada["nome"] = Rodadas->PegarRodadaAtual()->cartas[i]->CartaJogadaNaRodada->nome;
		cartaJogada["naipe"] = Rodadas->PegarRodadaAtual()->cartas[i]->CartaJogadaNaRodada->naipe;
		carta["cartaJogada"] = cartaJogada;
		cartasDaMesa.append(carta);
	}

	rodada["cartasDaMesa"] = cartasDaMesa;
	int valorDaPartida = Rodadas->QuantoEstaValendoARodada();
	rodada["valorDaRodada"] = valorDaPartida;

	if (valorDaPartida > 1) // Se valor da partida for maior que 1 alguém pediu truco
		rodada["idJogadorPediuTruco"] = Jogo->GetJogadorAtual()->ObtemNumeroJogador();
	
	return rodada;
}

Json::Value const PersistenciaController::GetMao(std::vector<Carta*> mao) {
	Json::Value maoDoJogador;

	__int64 numCartas = std::count_if(mao.begin(), mao.end(), [](Carta* carta) {
		return carta != nullptr;
	});

	for (int i = 0; i < numCartas; i++)
		maoDoJogador.append(GetCarta(mao[i]));

	return maoDoJogador;
}

Json::Value const PersistenciaController::GetJogadores(Jogador* dupla[2]) {
	Json::Value jogadores;

	for (int i = 0; i < 2; i++)
	{
		Json::Value jogador;

		jogador["id"] = dupla[i]->ObtemNumeroJogador();
		jogador["bot"] = dupla[i]->EhUmBot();
		bool estaNaVezDeJogar = Jogo->GetJogadorAtual()->ObtemNumeroJogador() == dupla[i]->ObtemNumeroJogador();
		jogador["vezDeJogar"] = estaNaVezDeJogar;

		jogador["mao"] = GetMao(dupla[i]->GetCartasNaoJogadas());

		jogadores.append(jogador);
	}

	return jogadores;
}

Json::Value const PersistenciaController::GetTime(Jogador* dupla[2], int pontosDoTime, int partidasVencidas) {
	Json::Value time;

	time["pontosDoTime"] = pontosDoTime;
	time["partidasVencidas"] = partidasVencidas;

	time["jogadores"] = GetJogadores(dupla);

	return time;
}

Json::Value const PersistenciaController::GetTimes() {
	Json::Value times;

	times.append(GetTime(Dupla1, PlacarDaPartida->PontosDaDupla1, PlacarDaPartida->PartidasVencidasDaDupla1));
	times.append(GetTime(Dupla2, PlacarDaPartida->PontosDaDupla2, PlacarDaPartida->PartidasVencidasDaDupla2));

	return times;
}

std::string PersistenciaController::MontarJSON() {
	Json::Value json;

	json["cartaVirada"] = GetCarta(Vira); //ok
	json["rodadaAtual"] = GetRodada(); //ok
	json["times"] = GetTimes();

	Json::StreamWriterBuilder writer;
	std::string value = Json::writeString(writer, json);

	return value;
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