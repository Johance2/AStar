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
	m_setOpen.clear();

	pStart->g = 0;
	pStart->h = Hn(pEnd, pStart);
	pStart->f = pStart->g + pStart->h;
	pStart->parent = 0;

	AddToOpen(pStart);
	bool bFind = false;
	// �д򿪵Ľڵ��һֱѰֱ���ߵ��յ㣬����û�е���
	while (!bFind)
	{
		if (m_setOpen.size() == 0)
			break;

		// ÿ�ζ�ȡ��һ�� ��һ����Զ����õ�
		CAStarNode *pCurrentNode = *m_setOpen.begin();
		m_setOpen.erase(m_setOpen.begin());
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
					m_listPath.push_front(pParend);
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

			int h = Hn(pEnd, pNextNode);
			if (h == -1)
			{
				AddToClose(pCurrentNode);
				continue;
			}
			int g = Gn(pCurrentNode, pNextNode);
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

					auto itr2 = m_setOpen.find(pNextNode);
					m_setOpen.erase(itr2);
					AddToOpen(pNextNode);
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
	return pPrevNode->g + pNode->loss;
}

int CAStarImpl::Hn(CAStarNode *pEndNode, CAStarNode *pNode)
{
	return 0;
}

void CAStarImpl::AddToOpen(CAStarNode *pNode)
{
	pNode->state = ASS_OPEN;
	m_setOpen.insert(pNode);
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