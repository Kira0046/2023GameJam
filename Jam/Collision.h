#pragma once
#include "RedBlock.h"
#include "GreenBlock.h"
#include "BlueBlock.h"


class Collision
{
public:

	static bool CheckrrBlock(int RedBlockX, int RedBlockY, int RedBlockX2, int RedBlockY2, int Size);

	static void CheckggBlock(GreenBlock& greenBlock, GreenBlock& greenBlock2, bool greenblockhit, bool greenblock2hit);

	static void CheckbbBlock(BlueBlock& blueBlock, BlueBlock& blueBlock2, bool blueblockhit, bool blueblock2hit);

	static void CheckrgBlock(RedBlock& redBlock, GreenBlock& greenBlock, bool redblockhit, bool greenblockhit);

	static void CheckrbBlock(RedBlock& redBlock, BlueBlock& blueBlock, bool redblockhit, bool blueblockhit);

	static void CheckgbBlock(GreenBlock& greenBlock, BlueBlock& blueBlock, bool greenblockhit, bool blueblockhit);
};

