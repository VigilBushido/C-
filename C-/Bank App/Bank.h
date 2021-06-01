#pragma once // This is version 1.1 // 
#include "ListOfCustomers.h"
#include "ListOfAccounts.h"

class Bank
{
public:
	string getCustomerList()
	{
		return listOfCus.getList();
	}
	string addCustomer(string name, string phoneNum)
	{
		return listOfCus.add(name, phoneNum);
	}
	string makeCustomerInactive(int key)
	{
		 return listOfCus.makeInactive(key);
	}
	string reactivateAllCustomers()
	{
		return listOfCus.reactivateAll();
	}
	string clearCustomers()
	{
		return listOfCus.clear();
	}
	string addRandCus(int count)
	{
		listOfCus.addRand(count);
		return intToString(count) + " random customers added.";
	}

	// Association Functions

	string associateCustomerWithAccount(int cusID, int actID)
	{
		bool aValid = listOfAct.isIDUsed(actID);
		bool cValid = listOfCus.isIDUsed(cusID);

		if (!aValid && !cValid) throw (string)"Error: Customer ID and AccountID are invalid.";
		else if (!aValid) throw (string)"Error: AccountID is invalid.";
		else if (!cValid) throw (string)"Error: CustomerID is invalid.";

		_ASSERT(cValid);
		_ASSERT(aValid);

		 listOfCus.associate_cus_with_act(cusID, actID);
// other half 
		 listOfAct.associate_act_with_cus(cusID, actID);
		 return "Association Made";
	}

	string unassociateCustomerWithAccount(int cusID, int actID)
	{
		listOfCus.unassociate(cusID, actID);
		listOfAct.unassociate(cusID, actID);

		return "UnAssociation Made";
	}

	// new functions for listOfAct

	string getAccountList()
	{
		return listOfAct.getList();
	}
	string addAccount(int balance, string accountType)
	{
		return listOfAct.add(balance, accountType);
	}
	string makeAccountInactive(int key)
	{
		return listOfAct.makeInactive(key);
	}
	string reactivateAllAccounts()
	{
		return listOfAct.reactivateAll();
	}
	string addRandAct(int count)
	{
		//Add functionality for ballance totals 
		//vector <int> randIDs = listOfCus.getRandomIDS(count);
		/*listOfAct.addRand(count, randIDs);*/
		listOfAct.addRand(count);
		return intToString(count) + " random accounts added.";
	}
	string clearAccounts()
	{
		return listOfAct.clear();
	}


private:
	ListOfCustomers listOfCus;
	ListOfAccounts listOfAct;
};
