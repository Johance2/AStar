#pragma once
#include "AStarImpl.h"
#include <vector>

class CAStarGateNode : public CAStarNode
{
public:
	float x, y;
};

class CAStarGate :
	public CAStarImpl
{
public:
	CAStarGate();
	~CAStarGate();
	void Init(const char *pXML);
	bool Search(int sx, int sy, int ex, int ey);
	std::vector<CAStarGateNode*> &GetNode() { return m_vecNode;  }
	
protected:
	int Distance(int sx, int sy, int ex, int ey);
	virtual int Hn(CAStarNode *pCurrentNode, CAStarNode *pPrevNode, CAStarNode *pEndNode);
	std::vector<CAStarGateNode*> m_vecNode;
	std::map<int, std::vector<CAStarGateNode*>> mapGateNode;
	std::map<int, std::vector<CAStarGateNode*>> mapProvinceNode;
	int m_nWidth;
	int m_nHeight;
	int *m_data;
	int m_tileSize;

	CAStarGateNode m_startNode;
	CAStarGateNode m_endNode;
};