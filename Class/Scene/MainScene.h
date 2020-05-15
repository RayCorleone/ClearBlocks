#ifndef __MAINSCENE_H__
#define __MAINSCENE_H__

#include "cocos2d.h"

class MainScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(MainScene);

    void initStillNode(cocos2d::Ref* pSender);
    void initMoveLayer(cocos2d::Ref* pSender);

    void menuCloseCallback(cocos2d::Ref* pSender);
    void getSetUpLayer(cocos2d::Ref* pSender, cocos2d::Node* pNode);
    void menuClose(cocos2d::Ref* pSender, cocos2d::Node* pNode);
};

#endif // __MAINSCENE_H__
