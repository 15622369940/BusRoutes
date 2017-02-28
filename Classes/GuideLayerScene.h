#pragma once

#include "cocos2d.h"
#include "Guide.h"
#include "CityMap.h"
#include "ui\UITextField.h"
#include "ui\UIListView.h"
#include "ui\UISlider.h"

USING_NS_CC;
using namespace ui;
using namespace std;

class GuideLayerScene : public cocos2d::Layer
{
private:
	EventListenerTouchOneByOne* list_line_info_listener;
	Guide *_guide;
public:
	bool touchable = true;
	bool click;
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GuideLayerScene);

	bool nodeProcess();
	bool eventDispatch();
	string guide(string start,string end,bool isFast,bool isWait);
	void sliderCallback(cocos2d::Ref * ref, cocos2d::ui::Slider::EventType type);

	Sprite *button_return, *button_guide;
	Node *guideLayer;
	CityMap *cityLayer;
	ListView* background;
	Slider* slider;
	ListView* list;
	bool is_guiding;
};

