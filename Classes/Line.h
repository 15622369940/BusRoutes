#pragma once

#include <vector>
#include <cocos2d.h>

USING_NS_CC;
using namespace std;

class Line {
private :
	const int number;
	const int speed;
	const int blanking;
	const int cost;
	vector<string>* nodeList;

public :
	Line(int _number, int _speed, int _blanking, int _cost) :number(_number), speed(_speed),blanking(_blanking), cost(_cost){
		nodeList = new vector<string>();
	}

	void addNode(string name) {
		nodeList->push_back(name);
	}

	int getNumber() {
		return number;
	}

	int getSpeed() {
		return speed;
	}

	int getBlanking() {
		return blanking;
	}

	int getCost() {
		return cost;
	}

	vector<string>* getNodes() {
		return nodeList;
	}
};