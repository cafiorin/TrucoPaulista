#include "pch.h"
#include "BotJogaSozinho.h"
#include "RodadasController.h"

BotJogaSozinho::BotJogaSozinho(int numero, std::string nome) : Jogador(numero, nome, true) {}
BotJogaSozinho::~BotJogaSozinho() {}

void BotJogaSozinho::FazerUmaJogadaRebatendo()
{
	//Não precisa de parametros pelo objeto MesaDaRodada ele tem todas as informações das Rodadas
	
	//Escolher a primeira carta maior para rebater (se tiver)
}

void BotJogaSozinho::FazerUmaJogadaComecando()
{
	//Não precisa de parametros pelo objeto MesaDaRodada ele tem todas as informações das Rodadas

	//

}

void BotJogaSozinho::InicializaRodada(RodadasController* mesaDaRodada)
{
	Jogador::InicializaRodada(mesaDaRodada);

	//Calcula a mao
	const Carta* carta1 = PrimeiraCartaNaMao();
	const Carta* carta2 = SegundaCartaNaMao();
	const Carta* carta3 = TerceiraCartaNaMao();

	Carta* vira = mesaDaRodada->QualOVira();
	int ValorCarta1 = carta1->ObtemValor(vira);
	int ValorCarta2 = carta2->ObtemValor(vira);
	int ValorCarta3 = carta3->ObtemValor(vira);

	// Ver regras de cartas otimas . boas
	//TODO



}


bool BotJogaSozinho::AceitarTruco()
{
	return Jogador::AceitarTruco();
}

bool BotJogaSozinho::PedeTruco()
{
	return Jogador::PedeTruco();
}
