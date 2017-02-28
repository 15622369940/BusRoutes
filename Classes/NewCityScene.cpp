#include "cocostudio/CocoStudio.h"

#include "NewCityScene.h"
#include "GuideLayerScene.h"
#include "CreateLineLayer.h"
#include "CreateNodeLayer.h"

#include "City.h"
#include "Guide.h"

Scene* NewCityScene::createScene()
{
	auto scene = Scene::create();
	auto layer = NewCityScene::create();
	scene->addChild(layer);
	return scene;
}

bool NewCityScene::init()
{

	if (!Layer::init())
		return false;

	touchable = true;
	City::Instance()->reset();

	rootNode = CSLoader::createNode("NewCityLayer.csb");
	addChild(rootNode);

	if (!nodeProcess() || !eventDispatch())
		exit(EXIT_FAILURE);

	return true;
}

bool NewCityScene::nodeProcess() {
	if (rootNode == nullptr)
		return false;

	sprite1 = (Sprite*)rootNode->getChildByName("new_node");
	if (sprite1 == nullptr) {
		return false;
	}

	sprite2 = (Sprite*)rootNode->getChildByName("new_completed");
	if (sprite2 == nullptr) {
		return false;
	}

	back_line = (Sprite*)rootNode->getChildByName("new_line_back");
	if (back_line == nullptr) {
		return false;
	}

	return true;
}

bool NewCityScene::eventDispatch() {
	auto new_city_listener = EventListenerTouchOneByOne::create();
	new_city_listener->onTouchBegan = [this](Touch* t, Event* e)
	{
		if (!touchable)
			return false;
		if (e->getCurrentTarget()->getBoundingBox().containsPoint(t->getLocation()))
		{
			if (e->getCurrentTarget()->getName() == sprite1->getName())
			{
				touchable = false;
				if (back_line->isVisible()) 
				{
					/*
					new line information edit
					and let the new line layer change the background by controling back_line
					*/
					auto new_line = CreateLine::create();
					addChild(new_line);
				}
				else
				{
					/*
					new node information edit
					*/
					auto new_node = CreateNode::create();
					addChild(new_node);
				}
			}
			else if (e->getCurrentTarget()->getName() == sprite2->getName())
			{
				if (!back_line->isVisible())
				{
					back_line->setVisible(true);
				}
				else
					Director::getInstance()->replaceScene(GuideLayerScene::createScene());
			}
		}
		return false;
	};
	Director::getInstance()->getEventDispatcher()
		->addEventListenerWithSceneGraphPriority(new_city_listener, sprite1);
	Director::getInstance()->getEventDispatcher()
		->addEventListenerWithSceneGraphPriority(new_city_listener->clone(), sprite2);
	return true;
}
