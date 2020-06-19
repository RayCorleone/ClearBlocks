#include "Classes/Block/IceBlock.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include <vector>

USING_NS_CC;
using namespace std;
using namespace CocosDenshion;
using namespace cocos2d::extension;

iceBlock::iceBlock(cocos2d::Point icePos, const int state) {
	this->icePos = icePos;
	this->iceState = state;
	this->icePic = Sprite::create("block/iceBlock.png");
	icePic->setPosition(Point(icePos));
	if (state == 1)
		icePic->setScale(1.4f);
	else
		icePic->setScale(0.0f);
}

iceBlock::~iceBlock()
{
}

cocos2d::Point iceBlock::GetPos()
{
	return this->icePos;
}

cocos2d::Sprite* iceBlock::GetPic()
{
	return this->icePic;
}

int iceBlock::getState()
{
	return this->iceState;
}

void iceBlock::setState(const int newIceState)
{
	this->iceState = newIceState;
}

void iceBlock::setPos(cocos2d::Point pos)
{
	this->icePos = pos;
}