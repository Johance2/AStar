#pragma once
#include "AStarImpl.h"

class CAStarTileNode : public CAStarNode
{
public:
	int index;
};

class CAStarTile :
	public CAStarImpl
{
public:
	CAStarTile();
	~CAStarTile();
	void Init(int width, int height);
	bool Search(int sx, int sy, int ex, int ey);

protected:
	virtual int Hn(CAStarNode *pEndNode, CAStarNode *pNode);

	CAStarTileNode *m_TileNode;
	int m_nWidth;
	int m_nHeight;
};

