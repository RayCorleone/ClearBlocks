#include "Classes/Overall/WidelyUsed.h"
#include "Classes/Scene/MainScene.h"
#include "Classes/Scene/SecondMainScene.h"
#include "Classes/Scene/TestTypeGameScene.h"
#include "Classes/Scene/ATypeGameScene.h"
#include "Classes/Scene/BTypeGameScene.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace CocosDenshion;
using namespace cocos2d::extension;

int totalMoney = UserDefault::getInstance()->getIntegerForKey("Money");
LabelTTF* moneyLabel;

int skin = UserDefault::getInstance()->getIntegerForKey("Skin");
LabelTTF* skinOneLabel;
LabelTTF* skinTwoLabel;
LabelTTF* skinThreeLabel;

int skillOne= UserDefault::getInstance()->getIntegerForKey("SkillOne");
LabelTTF* skillOneLabel;
int skillTwo = UserDefault::getInstance()->getIntegerForKey("SkillTwo");
LabelTTF* skillTwoLabel;
int skillThree = UserDefault::getInstance()->getIntegerForKey("SkillThree");
LabelTTF* skillThreeLabel;

Scene* SecondMainScene::createScene()
{
	return SecondMainScene::create();
}

bool SecondMainScene::init()
{
	if (!Scene::init()) { return false; }

	//静态元素层
	initStillNode();
	//交互元素层
	initMoveLayer();

	return true;
}

//静态元素层
void SecondMainScene::initStillNode()
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

	//背景
	auto backGround = Sprite::create("pic/SMSBackground.png");
	if (backGround == nullptr) {
		problemLoading("SMSBackground.png");
	}
	else {
		backGround->setScale(vSize.width / backGround->getContentSize().width);
		backGround->setPosition(Vec2(vSize.width / 2 + origin.x, vSize.height / 2 + origin.y));
		stillNode->addChild(backGround, 2);
	}

	//金币栏
	moneyLabel = LabelTTF::create("0", "fonts/Marker Felt", 42);
	moneyLabel->setColor(ccc3(0, 0, 1));
	moneyLabel->setPosition(Point(origin.x + vSize.width * 0.198, origin.y + vSize.height * 0.94));
	this->addChild(moneyLabel, 3);

	this->scheduleUpdate();
}

