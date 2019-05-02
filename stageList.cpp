#include "stageList.h"

stageList::stageList()
{
	//load text file of stage filenames
	loadFile();

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