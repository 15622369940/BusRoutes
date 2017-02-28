#include "GuideLayerScene.h"
#include "cocostudio/CocoStudio.h"
#include "HelloWorldScene.h"
#include "GuideConfirmLayer.h"
#include "City.h"
#include "LineInfoLayer.h"

Scene* GuideLayerScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GuideLayerScene::create();
	scene->addChild(layer);
	return scene;
}

bool GuideLayerScene::init()
{

	if (!Layer::init())
		return false;

	_guide = new Guide(City::Instance());
	_guide->preprocess();

	is_guiding = false;
	click = true;

	cityLayer = CityMap::create();

	guideLayer = CSLoader::createNode("GuideLayer.csb");
	if (guideLayer == nullptr)
		return false;
	addChild(guideLayer);

	list_line_info_listener = EventListenerTouchOneByOne::create();
	list_line_info_listener->onTouchBegan = [this](Touch* t,Event* e) 
	{
		if (!touchable)
			return false;
		
		auto target = (LabelTTF*)e->getCurrentTarget();
		if (target == nullptr)
			return false;
		if (target->getBoundingBox().containsPoint(
			Point(t->getLocation().x - list->getPositionX(),t->getLocation().y - list->getPositionY() + list->getContentSize().height)))
		{
			click = true;
			return true;
		}
		return false;
	};
	list_line_info_listener->onTouchMoved = [this](Touch* t,Event* e)
	{
		float y = t->getLocation().y - t->getStartLocation().y;
		if(abs(y) > 30)
			click = false;
	};
	list_line_info_listener->onTouchEnded = [this](Touch* t, Event* e)
	{
		if (click)
		{
			auto line = City::Instance()->getLine(Value(((LabelTTF*)e->getCurrentTarget())->getName()).asInt());
			touchable = false;
			auto line_info = LineInfoLayer::create(line);
			addChild(line_info);
		}
		click = false;
	};

	if (!nodeProcess() || !eventDispatch())
		exit(EXIT_FAILURE);

	return true;
}

bool GuideLayerScene::nodeProcess() {
	if (cityLayer == nullptr ||guideLayer == nullptr)
		return false;
	cityLayer->setAnchorPoint(Point(0,0));

	button_return = (Sprite*)guideLayer->getChildByName("mask_button_return");
	if (button_return == nullptr) {
		return false;
	}

	button_guide = (Sprite*)guideLayer->getChildByName("mask_button_guide");
	if (button_guide == nullptr) {
		return false;
	}

	background = (ListView*)guideLayer->getChildByName("background");
	if (background == nullptr)
		return false;
	background->setPassFocusToChild(true);
	background->addChild(cityLayer,-1);

	slider = (Slider*)guideLayer->getChildByName("scale_slider");
	if (slider == nullptr)
		return false;
	float scale = (SCALE_MAX - SCALE_MIN) * (slider->getPercent() / 100.0f) + SCALE_MIN;
	cityLayer->setScale(scale);
	background->setInnerContainerSize(cityLayer->getContentSize()*scale);

	list = (ListView*)guideLayer->getChildByName("scroll_view");
	if (list == nullptr)
		return false;
	Size list_size = list->getContentSize();
	if (!City::Instance()->isEmpty())
	{
		auto list_native = cityLayer->getList();
		list->setInnerContainerSize(Size(list->getContentSize().width,
			list_native.size() * (2 * list_native.at(0)->getContentSize().height / 3)));
		for (int i = 0; i < list_native.size(); i++)
		{
			LabelTTF* child;
			child = (LabelTTF*)list_native.at(i);
			child->setName(child->getString());

			string process = "";
			process += "--";
			process += child->getString();
			process += "--";
			child->setString(process);

			child->setAnchorPoint(Point(0.5f, 1.0f));
			child->setPosition(list_size.width / 2, list_size.height - i  * child->getContentSize().height);
			Director::getInstance()->getEventDispatcher()
				->addEventListenerWithSceneGraphPriority(list_line_info_listener->clone(), child);
			list->addChild(child, i);
		}
	}	

	return true;
}

bool GuideLayerScene::eventDispatch() {
	
	slider->addEventListener(CC_CALLBACK_2(GuideLayerScene::sliderCallback, this));

	auto guide_listener = EventListenerTouchOneByOne::create();
	guide_listener->onTouchBegan = [this](Touch* t, Event* e)
	{
		if (!touchable)
			return false;
		if (e->getCurrentTarget()->getBoundingBox().containsPoint(t->getLocation()))
		{
			if (e->getCurrentTarget()->getName() == button_return->getName())
			{

				if (is_guiding)
				{
					is_guiding = false;
					cityLayer->clearDrawGuide();
				}
				else
					Director::getInstance()->replaceScene(HelloWorld::createScene());
			}
			else if (e->getCurrentTarget()->getName() == button_guide->getName())
			{
				/*
				new guide layer added
				*/
				is_guiding = false;
				cityLayer->clearDrawGuide();
				touchable = false;
				auto layer = GuideConfirm::create();
				addChild(layer);
			}
		}
		return false;
	};
	Director::getInstance()->getEventDispatcher()
		->addEventListenerWithSceneGraphPriority(guide_listener, button_return);
	Director::getInstance()->getEventDispatcher()
		->addEventListenerWithSceneGraphPriority(guide_listener->clone(), button_guide);

	return true;
}

void GuideLayerScene::sliderCallback(cocos2d::Ref * ref, Slider::EventType type)
{
	switch (type)
	{
	case cocos2d::ui::Slider::EventType::ON_PERCENTAGE_CHANGED:
	{
		float scale = (SCALE_MAX - SCALE_MIN) * (slider->getPercent() / 100.0f) + SCALE_MIN;
		cityLayer->setScale(scale);
		background->setInnerContainerSize(cityLayer->getContentSize()*scale);
	}
	break;
	default:
		break;
	}
}

string GuideLayerScene::guide(string start, string end, bool isFast, bool isWait)
{
	string way;
	if (isFast)
		way = _guide->fast(start, end, isWait);	
	else
		way = _guide->cheap(start, end);
		
	if (way == "")
		way = "不存在指定路线，请检查您的输入";
	else
		cityLayer->drawGuide(_guide->getGuideSequence());
	//MessageBox(way.c_str(),"guide");
	
	return way;
}

