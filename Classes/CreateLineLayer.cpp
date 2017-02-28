#include "CreateLineLayer.h"
#include "cocostudio/CocoStudio.h"
#include "HelloWorldScene.h"
#include "NewCityScene.h"

#include "City.h"

bool CreateLine::init()
{

	if (!Layer::init())
		return false;

	rootNode = CSLoader::createNode("NewLineLayer.csb");
	addChild(rootNode);

	save = new TextField*[4];

	if (!nodeProcess() || !eventDispatch())
		exit(EXIT_FAILURE);

	return true;
}

bool CreateLine::nodeProcess() {
	if (rootNode == nullptr)
		return false;

	confirm = (Sprite*)rootNode->getChildByName("button_confirm");
	if (confirm == nullptr) {
		return false;
	}

	cancel = (Sprite*)rootNode->getChildByName("button_cancel");
	if (cancel == nullptr) {
		return false;
	}

	if (textFieldProcess(0,"bus_number") && textFieldProcess(1,"bus_speed")
		&& textFieldProcess(2,"bus_blanking") && textFieldProcess(3,"bus_cost"));
	else
		return false;

	return true;
}

bool CreateLine::textFieldProcess(int th,const string name) {

	save[th] = (TextField*)rootNode->getChildByName(name);
	if (save[th] == nullptr)
		return false;
	save[th]->setInsertText(true);
	save[th]->setDeleteBackward(true);
	save[th]->setAttachWithIME(true);

	return true;
}

bool CreateLine::eventDispatch() {
	auto save_listener = EventListenerTouchOneByOne::create();
	save_listener->onTouchBegan = [this](Touch* t, Event* e)
	{
		
		if (e->getCurrentTarget()->getBoundingBox().containsPoint(t->getLocation()))
		{
			if (e->getCurrentTarget()->getName() == confirm->getName())
			{
				int number,cost,speed,blanking;
				number = Value(save[0]->getString()).asInt();
				speed = Value(save[1]->getString()).asInt();
				blanking = Value(save[2]->getString()).asInt();
				cost = Value(save[3]->getString()).asInt();
				City::Instance()->addLine(number,speed,blanking,cost);

				((NewCityScene*)getParent())->touchable = true;
				((NewCityScene*)getParent())->back_line->setVisible(false);
				this->removeFromParentAndCleanup(true);
			}
			else if (e->getCurrentTarget()->getName() == cancel->getName())
			{
				((NewCityScene*)getParent())->touchable = true;
				((NewCityScene*)getParent())->back_line->setVisible(true);
				this->removeFromParentAndCleanup(true);
			}
		}
		return false;
	};
	Director::getInstance()->getEventDispatcher()
		->addEventListenerWithSceneGraphPriority(save_listener, confirm);
	Director::getInstance()->getEventDispatcher()
		->addEventListenerWithSceneGraphPriority(save_listener->clone(), cancel);

	return true;
}

