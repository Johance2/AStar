#include "stdafx.h"
#include "TileMap.h"


CTileMap::CTileMap()
{
}


CTileMap::~CTileMap()
{
}

bool CTileMap::Init(int width, int height, int cell)
{
	m_nWidth = width;
	m_nHeight = height;
	m_nCellSize = cell;
	return true;
}

void CTileMap::DrawMap(HDC hdc)
{
	for (int x = 0; x < m_nWidth; x++)
	{
		for (int y = 0; y < m_nHeight; y++)
		{
			DrawTile(hdc, x, y);
		}
	}
}

void CTileMap::DrawTile(HDC hdc, int nIndex, HBRUSH hBrush)
{
	int x = nIndex % m_nWidth;
	int y = nIndex / m_nWidth;
	DrawTile(hdc, x, y, hBrush);
}

void CTileMap::DrawTile(HDC hdc, int x, int y, HBRUSH hBrush)
{
	RECT rc;
	rc.left = x *m_nCellSize;
	rc.top = y *m_nCellSize;
	rc.right = rc.left + m_nCellSize;
	rc.bottom = rc.top + m_nCellSize;

	if (hBrush == 0)
	{
		hBrush = (HBRUSH)GetStockObject((y % 2 + x) % 2 ? WHITE_BRUSH : BLACK_BRUSH);
	}

	FillRect(hdc, &rc, hBrush);
}
