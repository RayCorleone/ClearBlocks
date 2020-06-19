#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "Classes/Block/Block.h"
#include <vector>

USING_NS_CC;
using namespace std;
using namespace CocosDenshion;
using namespace cocos2d::extension;

int Block::flag = 0;

Block::Block(cocos2d::Point pos, std::string name)
{
	this->pos = pos;
	this->state = 0;
	this->name = name;
	this->swap = 0;
	pic = cocos2d::MenuItemImage::create(name, name, CC_CALLBACK_1(Block::move, this));
	pic->setPosition(pos);
	pic->setScale(1.4f);
	specialPic = Sprite::create("block/specialLayer.png");
	specialPic->setPosition(pos);
	specialPic->setScale(0.0f);
}

Block::~Block()
{
}

//Get系列
cocos2d::MenuItemImage* Block::getPic() {
	return pic;
}

cocos2d::Sprite* Block::getSpePic() {
	return specialPic;
}

cocos2d::Point Block::getPos() {
	return pos;
}

int Block::getSwap() {
	return swap;
}

int Block::getState() {
	return state;
}

std::string Block::getName() {
	return name;
}

//Set系列
void Block::setPos(cocos2d::Point pos) {
	this->pos = pos;
}

void Block::initSwap() {
	this->swap = 0;
}

void Block::setName(std::string name) {
	this->name = name;
}

void Block::setState(const int newState) {
	this->state = newState;
	//在游戏界面中，更换状态时，需要对SpePic再操作(添加)
	if (state == 1) {
		specialPic->setScale(0.0f);
		specialPic = Sprite::create("block/specialLayer.png");
		specialPic->setPosition(pos);
		specialPic->setScale(0.0f);
	}
	else if (state == 2) {
		specialPic->setScale(0.0f);
		specialPic = Sprite::create("block/specialLayer.png");
		specialPic->setPosition(pos);
		specialPic->setScale(1.7f);
	}
	else if (state == 3){
		specialPic->setScale(0.0f);
		specialPic = Sprite::create("block/powerLayer.png");
		specialPic->setPosition(pos);
		specialPic->setScale(1.4f);
	}
}

void Block::resetPic(std::string name, cocos2d::Point pos) {
	pic = cocos2d::MenuItemImage::create(name, name, CC_CALLBACK_1(Block::move, this));
	pic->setPosition(pos);
	pic->setScale(1.4f);
	specialPic = Sprite::create("block/specialLayer.png");
	specialPic->setPosition(pos);
	specialPic->setScale(0.0f);
}

//其他函数
void Block::move(cocos2d::Ref* pSender) {
	if (swap == 0) {
		swap = 1;
		flag = flag + 1;
	}
	else {
		swap = 0;
		flag = 3;
	}
}