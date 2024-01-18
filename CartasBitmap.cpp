#include "pch.h"
#include "CartasBitmap.h"
#include "resource.h"
#include "Carta.h"

CartasBitmap::CartasBitmap(int idResource) : m_ID(idResource)
{
}

int CartasBitmap::GetID()
{
	return m_ID;
}

void CartasBitmap::SetID(const Carta &carta)
{
	this->m_ID = carta.idResource;
}

CBitmap* CartasBitmap::Getbitmap()
{
	m_cbmp.DeleteObject();
	m_cbmp.LoadBitmapW(m_ID);
	return &m_cbmp;
}
