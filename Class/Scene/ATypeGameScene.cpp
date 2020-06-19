#include "Classes/Scene/ATypeGameScene.h"
#include "Classes/Scene/SecondMainScene.h"
#include "Classes/Overall/WidelyUsed.h"
#include "Classes/Block/Block.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace std;
using namespace cocos2d::extension;
using namespace CocosDenshion;

//二维向量,元素舞台
std::vector<Block*> blockLine;
std::vector<std::vector<Block*>> blockStage;

Scene* ATypeGameScene::createScene()
{
	return ATypeGameScene::create();
}

bool ATypeGameScene::init()
{
	if (!Scene::init()) { return false; };

	if (UserDefault::getInstance()->getIntegerForKey("ATypeLevel") == 1) {
		maxStep = 15;
		maxGoal = 15;
		targetNum = 5;
		step = maxStep;
		goal = maxGoal;
	}
	else {
		maxStep = 12;
		maxGoal = 20;
		targetNum = 2;
		step = maxStep;
		goal = maxGoal;
	}

	sprintf(targetChar, "block/llk%d.png", targetNum + 6 * (UserDefault::getInstance()->getIntegerForKey("Skin") - 1));

	initStillNode();
	initMoveLayer();
	initGameLayer();

	return true;
}

//静态元素
void ATypeGameScene::initStillNode()
{
	auto vSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto stillNode = Node::create();
	this->addChild(stillNode, 1);

	//大背景
	auto theBackGround = Sprite::create("pic/TheBG2.png");
	if (theBackGround == nullptr) {
		problemLoading("TheBG2.png");
	}
	else {
		theBackGround->setScale(vSize.height / theBackGround->getContentSize().height + 0.02);
		theBackGround->setPosition(Vec2(vSize.width / 2 + origin.x, vSize.height / 2 + origin.y));
		stillNode->addChild(theBackGround, 1);
	}

	//游戏区背景
	auto gameBackGround = Sprite::create("pic/GameBG.png");
	if (gameBackGround == nullptr) {
		problemLoading("GameBG.png");
	}
	else {
		gameBackGround->setScale(vSize.height / gameBackGround->getContentSize().height);
		gameBackGround->setAnchorPoint(Vec2(1, 0));
		gameBackGround->setPosition(Vec2(vSize.width + origin.x,  origin.y));
		stillNode->addChild(gameBackGround, 2);
	}

	//分数栏和设置栏背景
	auto markBoard = Sprite::create("pic/MarkBoard.png");
	if (markBoard == nullptr) {
		problemLoading("MarkBoard.png");
	}
	else {
		markBoard->setScale(vSize.height / gameBackGround->getContentSize().height);
		markBoard->setPosition(Vec2(vSize.width * 0.25 + origin.x, vSize.height * 0.37 + origin.y));
		stillNode->addChild(markBoard, 3);
	}

	//目标栏背景
	auto goalBoard = Sprite::create("pic/GoalBoard.png");
	if (goalBoard == nullptr) {
		problemLoading("GoalBoard.png");
	}
	else {
		goalBoard->setScale(vSize.height / gameBackGround->getContentSize().height);
		goalBoard->setAnchorPoint(Vec2(0, 1));
		goalBoard->setPosition(Vec2(vSize.width * 0 + origin.x, vSize.height + origin.y));
		stillNode->addChild(goalBoard, 4);
	}
}

//动态元素
void ATypeGameScene::initMoveLayer()
{
	auto vSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto stillLayer = Layer::create();
	this->addChild(stillLayer, 2);
	auto moveLayer = Layer::create();
	this->addChild(moveLayer, 4);
	moveLayer->setVisible(false);

	//暂停按钮
	auto pauseItem = MenuItemImage::create("pic/PauseNormal.png", "pic/PauseSelected.png",
		CC_CALLBACK_1(ATypeGameScene::getSetUpLayer, this, moveLayer));
	if (pauseItem == nullptr || pauseItem->getContentSize().width <= 0 || pauseItem->getContentSize().height <= 0) {
		problemLoading("'PauseNormal.png' and 'PauseSelected.png'");
	}
	else {
		const float x = origin.x + pauseItem->getContentSize().width / 2;
		const float y = origin.y + pauseItem->getContentSize().height / 2;
		pauseItem->setPosition(Vec2(x, y));
	}

	//静态菜单
	auto stillMenu = Menu::create(pauseItem, NULL);
	stillMenu->setPosition(Vec2::ZERO);
	stillLayer->addChild(stillMenu);

	//二级菜单
	initMenu(moveLayer);
	moveLayer->runAction(ScaleTo::create(0.01, 0.01));
}

