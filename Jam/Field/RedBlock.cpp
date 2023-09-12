#include "RedBlock.h"

RedBlock::RedBlock(int x, int y, int pattern) {
	this->x = x;
	this->y = y;
	this->pattern = pattern;
	LoadDivGraph("Resource/field/color_block_800.png", 6, 6, 1, blockSizeX, blockSizeY, blockHandle);
	LoadDivGraph("Resource/field/color_block_connect.png", 6, 6, 1, blockSizeX, blockSizeY, connectHandle);
	LoadDivGraph("Resource/field/color_block_double.png", 6, 6, 1, blockSizeX, blockSizeY, doubleHandle);
	LoadDivGraph("Resource/field/color_block_Involvement.png", 6, 6, 1, blockSizeX, blockSizeY, involvementHnadle);
}

void RedBlock::Initialize() {


}

void RedBlock::Update() {
}

void RedBlock::Draw() {


	if (pattern == 1) {
		if (!isDelete) {
			DrawGraph(x - size, y - size, blockHandle[0], true);
		}
		else if (isDelete && !doubleMutch && !involvement) {
			DrawGraph(x - size, y - size, connectHandle[0], true);
		}
		else if (isDelete && doubleMutch && !involvement) {
			DrawGraph(x - size, y - size, doubleHandle[0], true);
		}
		else if (involvement) {
			DrawGraph(x - size, y - size, involvementHnadle[0], true);
		}
	}
	if (pattern == 2) {
		if (!isDelete) {
			DrawGraph(x - size, y - size, blockHandle[1], true);
		}
		else if (isDelete && !doubleMutch && !involvement) {
			DrawGraph(x - size, y - size, connectHandle[1], true);
		}
		else if (isDelete && doubleMutch && !involvement) {
			DrawGraph(x - size, y - size, doubleHandle[1], true);
		}
		else if (involvement) {
			DrawGraph(x - size, y - size, involvementHnadle[1], true);
		}
	}

}

void RedBlock::SetMatch(bool u, bool d, bool l, bool r, int num) {
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

void RedBlock::SetDelete(bool deleteFlag, bool doubkeMuctchFlag, bool involvement) {
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
