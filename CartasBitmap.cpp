#include "pch.h"
#include "CartasBitmap.h"
#include "resource.h"
#include "Carta.h"

CartasBitmap::CartasBitmap(const Carta &carta) : m_Carta(carta)
{
	SetID(carta);
}

int CartasBitmap::GetID()
{
	return m_ID;
}

const Carta& CartasBitmap::GetCarta()
{
	return m_Carta;
}

void CartasBitmap::SetID(const Carta &carta)
{
	this->m_ID = (IDB_BITMAP1-1) + carta.id + ((int)carta.naipe - 1) * 13;
}

CBitmap* CartasBitmap::Getbitmap()
{
	m_cbmp.DeleteObject();
	m_cbmp.LoadBitmapW(m_ID);
	return &m_cbmp;
}