//菜单元素
void ATypeGameScene::initMenu(Node* pNode)
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
		cccontrol_selector(ATypeGameScene::musicSliderCallBack), Control::EventType::VALUE_CHANGED);
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
		cccontrol_selector(ATypeGameScene::effectSliderCallBack), Control::EventType::VALUE_CHANGED);
	pNode->addChild(effectSlider, 6);

	//动态菜单关闭按钮
	auto menuCloseItem = MenuItemImage::create("pic/MenuCloseNormal.png", "pic/MenuCloseSelected.png",
		CC_CALLBACK_1(ATypeGameScene::menuClose, this, pNode));
	if (menuCloseItem == nullptr || menuCloseItem->getContentSize().width <= 0 || menuCloseItem->getContentSize().height <= 0) {
		problemLoading("MenuCloseNormal.png and MenuCloseSelected.png");
	}
	else {
		menuCloseItem->setAnchorPoint(Vec2(1, 1));
		const float x = origin.x + vSize.width / 2 + menuBackground->getContentSize().width / 2;
		const float y = origin.y + vSize.height / 2 + menuBackground->getContentSize().height / 2;
		menuCloseItem->setPosition(Vec2(x, y));
	}
	
	//返回按钮
	auto returnGameItem = MenuItemImage::create("pic/ReturnHomeNormal.png", "pic/ReturnHomeSelected.png",
		CC_CALLBACK_1(ATypeGameScene::returnCallBack, this));
	if (returnGameItem == nullptr || returnGameItem->getContentSize().width <= 0 || returnGameItem->getContentSize().height <= 0) {
		problemLoading("'ReturnHomeNormal.png' and 'ReturnHomeSelected.png'");
	}
	else {
		returnGameItem->setScale(1.2);
		const float x = origin.x + vSize.width * 0.37;
		const float y = origin.y + vSize.height * 0.355;
		returnGameItem->setPosition(Vec2(x, y));
	}

	//退出按钮
	auto closeItem = MenuItemImage::create("pic/CloseNormal2.png", "pic/CloseSelected2.png",
		CC_CALLBACK_1(ATypeGameScene::gameCloseCallback, this));
	if (closeItem == nullptr || closeItem->getContentSize().width <= 0 || closeItem->getContentSize().height <= 0) {
		problemLoading("'CloseNormal2.png' and 'CloseSelected2.png'");
	}
	else {
		closeItem->setScale(1.2);
		const float x = origin.x + vSize.width * 0.63;
		const float y = origin.y + vSize.height * 0.355;
		closeItem->setPosition(Vec2(x, y));
	}

	//二级菜单
	auto moveMenu = Menu::create(menuCloseItem, returnGameItem, closeItem, NULL);
	moveMenu->setPosition(Vec2::ZERO);
	pNode->addChild(moveMenu, 3);
}

//音乐滑块效果
void ATypeGameScene::musicSliderCallBack(Ref* pSender, Control::EventType type)
{
	auto slider = (ControlSlider*)pSender;
	auto value = slider->getValue();
	value = value / 100;
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(value);
	UserDefault::getInstance()->setFloatForKey("MusicVolume", value);
}

//音效滑块效果
void ATypeGameScene::effectSliderCallBack(Ref* pSender, Control::EventType type)
{
	auto slider = (ControlSlider*)pSender;
	auto value = slider->getValue();
	value = value / 100;
	SimpleAudioEngine::getInstance()->setEffectsVolume(value);
	UserDefault::getInstance()->setFloatForKey("EffectVolume", value);
}

//鼠标点击关闭操作
void ATypeGameScene::gameCloseCallback(Ref* pSender)
{
	blockLine.clear();
	blockStage.clear();
	UserDefault::getInstance()->setFloatForKey("MusicVolume", 0.5);
	UserDefault::getInstance()->setFloatForKey("EffectVolume", 0.5);
	UserDefault::getInstance()->setIntegerForKey("Money", 0);
	UserDefault::getInstance()->setIntegerForKey("Skin", 1);
	UserDefault::getInstance()->setIntegerForKey("SkillOne", 1);
	UserDefault::getInstance()->setIntegerForKey("SkillTwo", 1);
	UserDefault::getInstance()->setIntegerForKey("SkillThree", 1);
	Director::getInstance()->end();
}

//鼠标点击弹出菜单
void ATypeGameScene::getSetUpLayer(Ref* pSender, Node* pNode)
{
	pNode->runAction(ScaleTo::create(0.01, 1));
	pNode->setVisible(true);
	this->pauseSchedulerAndActions();
}

//鼠标点击关闭菜单
void ATypeGameScene::menuClose(Ref* pSender, Node* pNode)
{
	pNode->setVisible(false);
	pNode->runAction(ScaleTo::create(0.01, 0.01));
	this->resumeSchedulerAndActions();
}

