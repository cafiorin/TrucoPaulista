#pragma once

#include "pch.h"
#include "resource.h"
#include "Carta.h"

class CartasBitmap 
{
private:
	int m_ID;
	CBitmap m_cbmp;

public:
	CartasBitmap(int idResource);

	int GetID();
	void SetID(const Carta& carta);
	CBitmap* Getbitmap();
};