//交互元素层
void SecondMainScene::initMoveLayer()
{
	auto vSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto stillLayer = Layer::create();
	this->addChild(stillLayer, 2);
	auto moveLayer = Layer::create();
	this->addChild(moveLayer, 3);
	moveLayer->setVisible(false);
	auto shopLayer = Layer::create();
	this->addChild(shopLayer, 4);
	shopLayer->setVisible(false);

	//选择第0关卡
	auto levelItem0 = MenuItemImage::create("pic/Level0Normal.png", "pic/Level0Selected.png",
		CC_CALLBACK_1(SecondMainScene::zeroLevelCallBack, this));
	if (levelItem0 == nullptr || levelItem0->getContentSize().width <= 0 || levelItem0->getContentSize().height <= 0) {
		problemLoading("'Level0Normal.png' and 'Level0Selected.png'");
	}
	else {
		const float x = vSize.width * 0.15;
		const float y = vSize.height * 0.52;
		levelItem0->setScale(1.3f);
		levelItem0->setPosition(Vec2(x, y));
	}

	//选择第1关卡
	auto levelItem1 = MenuItemImage::create("pic/Level1Normal.png", "pic/Level1Selected.png",
		CC_CALLBACK_1(SecondMainScene::oneLevelCallBack, this));
	if (levelItem1 == nullptr || levelItem1->getContentSize().width <= 0 || levelItem1->getContentSize().height <= 0) {
		problemLoading("'Level1Normal.png' and 'Level1Selected.png'");
	}
	else {
		const float x = vSize.width * 0.325;
		const float y = vSize.height * 0.52;
		levelItem1->setScale(1.3f);
		levelItem1->setPosition(Vec2(x, y));
	}

	//选择第2关卡
	auto levelItem2 = MenuItemImage::create("pic/Level2Normal.png", "pic/Level2Selected.png",
		CC_CALLBACK_1(SecondMainScene::twoLevelCallBack, this));
	if (levelItem2 == nullptr || levelItem2->getContentSize().width <= 0 || levelItem2->getContentSize().height <= 0) {
		problemLoading("'Level2Normal.png' and 'Level2Selected.png'");
	}
	else {
		const float x = vSize.width * 0.5;
		const float y = vSize.height * 0.52;
		levelItem2->setScale(1.3f);
		levelItem2->setPosition(Vec2(x, y));
	}

	//选择第3关卡
	auto levelItem3 = MenuItemImage::create("pic/Level3Normal.png", "pic/Level3Selected.png",
		CC_CALLBACK_1(SecondMainScene::threeLevelCallBack, this));
	if (levelItem3 == nullptr || levelItem3->getContentSize().width <= 0 || levelItem3->getContentSize().height <= 0) {
		problemLoading("'Level3Normal.png' and 'Level3Selected.png'");
	}
	else {
		const float x = vSize.width * 0.675;
		const float y = vSize.height * 0.52;
		levelItem3->setScale(1.3f);
		levelItem3->setPosition(Vec2(x, y));
	}

	//选择第4关卡
	auto levelItem4 = MenuItemImage::create("pic/Level4Normal.png", "pic/Level4Selected.png",
		CC_CALLBACK_1(SecondMainScene::fourLevelCallBack, this));
	if (levelItem4 == nullptr || levelItem4->getContentSize().width <= 0 || levelItem4->getContentSize().height <= 0) {
		problemLoading("'Level4Normal.png' and 'Level4Selected.png'");
	}
	else {
		const float x = vSize.width * 0.85;
		const float y = vSize.height * 0.52;
		levelItem4->setScale(1.3f);
		levelItem4->setPosition(Vec2(x, y));
	}

	//关闭按钮
	auto closeItem = MenuItemImage::create("pic/CloseNormal.png", "pic/CloseSelected.png",
		CC_CALLBACK_1(SecondMainScene::gameCloseCallback, this));
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
		CC_CALLBACK_1(SecondMainScene::getSetUpLayer, this, moveLayer));
	if (setupItem == nullptr || setupItem->getContentSize().width <= 0 || setupItem->getContentSize().height <= 0) {
		problemLoading("'SetNormal.png' and 'SetSelected.png'");
	}
	else {
		const float x = origin.x + setupItem->getContentSize().width / 2;
		const float y = origin.y + setupItem->getContentSize().height / 2;
		setupItem->setPosition(Vec2(x, y));
	}

	//商店按钮
	auto shopItem = MenuItemImage::create("pic/ShopNormal.png", "pic/ShopSelected.png",
		CC_CALLBACK_1(SecondMainScene::getSetUpLayer, this, shopLayer));
	if (shopItem == nullptr || shopItem->getContentSize().width <= 0 || shopItem->getContentSize().height <= 0) {
		problemLoading("'ShopNormal.png' and 'ShopSelected.png'");
	}
	else {
		const float x = origin.x + vSize.width - shopItem->getContentSize().width;
		const float y = origin.y + vSize.height - shopItem->getContentSize().height / 2;
		shopItem->setScale(1.2f);
		shopItem->setPosition(Vec2(x, y));
	}

	auto menu = Menu::create(levelItem0, levelItem1, levelItem2, levelItem3, levelItem4, closeItem, setupItem, shopItem, NULL);
	menu->setPosition(Vec2::ZERO);
	stillLayer->addChild(menu, 1);

	initSetUpMenu(moveLayer);
	moveLayer->runAction(ScaleTo::create(0.01, 0.01));

	initShopMenu(shopLayer);
	shopLayer->runAction(ScaleTo::create(0.01, 0.01));
}

