#include "Classes/Scene/MainScene.h"
#include "Classes/Overall/WidelyUsed.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

//创建MainScene场景
Scene* MainScene::createScene()
{
    return MainScene::create();
}

//初始化MainScene场景
bool MainScene::init()
{
    if (!Scene::init()) { return false; }

    //静态元素层
    initStillNode(this);
    //交互元素层
    initMoveLayer(this);
    
    return true;
}

//静态元素层
void MainScene::initStillNode(cocos2d::Ref* pSender)
{
    auto vSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto stillNode = Node::create();
    this->addChild(stillNode, 1);
    //标题文字
    auto mainName = Sprite::create("ClearBlocks.png");
    if (mainName == nullptr) {
        problemLoading("ClearBlocks.png");
    }
    else {
        mainName->setScale(1.5f);
        mainName->setPosition(Vec2(vSize.width / 2 + origin.x, 2 * vSize.height / 3 + origin.y));
        stillNode->addChild(mainName, 1);
    }

    //中心文字
    auto label = Label::createWithTTF("Clear Blocks", "fonts/Marker Felt.ttf", 120);
    if (label == nullptr) {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else {
        label->setPosition(Vec2(origin.x + vSize.width / 2, origin.y + 5 * vSize.height / 9));
        stillNode->addChild(label, 2);
    }
}

//交互元素层
void MainScene::initMoveLayer(cocos2d::Ref* pSender)
{
    auto vSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto stillLayer = Layer::create();
    this->addChild(stillLayer, 2);
    auto moveLayer = Layer::create();
    this->addChild(moveLayer, 3);
    moveLayer->setVisible(false);

    //关闭按钮
    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png");
    closeItem->setTarget(this, menu_selector(MainScene::menuCloseCallback));
    if (closeItem == nullptr || closeItem->getContentSize().width <= 0 || closeItem->getContentSize().height <= 0) {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else {
        float x = origin.x + vSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    //设置按钮
    auto setupItem = MenuItemImage::create("SetNormal.png", "SetSelected.png",
        CC_CALLBACK_1(MainScene::getSetUpLayer, this, moveLayer));
    if (setupItem == nullptr || setupItem->getContentSize().width <= 0 || setupItem->getContentSize().height <= 0) {
        problemLoading("'SetNormal.png' and 'SetSelected.png'");
    }
    else {
        float x = origin.x + closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        setupItem->setPosition(Vec2(x, y));
    }

    //静态菜单
    auto stillMenu = Menu::create(closeItem, setupItem, NULL);
    stillMenu->setPosition(Vec2::ZERO);
    stillLayer->addChild(stillMenu);

    //半透明遮挡画布
    auto menuBack = Sprite::create("MenuBack.png");
    if (menuBack == nullptr) {
        problemLoading("MenuBack.png");
    }
    else {
        menuBack->setPosition(origin.x + vSize.width / 2, origin.y + vSize.height / 2);
        moveLayer->addChild(menuBack, 1);
    }

    //动态菜单背景
    auto menuBackground = Sprite::create("MenuBackground.png");
    if (menuBackground == nullptr) {
        problemLoading("MenuBackground.png");
    }
    else {
        menuBackground->setPosition(origin.x + vSize.width / 2, origin.y + vSize.height / 2);
        moveLayer->addChild(menuBackground, 2);
    }

    //动态菜单关闭按钮
    auto menuCloseItem = MenuItemImage::create("MenuCloseNormal.png", "MenuCloseSelected.png",
        CC_CALLBACK_1(MainScene::menuClose, this, moveLayer));
    if (menuCloseItem == nullptr || menuCloseItem->getContentSize().width <= 0 || menuCloseItem->getContentSize().height <= 0) {
        problemLoading("'MenuCloseNormal.png' and 'MenuCloseSelected.png'");
    }
    else {
        menuCloseItem->setAnchorPoint(Vec2(1, 1));
        float x = origin.x + vSize.width / 2 + menuBackground->getContentSize().width / 2;
        float y = origin.y + vSize.height / 2 + menuBackground->getContentSize().height / 2;
        menuCloseItem->setPosition(Vec2(x, y));
    }

    //二级菜单
    auto moveMenu = Menu::create(menuCloseItem, NULL);
    moveMenu->setPosition(Vec2::ZERO);
    moveLayer->addChild(moveMenu, 3);
}

//鼠标点击关闭操作
void MainScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

//鼠标点击弹出二级菜单
void MainScene::getSetUpLayer(Ref* pSender, Node* pNode)
{
    pNode->setVisible(true);
}

//鼠标点击关闭二级菜单
void MainScene::menuClose(Ref* pSender, Node* pNode)
{
    pNode->setVisible(false);
}