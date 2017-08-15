#pragma once
class CTileMap
{
public:
	CTileMap();
	~CTileMap();
	bool Init(int width = 10, int height = 10, int cell=50);
	void DrawMap(HDC hdc);
	void DrawTile(HDC hdc, int nIndex, HBRUSH hBrush = 0);
	void DrawTile(HDC hdc, int x, int y, HBRUSH hBrush = 0);

	int GetWidth() { return m_nWidth; }
	int GetHeight() { return m_nHeight; }
	int GetCellSize() { return m_nCellSize; }

private:
	int m_nWidth;
	int m_nHeight;
	int m_nCellSize;

	HDC m_hDC;
	HDC m_mapDC;
};

