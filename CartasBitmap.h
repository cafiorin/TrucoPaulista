#pragma once

#include "pch.h"
#include "resource.h"
#include "Carta.h"

class CartasBitmap 
{
private:
	int m_ID;
	const Carta m_Carta;
	CBitmap m_cbmp;

public:
	CartasBitmap(const Carta& carta);

	int GetID();
	const Carta& GetCarta();
	void SetID(const Carta& carta);
	CBitmap* Getbitmap();
};