//设置菜单层
void SecondMainScene::initSetUpMenu(cocos2d::Node* pNode)
{
	auto vSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
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

	//动态菜单关闭按钮
	auto menuCloseItem = MenuItemImage::create("pic/MenuCloseNormal.png", "pic/MenuCloseSelected.png",
		CC_CALLBACK_1(SecondMainScene::menuClose, this, pNode));
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
		cccontrol_selector(SecondMainScene::musicSliderCallBack), Control::EventType::VALUE_CHANGED);
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
		cccontrol_selector(SecondMainScene::effectSliderCallBack), Control::EventType::VALUE_CHANGED);
	pNode->addChild(effectSlider, 6);

	//返回按钮
	auto returnGameItem = MenuItemImage::create("pic/ReturnMSNormal.png", "pic/ReturnMSSelected.png",
		CC_CALLBACK_1(SecondMainScene::returnCallBack, this));
	if (returnGameItem == nullptr || returnGameItem->getContentSize().width <= 0 || returnGameItem->getContentSize().height <= 0) {
		problemLoading("'ReturnMSNormal.png' and 'ReturnMSSelected.png'");
	}
	else {
		returnGameItem->setScale(1.4);
		const float x = origin.x + vSize.width * 0.5;
		const float y = origin.y + vSize.height * 0.355;
		returnGameItem->setPosition(Vec2(x, y));
	}

	//二级菜单
	auto moveMenu = Menu::create(menuCloseItem, returnGameItem, NULL);
	moveMenu->setPosition(Vec2::ZERO);
	pNode->addChild(moveMenu, 3);
}

