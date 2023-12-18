#include "pch.h"
#include "CartasBitmap.h"
#include "resource.h"
#include "Carta.h"

CartasBitmap::CartasBitmap(Carta &carta) : m_Carta(carta)
{
	SetID(carta);
}

int CartasBitmap::GetID()
{
	return m_ID;
}

Carta& CartasBitmap::GetCarta()
{
	return m_Carta;
}

void CartasBitmap::SetID(Carta &carta)
{
	int valor = carta.valor > 10 ? carta.valor - 10 : carta.valor;
	this->m_ID = (IDB_BITMAP1-1) + valor + ((int)carta.naipe - 1) * 13;
}

CBitmap* CartasBitmap::Getbitmap()
{
	m_cbmp.DeleteObject();
	m_cbmp.LoadBitmapW(m_ID);
	return &m_cbmp;
}
