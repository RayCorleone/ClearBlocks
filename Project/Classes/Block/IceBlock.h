#ifndef __ICE_BLOCK_H__
#define __ICE_BLOCK_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include <vector>

USING_NS_CC;
using namespace std;
using namespace CocosDenshion;
using namespace cocos2d::extension;

class IceBlock
{
private:
	//0为不存在，1为存在
	int state;
	cocos2d::Point pos;
	cocos2d::Sprite* specialPic;
public:
	IceBlock(cocos2d::Point icePos, const int state);
	~IceBlock();

	cocos2d::Point getPos();
	cocos2d::Sprite* getSpePic();
	int getState();

	void setState(const int newState);
	void setPos(cocos2d::Point pos);
};

#endif // !__ICE_BLOCK_H__

