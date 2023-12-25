// ExampleConsole.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "../AStar/AStarTile.h"
#include "../AStar/AStarGate.h"
using namespace std;

#define MAP_WIDTH (600)
#define MAP_HEIGHT (600)
#define TEST_COUNT (1)

int main()
{
	//{
	//	CAStarTile ai;
	//	ai.Init(MAP_WIDTH, MAP_HEIGHT, true);

	//	auto tiles = ai.GetTileNode();
	//	srand(GetTickCount());
	//	int count = TEST_COUNT;
	//	float nTotalTime = 0;
	//	DWORD dwTime = GetTickCount();
	//	for (int i = 0; i < tiles.size(); i++)
	//	{
	//		tiles[i].loss = rand() % 3 == 0 ? -1 : 10;
	//	}
	//	while (count--)
	//	{
	//		ai.Search(0, 0, MAP_WIDTH - 1, MAP_HEIGHT - 1);
	//		//cout << "Time:" << dwTime << endl;
	//	}
	//	nTotalTime = GetTickCount() - dwTime;
	//	cout << "TotalCount:" << TEST_COUNT << endl;
	//	cout << "TotalTime:" << nTotalTime << endl;
	//	cout << "PerfTime:" << nTotalTime / TEST_COUNT << endl;
	//}
	{
		float nTotalTime = 0;
		int count = TEST_COUNT;
		DWORD dwTime = GetTickCount();
		CAStarGate gate;
		gate.Init(".\\TileMap\\map_1_1.tmx");
		while (count--)
		{
			if (gate.Search(10, 10, 2500, 2500))
			{
				gate.GetPath();
				for (auto itr = gate.GetPath().begin(); itr != gate.GetPath().end(); ++itr)
				{
					cout << ((CAStarGateNode*)(*itr))->x << "," << ((CAStarGateNode*)(*itr))->y << endl;
				}
			}
		}
		nTotalTime = GetTickCount() - dwTime;
		cout << "TotalCount:" << TEST_COUNT << endl;
		cout << "TotalTime:" << nTotalTime << endl;
		cout << "PerfTime:" << nTotalTime / TEST_COUNT << endl;
	}
	system("pause");

    return 0;
}

