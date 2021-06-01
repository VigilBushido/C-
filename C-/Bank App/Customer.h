#pragma once // This is version 1.1 // 
#include "misc.h" 




class Customer
{
	friend class ListOfCustomers;
public:
	Customer(string n, string p)
	{
		name = n;
		phoneNumber = p;
		getNewID();
		isActive = true;
	}
	Customer(int id,string n, string p,bool ia)
	{
		name = n;
		phoneNumber = p;
		idNumber = id;
		isActive = ia;
	}

	void getNewID()
	{
		idNumber = randomInt(100000000, 900000000);
	}


	string getIDstring()
	{
		return intToString(idNumber);
	}
private:
	string name;
	string phoneNumber;
	int idNumber;
	bool isActive;
	vector<int> accountIDs;
};