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
	RECT rc = {0, 0, m_nCellSize*m_nWidth, m_nCellSize*m_nHeight};
	FillRect(hdc, &rc, (HBRUSH)GetStockObject(WHITE_BRUSH));
	POINT pt;
	for (int x = 0; x < m_nWidth; x++)
	{
		MoveToEx(hdc, x * m_nCellSize, 0, &pt);
		LineTo(hdc, x * m_nCellSize, m_nCellSize * m_nHeight);
	}
	for (int y = 0; y < m_nHeight; y++)
	{
		MoveToEx(hdc, 0, y * m_nCellSize, &pt);
		LineTo(hdc, m_nWidth * m_nCellSize, y * m_nCellSize);
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
	rc.left = x *m_nCellSize+2;
	rc.top = y *m_nCellSize+2;
	rc.right = rc.left + m_nCellSize-4;
	rc.bottom = rc.top + m_nCellSize-4;

	if (hBrush == 0)
	{
		hBrush = (HBRUSH)GetStockObject((y % 2 + x) % 2 ? WHITE_BRUSH : BLACK_BRUSH);
	}

	FillRect(hdc, &rc, hBrush);
}
