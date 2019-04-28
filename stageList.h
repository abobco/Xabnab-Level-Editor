#pragma once
#include <fstream>
#include <vector>
#include <string>
#include "menuButton.h"
#include "LTexture.h"

#ifndef __STAGELIST_H__
#define __STAGELIST_H__

using namespace std;
class stageList
{
private:
	ifstream listIF;
	ofstream listOF;
	
private:


public:
	stageList();
	vector<string> vStages;
	vector<menuButton> vButtons;
	void loadFile();
	void newStage(string filename);
	void removeItem(int index);
	LTexture textTexture;
};

#endif
