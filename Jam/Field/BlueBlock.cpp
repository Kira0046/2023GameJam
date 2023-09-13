#include "BlueBlock.h"

BlueBlock::BlueBlock(int x, int y, int pattern, bool center) {
	this->x = x;
	this->y = y;
	this->pattern = pattern;
	LoadDivGraph("Resource/field/color_block_800.png", 6, 6, 1, blockSizeX, blockSizeY, blockHandle);
	LoadDivGraph("Resource/field/color_block_connect.png", 6, 6, 1, blockSizeX, blockSizeY, connectHandle);
	LoadDivGraph("Resource/field/color_block_double.png", 6, 6, 1, blockSizeX, blockSizeY, doubleHandle);
	LoadDivGraph("Resource/field/color_block_Involvement.png", 6, 6, 1, blockSizeX, blockSizeY, involvementHnadle);
	this->center = center;
}

void BlueBlock::Initialize() {

}

void BlueBlock::Update() {
}

void BlueBlock::Draw() {

	if (pattern == 1) {
		if (!isDelete) {
			DrawGraph(x - size, y - size, blockHandle[2], true);
		}
		else if (isDelete && !doubleMutch && !involvement) {
			DrawGraph(x - size, y - size, connectHandle[2], true);
		}
		else if (isDelete && doubleMutch && !involvement) {
			DrawGraph(x - size, y - size, doubleHandle[2], true);
		}
		else if (involvement) {
			DrawGraph(x - size, y - size, involvementHnadle[2], true);
		}
	}
	if (pattern == 2) {
		if (!isDelete) {
			DrawGraph(x - size, y - size, blockHandle[3], true);
		}
		else if (isDelete && !doubleMutch && !involvement) {
			DrawGraph(x - size, y - size, connectHandle[3], true);
		}
		else if (isDelete && doubleMutch && !involvement) {
			DrawGraph(x - size, y - size, doubleHandle[3], true);
		}
		else if (involvement) {
			DrawGraph(x - size, y - size, involvementHnadle[3], true);
		}
	}

}

void BlueBlock::SetMatch(bool u, bool d, bool l, bool r, int num) {
	//ã‘‚«‚Åtrue‚ðfalse‚É‚µ‚È‚¢‚æ‚¤‚É
	if (!up[num]) {
		up[num] = u;
	}
	if (!down[num]) {
		down[num] = d;
	}
	if (!left[num]) {
		left[num] = l;
	}
	if (!right[num]) {
		right[num] = r;
	}
}

void BlueBlock::SetDelete(bool deleteFlag, bool doubkeMuctchFlag, bool involvement) {
	//‰ºŽè‚Èã‘‚«‹ÖŽ~
	if (deleteFlag) {
		isDelete = deleteFlag;
	}
	if (doubkeMuctchFlag) {
		doubleMutch = doubkeMuctchFlag;
	}
	if (involvement) {
		this->involvement = involvement;
	}
}