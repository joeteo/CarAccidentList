#include "pch.h"
#include "Data.h"

Data::Data(string _siDo, string _siGunGoo, string* _accidentCount)
	:siDo(_siDo.c_str()), siGunGoo(_siGunGoo.c_str())
{
	

	for (int i = 0; i < LOCATION_NUMBER; i++)
	{
		if (*(_accidentCount + i) == "-")
		{
			accidentCount[i] = 0;
		}
		else
		{
			accidentCount[i] = stoi(*(_accidentCount + i));
		}
	}
}

CString& Data::GetSiDo()
{
	return siDo;
}

CString& Data::GetSiGunGoo()
{
	return siGunGoo;
}

int Data::GetAccidentCount(int idx)
{
	return accidentCount[idx];
}