//返回上级场景
void ATypeGameScene::returnCallBack(Ref* pSender)
{
	step = maxStep;
	goal = maxGoal;
	grade = 0;
	blockLine.clear();
	blockStage.clear();
	auto scene = SecondMainScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

/*********************************游戏逻辑部分*********************************/
void ATypeGameScene::initGameLayer()
{
	Size vSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	auto gameLayer = Node::create();
	this->addChild(gameLayer, 3);

	auto menu = Menu::create();
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);

	//设置各个图片位置
	int x = -180, y = -180;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			int tempX = origin.x + vSize.width * 0.7 + x;
			int tempY = origin.y + vSize.height * 0.43 + y;
			pos[i][j] = Point(tempX, tempY);
			x = x + 70;
		}
		x = -180;
		y = y + 70;
	}

	x = -180;
	for (int i = 0; i < 8; i++) {
		int tempX = origin.x + vSize.width * 0.7 + x;
		int tempY = origin.y + vSize.height + 100;
		spos[i] = Point(tempX, tempY);
		x = x + 70;
	}

	//分数栏
	gradeLabel = LabelTTF::create("0", "fonts/Marker Felt", 44);
	gradeLabel->setColor(ccc3(0, 0, 1));
	gradeLabel->setPosition(Point(origin.x + vSize.width * 0.216, origin.y + vSize.height * 0.625 - gradeLabel->getContentSize().height));
	gameLayer->addChild(gradeLabel, 1);

	//步数栏
	stepLabel = LabelTTF::create("0", "fonts/Marker Felt", 44);
	stepLabel->setColor(ccc3(0, 0, 1));
	stepLabel->setPosition(Point(origin.x + vSize.width * 0.202, origin.y + vSize.height * 0.495 - stepLabel->getContentSize().height));
	gameLayer->addChild(stepLabel, 1);

	//目标栏
	goalLabel = LabelTTF::create("15", "fonts/Marker Felt", 60);
	goalLabel->setColor(ccc3(0, 0, 1));
	goalLabel->setPosition(Point(origin.x + vSize.width * 0.118, origin.y + vSize.height * 0.96 - gradeLabel->getContentSize().height));
	gameLayer->addChild(goalLabel, 1);

	//目标物体
	auto targetPic = Sprite::create(targetChar);
	targetPic->setPosition(Vec2(origin.x + vSize.width * 0.0355, origin.y + vSize.height * 0.91));
	targetPic->setScale(1.4f);
	this->addChild(targetPic, 1);

	//特技1-加3步
	auto skillItem1 = MenuItemImage::create("pic/Skill1Normal.png", "pic/Skill1Selected.png",
		CC_CALLBACK_1(ATypeGameScene::addStep, this));
	if (skillItem1 == nullptr || skillItem1->getContentSize().width <= 0 || skillItem1->getContentSize().height <= 0) {
		problemLoading("'Skill1Normal.png' and 'Skill1Selected.png'");
	}
	else {
		const float x = origin.x + vSize.width * 0.228;
		const float y = origin.y + vSize.height * 0.908;
		skillItem1->setScale(0.7f);
		skillItem1->setPosition(Vec2(x, y));
	}

	//特技2-交换两个
	auto skillItem2 = MenuItemImage::create("pic/Skill2Normal.png", "pic/Skill2Selected.png",
		CC_CALLBACK_1(ATypeGameScene::switchTwo, this));
	if (skillItem2 == nullptr || skillItem2->getContentSize().width <= 0 || skillItem2->getContentSize().height <= 0) {
		problemLoading("'Skill2Normal.png' and 'Skill2Selected.png'");
	}
	else {
		const float x = origin.x + vSize.width * 0.2835;
		const float y = origin.y + vSize.height * 0.908;
		skillItem2->setScale(0.7f);
		skillItem2->setPosition(Vec2(x, y));
	}

	//特技3-重新排序
	auto skillItem3 = MenuItemImage::create("pic/Skill3Normal.png", "pic/Skill3Selected.png",
		CC_CALLBACK_1(ATypeGameScene::reFill, this));
	if (skillItem3 == nullptr || skillItem3->getContentSize().width <= 0 || skillItem3->getContentSize().height <= 0) {
		problemLoading("'Skill3Normal.png' and 'Skill3Selected.png'");
	}
	else {
		const float x = origin.x + vSize.width * 0.339;
		const float y = origin.y + vSize.height * 0.908;
		skillItem3->setScale(0.7f);
		skillItem3->setPosition(Vec2(x, y));
	}

	menu = Menu::create(skillItem1, skillItem2, skillItem3, NULL);
	menu->setPosition(Point::ZERO);
	gameLayer->addChild(menu, 1);

	//选择框
	auto outSq = Sprite::create("block/kuang.png");
	outSq->setPosition(0, 0);
	outSq->setScale(1.4f);
	this->addChild(outSq, 2, 101);

	//隐藏选择框
	Hide* hide = Hide::create();
	outSq->runAction(hide);

	//特效2选择时遮罩
	auto skillTwoOn = Sprite::create("pic/Skill2On.png");
	skillTwoOn->setPosition(Vec2(origin.x + vSize.width * 0.2835, origin.y + vSize.height * 0.908));
	skillTwoOn->setName("test");
	skillTwoOn->setScale(0.7f);
	this->addChild(skillTwoOn, 3);
	skillTwoOn->runAction(ScaleTo::create(0.01f, 0.01f));
	
	//创建游戏主区域
	int picNum;
	char picName[30];
	std::srand(time(NULL));
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			picNum = rand() % 6 + 1 + 6 * (UserDefault::getInstance()->getIntegerForKey("Skin") - 1);
			sprintf(picName, "block/llk%d.png", picNum);

			Block* p = new Block(pos[i][j], picName);
			blockLine.push_back(p);

			menu = Menu::create(p->getPic(), NULL);
			menu->setPosition(Point::ZERO);
			this->addChild(menu, 1);
			this->addChild(p->getSpePic(), 1);
		}
		blockStage.push_back(blockLine);
		blockLine.clear();
	}

	//刷新
	this->schedule(schedule_selector(ATypeGameScene::clearBlocks), 0.5f);
	this->schedule(schedule_selector(ATypeGameScene::explode), 1.5f);
	this->schedule(schedule_selector(ATypeGameScene::endGame), 3.7f);
	this->scheduleUpdate();
}
	
void ATypeGameScene::addStep(cocos2d::Ref* pSender)
{
	if (UserDefault::getInstance()->getIntegerForKey("SkillOne") > 0) {
		isAddStep = true;
		int temp = UserDefault::getInstance()->getIntegerForKey("SkillOne");
		UserDefault::getInstance()->setIntegerForKey("SkillOne", temp - 1);
		step = step + 3;
	}
}

void ATypeGameScene::switchTwo(cocos2d::Ref* pSender)
{
	if (UserDefault::getInstance()->getIntegerForKey("SkillTwo") > 0) {
		int temp = UserDefault::getInstance()->getIntegerForKey("SkillTwo");
		UserDefault::getInstance()->setIntegerForKey("SkillTwo", temp - 1);
		auto skillTwoOn = getChildByName("test");

		if (isSwitchOn == true) {
			isSwitchOn = false;
		}
		else {
			isSwitchOn = true;
			skillTwoOn->runAction(ScaleTo::create(0.01f, 0.7f));
		}
	}
}

void ATypeGameScene::reFill(cocos2d::Ref* pSender)
{
	if (UserDefault::getInstance()->getIntegerForKey("SkillThree") > 0) {
		int temp = UserDefault::getInstance()->getIntegerForKey("SkillThree");
		UserDefault::getInstance()->setIntegerForKey("SkillThree", temp - 1);
		
		this->unscheduleUpdate();
		this->unschedule(schedule_selector(ATypeGameScene::clearBlocks));

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				blockStage[i][j]->getPic()->runAction(ScaleTo::create(0.0f, 0.0f));
				blockStage[i][j]->getSpePic()->runAction(ScaleTo::create(0.0f, 0.0f));
			}
		}

		blockLine.clear();
		blockStage.clear();

		auto menu = Menu::create();
		menu->setPosition(Point::ZERO);
		this->addChild(menu, 1);

		int picNum;
		char picName[30];
		std::srand(time(NULL));
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				picNum = rand() % 6 + 1 + 6 * (UserDefault::getInstance()->getIntegerForKey("Skin") - 1);
				sprintf(picName, "block/llk%d.png", picNum);

				Block* p = new Block(pos[i][j], picName);
				blockLine.push_back(p);

				menu = Menu::create(p->getPic(), NULL);
				menu->setPosition(Point::ZERO);
				this->addChild(menu, 1);
				this->addChild(p->getSpePic(), 1);
			}
			blockStage.push_back(blockLine);
			blockLine.clear();
		}

		this->schedule(schedule_selector(ATypeGameScene::clearBlocks), 0.5f);
		this->scheduleUpdate();
	}
}

