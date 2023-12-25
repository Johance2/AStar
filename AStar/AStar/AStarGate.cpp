#include "AStarGate.h"
#include <time.h>
#include "tinyxml2.h"

CAStarGate::CAStarGate()
{
}


CAStarGate::~CAStarGate()
{
}

void CAStarGate::Init(const char* pXML)
{
	tinyxml2::XMLDocument doc;
	if (doc.LoadFile(pXML) != tinyxml2::XML_SUCCESS)
	{
		return;
	}
	tinyxml2::XMLElement *pRoot = doc.RootElement();

	pRoot->QueryAttribute("tilewidth", &m_tileSize);

	tinyxml2::XMLElement *pLayerNode = pRoot->FirstChildElement("layer");
	pLayerNode->QueryAttribute("width", &m_nWidth);
	pLayerNode->QueryAttribute("height", &m_nHeight);
	auto *pDataNode = pLayerNode->FirstChildElement("data");
	auto *data = (char*)pDataNode->FirstChild()->Value();
	char *data2 = data;
	m_data= new int[m_nWidth * m_nHeight];
	for (int j = 0; j < m_nWidth; j++)
	{
		data2 += 1;
		for (int i = 0; i < m_nHeight; i++)
		{
			int index = j * m_nWidth + i;
			m_data[index] = data2[0] - '0';
			data2 +=2;
		}
	}

	//for (int i = 0; i < m_nWidth * m_nHeight; i++)
	//{
	//}

	tinyxml2::XMLElement* pPrvianceNode = pRoot->FirstChildElement("objectgroup");
	auto pObectNode = pPrvianceNode->FirstChildElement();

	while (pObectNode)
	{
		auto node = new CAStarGateNode();
		m_vecNode.push_back(node);

		pObectNode->QueryAttribute("x", &node->x);
		pObectNode->QueryAttribute("y", &node->y);
		int group;
		pObectNode->QueryAttribute("name", &group);
		mapGateNode[group].push_back(node);

		int x = node->x / m_tileSize;
		int y = node->y / m_tileSize;
		int index = y* m_nWidth + x;
		int province = m_data[index];
		mapProvinceNode[province].push_back(node);

		pObectNode = pObectNode->NextSiblingElement();
	}

	for (auto itr = mapGateNode.begin(); itr != mapGateNode.end(); ++itr)
	{
		auto &vecNode = itr->second;
		for (int i = 0; i < vecNode.size(); i++)
		{
			for (int j = i + 1; j < vecNode.size(); j++)
			{
				Neighbor neighbor;
				neighbor.node = vecNode[j];
				neighbor.loss = Distance(vecNode[i]->x, vecNode[i]->y, vecNode[j]->x, vecNode[j]->y);
				vecNode[i]->neighbor.push_back(neighbor);
				neighbor.node = vecNode[i];
				vecNode[j]->neighbor.push_back(neighbor);
			}
		}
	}

	for (auto itr = mapProvinceNode.begin(); itr != mapProvinceNode.end(); ++itr)
	{
		auto &vecNode = itr->second;
		for (int i = 0; i < vecNode.size(); i++)
		{
			for (int j = i + 1; j < vecNode.size(); j++)
			{
				Neighbor neighbor;
				neighbor.node = vecNode[j];
				neighbor.loss = Distance(vecNode[i]->x, vecNode[i]->y, vecNode[j]->x, vecNode[j]->y);
				vecNode[i]->neighbor.push_back(neighbor);
				neighbor.node = vecNode[i];
				vecNode[j]->neighbor.push_back(neighbor);
			}
		}
	}
}

bool CAStarGate::Search(int sx, int sy, int ex, int ey)
{
	for (int i = 0; i < m_vecNode.size(); i++)
	{
		m_vecNode[i]->parent = 0;
		m_vecNode[i]->f = 0;
		m_vecNode[i]->g = 0;
		m_vecNode[i]->h = 0;
		m_vecNode[i]->state = 0;
	}

	{
		m_startNode.parent = 0;
		m_startNode.f = 0;
		m_startNode.g = 0;
		m_startNode.h = 0;
		m_startNode.state = 0;
		m_startNode.neighbor.clear();
		m_startNode.x = sx;
		m_startNode.y = sy;
		int x = sx / m_tileSize;
		int y = sy / m_tileSize;
		int index = y * m_nWidth + x;
		int province = m_data[index];

		auto& nodes = mapProvinceNode[province];
		for (auto itr = nodes.begin(); itr != nodes.end(); ++itr)
		{
			Neighbor neighbor;
			neighbor.node = *itr;
			neighbor.loss = Distance(sx, sy, (*itr)->x, (*itr)->y);
			m_startNode.neighbor.push_back(neighbor);
		}
	}
	{
		m_endNode.x = ex;
		m_endNode.y = ey;
		m_endNode.f = 0;
		m_endNode.g = 0;
		m_endNode.h = 0;
		m_endNode.state = 0;
		int x = ex / m_tileSize;
		int y = ey / m_tileSize;
		int index = y * m_nWidth + x;
		int province = m_data[index];

		auto& nodes = mapProvinceNode[province];
		for (auto itr = nodes.begin(); itr != nodes.end(); ++itr)
		{
			Neighbor neighbor;
			neighbor.node = &m_endNode;
			neighbor.loss = Distance(ex, ey, (*itr)->x, (*itr)->y);
			(*itr)->neighbor.push_back(neighbor);
		}
		bool ret = CAStarImpl::Search(&m_startNode, &m_endNode);

		//移除插进去的结束点
		for (auto itr = nodes.begin(); itr != nodes.end(); ++itr)
		{
			(*itr)->neighbor.pop_back();
		}

		return ret;
	}
}

int CAStarGate::Distance(int sx, int sy, int ex, int ey)
{
	return pow(pow((sx - ex), 2) + pow((sy - ey), 2), 0.5);
}
int CAStarGate::Hn(CAStarNode *pCurrentNode, CAStarNode *pPrevNode, CAStarNode *pEndNode)
{
	if (pCurrentNode->loss == -1)
	{
		return -1;
	}
	int nCol1 = ((CAStarGateNode*)pCurrentNode)->x;
	int nCol2 = ((CAStarGateNode*)pCurrentNode)->x;
	int nRow1 = ((CAStarGateNode*)pEndNode)->y;
	int nRow2 = ((CAStarGateNode*)pEndNode)->y;

	return (abs(nRow2 - nRow1) + abs(nCol2 - nCol1));
}