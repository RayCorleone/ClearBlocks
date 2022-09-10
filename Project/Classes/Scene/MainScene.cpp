#include "Classes/Scene/MainScene.h"
#include "Classes/Overall/WidelyUsed.h"
#include "Classes/Scene/SecondMainScene.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace CocosDenshion;
using namespace cocos2d::extension;


//创建MainScene场景
Scene* MainScene::createScene()
{
    UserDefault::getInstance()->setIntegerForKey("Money", 2000);
    return MainScene::create();
}

//初始化MainScene场景
bool MainScene::init()
{
    if (!Scene::init()) { return false; }
   
    //静态元素层
    initStillNode();
    //交互元素层
    initMoveLayer();
    
    return true;
}

//静态元素层
void MainScene::initStillNode()
{
    auto vSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto stillNode = Node::create();
    this->addChild(stillNode, 1);

    //大背景
    auto theBackGround = Sprite::create("pic/TheBG.png");
    if (theBackGround == nullptr) {
        problemLoading("TheBG.png");
    }
    else {
        theBackGround->setScale(1.5);
        theBackGround->setPosition(Vec2(vSize.width / 2 + origin.x, vSize.height / 2 + origin.y));
        stillNode->addChild(theBackGround, 1);
    }
    
    //背景图片
    auto mainBackGround = Sprite::create("pic/MSBackground.png");
    if (mainBackGround == nullptr) {
        problemLoading("MSBackground.png");
    }
    else {
        mainBackGround->setScale(2);
        mainBackGround->setPosition(Vec2(2 * vSize.width / 3 + origin.x, vSize.height / 2 + origin.y));
        stillNode->addChild(mainBackGround, 2);
    }

    //标题文字
    auto mainName = Sprite::create("pic/ClearBlocks.png");
    if (mainName == nullptr) {
        problemLoading("ClearBlocks.png");
    }
    else {
        mainName->setScale(1.5f);
        mainName->setPosition(Vec2(vSize.width / 2 + origin.x, 2 * vSize.height / 3 + origin.y));
        stillNode->addChild(mainName, 3);
    }

    //中心文字
    auto label = Label::createWithTTF("Clear Blocks", "fonts/Marker Felt.ttf", 120);
    if (label == nullptr) {
        problemLoading("Marker Felt.ttf");
    }
    else {
        label->setColor(Color3B(0, 0, 0));
        label->setPosition(Vec2(origin.x + vSize.width / 2, origin.y + 5 * vSize.height / 9));
        stillNode->addChild(label, 4);
    }
}