void ATypeGameScene::update(float dt)
{
	auto outSq = getChildByTag(101);
	auto skillTwoOn = getChildByName("test");

	if (step == maxStep && isAddStep == false) {
		grade = 0;
		goal = maxGoal;
	}

	char newGrade[20];
	if (grade >= 99999) {
		grade = 99999;
		sprintf(newGrade, "%d", grade);
		gradeLabel->setString(newGrade);
	}
	else {
		sprintf(newGrade, "%d", grade);
		gradeLabel->setString(newGrade);
	}

	char newStep[20];
	if (step == 0) {
		sprintf(newStep, "%d", step);
		stepLabel->setString(newStep);
		this->unscheduleUpdate();
	}
	else {
		sprintf(newStep, "%d", step);
		stepLabel->setString(newStep);
	}

	char newGoal[20];
	if (goal <= 0) {
		goal = 0;
		sprintf(newGoal, "%d", goal);
		goalLabel->setString(newGoal);
		this->unscheduleUpdate();
	}
	else {
		sprintf(newGoal, "%d", goal);
		goalLabel->setString(newGoal);
	}

	//鼠标点击第1次
	if (Block::flag == 1) {
		for (int i = 0; i < blockStage.size(); i++) {
			for (int j = 0; j < blockStage[i].size(); j++) {
				if (blockStage[i][j]->getSwap() == 1) {
					MoveTo* move = MoveTo::create(0, blockStage[i][j]->getPos());
					auto unHide = Sequence::create(Show::create(), NULL);
					outSq->runAction(Spawn::create(move, unHide, NULL));
				}
			}
		}
	}

	//鼠标点击第2次
	if (Block::flag == 2) {
		std::vector<int> numi;
		std::vector<int> numj;

		for (int i = 0; i < blockStage.size(); i++) {
			for (int j = 0; j < blockStage[i].size(); j++) {
				if (blockStage[i][j]->getSwap() == 1) {
					numi.push_back(i);
					numj.push_back(j);
				}
			}
		}

		if ((numi[0] == numi[1] && abs(numj[0] - numj[1]) == 1) || (numj[0] == numj[1] && abs(numi[0] - numi[1]) == 1)) {
			cocos2d::MoveTo* move1 = cocos2d::MoveTo::create(0.05f, blockStage[numi[0]][numj[0]]->getPos());
			cocos2d::MoveTo* move2 = cocos2d::MoveTo::create(0.05f, blockStage[numi[1]][numj[1]]->getPos());

			blockStage[numi[0]][numj[0]]->getPic()->runAction(Sequence::create(move2->clone(), DelayTime::create(0.05f), NULL));
			blockStage[numi[0]][numj[0]]->getSpePic()->runAction(Sequence::create(move2->clone(), DelayTime::create(0.05f), NULL));
			blockStage[numi[1]][numj[1]]->getPic()->runAction(Sequence::create(move1->clone(), DelayTime::create(0.05f), NULL));
			blockStage[numi[1]][numj[1]]->getSpePic()->runAction(Sequence::create(move1->clone(), DelayTime::create(0.05f), NULL));

			Point po = blockStage[numi[0]][numj[0]]->getPos();
			blockStage[numi[0]][numj[0]]->setPos(blockStage[numi[1]][numj[1]]->getPos());
			blockStage[numi[1]][numj[1]]->setPos(po);

			blockStage[numi[0]][numj[0]]->initSwap();
			blockStage[numi[1]][numj[1]]->initSwap();

			std::swap(blockStage[numi[0]][numj[0]], blockStage[numi[1]][numj[1]]);

			if (!clearAble(numi[0], numj[0]) && !clearAble(numi[1], numj[1]) && isSwitchOn == false) {
				cocos2d::MoveTo* move3 = cocos2d::MoveTo::create(0.05f, blockStage[numi[0]][numj[0]]->getPos());
				cocos2d::MoveTo* move4 = cocos2d::MoveTo::create(0.05f, blockStage[numi[1]][numj[1]]->getPos());

				blockStage[numi[0]][numj[0]]->getPic()->runAction(Sequence::create(DelayTime::create(0.05f), move4->clone(), NULL));
				blockStage[numi[0]][numj[0]]->getSpePic()->runAction(Sequence::create(DelayTime::create(0.05f), move4->clone(), NULL));
				blockStage[numi[1]][numj[1]]->getPic()->runAction(Sequence::create(DelayTime::create(0.05f), move3->clone(), NULL));
				blockStage[numi[1]][numj[1]]->getSpePic()->runAction(Sequence::create(DelayTime::create(0.05f), move3->clone(), NULL));

				po = blockStage[numi[0]][numj[0]]->getPos();
				blockStage[numi[0]][numj[0]]->setPos(blockStage[numi[1]][numj[1]]->getPos());
				blockStage[numi[1]][numj[1]]->setPos(po);

				blockStage[numi[0]][numj[0]]->initSwap();
				blockStage[numi[1]][numj[1]]->initSwap();

				std::swap(blockStage[numi[0]][numj[0]], blockStage[numi[1]][numj[1]]);
			}
			else {
				if (isSwitchOn == true) {
					isSwitchOn = false;
					skillTwoOn->runAction(ScaleTo::create(0.01f, 0.01f));
				}
				else {
					step = step - 1;
				}
			}

			numi.clear();
			numj.clear();
		}
		else {
			blockStage[numi[0]][numj[0]]->initSwap();
			blockStage[numi[1]][numj[1]]->initSwap();

			numi.clear();
			numj.clear();
		}

		Hide* hide = Hide::create();
		outSq->runAction(hide);
		Block::flag = 0;
	}

	//鼠标点击第3次
	if (Block::flag == 3) {
		Hide* hide = Hide::create();
		outSq->runAction(hide);
		Block::flag = 0;
	}
}

