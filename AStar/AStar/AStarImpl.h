#pragma once
#include <map>
#include <list>
#include <set>

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
	int loss; // ����ֵ ���Ϊ-1 ��ʾ��������
	char state;
}; 

typedef CAStarNode* CAStarNodePtr;

struct CAStarNodeComp {
	bool operator()(const CAStarNodePtr &k1, const CAStarNodePtr &k2) const {
		return k1->f < k2->f;
	}
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
	// ���
	virtual int Gn(CAStarNode *pPrevNode, CAStarNode *pNode);
	// �������� �������ֵΪ -1 ��ʾ ������
	virtual int Hn(CAStarNode *pEndNode, CAStarNode *pNode);

private:
	void AddToOpen(CAStarNode *pNode);
	void AddToClose(CAStarNode *pNode);
	// �Ƿ��ڹرսڵ��б�
	bool IsInClose(CAStarNode *pNode);
	// �Ƿ��ڴ򿪽ڵ��б�
	bool IsInOpen(CAStarNode *pNode);

protected:
	std::multiset<CAStarNodePtr, CAStarNodeComp> m_setOpen;  // ���б�
	std::list<CAStarNode*> m_listPath; // ����·��
};

