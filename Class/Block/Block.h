#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include <vector>

USING_NS_CC;
using namespace std;
using namespace CocosDenshion;
using namespace cocos2d::extension;

class Block
{
private:
	int swap;
	//×´Ì¬1-ÆÕÍ¨£¬2-4Ïû£¬3-5Ïû
	int state;

	cocos2d::Point pos;
	std::string name;
	cocos2d::MenuItemImage* pic;
	cocos2d::Sprite* specialPic;

public:
	Block(cocos2d::Point pos, std::string name);
	~Block();

	static int flag;

	cocos2d::Point getPos();
	cocos2d::MenuItemImage* getPic();
	cocos2d::Sprite* getSpePic();
	int getSwap();
	int getState();
	std::string getName();

	void initSwap();
	void setName(std::string name);
	void setState(const int newState);
	void setPos(cocos2d::Point pos);
	void resetPic(std::string name, cocos2d::Point pos);

	void move(cocos2d::Ref* pSender);
};

#endif // !__BLOCK_H__
