#include "stageList.h"

stageList::stageList()
{
	//load text file of stage filenames
	loadFile();
	
	//make a set of buttons for each stage
	for (int i = 0; i < vStages.size(); i++)
	{
		vButtons.push_back(menuButton(300, 100 + 100 * i));
	}
	//make a scroll bar

}

void stageList::loadFile()
{
	listIF.open("stages/stageList.txt");
	string currStage;
	while (getline(listIF, currStage))
	{
		vStages.push_back(currStage);
	}
	listIF.close();
}
void stageList::newStage(string filename)
{
	vStages.push_back(filename);
	listOF.open(filename, ios_base::app);
	listOF << filename << endl;
	listOF.close();
}
void stageList::removeItem(int index)
{
	vStages.erase(vStages.begin() + index);
}