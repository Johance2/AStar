#include "AStarTile.h"
#include <time.h>

CAStarTile::CAStarTile()
{
}


CAStarTile::~CAStarTile()
{
}

void CAStarTile::Init(int width, int height)
{
	m_nWidth = width;
	m_nHeight = height;
	m_vecTileNode.resize(width*height);
	for (int i = 0; i < width*height; i++)
	{
		m_vecTileNode[i].index = i;
		m_vecTileNode[i].loss = 10;
	}
	// 初始化所有节点的相邻节点
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			int nIndex = row*width + col;

			CAStarTileNode *pNode = &m_vecTileNode[nIndex];

			// 上
			if (row > 0)
			{
				pNode->neighbor.push_back(&m_vecTileNode[nIndex-width]);
			}
			// 下
			if (row < height-1)
			{
				pNode->neighbor.push_back(&m_vecTileNode[nIndex + width]);
			}

			// 左
			if (col > 0)
			{
				pNode->neighbor.push_back(&m_vecTileNode[nIndex - 1]);
			}
			// 下
			if (col < width - 1)
			{
				pNode->neighbor.push_back(&m_vecTileNode[nIndex + 1]);
			}
		}
	}
}

bool CAStarTile::Search(int sx, int sy, int ex, int ey)
{
	int nStartIndex = sy*m_nWidth + sx;
	int nEndIndex = ey*m_nWidth + ex;

	for (int i = 0; i < m_nWidth*m_nHeight; i++)
	{
		m_vecTileNode[i].parent = 0;
		m_vecTileNode[i].f = 0;
		m_vecTileNode[i].g = 0;
		m_vecTileNode[i].h = 0;
		m_vecTileNode[i].state = 0;
	}
	m_vecTileNode[nStartIndex].loss = 10;

	return CAStarImpl::Search(&m_vecTileNode[nStartIndex], &m_vecTileNode[nEndIndex]);
}

int CAStarTile::Hn(CAStarNode *pEndNode, CAStarNode *pNode)
{
	if (pNode->loss == -1)
	{
		return -1;
	}
	int nIndex1 = ((CAStarTileNode*)pNode)->index;
	int nIndex2 = ((CAStarTileNode*)pEndNode)->index;

	int nRow1 = nIndex1 / m_nWidth;
	int nCol1 = nIndex1 % m_nWidth;

	int nRow2 = nIndex2 / m_nWidth;
	int nCol2 = nIndex2 % m_nWidth;

	return (abs(nRow2 - nRow1) + abs(nCol2 - nCol1))*10;
}