//交互元素层
void MainScene::initMoveLayer()
{
    auto vSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto stillLayer = Layer::create();
    this->addChild(stillLayer, 2);
    auto moveLayer = Layer::create();
    this->addChild(moveLayer, 3);
    moveLayer->setVisible(false);

    //关闭按钮
    auto closeItem = MenuItemImage::create("pic/CloseNormal.png", "pic/CloseSelected.png",
        CC_CALLBACK_1(MainScene::gameCloseCallback, this));
    if (closeItem == nullptr || closeItem->getContentSize().width <= 0 || closeItem->getContentSize().height <= 0) {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else {
        const float x = origin.x + vSize.width - closeItem->getContentSize().width / 2;
        const float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    //设置按钮
    auto setupItem = MenuItemImage::create("pic/SetNormal.png", "pic/SetSelected.png",
        CC_CALLBACK_1(MainScene::getSetUpLayer, this, moveLayer));
    if (setupItem == nullptr || setupItem->getContentSize().width <= 0 || setupItem->getContentSize().height <= 0) {
        problemLoading("'SetNormal.png' and 'SetSelected.png'");
    }
    else {
        const float x = origin.x + setupItem->getContentSize().width / 2;
        const float y = origin.y + setupItem->getContentSize().height / 2;
        setupItem->setPosition(Vec2(x, y));
    }

    //开始游戏按钮
    auto startGameItem = MenuItemImage::create("pic/MSStartGameNormal.png", "pic/MSStartGameSelected.png",
        CC_CALLBACK_1(MainScene::startGameCallBack, this));
    if (startGameItem == nullptr || startGameItem->getContentSize().width <= 0 || startGameItem->getContentSize().height <= 0) {
        problemLoading("'MSStartGameNormal.png' and 'MSStartGameSelected.png'");
    }
    else {
        const float x = origin.x + vSize.width / 2;
        const float y = origin.y + vSize.height * 0.2;
        startGameItem->setPosition(Vec2(x, y));
    }

    //静态菜单
    auto stillMenu = Menu::create(closeItem, setupItem, startGameItem, NULL);
    stillMenu->setPosition(Vec2::ZERO);
    stillLayer->addChild(stillMenu);

    //二级菜单
    initSecondMenu(moveLayer);
    moveLayer->runAction(ScaleTo::create(0.01, 0.01));
}

//二级菜单元素
void MainScene::initSecondMenu(Node* pNode)
{
    auto vSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/MainSceneBGM.mp3", true);
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(UserDefault::getInstance()->getFloatForKey("MusicVolume"));
    SimpleAudioEngine::getInstance()->setEffectsVolume(UserDefault::getInstance()->getFloatForKey("EffectVolume"));
    
    //半透明遮挡画布
    auto menuBack = Sprite::create("pic/MenuBack.png");
    if (menuBack == nullptr) {
        problemLoading("pic/MenuBack.png");
    }
    else {
        menuBack->setPosition(origin.x + vSize.width / 2, origin.y + vSize.height / 2);
        pNode->addChild(menuBack, 1);
    }

    //动态菜单背景
    auto menuBackground = Sprite::create("pic/MenuBackground.png");
    if (menuBackground == nullptr) {
        problemLoading("MenuBackground.png");
    }
    else {
        menuBackground->setPosition(origin.x + vSize.width / 2, origin.y + vSize.height / 2);
        pNode->addChild(menuBackground, 2);
    }

    //动态菜单背景字符
    auto menuBackGWord = Sprite::create("pic/MenuBackGWord.png");
    if (menuBackGWord == nullptr) {
        problemLoading("MenuBackGWord.png");
    }
    else {
        menuBackGWord->setPosition(origin.x + vSize.width / 2, origin.y + vSize.height * 0.35);
        pNode->addChild(menuBackGWord, 3);
    }

    //动态菜单关闭按钮
    auto menuCloseItem = MenuItemImage::create("pic/MenuCloseNormal.png", "pic/MenuCloseSelected.png",
        CC_CALLBACK_1(MainScene::menuClose, this, pNode));
    if (menuCloseItem == nullptr || menuCloseItem->getContentSize().width <= 0 || menuCloseItem->getContentSize().height <= 0) {
        problemLoading("MenuCloseNormal.png and MenuCloseSelected.png");
    }
    else {
        menuCloseItem->setAnchorPoint(Vec2(1, 1));
        const float x = origin.x + vSize.width / 2 + menuBackground->getContentSize().width / 2;
        const float y = origin.y + vSize.height / 2 + menuBackground->getContentSize().height / 2;
        menuCloseItem->setPosition(Vec2(x, y));
    }

    //音乐音量按钮
    auto musicItem = Sprite::create("pic/Sound.png");
    if (musicItem == nullptr) {
        problemLoading("Sound.png");
    }
    else {
        musicItem->setScale(1.7f);
        const float x = origin.x + vSize.width * 0.32;
        const float y = origin.y + vSize.height * 0.65;
        musicItem->setPosition(Vec2(x, y));
        pNode->addChild(musicItem, 5);
    }

    //音乐控制滑条
    auto musicSlider = ControlSlider::create("pic/SliderNormal.png", "pic/SliderSelected.png", "pic/SliderButton.png");
    musicSlider->setPosition(Vec2(origin.x + vSize.width * 0.52, origin.y + vSize.height * 0.65));
    musicSlider->setMinimumValue(0);
    musicSlider->setMaximumValue(100);
    auto tempMV = UserDefault::getInstance()->getFloatForKey("MusicVolume") * 100;
    musicSlider->setValue(tempMV);
    musicSlider->addTargetWithActionForControlEvents(this,
        cccontrol_selector(MainScene::musicSliderCallBack), Control::EventType::VALUE_CHANGED);
    pNode->addChild(musicSlider, 4);

    //音效音量按钮
    auto effectItem = Sprite::create("pic/Effect.png");
    if (effectItem == nullptr) {
        problemLoading("Effect.png");
    }
    else {
        effectItem->setScale(1.7f);
        const float x = origin.x + vSize.width * 0.32;
        const float y = origin.y + vSize.height * 0.52;
        effectItem->setPosition(Vec2(x, y));
        pNode->addChild(effectItem, 7);
    }

    //音效控制滑条
    auto effectSlider = ControlSlider::create("pic/SliderNormal.png", "pic/SliderSelected.png", "pic/SliderButton.png");
    effectSlider->setPosition(Vec2(origin.x + vSize.width * 0.52, origin.y + vSize.height * 0.52));
    effectSlider->setMinimumValue(0);
    effectSlider->setMaximumValue(100);
    auto tempEV = UserDefault::getInstance()->getFloatForKey("EffectVolume") * 100;
    effectSlider->setValue(tempEV);
    effectSlider->addTargetWithActionForControlEvents(this,
        cccontrol_selector(MainScene::effectSliderCallBack), Control::EventType::VALUE_CHANGED);
    pNode->addChild(effectSlider, 6);

    //二级菜单
    auto moveMenu = Menu::create(menuCloseItem, NULL);
    moveMenu->setPosition(Vec2::ZERO);
    pNode->addChild(moveMenu, 3);
}

//音乐滑块效果
void MainScene::musicSliderCallBack(Ref* pSender, Control::EventType type)
{
    auto slider = (ControlSlider*)pSender;
    auto value = slider->getValue();
    value = value / 100;
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(value);
    UserDefault::getInstance()->setFloatForKey("MusicVolume", value);
}

//音效滑块效果
void MainScene::effectSliderCallBack(Ref* pSender, Control::EventType type)
{
    auto slider = (ControlSlider*)pSender;
    auto value = slider->getValue();
    value = value / 100;
    SimpleAudioEngine::getInstance()->setEffectsVolume(value);
    UserDefault::getInstance()->setFloatForKey("EffectVolume", value);
}

//鼠标点击关闭操作
void MainScene::gameCloseCallback(Ref* pSender)
{
    UserDefault::getInstance()->setFloatForKey("MusicVolume", 0.5);
    UserDefault::getInstance()->setFloatForKey("EffectVolume", 0.5);
    UserDefault::getInstance()->setIntegerForKey("Money", 0);
    UserDefault::getInstance()->setIntegerForKey("Skin", 1);
    UserDefault::getInstance()->setIntegerForKey("SkillOne", 1);
    UserDefault::getInstance()->setIntegerForKey("SkillTwo", 1);
    UserDefault::getInstance()->setIntegerForKey("SkillThree", 1);
    Director::getInstance()->end();
}

//鼠标点击弹出二级菜单
void MainScene::getSetUpLayer(Ref* pSender, Node* pNode)
{
    pNode->runAction(ScaleTo::create(0.01, 1));
    pNode->setVisible(true);
}

//鼠标点击关闭二级菜单
void MainScene::menuClose(Ref* pSender, Node* pNode)
{
    pNode->setVisible(false);
    pNode->runAction(ScaleTo::create(0.01, 0.01));
}

//开始游戏切换场景
void MainScene::startGameCallBack(Ref* pSender)
{
    auto scene = SecondMainScene::createScene();
    Director::getInstance()->replaceScene(scene);
}