void ATypeGameScene::isTarget(const int x, const int y) {
	if (blockStage[x][y]->getName() == targetChar)
		goal = goal - 1;
}

void ATypeGameScene::clearBlocks(float dt)
{
	std::vector<int> tempMelti;
	std::vector<int> tempMeltj;
	std::vector<int> maxMelti;
	std::vector<int> maxMeltj;

	char newGrade[30];
	if (grade >= 99999) {
		grade = 99999;
		sprintf(newGrade, "%d", grade);
		gradeLabel->setString(newGrade);
	}

	auto pushMeltPos = [&](int x, int y) {
		tempMelti.push_back(x);
		tempMeltj.push_back(y);
	};
	
	auto clearOne = [&](int X, int Y) {
		blockStage[X][Y]->getPic()->runAction(Sequence::create(ScaleTo::create(0.15f, 0.0f), NULL));
		blockStage[X][Y]->getSpePic()->runAction(Sequence::create(ScaleTo::create(0.15f, 0.0f), NULL));
		isTarget(X, Y);
		choseEffect(X, Y);
		blockStage[X][Y]->setName("null");
	};

	int key = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			tempMelti.clear();
			tempMeltj.clear();

			//判断有没有横着的(向右看)
			if (j < blockStage[i].size() - 2) {
				if (blockStage[i][j]->getName() == blockStage[i][j + 1]->getName() && blockStage[i][j]->getName() == blockStage[i][j + 2]->getName()) {
					pushMeltPos(i, j);
					pushMeltPos(i, j + 1);
					pushMeltPos(i, j + 2);
					//4消
					if (j + 3 < blockStage[i].size() && blockStage[i][j]->getName() == blockStage[i][j + 3]->getName()) {
						pushMeltPos(i, j + 3);
						//5消
						if (j + 4 < blockStage[i].size() && blockStage[i][j]->getName() == blockStage[i][j + 4]->getName()) {
							pushMeltPos(i, j + 4);
						}
					}
					key = 1;
				}
			}
			//判断有没有横着的(向左看)
			if (j - 2 >= 0) {
				if (blockStage[i][j]->getName() == blockStage[i][j - 1]->getName() && blockStage[i][j]->getName() == blockStage[i][j - 2]->getName()) {
					if (key == 0) {
						pushMeltPos(i, j);
					}
					pushMeltPos(i, j - 1);
					pushMeltPos(i, j - 2);
					//4消
					if (j - 3 >= 0 && blockStage[i][j]->getName() == blockStage[i][j - 3]->getName()) {
						pushMeltPos(i, j - 3);
						//5消
						if (j - 4 >= 0 && blockStage[i][j]->getName() == blockStage[i][j - 4]->getName()) {
							pushMeltPos(i, j - 4);
						}
					}
					key = 1;
				}
			}
			//判断有没有竖着的(向上看)
			if (i < blockStage.size() - 2) {
				if (blockStage[i][j]->getName() == blockStage[i + 1][j]->getName() && blockStage[i][j]->getName() == blockStage[i + 2][j]->getName()) {

					if (key == 0) {
						pushMeltPos(i, j);
					}
					pushMeltPos(i + 1, j);
					pushMeltPos(i + 2, j);
					//4消
					if (i + 3 < blockStage.size() && blockStage[i][j]->getName() == blockStage[i + 3][j]->getName()) {
						pushMeltPos(i + 3, j);
						//5消
						if (i + 4 < blockStage.size() && blockStage[i][j]->getName() == blockStage[i + 4][j]->getName()) {
							pushMeltPos(i + 4, j);
						}
					}
					key = 1;
				}
			}
			//判断有没有竖着的(向下看)
			if (i - 2 >= 0) {
				if (blockStage[i][j]->getName() == blockStage[i - 1][j]->getName() && blockStage[i][j]->getName() == blockStage[i - 2][j]->getName()) {

					if (key == 0) {
						pushMeltPos(i, j);
					}
					pushMeltPos(i - 1, j);
					pushMeltPos(i - 2, j);
					//4消
					if (i - 3 >= 0 && blockStage[i][j]->getName() == blockStage[i - 3][j]->getName()) {
						pushMeltPos(i - 3, j);
						//5消
						if (i - 4 >= 0 && blockStage[i][j]->getName() == blockStage[i - 4][j]->getName()) {
							pushMeltPos(i - 4, j);
						}
					}
					key = 1;
				}
			}

			//判断有没有可以消除的
			if (key == 1) {
				if (tempMelti.size() > maxMelti.size()) {
					maxMelti.clear();
					maxMeltj.clear();
					maxMelti = tempMelti;
					maxMeltj = tempMeltj;
				}
			}

			tempMelti.clear();
			tempMeltj.clear();
			key = 0;
		}
	}

	//消除
	if (maxMelti.size() != 0) {
		//3消
		if (maxMelti.size() == 3) {
			//判断有无特效block
			int specialKey = 0;
			int powerKey = 0;
			for (int i = 0; i < 3; i++) {
				if (blockStage[maxMelti[i]][maxMeltj[i]]->getState() == 2) {
					blockStage[maxMelti[i]][maxMeltj[i]]->setState(1);
					this->addChild(blockStage[maxMelti[i]][maxMeltj[i]]->getSpePic(), 1);
					specialKey = 1;
				}
				if (blockStage[maxMelti[i]][maxMeltj[i]]->getState() == 3) {
					blockStage[maxMelti[i]][maxMeltj[i]]->setState(1);
					this->addChild(blockStage[maxMelti[i]][maxMeltj[i]]->getSpePic(), 1);
					powerKey = 1;
				}
			}

			if (specialKey == 0 && powerKey == 0) {
				for (int k1 = 0; k1 < maxMelti.size(); k1++) {
					clearOne(maxMelti[k1], maxMeltj[k1]);
					grade += pow(2, maxMelti.size());
				}
			}
			else if (specialKey == 1 && powerKey == 0) {
				if (maxMelti[0] == maxMelti[1]) {
					for (int i = 0; i < 8; i++) {
						clearOne(maxMelti[0], i);
						grade += pow(2, 9);
					}
				}
				else {
					for (int i = 0; i < 8; i++) {
						clearOne(i, maxMeltj[0]);
						grade += pow(2, 9);
					}
				}
			}
			else {
				for (int k = 0; k < maxMelti.size(); k++) {
					for (int i = 0; i < 8; i++) {
						if (blockStage[maxMelti[k]][i]->getName() != "null") {
							clearOne(maxMelti[k], i);
						}
						grade += pow(2, 9);
					}
					for (int i = 0; i < 8; i++) {
						if (blockStage[i][maxMeltj[k]]->getName() != "null") {
							clearOne(i, maxMeltj[k]);
						}
						grade += pow(2, 9);
					}
				}
			}
		}
		//4消
		else if (maxMelti.size() == 4) {
			int specialKey = 0;
			int powerKey = 0;
			for (int i = 0; i < 3; i++) {
				if (blockStage[maxMelti[i]][maxMeltj[i]]->getState() == 2) {
					blockStage[maxMelti[i]][maxMeltj[i]]->setState(1);
					this->addChild(blockStage[maxMelti[i]][maxMeltj[i]]->getSpePic(), 1);
					specialKey = 1;
				}
				if (blockStage[maxMelti[i]][maxMeltj[i]]->getState() == 3) {
					blockStage[maxMelti[i]][maxMeltj[i]]->setState(1);
					this->addChild(blockStage[maxMelti[i]][maxMeltj[i]]->getSpePic(), 1);
					powerKey = 1;
				}
			}

			if (specialKey == 0 && powerKey == 0) {
				for (int k1 = 0; k1 < maxMelti.size(); k1++) {
					if (k1 == 1) {
						blockStage[maxMelti[1]][maxMeltj[1]]->setState(2);
						this->addChild(blockStage[maxMelti[1]][maxMeltj[1]]->getSpePic(), 1);
						isTarget(maxMelti[1], maxMeltj[1]);
					}
					else {
						clearOne(maxMelti[k1], maxMeltj[k1]);
					}
					grade += pow(2, maxMelti.size());
				}
			}
			else if (specialKey == 1 && powerKey == 0) {
				if (maxMelti[0] == maxMelti[1]) {
					for (int i = 0; i < 8; i++) {
						if (i == maxMelti[1]) {
							blockStage[maxMelti[1]][maxMeltj[1]]->setState(2);
							this->addChild(blockStage[maxMelti[1]][maxMeltj[1]]->getSpePic(), 1);
							isTarget(maxMelti[1], maxMeltj[1]);
						}
						else {
							clearOne(maxMelti[0], i);
						}
						grade += pow(2, 9);
					}
				}
				else {
					for (int i = 0; i < 8; i++) {
						if (i == maxMelti[1]) {
							blockStage[maxMelti[1]][maxMeltj[1]]->setState(2);
							this->addChild(blockStage[maxMelti[1]][maxMeltj[1]]->getSpePic(), 1);
							isTarget(maxMelti[1], maxMeltj[1]);
						}
						else {
							clearOne(i, maxMeltj[0]);
						}
						grade += pow(2, 9);
					}
				}
			}
			else {
				for (int k = 0; k < maxMelti.size(); k++) {
					for (int i = 0; i < 8; i++) {
						if (blockStage[maxMelti[k]][i]->getName() != "null") {
							if (k == 1 && i == maxMeltj[1]) {
								blockStage[maxMelti[1]][maxMeltj[1]]->setState(2);
								this->addChild(blockStage[maxMelti[1]][maxMeltj[1]]->getSpePic(), 1);
								isTarget(maxMelti[1], maxMeltj[1]);
							}
							else {
								clearOne(maxMelti[k], i);
							}
						}
						grade += pow(2, 13);
					}
					for (int i = 0; i < 8; i++) {
						if (blockStage[i][maxMeltj[k]]->getName() != "null") {
							if (k == 1 && i == maxMelti[1]) {
								blockStage[maxMelti[1]][maxMeltj[1]]->setState(2);
								this->addChild(blockStage[maxMelti[1]][maxMeltj[1]]->getSpePic(), 1);
								isTarget(maxMelti[1], maxMeltj[1]);
							}
							else {
								clearOne(i, maxMeltj[k]);
							}
						}
						grade += pow(2, 13);
					}
				}
			}
		}
		//5或更多消
		else {
			int specialKey = 0;
			int powerKey = 0;
			for (int i = 0; i < 3; i++) {
				if (blockStage[maxMelti[i]][maxMeltj[i]]->getState() == 2) {
					blockStage[maxMelti[i]][maxMeltj[i]]->setState(1);
					this->addChild(blockStage[maxMelti[i]][maxMeltj[i]]->getSpePic(), 1);
					specialKey = 1;
				}
				if (blockStage[maxMelti[i]][maxMeltj[i]]->getState() == 3) {
					blockStage[maxMelti[i]][maxMeltj[i]]->setState(1);
					this->addChild(blockStage[maxMelti[i]][maxMeltj[i]]->getSpePic(), 1);
					powerKey = 1;
				}
			}

			if (specialKey == 0 && powerKey == 0) {
				for (int k1 = 0; k1 < maxMelti.size(); k1++) {
					if (k1 == 1) {
						blockStage[maxMelti[1]][maxMeltj[1]]->setState(3);
						this->addChild(blockStage[maxMelti[1]][maxMeltj[1]]->getSpePic(), 1);
						isTarget(maxMelti[1], maxMeltj[1]);
					}
					else {
						clearOne(maxMelti[k1], maxMeltj[k1]);
					}
					grade += pow(2, maxMelti.size());
				}
			}
			else if (specialKey == 1 && powerKey == 0) {
				if (maxMelti[0] == maxMelti[1]) {
					for (int i = 0; i < 8; i++) {
						if (i == maxMelti[1]) {
							blockStage[maxMelti[1]][maxMeltj[1]]->setState(3);
							this->addChild(blockStage[maxMelti[1]][maxMeltj[1]]->getSpePic(), 1);
							isTarget(maxMelti[1], maxMeltj[1]);
						}
						else {
							clearOne(maxMelti[0], i);
						}
						grade += pow(2, 9);
					}
				}
				else {
					for (int i = 0; i < 8; i++) {
						if (i == maxMelti[1]) {
							blockStage[maxMelti[1]][maxMeltj[1]]->setState(3);
							this->addChild(blockStage[maxMelti[1]][maxMeltj[1]]->getSpePic(), 1);
							isTarget(maxMelti[1], maxMeltj[1]);
						}
						else {
							clearOne(i, maxMeltj[0]);
						}
						grade += pow(2, 9);
					}
				}
			}
			else {
				for (int k = 0; k < maxMelti.size(); k++) {
					for (int i = 0; i < 8; i++) {
						if (blockStage[maxMelti[k]][i]->getName() != "null") {
							if (k == 1 && i == maxMeltj[1]) {
								blockStage[maxMelti[1]][maxMeltj[1]]->setState(3);
								this->addChild(blockStage[maxMelti[1]][maxMeltj[1]]->getSpePic(), 1);
								isTarget(maxMelti[1], maxMeltj[1]);
							}
							else {
								clearOne(maxMelti[k], i);
							}
						}
						grade += pow(2, 13);
					}
					for (int i = 0; i < 8; i++) {
						if (blockStage[i][maxMeltj[k]]->getName() != "null") {
							if (k == 1 && i == maxMelti[1]) {
								blockStage[maxMelti[1]][maxMeltj[1]]->setState(3);
								this->addChild(blockStage[maxMelti[1]][maxMeltj[1]]->getSpePic(), 1);
								isTarget(maxMelti[1], maxMeltj[1]);
							}
							else {
								clearOne(i, maxMeltj[k]);
							}
						}
						grade += pow(2, 13);
					}
				}
			}
		}

		fillFull();
		
		maxMelti.clear();
		maxMeltj.clear();
	}
}

