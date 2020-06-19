#ifndef __SECOND_MAINSCENE_H__
#define __SECOND_MAINSCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;
using namespace cocos2d::extension;

class SecondMainScene :public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(SecondMainScene);

	void initStillNode();
	void initMoveLayer();
	void initSetUpMenu(cocos2d::Node* pNode);
	void initShopMenu(cocos2d::Node* pNode);

	void musicSliderCallBack(cocos2d::Ref* pSender, Control::EventType type);
	void effectSliderCallBack(cocos2d::Ref* pSender, Control::EventType type);
	void gameCloseCallback(cocos2d::Ref* pSender);
	void getSetUpLayer(cocos2d::Ref* pSender, cocos2d::Node* pNode);
	void menuClose(cocos2d::Ref* pSender, cocos2d::Node* pNode);
	void returnCallBack(cocos2d::Ref* pSender);
	
	void choseSkin(cocos2d::Ref* pSender, const int num);
	void buySkill(cocos2d::Ref* pSender, const int num);

	void zeroLevelCallBack(cocos2d::Ref* pSender);
	void oneLevelCallBack(cocos2d::Ref* pSender);
	void twoLevelCallBack(cocos2d::Ref* pSender);
	void threeLevelCallBack(cocos2d::Ref* pSender);
	void fourLevelCallBack(cocos2d::Ref* pSender);

	void update(float dt);
};

#endif // __SECOND_MAINSCENE_H__
