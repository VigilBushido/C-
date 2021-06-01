#pragma once // This is version 1.1 //
#include <vector> 
#include <map>
//#include <hash_map>
//#include <unordered_map>
#include "Account.h"
#include <fstream>
#include "misc.h"

using namespace std;


class ListOfAccounts
{
public:
	ListOfAccounts()
	{
		ifstream inFile("loaData.txt");
		if (inFile.fail()) return;
		while (!inFile.eof())
		{
			string data;
			getline(inFile, data);
			vector<string> field = tokenize(data);
			if (field.size() != 0)
			{
				bool isAct = false;
				if (field[3] == "1")isAct = true;
				Account readAct(stringToInt(field[0]), stringToInt(field[1]), field[2], isAct);
				for (unsigned int i = 3; i < field.size(); i++)
				{
					readAct.customerIDs.push_back(stringToInt(field[i]));
				}
				vAccount.push_back(readAct);
				indexByID[readAct.idNumber] = vAccount.size() - 1;
			}
		}
		inFile.close();
	}

	~ListOfAccounts()
	{
		ofstream outFile("loaData.txt");
		for each (Account c in vAccount)
		{
			outFile << c.idNumber << " ";
			outFile << c.balance << ";";
			outFile << c.accountType << ";";
			outFile << c.isActive;
			for each(int ai in c.customerIDs)
			{
				outFile << ";" << ai;
			}
			outFile << "\n";
		}
		outFile.close();
	}
	// The Get Account List Part
	string getList()
	{
		string result;

		result = getListHeader();

		for each (Account c in vAccount)
		{
			if (c.isActive)
			{
				result += padRight(intToString(c.balance), ' ', 25) + " ";
				result += padRight(c.accountType, ' ', 16) + " ";
				result += padLeft(c.getIDstring(), ' ', 9) + "\n";
				for each(int ci in c.customerIDs)
				{
					result += "\t" + intToString(ci) + "\n";
				}
			}
		}
		return result;
	}

	// The Add Account Part
	string add(int balance, string accountType)
	{
		Account nuAct(balance, accountType);
		while (isIDUsed(nuAct.idNumber))
		{
			nuAct.getNewID();
		}

		vAccount.push_back(nuAct);
		indexByID[nuAct.idNumber] = vAccount.size() - 1;
		return "Account " + nuAct.getIDstring() + " was added.";
	}
	void unassociate(int cID, int aID)
	{
		Account & a = getActByID(cID);
		vector<int> & vi = a.customerIDs;

		vector<int>::iterator found;
		found = find(vi.begin(), vi.end(), aID);
		if (found == vi.end()) throw (string) "They were not currently associated.";
		vi.erase(found);
	}

	// Associate the Account with Customer
	void associate_act_with_cus(int cusID, int actID)
	{
		getActByID(actID).customerIDs.push_back(cusID);
	}
	// The isIDUsed check part
#define FASTGET

	Account & getActByID(int key)
	{
#ifndef FASTGET
		for (unsigned int i = 0; i < vAccount.size(); i++)
		{
			if (vAccount[i].isActive)
			{
				if (key == vAccount[i].idNumber) return vAccount[i];
			}
		}
		throw "Invalid or Inactive ID:" + intToString(key);
#else
		map<int, int>::iterator fIter = indexByID.find(key);
		if (fIter == indexByID.end()) throw "Error: Invalid ID# " + intToString(key);
		return vAccount[(*fIter).second];
#endif
	}

	bool isIDUsed(int key)
	{
#ifndef FASTGET
		for (unsigned int i = 0; i < vAccount.size(); i++)
		{
			if (key == vAccount[i].idNumber) return true;
		}
		return false;
#else
		map<int, int>::iterator fIter = indexByID.find(key);
		if (fIter == indexByID.end()) return false;
		return true;
#endif
	}
	// The end of isIDused FastGet Section

	// Make Account Inactive Part
	string makeInactive(int key)
	{
		getActByID(key).isActive = false;
		return "Account is now inactive.";
	}

	// Reactivate All Accounts
	string reactivateAll()
	{
		for (unsigned int i = 0; i < vAccount.size(); i++)
		{
			vAccount[i].isActive = true;
		}
		return "All accounts are now reactivated.";
	}

	// Add Random Accounts
	// change the random; to rutrn vector
	//vector<int> addRand(int count)
	//{
	//	for (int i = 0; i < count; i++)
	//	{
	//		string type = "Checking";
	//		if (randInt(1, 5) == 1)
	//		{
	//			type = "Saving";
	//		}
	//		string rv = add(randInt(1, 1000000), type);
	//		rv = rv.substr(8, 99999);

	//	}
	//}

	void addRand(int count)
	{
		for (int i = 0; i < count; i++)
		{
			string type = "Checking";
			if (randInt(1, 5) == 1)
			{
				type = "Saving";
			}
			add(randInt(1,1000000), type);
		}
	}

	// Clear All Accounts
	string clear()
	{
		vAccount.clear();
		return "All accounts in list have been removed.";
	}

private:

	string getListHeader()
	{
		string result;
		result += padRight("Balance", ' ', 25) + " ";
		result += padRight("AccountType", ' ', 16) + " ";
		result += padRight("ID#", ' ', 9) + "\n";
		result += padRight("", '_', 25) + " ";
		result += padRight("", '_', 16) + " ";
		result += padRight("", '_', 9) + "\n";
		return result;
	}


	vector<Account> vAccount;
	map<int, int> indexByID;

};