void ATypeGameScene::fillFull()
{
	//向下补齐
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (blockStage[j][i]->getName() == "null") {
				for (int k2 = j; k2 < 8; k2++) {
					if (blockStage[k2][i]->getName() == "null") {
						continue;
					}
					else {
						Point tempPos = blockStage[k2][i]->getPos();
						blockStage[k2][i]->setPos(blockStage[j][i]->getPos());
						blockStage[j][i]->setPos(tempPos);

						std::swap(blockStage[k2][i], blockStage[j][i]);

						blockStage[j][i]->getPic()->runAction(
							Sequence::create(MoveTo::create(0.15f, pos[j][i]), NULL));
						blockStage[j][i]->getSpePic()->runAction(
							Sequence::create(MoveTo::create(0.15f, pos[j][i]), NULL));
						blockStage[k2][i]->getPic()->runAction(
							Sequence::create(MoveTo::create(0.15f, pos[k2][i]), NULL));
						blockStage[k2][i]->getSpePic()->runAction(
							Sequence::create(MoveTo::create(0.15f, pos[j][i]), NULL));

						break;
					}
				}
			}
		}
	}

	//额外补齐
	int picNum;
	char picName[30];
	std::srand(time(NULL));
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (blockStage[i][j]->getName() == "null") {
				picNum = rand() % 6 + 1 + 6 * (UserDefault::getInstance()->getIntegerForKey("Skin") - 1);
				sprintf(picName, "block/llk%d.png", picNum);
				blockStage[i][j]->setName(picName);
				blockStage[i][j]->resetPic(picName, spos[j]);

				blockStage[i][j]->getPic()->runAction(
					Sequence::create(MoveTo::create(0.15f, pos[i][j]), NULL));
				blockStage[i][j]->getSpePic()->runAction(
					Sequence::create(MoveTo::create(0.15f, pos[i][j]), NULL));

				auto menu = Menu::create(blockStage[i][j]->getPic(), NULL);
				menu->setPosition(Point::ZERO);
				this->addChild(menu, 1);
				this->addChild(blockStage[i][j]->getSpePic(), 1);
			}
		}
	}
}

