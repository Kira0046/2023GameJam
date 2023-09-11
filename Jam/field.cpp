#include "field.h"

void Initialize()
{

}

void Update()
{

}

void Draw()
{
	//マップの縦幅
	int mapHeight = 18;
	//マップの横幅
	int mapWidth = 9;

	int block = 32;

	int BlockSize = 16;

	int BLOCK = 1;

	//マップチップ
	int map[18][9] =
	{
		{1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1}
	};

	//フィールド画像の読み込み
	LoadGraph("Resource/field/field.png");

	for (int y = 0; y < mapHeight; y++)
	{
		for (int x = 0; x < mapWidth; x++)
		{
			if (map[y][x] == BLOCK)
			{
				DrawGraph(x * BlockSize, y * BlockSize, block, true);
			}
		}
	}
}