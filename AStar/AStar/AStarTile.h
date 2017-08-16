#pragma once
#include "AStarImpl.h"
#include <vector>

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

	const std::vector<CAStarTileNode> &GetTileNode() { return m_vecTileNode;  }
	
protected:
	virtual int Hn(CAStarNode *pEndNode, CAStarNode *pNode);

	std::vector<CAStarTileNode> m_vecTileNode;
	int m_nWidth;
	int m_nHeight;
};

