#pragma once // This is version 1.1 // 
#include <vector> 
#include <map>
//#include <hash_map>
//#include <unordered_map>
#include "Customer.h"
#include <fstream>
#include "misc.h"
#include <algorithm>

using namespace std;


class ListOfCustomers
{
public:
	ListOfCustomers()
	{
		ifstream inFile("locData.txt");	
		if (inFile.fail()) return;
		while (!inFile.eof())
		{
			string data;
			getline(inFile, data);
			vector<string> field = tokenize(data);
			if (field.size() != 0)
			{
				bool act = false;
				if (field[3] == "1")act = true;
				Customer readCus(stringToInt(field[0]), field[1], field[2], act);
				for (unsigned int i = 4; i < field.size(); i++)
				{
					readCus.accountIDs.push_back(stringToInt(field[i]));
				}
				vCustomer.push_back(readCus);
				indexByID[readCus.idNumber] = vCustomer.size() - 1;
			}
		}
		inFile.close();
	}

	~ListOfCustomers()
	{
		ofstream outFile("locData.txt");
		for each (Customer c in vCustomer)
		{
			outFile << c.idNumber << " ";
			outFile << c.name + ";";
			outFile << c.phoneNumber + ";";
			outFile << c.isActive ;
			for each(int ai in c.accountIDs)
			{
				outFile << ";" << ai;
			}
			outFile << "\n";
		}
		outFile.close();
	}
	//vector <int> getRandIDs(int howMany)
	//{
	//	vector<int> result;
	//	for (int i = 0; i < howMany; i++)
	//	{
	//		int randIndex = randomInt(0, vCustomer.size() - 1);
	//		int randID = vCustomer[randIndex]idNumber;
	//		result.push_back(randID);
	//		return result;
	//	}
	//}
	// unassociate
	void unassociate(int cID, int aID)
	{
		Customer & c = getCusByID(cID);
		vector<int> & vi = c.accountIDs;

		vector<int>::iterator found;
		found = find(vi.begin(), vi.end(), aID);
		if (found == vi.end()) throw (string) "They were not currently associated.";
		vi.erase(found);
	}

	void addRand(int count)
	{
		for (int i = 0; i < count; i++)
		{
			add(randString(10), randNumberString(10));
		}
	}

	string add(string name, string phoneNum)
	{
		Customer nuCus(name, phoneNum);
		while (isIDUsed(nuCus.idNumber))
		{
			nuCus.getNewID();
		}

		vCustomer.push_back(nuCus);
		indexByID[nuCus.idNumber] = vCustomer.size() - 1;
		return "Customer " + nuCus.getIDstring() + " was added.";
	}
	string reactivateAll()
	{
		for (unsigned int i = 0; i < vCustomer.size(); i++)
		{
			vCustomer[i].isActive = true;
		}
		return "All customers are now reactivated.";
	}

	//string getList()
	//{
	//	string result;

	//	for each (Customer c in vCustomer)
	//	{
	//		result += c.name + "   ";
	//		result += c.phoneNumber + "   ";
	//		result += c.getIDstring() + "\n";
	//	}
	//	return result;
	//}

	string getList()
	{
		string result;

		result = getListHeader();

		for each (Customer c in vCustomer)
		{
			if (c.isActive)
			{
				result += padRight(c.name, ' ', 25) + " ";
				result += padRight(c.phoneNumber, ' ', 16) + " ";
				result += padLeft(c.getIDstring(), ' ', 9) + "\n";

				for each(int ai in c.accountIDs)
				{
					result += "\t" + intToString(ai) + "\n";
				}
			}
		}
		return result;
	}

	string makeInactive(int key)
	{
		getCusByID(key).isActive = false;
		return "Customer is now inactive.";
	}
	// Association
	void associate_cus_with_act(int cusID, int actID)
	{
		getCusByID(cusID).accountIDs.push_back(actID);
	}

#define FASTGET

	Customer & getCusByID(int key)
	{
#ifndef FASTGET
		for (unsigned int i = 0; i < vCustomer.size(); i++)
		{
			if (vCustomer[i].isActive)
			{
				if (key == vCustomer[i].idNumber) return vCustomer[i];
			}
		}
		throw "Invalid or Inactive ID:" + intToString(key);
#else
		map<int, int>::iterator fIter = indexByID.find(key);
		if(fIter==indexByID.end()) throw "Error: Invalid ID# " + intToString(key);
		return vCustomer[(*fIter).second];
#endif
	}

	bool isIDUsed(int key)
	{
#ifndef FASTGET
		for (unsigned int i = 0; i < vCustomer.size(); i++)
		{
			if (key == vCustomer[i].idNumber) return true;
		}
		return false;
#else
		map<int, int>::iterator fIter = indexByID.find(key);
		if (fIter == indexByID.end()) return false;
		return true;
#endif
	}
	string clear()
	{
		vCustomer.clear();
		return "All customers in list have been removed.";
	}

private:

	string getListHeader()
	{
		string result;
		result += padRight("Name", ' ', 25) + " ";
		result += padRight("PhoneNumber", ' ', 16) + " ";
		result += padRight("ID#", ' ', 9) + "\n";
		result += padRight("", '_', 25) + " ";
		result += padRight("", '_', 16) + " ";
		result += padRight("", '_', 9) + "\n";
		return result;
	}


	vector<Customer> vCustomer;
	map<int, int> indexByID;
};