//商店层
void SecondMainScene::initShopMenu(cocos2d::Node* pNode)
{
	auto vSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//半透明遮挡画布
	auto shopBack = Sprite::create("pic/MenuBack.png");
	if (shopBack == nullptr) {
		problemLoading("pic/MenuBack.png");
	}
	else {
		shopBack->setPosition(origin.x + vSize.width / 2, origin.y + vSize.height / 2);
		pNode->addChild(shopBack, 1);
	}

	//动态菜单背景
	auto shopBackground = Sprite::create("pic/ShopBackground.png");
	if (shopBackground == nullptr) {
		problemLoading("ShopBackground.png");
	}
	else {
		shopBackground->setScale(1.2f);
		shopBackground->setPosition(origin.x + vSize.width / 2, origin.y + vSize.height / 2);
		pNode->addChild(shopBackground, 2);
	}

	//动态菜单关闭按钮
	auto shopCloseItem = MenuItemImage::create("pic/MenuCloseNormal.png", "pic/MenuCloseSelected.png",
		CC_CALLBACK_1(SecondMainScene::menuClose, this, pNode));
	if (shopCloseItem == nullptr || shopCloseItem->getContentSize().width <= 0 || shopCloseItem->getContentSize().height <= 0) {
		problemLoading("MenuCloseNormal.png and MenuCloseSelected.png");
	}
	else {
		shopCloseItem->setAnchorPoint(Vec2(1, 1));
		const float x = origin.x + vSize.width / 2 + 1.2 * shopBackground->getContentSize().width / 2;
		const float y = origin.y + vSize.height / 2 + 1.2 * shopBackground->getContentSize().height / 2;
		shopCloseItem->setPosition(Vec2(x, y));
	}

	//皮肤1按钮
	auto skinItem1 = MenuItemImage::create("pic/Skin1Normal.png", "pic/Skin1Selected.png",
		CC_CALLBACK_1(SecondMainScene::choseSkin, this, 1));
	if (skinItem1 == nullptr || skinItem1->getContentSize().width <= 0 || skinItem1->getContentSize().height <= 0) {
		problemLoading("Skin1Normal.png and Skin1Selected.png");
	}
	else {
		skinItem1->setScale(1.2f);
		const float x = origin.x + vSize.width * 0.385;
		const float y = origin.y + vSize.height * 0.57;
		skinItem1->setPosition(Vec2(x, y));
	}

	//皮肤2按钮
	auto skinItem2 = MenuItemImage::create("pic/Skin2Normal.png", "pic/Skin2Selected.png",
		CC_CALLBACK_1(SecondMainScene::choseSkin, this, 2));
	if (skinItem2 == nullptr || skinItem2->getContentSize().width <= 0 || skinItem2->getContentSize().height <= 0) {
		problemLoading("Skin2Normal.png and Skin2Selected.png");
	}
	else {
		skinItem2->setScale(1.2f);
		const float x = origin.x + vSize.width * 0.53;
		const float y = origin.y + vSize.height * 0.57;
		skinItem2->setPosition(Vec2(x, y));
	}

	//皮肤3按钮
	auto skinItem3 = MenuItemImage::create("pic/Skin3Normal.png", "pic/Skin3Selected.png",
		CC_CALLBACK_1(SecondMainScene::choseSkin, this, 3));
	if (skinItem3 == nullptr || skinItem3->getContentSize().width <= 0 || skinItem3->getContentSize().height <= 0) {
		problemLoading("Skin3Normal.png and Skin3Selected.png");
	}
	else {
		skinItem3->setScale(1.2f);
		const float x = origin.x + vSize.width * 0.675;
		const float y = origin.y + vSize.height * 0.57;
		skinItem3->setPosition(Vec2(x, y));
	}

	//技能1按钮：加3步
	auto skillItem1 = MenuItemImage::create("pic/Skill1Normal.png", "pic/Skill1Selected.png",
		CC_CALLBACK_1(SecondMainScene::buySkill, this, 1));
	if (skillItem1 == nullptr || skillItem1->getContentSize().width <= 0 || skillItem1->getContentSize().height <= 0) {
		problemLoading("Skill1Normal.png and Skill1Selected.png");
	}
	else {
		skillItem1->setScale(1.2f);
		const float x = origin.x + vSize.width * 0.385;
		const float y = origin.y + vSize.height * 0.288;
		skillItem1->setPosition(Vec2(x, y));
	}

	//技能2按钮：交换指定一对儿
	auto skillItem2 = MenuItemImage::create("pic/Skill2Normal.png", "pic/Skill2Selected.png",
		CC_CALLBACK_1(SecondMainScene::buySkill, this, 2));
	if (skillItem2 == nullptr || skillItem2->getContentSize().width <= 0 || skillItem2->getContentSize().height <= 0) {
		problemLoading("Skill2Normal.png and Skill2Selected.png");
	}
	else {
		skillItem2->setScale(1.2f);
		const float x = origin.x + vSize.width * 0.53;
		const float y = origin.y + vSize.height * 0.288;
		skillItem2->setPosition(Vec2(x, y));
	}

	//技能3按钮：重新洗牌
	auto skillItem3 = MenuItemImage::create("pic/Skill3Normal.png", "pic/Skill3Selected.png",
		CC_CALLBACK_1(SecondMainScene::buySkill, this, 3));
	if (skillItem3 == nullptr || skillItem3->getContentSize().width <= 0 || skillItem3->getContentSize().height <= 0) {
		problemLoading("Skill3Normal.png and Skill3Selected.png");
	}
	else {
		skillItem3->setScale(1.2f);
		const float x = origin.x + vSize.width * 0.675;
		const float y = origin.y + vSize.height * 0.288;
		skillItem3->setPosition(Vec2(x, y));
	}

	//二级菜单
	auto shopMenu = Menu::create(shopCloseItem, skinItem1, skinItem2, skinItem3, skillItem1, skillItem2, skillItem3, NULL);
	shopMenu->setPosition(Vec2::ZERO);
	pNode->addChild(shopMenu, 3);

	//皮肤栏
	skinOneLabel = LabelTTF::create("X", "fonts/Marker Felt", 42);
	skinOneLabel->setColor(ccc3(0, 0, 1));
	skinOneLabel->setPosition(Point(origin.x + vSize.width * 0.439, origin.y + vSize.height * 0.522));
	pNode->addChild(skinOneLabel, 4);

	skinTwoLabel = LabelTTF::create("X", "fonts/Marker Felt", 42);
	skinTwoLabel->setColor(ccc3(0, 0, 1));
	skinTwoLabel->setPosition(Point(origin.x + vSize.width * 0.584, origin.y + vSize.height * 0.522));
	pNode->addChild(skinTwoLabel, 4);

	skinThreeLabel = LabelTTF::create("X", "fonts/Marker Felt", 42);
	skinThreeLabel->setColor(ccc3(0, 0, 1));
	skinThreeLabel->setPosition(Point(origin.x + vSize.width * 0.729, origin.y + vSize.height * 0.522));
	pNode->addChild(skinThreeLabel, 4);

	
	//技能栏
	skillOneLabel = LabelTTF::create("0", "fonts/Marker Felt", 42);
	skillOneLabel->setColor(ccc3(0, 0, 1));
	skillOneLabel->setPosition(Point(origin.x + vSize.width * 0.45, origin.y + vSize.height * 0.24));
	pNode->addChild(skillOneLabel, 4);

	skillTwoLabel = LabelTTF::create("0", "fonts/Marker Felt", 42);
	skillTwoLabel->setColor(ccc3(0, 0, 1));
	skillTwoLabel->setPosition(Point(origin.x + vSize.width * 0.595, origin.y + vSize.height * 0.24));
	pNode->addChild(skillTwoLabel, 4);

	skillThreeLabel = LabelTTF::create("0", "fonts/Marker Felt", 42);
	skillThreeLabel->setColor(ccc3(0, 0, 1));
	skillThreeLabel->setPosition(Point(origin.x + vSize.width * 0.74, origin.y + vSize.height * 0.24));
	pNode->addChild(skillThreeLabel, 4);
}

