#pragma once

#include"Data.h"
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

class DataController
{

private:
	vector<Data*> list;

public:
	void loadListFromFile();
	vector<Data*>& getList();
	vector<Data> searchList(CString keyword);

};

