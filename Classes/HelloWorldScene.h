#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

using namespace std;

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HelloWorld);

	void fastEditCity();

	bool nodeProcess();
	bool eventDispatch();

	Sprite *sprite1,*sprite2,*sprite3;
	Node* rootNode;

};

#endif // __HELLOWORLD_SCENE_H__
