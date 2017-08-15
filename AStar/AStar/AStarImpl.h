#pragma once
#include <set>
#include <list>

enum AStarNodeState
{
	ASS_NONE,
	ASS_OPEN,
	ASS_CLOSE,
};
// AStar�㷨�Ľڵ�
class CAStarNode
{
public:
	CAStarNode();
	CAStarNode *parent; // ��һ���ڵ�
	std::list<CAStarNode*> neighbor; // ���ڵĽڵ�
	int f; // ����ֵ
	int g; // ʵ������
	int h; // Ԥ������return false;
	char state;
};

class CAStarImpl
{
public:
	CAStarImpl();
	~CAStarImpl();
	// Ѱ·
	virtual bool Search(CAStarNode *pStart, CAStarNode *pEnd);
	const std::list<CAStarNode*> &GetPath();

protected:
	// ��������ֵ
	virtual int Gn(CAStarNode *pPrevNode, CAStarNode *pNode);
	virtual int Hn(CAStarNode *pEndNode, CAStarNode *pNode);

private:
	void AddToOpen(CAStarNode *pNode);
	void AddToClose(CAStarNode *pNode);
	// �Ƿ��ڹرսڵ��б�
	bool IsInClose(CAStarNode *pNode);
	// �Ƿ��ڴ򿪽ڵ��б�
	bool IsInOpen(CAStarNode *pNode);

protected:
	std::list<CAStarNode*> m_listOpen;  // ���б�
	std::list<CAStarNode*> m_listPath; // ����·��
};

