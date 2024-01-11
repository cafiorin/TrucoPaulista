#include "pch.h"
#include "PersistenciaController.h"
#include <fstream>
#include <json/json.h>

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

std::string PersistenciaController::MontarJSON(/*colocar params e remover mock*/) {
	Json::Value json;

	// ---
	Json::Value cartaViradaObject;
	cartaViradaObject["id"] = 1;
	cartaViradaObject["valor"] = 4;
	cartaViradaObject["nome"] = "Q";
	cartaViradaObject["naipe"] = "ouro";

	json["cartaVirada"] = cartaViradaObject;
	// ---

	// ---
	Json::Value rodada;
	rodada["numeroDaRodade"] = 0;

	Json::Value cartasDaMesa;

	Json::Value carta1;
	carta1["cartaCoberta"] = false;
	carta1["idJogador"] = 1;
	Json::Value cartaJogada;
	cartaJogada["id"] = 1;
	cartaJogada["valor"] = 4;
	cartaJogada["nome"] = "Q";
	cartaJogada["naipe"] = "ouro";
	carta1["cartaJogada"] = cartaJogada;
	cartasDaMesa.append(carta1);

	//Json::Value carta2;
	//cartasDaMesa.append(carta2);
	//Json::Value carta3;
	//cartasDaMesa.append(carta3);
	//Json::Value carta4;
	//cartasDaMesa.append(carta4);

	rodada["cartasDaMesa"] = cartasDaMesa;
	rodada["valorDaRodada"] = 1;
	rodada["idJogadorPediuTruco"] = 1;

	json["rodada"] = rodada;
	// ---

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