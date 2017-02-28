#include "GuideConfirmLayer.h"
#include "cocostudio/CocoStudio.h"
#include "GuideLayerScene.h"

#include "Guide.h"

bool GuideConfirm::init()
{

	if (!Layer::init())
		return false;

	rootNode = CSLoader::createNode("GuideConfirmLayer.csb");
	addChild(rootNode);

	if (!nodeProcess() || !eventDispatch())
		exit(EXIT_FAILURE);

	return true;
}

bool GuideConfirm::nodeProcess() {
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

	start = (TextField*)rootNode->getChildByName("input_start");
	if (start == nullptr) {
		return false;
	}

	end = (TextField*)rootNode->getChildByName("input_end");
	if (end == nullptr) {
		return false;
	}

	mode_fast = (Sprite*)rootNode->getChildByName("choice_mode_fast");
	if (mode_fast == nullptr) {
		return false;
	}

	wait_yes = (Sprite*)rootNode->getChildByName("choice_wait_yes");
	if (wait_yes == nullptr) {
		return false;
	}

	return true;
}

bool GuideConfirm::eventDispatch() {
	auto guide_confirm_listener = EventListenerTouchOneByOne::create();
	guide_confirm_listener->onTouchBegan = [this](Touch* t, Event* e)
	{

		if (e->getCurrentTarget()->getBoundingBox().containsPoint(t->getLocation()))
		{
			if (e->getCurrentTarget()->getName() == confirm->getName())
			{
				string way = ((GuideLayerScene*)getParent())->guide(start->getString(),end->getString(),
					mode_fast->isVisible(),wait_yes->isVisible());
				speak(way.c_str());
				((GuideLayerScene*)getParent())->touchable = true;
				((GuideLayerScene*)getParent())->is_guiding = true;
				removeFromParentAndCleanup(true);
			}
			else if (e->getCurrentTarget()->getName() == cancel->getName())
			{
				((GuideLayerScene*)getParent())->touchable = true;
				((GuideLayerScene*)getParent())->is_guiding = false;
				removeFromParentAndCleanup(true);
			}
			else if (e->getCurrentTarget()->getName() == mode_fast->getName())
			{
				if (mode_fast->isVisible())
					mode_fast->setVisible(false);
				else
					mode_fast->setVisible(true);
			}
			else if (e->getCurrentTarget()->getName() == wait_yes->getName())
			{
				if (wait_yes->isVisible())
					wait_yes->setVisible(false);
				else
					wait_yes->setVisible(true);
			}
		}
		return false;
	};
	Director::getInstance()->getEventDispatcher()
		->addEventListenerWithSceneGraphPriority(guide_confirm_listener, confirm);
	Director::getInstance()->getEventDispatcher()
		->addEventListenerWithSceneGraphPriority(guide_confirm_listener->clone(), cancel);
	Director::getInstance()->getEventDispatcher()
		->addEventListenerWithSceneGraphPriority(guide_confirm_listener->clone(), mode_fast);
	Director::getInstance()->getEventDispatcher()
		->addEventListenerWithSceneGraphPriority(guide_confirm_listener->clone(), wait_yes);

	return true;
}

void GuideConfirm::speak(const char* words) {
	string out = GBKToUTF8(words);
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		MessageBox(words,"Guide");
		log(out.c_str());
	#endif
		
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台
		//GBK2UTF* trans = new GBK2UTF();
		//GBK* gbk = new GBK(words);

		JniMethodInfo say;

		bool isHave = JniHelper::getStaticMethodInfo(say, "org/cocos2dx/cpp/AppActivity", "speak", "(Ljava/lang/String;)V");
		if (!isHave) {
			log("not exist");
		}
		else {
			jstring js = say.env->NewStringUTF(GBKToUTF8(words).c_str());
			say.env->CallStaticVoidMethod(say.classID, say.methodID,js);
		}
	#endif
		
}


