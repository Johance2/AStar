#pragma once
#include <set>
#include <list>

enum AStarNodeState
{
	ASS_NONE,
	ASS_OPEN,
	ASS_CLOSE,
};
// AStar算法的节点
class CAStarNode
{
public:
	CAStarNode();
	CAStarNode *parent; // 上一个节点
	std::list<CAStarNode*> neighbor; // 相邻的节点
	int f; // 评估值
	int g; // 实际消耗
	int h; // 预计消耗return false;
	char state;
};

class CAStarImpl
{
public:
	CAStarImpl();
	~CAStarImpl();
	// 寻路
	virtual bool Search(CAStarNode *pStart, CAStarNode *pEnd);
	const std::list<CAStarNode*> &GetPath();

protected:
	// 计算消耗值
	virtual int Gn(CAStarNode *pPrevNode, CAStarNode *pNode);
	virtual int Hn(CAStarNode *pEndNode, CAStarNode *pNode);

private:
	void AddToOpen(CAStarNode *pNode);
	void AddToClose(CAStarNode *pNode);
	// 是否在关闭节点列表
	bool IsInClose(CAStarNode *pNode);
	// 是否在打开节点列表
	bool IsInOpen(CAStarNode *pNode);

protected:
	std::list<CAStarNode*> m_listOpen;  // 打开列表
	std::list<CAStarNode*> m_listPath; // 最终路径
};

