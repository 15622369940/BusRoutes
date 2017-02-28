#include "CreateNodeLayer.h"
#include "cocostudio/CocoStudio.h"
#include "HelloWorldScene.h"
#include "NewCityScene.h"

#include "City.h"

bool CreateNode::init()
{

	if (!Layer::init())
		return false;

	rootNode = CSLoader::createNode("NewNodeLayer.csb");
	addChild(rootNode);

	save = new TextField*[3];

	if (!nodeProcess() || !eventDispatch())
		exit(EXIT_FAILURE);

	return true;
}

bool CreateNode::nodeProcess() {
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

	if (textFieldProcess(0,"node_name") && textFieldProcess(1,"node_name_x")
		&& textFieldProcess(2,"node_name_y") );
	else
		return false;

	return true;
}

bool CreateNode::textFieldProcess(int th,const string name) {

	save[th] = (TextField*)rootNode->getChildByName(name);
	if (save[th] == nullptr)
		return false;
	save[th]->setInsertText(true);
	save[th]->setDeleteBackward(true);
	save[th]->setAttachWithIME(true);

	return true;
}

bool CreateNode::eventDispatch() {
	auto save_listener = EventListenerTouchOneByOne::create();
	save_listener->onTouchBegan = [this](Touch* t, Event* e)
	{
		
		if (e->getCurrentTarget()->getBoundingBox().containsPoint(t->getLocation()))
		{
			if (e->getCurrentTarget()->getName() == confirm->getName())
			{
				int x, y;
				x = Value(save[1]->getString()).asInt();
				y = Value(save[2]->getString()).asInt();
				City::Instance()->addNode(save[1]->getString(),x,y);

				((NewCityScene*)getParent())->touchable = true;
				this->removeFromParentAndCleanup(true);
			}
			else if (e->getCurrentTarget()->getName() == cancel->getName())
			{
				((NewCityScene*)getParent())->touchable = true;
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

