#include "AStarImpl.h"
#include <algorithm>


CAStarNode::CAStarNode()
{
	parent = NULL;
}

CAStarImpl::CAStarImpl()
{
}


CAStarImpl::~CAStarImpl()
{
}

bool UDgreater(CAStarNode *elem1, CAStarNode *elem2)
{
	return elem1->f < elem2->f;
}

bool CAStarImpl::Search(CAStarNode *pStart, CAStarNode *pEnd)
{
	m_listPath.clear();
	m_listOpen.clear();

	pStart->g = 0;
	pStart->h = Hn(pEnd, pStart);
	pStart->f = pStart->g + pStart->h;
	pStart->parent = 0;

	AddToOpen(pStart);
	bool bFind = false;
	// 有打开的节点就一直寻直到走到终点，或者没有点了
	while (!bFind)
	{
		if (m_listOpen.size() == 0)
			break;

		m_listOpen.sort(UDgreater);
		// 每次都取第一个 第一个永远是最好的
		CAStarNode *pCurrentNode = m_listOpen.front();
		m_listOpen.pop_front();
		AddToClose(pCurrentNode);

		// 给相邻节点计算期望值
		for (auto itr = pCurrentNode->neighbor.begin(); itr != pCurrentNode->neighbor.end(); ++itr)
		{
			CAStarNode *pNextNode = *itr;
			// 到达终点
			if (pNextNode == pEnd)
			{
				pNextNode->g = Gn(pCurrentNode, pNextNode);
				pNextNode->h = Hn(pEnd, pNextNode);
				pNextNode->f = pNextNode->g + pNextNode->h;
				pNextNode->parent = pCurrentNode;

				CAStarNode *pParend = pNextNode;
				while (pParend)
				{
					m_listPath.push_back(pParend);
					pParend = pParend->parent;
				}
				bFind = true;
				break;
			}

			// 在关闭列表 则把该节点
			if (IsInClose(pNextNode))
			{
				continue;
			}

			int g = Gn(pCurrentNode, pNextNode);
			int h = Hn(pEnd, pNextNode);
			int f = g + h;

			// 如果在打开列表 则更新该节点的期望值
			if (IsInOpen(pNextNode))
			{
				// 消耗比较少则使用它
				if (pNextNode->f < f)
				{
					pNextNode->parent = pCurrentNode;
					pNextNode->g = g;
					pNextNode->h = h;
					pNextNode->f = f;
				}
			}
			// 如果不在打开列表 则添加该节点
			else
			{
				pNextNode->parent = pCurrentNode;
				pNextNode->g = g;
				pNextNode->h = h;
				pNextNode->f = f;
				AddToOpen(pNextNode);
			}
		}
	};

	return bFind;
}

const std::list<CAStarNode*> &CAStarImpl::GetPath()
{
	return m_listPath;
}

int CAStarImpl::Gn(CAStarNode *pPrevNode, CAStarNode *pNode)
{
	return pPrevNode->g + 1;
}

int CAStarImpl::Hn(CAStarNode *pEndNode, CAStarNode *pNode)
{
	return 0;
}

void CAStarImpl::AddToOpen(CAStarNode *pNode)
{
	pNode->state = ASS_OPEN;
	m_listOpen.push_back(pNode);
}

void CAStarImpl::AddToClose(CAStarNode *pNode)
{
	pNode->state = ASS_CLOSE;
}

// 是否在关闭节点列表
bool CAStarImpl::IsInClose(CAStarNode *pNode)
{
	return pNode->state == ASS_CLOSE;
}
// 是否在打开节点列表
bool CAStarImpl::IsInOpen(CAStarNode *pNode)
{
	return pNode->state == ASS_OPEN;
}