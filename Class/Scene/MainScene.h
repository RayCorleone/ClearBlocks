#ifndef __MAINSCENE_H__
#define __MAINSCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;
using namespace cocos2d::extension;

class MainScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(MainScene);

    void initStillNode();
    void initMoveLayer();
    void initSecondMenu(cocos2d::Node* pNode);

    void musicSliderCallBack(cocos2d::Ref* pSender, Control::EventType type);
    void effectSliderCallBack(cocos2d::Ref* pSender, Control::EventType type);
    void gameCloseCallback(cocos2d::Ref* pSender);
    void getSetUpLayer(cocos2d::Ref* pSender, cocos2d::Node* pNode);
    void menuClose(cocos2d::Ref* pSender, cocos2d::Node* pNode);
    void startGameCallBack(cocos2d::Ref* pSender);
};

#endif // __MAINSCENE_H__
