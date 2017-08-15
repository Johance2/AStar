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
	// �д򿪵Ľڵ��һֱѰֱ���ߵ��յ㣬����û�е���
	while (!bFind)
	{
		if (m_listOpen.size() == 0)
			break;

		m_listOpen.sort(UDgreater);
		// ÿ�ζ�ȡ��һ�� ��һ����Զ����õ�
		CAStarNode *pCurrentNode = m_listOpen.front();
		m_listOpen.pop_front();
		AddToClose(pCurrentNode);

		// �����ڽڵ��������ֵ
		for (auto itr = pCurrentNode->neighbor.begin(); itr != pCurrentNode->neighbor.end(); ++itr)
		{
			CAStarNode *pNextNode = *itr;
			// �����յ�
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

			// �ڹر��б� ��Ѹýڵ�
			if (IsInClose(pNextNode))
			{
				continue;
			}

			int g = Gn(pCurrentNode, pNextNode);
			int h = Hn(pEnd, pNextNode);
			int f = g + h;

			// ����ڴ��б� ����¸ýڵ������ֵ
			if (IsInOpen(pNextNode))
			{
				// ���ıȽ�����ʹ����
				if (pNextNode->f < f)
				{
					pNextNode->parent = pCurrentNode;
					pNextNode->g = g;
					pNextNode->h = h;
					pNextNode->f = f;
				}
			}
			// ������ڴ��б� ����Ӹýڵ�
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

// �Ƿ��ڹرսڵ��б�
bool CAStarImpl::IsInClose(CAStarNode *pNode)
{
	return pNode->state == ASS_CLOSE;
}
// �Ƿ��ڴ򿪽ڵ��б�
bool CAStarImpl::IsInOpen(CAStarNode *pNode)
{
	return pNode->state == ASS_OPEN;
}