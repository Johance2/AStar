// ExampleConsole.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "../AStar/AStarTile.h"
using namespace std;

#define MAP_WIDTH (1024)
#define MAP_HEIGHT (1024)
#define TEST_COUNT (100)

int main()
{
	CAStarTile ai;
	ai.Init(MAP_WIDTH, MAP_HEIGHT);

	auto tiles = ai.GetTileNode();
	srand(GetTickCount());
	int count = TEST_COUNT;
	float nTotalTime = 0;
	while (count--)
	{
		for (int i = 0; i < tiles.size(); i++)
		{
			tiles[i].loss = rand() % 10 == 0 ? -1 : 10;
		}
		DWORD dwTime = GetTickCount();
		ai.Search(0, 0, MAP_WIDTH - 1, MAP_HEIGHT-1);
		dwTime = GetTickCount() - dwTime;
		cout << "Time:" << dwTime << endl;
		nTotalTime += dwTime;
	}
	cout << "TotalCount:" << TEST_COUNT << endl;
	cout << "TotalTime:" << nTotalTime << endl;
	cout << "PerfTime:" << nTotalTime / TEST_COUNT << endl;
	system("pause");

    return 0;
}

