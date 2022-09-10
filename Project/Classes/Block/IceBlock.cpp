#include "Classes/Block/IceBlock.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include <vector>

USING_NS_CC;
using namespace std;
using namespace CocosDenshion;
using namespace cocos2d::extension;

IceBlock::IceBlock(cocos2d::Point icePos, const int state) {
	this->pos = icePos;
	this->state = state;
	this->specialPic = Sprite::create("block/iceBlock.png");
	specialPic->setPosition(Point(icePos));
	if (state == 1)
		specialPic->setScale(1.4f);
	else
		specialPic->setScale(0.0f);
}

IceBlock::~IceBlock()
{
}

cocos2d::Point IceBlock::getPos()
{
	return this->pos;
}

cocos2d::Sprite* IceBlock::getSpePic()
{
	return this->specialPic;
}

int IceBlock::getState()
{
	return this->state;
}

void IceBlock::setPos(cocos2d::Point pos)
{
	this->pos = pos;
}

void IceBlock::setState(const int newIceState)
{
	this->state = newIceState;
}