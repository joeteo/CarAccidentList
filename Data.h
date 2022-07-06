#pragma once
#include <CString>
#include <string>

using namespace std;

#define COLUMN_NUMBER 13
#define LOCATION_NUMBER 11

class Data
{
private:
	CString siDo;
	CString siGunGoo;
	int accidentCount[LOCATION_NUMBER];

public:
	Data() {};
	Data(string _siDo, string _siGunGoo, string* _accidentCount);

	CString& GetSiDo();
	CString& GetSiGunGoo();
	int GetAccidentCount(int idx);

};
