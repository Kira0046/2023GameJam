#include "field.h"

void Initialize()
{

}

void Update()
{

}

void Draw()
{
	//�}�b�v�̏c��
	int mapHeight = 18;
	//�}�b�v�̉���
	int mapWidth = 9;

	int block = 32;

	int BlockSize = 16;

	int BLOCK = 1;

	//�}�b�v�`�b�v
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

	//�t�B�[���h�摜�̓ǂݍ���
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