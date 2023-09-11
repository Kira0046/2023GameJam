#include "Collision.h"

bool Collision::CheckrrBlock(int RedBlockX, int RedBlockY, int RedBlockX2, int RedBlockY2, int Size) {
	//それぞれの座標を取り出す
	int X1 = RedBlockX;
	int X2 = RedBlockX2;

	int Y1 = RedBlockY;
	int Y2 = RedBlockY2;

	int Size1 = Size;

	//左上と右下の座標を求める
	int mx1 = X1 - Size1 - 1;
	int my1 = Y1 - Size1;

	int mx2 = X1 + Size1 - 1;
	int my2 = Y1 + Size1;

	int ex1 = X2 - Size1 - 1;
	int ey1 = Y2 - Size1;

	int ex2 = X2 + Size1 - 1;
	int ey2 = Y2 + Size1;

	if (mx1 <= ex2 && ex1 <= mx2 && my1 <= ey2 && ey1 <= my2) {

		return true;
	}
	else {
		return false;
	}

}

void Collision::CheckggBlock(GreenBlock& greenBlock, GreenBlock& greenBlock2, bool greenblockhit, bool greenblock2hit) {
	int X1 = greenBlock.GetPositionX();
	int X2 = greenBlock2.GetPositionX();

	int Y1 = greenBlock.GetPositionY();
	int Y2 = greenBlock2.GetPositionY();

	int Size1 = greenBlock.GetSize();
	int Size2 = greenBlock2.GetSize();
}

void Collision::CheckbbBlock(BlueBlock& blueBlock, BlueBlock& blueBlock2, bool blueblockhit, bool blueblock2hit) {
	int X1 = blueBlock.GetPositionX();
	int X2 = blueBlock2.GetPositionX();

	int Y1 = blueBlock.GetPositionY();
	int Y2 = blueBlock2.GetPositionY();

	int Size1 = blueBlock.GetSize();
	int Size2 = blueBlock2.GetSize();
}

void Collision::CheckrgBlock(RedBlock& redBlock, GreenBlock& greenBlock, bool redblockhit, bool greenblockhit) {
	int X1 = redBlock.GetPositionX();
	int X2 = greenBlock.GetPositionX();

	int Y1 = redBlock.GetPositionY();
	int Y2 = greenBlock.GetPositionY();

	int Size1 = redBlock.GetSize();
	int Size2 = greenBlock.GetSize();
}

void Collision::CheckrbBlock(RedBlock& redBlock, BlueBlock& blueBlock, bool redblockhit, bool blueblockhit) {
	int X1 = redBlock.GetPositionX();
	int X2 = blueBlock.GetPositionX();

	int Y1 = redBlock.GetPositionY();
	int Y2 = blueBlock.GetPositionY();

	int Size1 = redBlock.GetSize();
	int Size2 = blueBlock.GetSize();
}

void Collision::CheckgbBlock(GreenBlock& greenBlock, BlueBlock& blueBlock, bool greenblockhit, bool blueblockhit) {
	int X1 = greenBlock.GetPositionX();
	int X2 = blueBlock.GetPositionX();

	int Y1 = greenBlock.GetPositionY();
	int Y2 = blueBlock.GetPositionY();

	int Size1 = greenBlock.GetSize();
	int Size2 = blueBlock.GetSize();
}


