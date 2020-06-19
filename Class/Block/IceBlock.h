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

class iceBlock
{
private:
	//0为不存在，1为存在
	int iceState;
	cocos2d::Point icePos;
	cocos2d::Sprite* icePic;
public:
	iceBlock(cocos2d::Point icePos, const int state);
	~iceBlock();

	cocos2d::Point GetPos();
	cocos2d::Sprite* GetPic();
	int getState();

	void setState(const int newIceState);
	void setPos(cocos2d::Point pos);
};

#endif // !__ICE_BLOCK_H__

