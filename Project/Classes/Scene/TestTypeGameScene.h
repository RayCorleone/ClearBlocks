#ifndef __TEST_TYPEGAMESCENE_H__
#define __TEST_TYPEGAMESCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include <vector>

USING_NS_CC;
using namespace std;
using namespace CocosDenshion;
using namespace cocos2d::extension;

class TestTypeGameScene :public cocos2d::Scene
{
private:
    //方框图片的位置
    cocos2d::Point pos[8][8];
    //记录每一列的横坐标（x）
    cocos2d::Point spos[8];
    int maxStep;

    bool isAddStep = false;
    bool isSwitchOn = false;

    int grade = 0;
    int step;

    LabelTTF* gradeLabel;
    LabelTTF* stepLabel;

public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(TestTypeGameScene);

    void initStillNode();
    void initMoveLayer();
    void initGameLayer();
    void initMenu(cocos2d::Node* pNode);

    void gameCloseCallback(cocos2d::Ref* pSender);
    void musicSliderCallBack(cocos2d::Ref* pSender, Control::EventType type);
    void effectSliderCallBack(cocos2d::Ref* pSender, Control::EventType type);
    void getSetUpLayer(cocos2d::Ref* pSender, cocos2d::Node* pNode);
    void menuClose(cocos2d::Ref* pSender, cocos2d::Node* pNode);
    void returnCallBack(cocos2d::Ref* pSender);

    void update(float dt);
    void isTarget(const int x, const int y);
    void clearBlocks(float dt);
    bool clearAble(const int x1, const int y1);
    void choseEffect(const int x2, const int y2);
    void fillFull();

    void addStep(cocos2d::Ref* pSender);
    void switchTwo(cocos2d::Ref* pSender);
    void reFill(cocos2d::Ref* pSender);

    void endGame(float dt);
    void initEndLayer(const int result);
};

#endif // __TEST_TYPEGAMESCENE_H__
