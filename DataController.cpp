#include "pch.h"
#include "DataController.h"
#include "CNewDlg.h"


void DataController::loadListFromFile()
{
	ifstream data("ANSIData.csv");
	
	string line;
		
	if(list.size()!=0)
	{
		return;
	}

	while (getline(data, line))
	{
		stringstream linestream(line);
		string cell[COLUMN_NUMBER];
		for (int j = 0; j < COLUMN_NUMBER; j++)
		{
			getline(linestream, cell[j], ',');
		}
		list.push_back(new Data(cell[0], cell[1], &cell[2]));
	}
}

vector<Data*>& DataController::getList()
{
	return this->list;
}


vector<Data> DataController::searchList(CString keyword)
{
	
	int chk = 0;
	vector<Data> searchedRows;

	for (int i = 0; i < list.size(); i++)
	{
		if (keyword.Compare(list.at(i)->GetSiDo()) == 0)
		{
			chk++;
			searchedRows.push_back(*list.at(i));
		}
	}

	if (chk == 0)
	{
		for (int i = 0; i < list.size(); i++)
		{
			if (keyword.Compare(list.at(i)->GetSiGunGoo()) == 0)
			{
				searchedRows.push_back(*list.at(i));
			}
		}
	}
	return searchedRows;
}