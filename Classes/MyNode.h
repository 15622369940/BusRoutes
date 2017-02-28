#pragma once

#include <string>
#include <vector>

using namespace std;


	class MyNode {
	private:
		string name;
		int x, y;
		vector<int>* lines;

	public:
		MyNode(string name, int x, int y) {
			this->name = name;
			this->x = x;
			this->y = y;
			lines = new vector<int>();
		}

		bool addLine(int line) {
			for (unsigned int i = 0; i < lines->size(); i++)
				if (lines->at(i) == line)
					return false;
			lines->push_back(line);
			return true;
		}

		vector<int>* getLines() {
			return lines;
		}

		string getName() {
			return name;
		}

		int getX() {
			return x;
		}

		int getY() {
			return y;
		}

	};

	class NodeTree {
	public:
		MyNode* node;
		NodeTree* leftChild;
		NodeTree* rightChild;
		NodeTree() {
			node = nullptr;
			leftChild = nullptr;
			rightChild = nullptr;
		}
	};


