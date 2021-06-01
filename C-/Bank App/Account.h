#pragma once // This is version 1.1 // 
#include "misc.h"

using namespace std;



class Account
{
	friend class ListOfAccounts;
public:
	Account(int n, string p)
	{
		balance = n;
		accountType = p;
		getNewID();
		isActive = true;
	}
	Account(int id, int n, string p, bool ia)
	{
		balance = n;
		accountType = p;
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

	// Add class functions here similar to Customer.h

private:

	bool isActive;
	int balance;  // kept as the number of pennies in the account
	int idNumber;
	string accountType;  // "Checking" or "Saving"
	vector<int> customerIDs;
};
