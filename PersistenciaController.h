#pragma once
#include "Carta.h"
#include "Rodada.h"

class PersistenciaController
{
public:
	const std::string nomeArquivo = "trucoPaulista.json";

	bool ContinuarJogoPausado();

	void CriarArquivo();

	void RemoverArquivo();

	void AtualizarArquivo();

private:
	
	std::string MontarJSON();
	void PersistirJSON(std::string &json);
};