bool ATypeGameScene::clearAble(const int x1, const int y1)
{
	int count = 1;
	if (x1 + 1 < 8 && blockStage[x1][y1]->getName() == blockStage[x1 + 1][y1]->getName()) {
		count = count + 1;
		if (x1 + 2 < 8 && blockStage[x1][y1]->getName() == blockStage[x1 + 2][y1]->getName())
			count = count + 1;
	}
	if (x1 - 1 >= 0 && blockStage[x1][y1]->getName() == blockStage[x1 - 1][y1]->getName()) {
		count = count + 1;
		if (x1 - 2 >= 0 && blockStage[x1][y1]->getName() == blockStage[x1 - 2][y1]->getName())
			count = count + 1;
	}

	if (count >= 3)
		return true;
	else {
		count = 1;
		if (y1 + 1 < 8 && blockStage[x1][y1]->getName() == blockStage[x1][y1 + 1]->getName()) {
			count = count + 1;
			if (y1 + 2 < 8 && blockStage[x1][y1]->getName() == blockStage[x1][y1 + 2]->getName())
				count = count + 1;
		}
		if (y1 - 1 >= 0 && blockStage[x1][y1]->getName() == blockStage[x1][y1 - 1]->getName()) {
			count = count + 1;
			if (y1 - 2 >= 0 && blockStage[x1][y1]->getName() == blockStage[x1][y1 - 2]->getName())
				count = count + 1;
		}
		if (count >= 3)
			return true;
		else
			return false;
	}
}

