#include "pch.h"
#include "PersistenciaController.h"
#include <fstream>

#pragma region public

PersistenciaController::PersistenciaController(Partida* jogo) 
{
	if (jogo != nullptr)
		InicializarPersistencia(jogo);
}

PersistenciaController::~PersistenciaController() 
{
}

bool PersistenciaController::TemJogoSalvo() 
{
	std::ifstream arquivoTruco(nomeArquivo);

	if (!arquivoTruco)
		throw PersistenciaException();

	if (arquivoTruco.is_open() && arquivoTruco.peek() != std::ifstream::traits_type::eof())
	{
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

Partida* PersistenciaController::RecriarPartida() {

	if (TemJogoSalvo())
	{
		std::ifstream arquivo(nomeArquivo);

		std::string json(std::istreambuf_iterator<char>(arquivo), {});

		Partida* partida = MontarPartida(json);

		arquivo.close();

		return partida;
	}
}

void PersistenciaController::InicializarPersistencia(Partida* jogo) {
	PlacarDaPartida = jogo->GetPlacar();

	Dupla1[0] = jogo->ObtemJogadorHumano1();
	Dupla1[1] = jogo->ObtemJogadorHumano2();

	Dupla2[0] = jogo->ObtemJogadorBot1();
	Dupla2[1] = jogo->ObtemJogadorBot2();

	Rodadas = jogo->GetRodada();
	Vira = jogo->ObtemVira();

	JogadorAtual = jogo->GetJogadorAtual();

	NumeroJogadores = jogo->PegarNumeroJogadores();
	MultiplasInstancias = jogo->MultiInstancia();
}

#pragma endregion

#pragma region private

#pragma region write

void PersistenciaController::PersistirJSON(std::string& json) 
{
	std::ofstream trucoArquivo(nomeArquivo.c_str(), std::ios::out | std::ios::trunc);

	if (trucoArquivo.is_open()) {
		trucoArquivo << json;
		trucoArquivo.close();
	}
}

Json::Value PersistenciaController::GetCarta(Carta* carta) {

	Json::Value cartaViradaObject;
	cartaViradaObject["id"] = carta->id;
	cartaViradaObject["valor"] = carta->valor;
	cartaViradaObject["nome"] = carta->nome;
	cartaViradaObject["naipe"] = carta->naipe;

	return cartaViradaObject;
}

Json::Value PersistenciaController::GetHistoricoRodadas() {
	Json::Value historicoPartida;
	Json::Value historicoRodada;

	historicoPartida["quantasVezesTrucou"] = Rodadas->QuantosVezesTrucou();
	historicoPartida["numeroDaRodadaAtual"] = Rodadas->QualRodadaEsta();
	int valorDaPartida = Rodadas->QuantoEstaValendoARodada();
	historicoPartida["valorDaRodada"] = valorDaPartida;
	if (valorDaPartida > 1) // Se valor da partida for maior que 1 alguém pediu truco
		historicoPartida["idJogadorPediuTruco"] = JogadorAtual->ObtemNumeroJogador();

	for (int idxRodada = 0; idxRodada < 3; idxRodada++)
	{
		Json::Value rodada;

		Rodada* hRodada = Rodadas->PegarRodada(idxRodada);
		if (hRodada == nullptr)
			continue;

		rodada["numeroDaRodada"] = idxRodada + 1;
		
		Json::Value cartasNaMesaDaRodada;

		for (int i = 0; i < 4; i++)
		{
			if (hRodada->cartas[i] == nullptr) {
				break;
			}

			Json::Value carta;
			carta["cartaCoberta"] = hRodada->cartas[i]->CartaCoberta;
			carta["idJogador"] = hRodada->cartas[i]->JogadorDaCarta->ObtemNumeroJogador();

			Json::Value cartaJogada;
			cartaJogada["id"] = hRodada->cartas[i]->CartaJogadaNaRodada->id;
			cartaJogada["valor"] = hRodada->cartas[i]->CartaJogadaNaRodada->valor;
			cartaJogada["nome"] = hRodada->cartas[i]->CartaJogadaNaRodada->nome;
			cartaJogada["naipe"] = hRodada->cartas[i]->CartaJogadaNaRodada->naipe;
			carta["cartaJogada"] = cartaJogada;
			cartasNaMesaDaRodada.append(carta);
		}

		rodada["cartasNaMesaDaRodada"] = cartasNaMesaDaRodada;
		
		historicoRodada.append(rodada);
	}

	historicoPartida["rodadas"] = historicoRodada;

	return historicoPartida;
}

Json::Value PersistenciaController::GetMao(Carta* mao[3]) {
	Json::Value maoDoJogador;

	for (int i = 0; i < 3; i++)
		maoDoJogador.append(GetCarta(mao[i]));

	return maoDoJogador;
}

Json::Value PersistenciaController::GetJogadores(Jogador* dupla[2]) {
	Json::Value jogadores;

	for (int i = 0; i < 2; i++)
	{
		Json::Value jogador;

		jogador["id"] = dupla[i]->ObtemNumeroJogador();
		jogador["bot"] = dupla[i]->EhUmBot();
		bool estaNaVezDeJogar = JogadorAtual != nullptr && JogadorAtual->ObtemNumeroJogador() == dupla[i]->ObtemNumeroJogador();
		jogador["vezDeJogar"] = estaNaVezDeJogar;

		Carta* cartasDoJogador[3];

		std::vector<std::tuple<Carta*, bool>> cartasJogador = dupla[i]->GetCartasDoJogador();
		for (const auto& tupla : cartasJogador) {
			bool cartaJogada;
			Carta* cartaDoJogador;

			std::tie(cartaDoJogador, cartaJogada) = tupla;

			auto it = std::find(cartasJogador.begin(), cartasJogador.end(), tupla);
			size_t indiceDaCarta = std::distance(cartasJogador.begin(), it);
			cartasDoJogador[indiceDaCarta] = cartaDoJogador;

			std::string chave = "carta_" + std::to_string(indiceDaCarta) + "_jogada";
			jogador[chave] = cartaJogada;
		}

		jogador["mao"] = GetMao(cartasDoJogador);

		jogadores.append(jogador);
	}

	return jogadores;
}

Json::Value PersistenciaController::GetTime(Jogador* dupla[2], int pontosDoTime, int partidasVencidas) {
	Json::Value time;

	time["pontosDoTime"] = pontosDoTime;
	time["partidasVencidas"] = partidasVencidas;

	time["jogadores"] = GetJogadores(dupla);

	return time;
}

Json::Value PersistenciaController::GetTimes() {
	Json::Value times;

	times.append(GetTime(Dupla1, PlacarDaPartida->PontosDaDupla1, PlacarDaPartida->PartidasVencidasDaDupla1));
	times.append(GetTime(Dupla2, PlacarDaPartida->PontosDaDupla2, PlacarDaPartida->PartidasVencidasDaDupla2));

	return times;
}

Json::Value PersistenciaController::GetConfiguracoes() {
	Json::Value configuracoes;

	configuracoes["numeroJogadores"] = NumeroJogadores;
	configuracoes["multiInstance"] = MultiplasInstancias;

	return configuracoes;
}

std::string PersistenciaController::MontarJSON() {
	Json::Value json;

	json["cartaVirada"] = GetCarta(Vira);
	json["historicoRodadas"] = GetHistoricoRodadas();
	json["times"] = GetTimes();
	json["configuracoes"] = GetConfiguracoes();

	Json::StreamWriterBuilder writer;
	std::string value = Json::writeString(writer, json);

	return value;
}

#pragma endregion

#pragma region read

Partida* PersistenciaController::MontarPartida(std::string json) {

	Json::CharReaderBuilder reader;
	Json::Value jsonObject;
	std::istringstream jsonStream(json);
	Json::parseFromStream(reader, jsonStream, &jsonObject, nullptr);

	Partida* jogo = CriarPartida(jsonObject);

	return jogo;
}

Partida* PersistenciaController::CriarPartida(Json::Value json) {
	const std::string nomeBot = "Bot";
	const std::string nomeHumano = "Humano";

	std::vector<Jogador*> jogadores;

	int numDupla = 1;
	int numUltimoJogador = 1;

	int numeroDeJogadores = json["configuracoes"]["numeroJogadores"].asInt();
	bool multiInstance = json["configuracoes"]["multiInstance"].asBool();

	Placar* placar = new Placar();
	Jogador* dupla1[2];
	Jogador* dupla2[2];

	for (const auto& time : json["times"]) {

		int partidasVencidas = time["partidasVencidas"].asInt();
		int pontosDoTime = time["pontosDoTime"].asInt();

		if (numDupla == 1) {
			placar->PartidasVencidasDaDupla1 = partidasVencidas;
			placar->PontosDaDupla1 = pontosDoTime;
		}
		else {
			placar->PartidasVencidasDaDupla2 = partidasVencidas;
			placar->PontosDaDupla2 = pontosDoTime;
		}

		int jogadorIdx = 0;

		for (const auto& jogador : time["jogadores"]) {

			bool bot = jogador["bot"].asBool();
			int idJogador = jogador["id"].asInt();
			bool vezDeJogar = jogador["vezDeJogar"].asBool();

			if (vezDeJogar)
				numUltimoJogador = idJogador;

			std::string nomeJogador = bot ? nomeBot + std::to_string(numDupla) : nomeHumano + std::to_string(numDupla);
			
			Jogador* player;

			if (bot) {
				if (numeroDeJogadores == 2) {
					player = new BotJogaSozinho(idJogador, nomeJogador, numDupla);
				}
				else {
					player = new Bot(idJogador, nomeJogador, numDupla);
				}
			}
			else {

				bool mostrarCarta = (numeroDeJogadores == 2 && idJogador == 1) || (numeroDeJogadores == 4 && nomeJogador == "Humano1");

				player = new Jogador(idJogador, nomeJogador, numDupla, false, mostrarCarta);
			}

			Carta* cartasJogador[3] = { nullptr, nullptr, nullptr };
			int idCarta = 0;
			for (const auto& mao : jogador["mao"]) {
				cartasJogador[idCarta] = CriarCarta(mao);
				idCarta++;
			}

			player->RecebeCartas(cartasJogador[0], jogador["carta_0_jogada"].asBool(),
							     cartasJogador[1], jogador["carta_1_jogada"].asBool(),
								 cartasJogador[2], jogador["carta_2_jogada"].asBool());

			if (numDupla == 1)
				dupla1[jogadorIdx] = player;
			else 
				dupla2[jogadorIdx] = player;

			jogadores.push_back(player);

			jogadorIdx++;
		}

		numDupla++;
	}

	Carta* vira = CriarCarta(json["cartaVirada"]);
	RodadasController* rodada = CriarRodadaController(json["historicoRodadas"], jogadores, placar, vira, numeroDeJogadores);

	return new Partida(placar, dupla1, dupla2, rodada, vira, numeroDeJogadores, multiInstance, numUltimoJogador);
}

Carta* PersistenciaController::CriarCarta(Json::Value cartaVirada) {
	int id = cartaVirada["id"].asInt();
	int valor = cartaVirada["valor"].asInt();
	std::string nome = cartaVirada["nome"].asString();
	Naipes naipe = static_cast<Naipes>(cartaVirada["naipe"].asInt());

	return new Carta(id, valor, nome, naipe);
}

RodadasController* PersistenciaController::CriarRodadaController(Json::Value historicoRodadas, std::vector<Jogador*> jogadores, Placar* placar, Carta* vira, int numeroDeJogadores) {
	int quantasVezesTrucou = historicoRodadas["quantasVezesTrucou"].asInt();
	int valorDaRodada = historicoRodadas["valorDaRodada"].asInt();
	int numeroDaRodada = historicoRodadas["numeroDaRodadaAtual"].asInt();
	
	RodadasController* rodadaController = new RodadasController(placar, vira, numeroDeJogadores == 4, valorDaRodada, quantasVezesTrucou, numeroDaRodada);
	
	Rodada* rodadas[3];
	int idRodada = 0;
	for (const auto& historicoDaRodada : historicoRodadas["rodadas"]) {
		Rodada* rodada = new Rodada(idRodada + 1, rodadaController);

		int idxCarta = 0;
		for (const auto& cartaDaMesa : historicoDaRodada["cartasNaMesaDaRodada"]) {
			CartaDaRodada* cartaDaRodada = new CartaDaRodada(idRodada + 1);

			bool cartaCoberta = cartaDaMesa["cartaCoberta"].asBool();
			cartaDaRodada->CartaCoberta = cartaCoberta;

			Carta* cartaJogada = CriarCarta(cartaDaMesa["cartaJogada"]);
			cartaDaRodada->CartaJogadaNaRodada = cartaJogada;

			int idJogador = cartaDaMesa["idJogador"].asInt();

			for (Jogador* jogador : jogadores) {
				if (jogador->ObtemNumeroJogador() == idJogador) {
					cartaDaRodada->JogadorDaCarta = jogador;
					break;
				}
			}

			rodada->cartas[idxCarta] = cartaDaRodada;
			
			idxCarta++;
		}

		rodada->CartasAdicionadas = idxCarta;

		rodadas[idRodada] = rodada;
		idRodada++;
	}

	rodadaController->RecriarRodada(rodadas, numeroDaRodada);

	return rodadaController;
}

#pragma endregion

#pragma endregion

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