//自动更新
void SecondMainScene::update(float dt)
{
	char newMoney[20];
	totalMoney = UserDefault::getInstance()->getIntegerForKey("Money");
	if (totalMoney >= 999999) {
		totalMoney = 999999;
		UserDefault::getInstance()->setIntegerForKey("Money", 999999);
		sprintf(newMoney, "%d", totalMoney);
		moneyLabel->setString(newMoney);
	}
	else {
		sprintf(newMoney, "%d", totalMoney);
		moneyLabel->setString(newMoney);
	}

	skin = UserDefault::getInstance()->getIntegerForKey("Skin");
	if (skin == 1) {
		skinOneLabel->setString("X");
		skinTwoLabel->setString(" ");
		skinThreeLabel->setString(" ");
	}
	else if (skin == 2) {
		skinOneLabel->setString(" ");
		skinTwoLabel->setString("X");
		skinThreeLabel->setString(" ");
	}
	else {
		skinOneLabel->setString(" ");
		skinTwoLabel->setString(" ");
		skinThreeLabel->setString("X");
	}
	
	char newSkillOne[20];
	skillOne = UserDefault::getInstance()->getIntegerForKey("SkillOne");
	if (skillOne >= 999) {
		skillOne = 999;
		UserDefault::getInstance()->setIntegerForKey("SkillOne", 999);
		sprintf(newSkillOne, "%d", skillOne);
		skillOneLabel->setString(newSkillOne);
	}
	else {
		sprintf(newSkillOne, "%d", skillOne);
		skillOneLabel->setString(newSkillOne);
	}

	char newSkillTwo[20];
	skillTwo = UserDefault::getInstance()->getIntegerForKey("SkillTwo");
	if (skillTwo >= 999) {
		skillTwo = 999;
		UserDefault::getInstance()->setIntegerForKey("SkillTwo", 999);
		sprintf(newSkillTwo, "%d", skillTwo);
		skillTwoLabel->setString(newSkillTwo);
	}
	else {
		sprintf(newSkillTwo, "%d", skillTwo);
		skillTwoLabel->setString(newSkillTwo);
	}

	char newSkillThree[20];
	skillThree = UserDefault::getInstance()->getIntegerForKey("SkillThree");
	if (skillThree >= 999) {
		skillThree = 999;
		UserDefault::getInstance()->setIntegerForKey("SkillThree", 999);
		sprintf(newSkillThree, "%d", skillThree);
		skillThreeLabel->setString(newSkillThree);
	}
	else {
		sprintf(newSkillThree, "%d", skillThree);
		skillThreeLabel->setString(newSkillThree);
	}
}