void ATypeGameScene::choseEffect(const int x2, const int y2)
{
	if (UserDefault::getInstance()->getIntegerForKey("Skin") == 1) {
		auto effectID = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("audio/Effect/melt.mp3");
	}
	else if (UserDefault::getInstance()->getIntegerForKey("Skin") == 2) {
		auto effectID = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("audio/Effect/skin2.mp3");
	}
	else {
		if (blockStage[x2][y2]->getName() == "block/llk13.png")
			auto effectID = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("audio/Effect/skin3mihotel.mp3");
		else if (blockStage[x2][y2]->getName() == "block/llk14.png")
			auto effectID = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("audio/Effect/skin3kuzao.mp3");
		else if (blockStage[x2][y2]->getName() == "block/llk15.png")
			auto effectID = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("audio/Effect/skin3cesuo.mp3");
		else if (blockStage[x2][y2]->getName() == "block/llk16.png")
			auto effectID = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("audio/Effect/skin3aoligei.mp3");
		else if (blockStage[x2][y2]->getName() == "block/llk17.png")
			auto effectID = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("audio/Effect/skin3giao.mp3");
		else if (blockStage[x2][y2]->getName() == "block/llk18.png")
			auto effectID = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("audio/Effect/skin3ZBC.mp3");
		else
			auto effectID = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("audio/Effect/melt.mp3");
	}
}

void ATypeGameScene::explode(float dt)
{
	if (step > 0 && goal <= 0) {
		std::srand(time(NULL));
		int x = rand() % 8;
		int y = rand() % 8;
		
		this->unschedule(schedule_selector(ATypeGameScene::clearBlocks));

		blockStage[x][y]->setState(2);
		this->addChild(blockStage[x][y]->getSpePic(),1);

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (blockStage[i][j]->getState() == 2 || blockStage[i][j]->getState() == 3) {
					for (int k = 0; k < 8; k++) {
						blockStage[i][k]->getPic()->runAction(Sequence::create(ScaleTo::create(0.15f, 0.0f), NULL));
						blockStage[i][k]->getSpePic()->runAction(Sequence::create(ScaleTo::create(0.15f, 0.0f), NULL));
						choseEffect(i, k);
						blockStage[i][k]->setName("null");
						grade += pow(2, 9);
					}
					break;
				}
			}
		}

		/*for (int i = 0; i < 8; i++) {
			blockStage[x][i]->getPic()->runAction(Sequence::create(ScaleTo::create(0.15f, 0.0f), NULL));
			blockStage[x][i]->getSpePic()->runAction(Sequence::create(ScaleTo::create(0.15f, 0.0f), NULL));
			choseEffect(x, i);
			blockStage[x][i]->setName("null");
			grade += pow(2, 9);
		}*/

		fillFull();

		step = step - 1;

		char newGrade[20];
		if (grade >= 99999) {
			grade = 99999;
			sprintf(newGrade, "%d", grade);
			gradeLabel->setString(newGrade);
		}
		else {
			sprintf(newGrade, "%d", grade);
			gradeLabel->setString(newGrade);
		}

		char newStep[20];
		if (step == 0) {
			sprintf(newStep, "%d", step);
			stepLabel->setString(newStep);
			this->unscheduleUpdate();
		}
		else {
			sprintf(newStep, "%d", step);
			stepLabel->setString(newStep);
		}

		this->schedule(schedule_selector(ATypeGameScene::clearBlocks), 0.5f);
	}
}

void ATypeGameScene::endGame(float dt)
{
	//全部消除，步数没有剩余
	if (step <= 0 && goal <= 0) {
		this->unschedule(schedule_selector(ATypeGameScene::clearBlocks));
		int money = grade / 1000 + UserDefault::getInstance()->getIntegerForKey("Money");
		UserDefault::getInstance()->setIntegerForKey("Money", money);
		initEndLayer(1);
		this->unschedule(schedule_selector(ATypeGameScene::endGame));
	}
	//没有步数,还没有消除完
	if (step <= 0 && goal > 0) {
		initEndLayer(2);
		this->unschedule(schedule_selector(ATypeGameScene::endGame));
	}
}

void ATypeGameScene::initEndLayer(const int result)
{
	auto vSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto pNode = Layer::create();

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
	char resultName[30];
	sprintf(resultName, "pic/Result%d.png", result);
	auto menuBackground = Sprite::create(resultName);
	menuBackground->setPosition(origin.x + vSize.width / 2, origin.y + vSize.height / 2);
	pNode->addChild(menuBackground, 2);

	//返回按钮
	auto returnGameItem = MenuItemImage::create("pic/ReturnHomeNormal.png", "pic/ReturnHomeSelected.png",
		CC_CALLBACK_1(ATypeGameScene::returnCallBack, this));
	if (returnGameItem == nullptr || returnGameItem->getContentSize().width <= 0 || returnGameItem->getContentSize().height <= 0) {
		problemLoading("'ReturnHomeNormal.png' and 'ReturnHomeSelected.png'");
	}
	else {
		returnGameItem->setScale(1.2);
		const float x = origin.x + vSize.width * 0.37;
		const float y = origin.y + vSize.height * 0.355;
		returnGameItem->setPosition(Vec2(x, y));
	}

	//退出按钮
	auto closeItem = MenuItemImage::create("pic/CloseNormal2.png", "pic/CloseSelected2.png",
		CC_CALLBACK_1(ATypeGameScene::gameCloseCallback, this));
	if (closeItem == nullptr || closeItem->getContentSize().width <= 0 || closeItem->getContentSize().height <= 0) {
		problemLoading("'CloseNormal2.png' and 'CloseSelected2.png'");
	}
	else {
		closeItem->setScale(1.2);
		const float x = origin.x + vSize.width * 0.63;
		const float y = origin.y + vSize.height * 0.355;
		closeItem->setPosition(Vec2(x, y));
	}

	//二级菜单
	auto moveMenu = Menu::create(returnGameItem, closeItem, NULL);
	moveMenu->setPosition(Vec2::ZERO);
	pNode->addChild(moveMenu, 3);

	this->addChild(pNode, 5);
}