//鼠标点击选择关卡-0
void SecondMainScene::zeroLevelCallBack(Ref* pSender)
{
	auto scene = TestTypeGameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

//鼠标点击选择关卡-1
void SecondMainScene::oneLevelCallBack(Ref* pSender)
{
	UserDefault::getInstance()->setIntegerForKey("ATypeLevel", 1);
	auto scene = ATypeGameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

//鼠标点击选择关卡-2
void SecondMainScene::twoLevelCallBack(Ref* pSender)
{
	UserDefault::getInstance()->setIntegerForKey("ATypeLevel", 2);
	auto scene = ATypeGameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

//鼠标点击选择关卡-3
void SecondMainScene::threeLevelCallBack(Ref* pSender)
{
	UserDefault::getInstance()->setIntegerForKey("BTypeLevel", 1);
	auto scene = BTypeGameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

//鼠标点击选择关卡-4
void SecondMainScene::fourLevelCallBack(Ref* pSender)
{
	UserDefault::getInstance()->setIntegerForKey("BTypeLevel", 2);
	auto scene = BTypeGameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

//鼠标点击关闭操作
void SecondMainScene::gameCloseCallback(cocos2d::Ref* pSender)
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
void SecondMainScene::getSetUpLayer(Ref* pSender, Node* pNode)
{
	pNode->runAction(ScaleTo::create(0.01, 1));
	pNode->setVisible(true);
}

//鼠标点击关闭二级菜单
void SecondMainScene::menuClose(Ref* pSender, Node* pNode)
{
	pNode->setVisible(false);
	pNode->runAction(ScaleTo::create(0.01, 0.01));
}

//音乐滑块效果
void SecondMainScene::musicSliderCallBack(Ref* pSender, Control::EventType type)
{
	auto slider = (ControlSlider*)pSender;
	auto value = slider->getValue();
	value = value / 100;
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(value);
	UserDefault::getInstance()->setFloatForKey("MusicVolume", value);
}

//音效滑块效果
void SecondMainScene::effectSliderCallBack(Ref* pSender, Control::EventType type)
{
	auto slider = (ControlSlider*)pSender;
	auto value = slider->getValue();
	value = value / 100;
	SimpleAudioEngine::getInstance()->setEffectsVolume(value);
	UserDefault::getInstance()->setFloatForKey("EffectVolume", value);
}

//返回上级场景
void SecondMainScene::returnCallBack(Ref* pSender)
{
	auto scene = MainScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

//选择皮肤
void SecondMainScene::choseSkin(cocos2d::Ref* pSender, const int num)
{
	UserDefault::getInstance()->setIntegerForKey("Skin", num);
}

//购买特效
void SecondMainScene::buySkill(cocos2d::Ref* pSender, const int num)
{
	if (totalMoney >= 100) {
		totalMoney = totalMoney - 100;
		UserDefault::getInstance()->setIntegerForKey("Money", totalMoney);

		if (num == 1) {
			skillOne = skillOne + 1;
			UserDefault::getInstance()->setIntegerForKey("SkillOne", skillOne);
		}
		else if (num == 2) {
			skillTwo = skillTwo + 1;
			UserDefault::getInstance()->setIntegerForKey("SkillTwo", skillTwo);
		}
		else {
			skillThree = skillThree + 1;
			UserDefault::getInstance()->setIntegerForKey("SkillThree", skillThree);
		}
	}
}