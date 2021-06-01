#include "Transducer.h" // This is version 1.1 // 
#include <vector>
#include "misc.h"
using namespace std;


string Transducer::transduce(string command)
{
	try
	{
		string result;
		vector<string> token = tokenize(command);

		if (token.size() == 0) return "";
		
		if ((token[0] == "Help") || (token[0] == "H"))
		{
			if (token.size() != 1) throw (string)"ERROR: Wrong number of parameters for this command.";
			result = "Commands:\n";
			result += "-------------------\n";
			result += "\tHelp(H)\n";
			result += "\tAddCustomer(AC) <name>;<phoneNumber>\n";
			result += "\tMakeCustomerInactive(MCI) <id#>\n";
			result += "\tShowCustomerList(SCL)\n";
			result += "\tReactivateAllCustomers(RAC)\n";
			result += "\tReactivateAllAccounts(RAA)\n";
			result += "\tClearCustomers(CC)\n";
			result += "\tClearAccounts(CA)\n";
			result += "\tAddRandCustomers(ARC) <count>\n";
			result += "\tAddAccount(AA) <InitialAmount>;<AccountType>\n";
			result += "\tMakeAccountInactive(MAI) <Account#>\n";
			result += "\tShowAccountList(SAL) <Account#>\n";
			result += "\tAddRandomAccounts(ARA) <count>\n";
			result += "\tAssociateCustomerAndAccount(ACAA) <Customer#;<Account#>\n";
			result += "\tUnassociateCustomerAndAccount(UCAA) <Customer#;<Account#>\n";
			result += "\tQuit(Q)\n";
			result += "-------------------\n";

		}
		else if ((token[0] == "Quit") || (token[0] == "Q"))
		{
			if (token.size() != 1) throw (string)"ERROR: Wrong number of parameters for this command.";
			result = "Goodbye.";
		}
		else if ((token[0] == "AddCustomer") || (token[0] == "AC"))
		{
			if (token.size() != 3) throw (string)"ERROR: Wrong number of parameters for this command.";
			result = bank.addCustomer(token[1], token[2]);
		}
		else if ((token[0] == "MakeCustomerInactive") || (token[0] == "MCI"))
		{
			if (token.size() != 2) throw (string)"ERROR: Wrong number of parameters for this command.";
			result = bank.makeCustomerInactive(stringToInt(token[1]));
		}
		else if ((token[0] == "ShowCustomerList") || (token[0] == "SCL"))
		{
			if (token.size() != 1) throw (string)"ERROR: Wrong number of parameters for this command.";
			result = bank.getCustomerList();
		}
		else if ((token[0] == "ReactivateAllCustomers") || (token[0] == "RAC"))
		{
			if (token.size() != 1) throw (string)"ERROR: Wrong number of parameters for this command.";
			result = bank.reactivateAllCustomers();
		}
		else if ((token[0] == "ClearCustomers") || (token[0] == "CC"))
		{
			if (token.size() != 1) throw (string)"ERROR: Wrong number of parameters for this command.";
			result = bank.clearCustomers();
		}
		else if ((token[0] == "ClearAccounts") || (token[0] == "CA"))
		{
			if (token.size() != 1) throw (string)"ERROR: Wrong number of parameters for this command.";
			result = bank.clearAccounts();
		}
		else if ((token[0] == "AddRandCustomers") || (token[0] == "ARC"))
		{
			if (token.size() != 2) throw (string)"ERROR: Wrong number of parameters for this command.";
			result = bank.addRandCus(stringToInt(token[1]));
		}// the new commands below
		else if ((token[0] == "AddAccount") || (token[0] == "AA")) // Done
			{
				if (token.size() != 3) throw (string)"ERROR: Wrong number of parameters for this command.";
				result = bank.addAccount(stringToInt(token[1]), token[2]);
		}
		else if ((token[0] == "MakeAccountInactive") || (token[0] == "MAI")) // Done
		{
			if (token.size() != 2) throw (string)"ERROR: Wrong number of parameters for this command.";
			result = bank.makeAccountInactive(stringToInt(token[1])); 
		}
		else if ((token[0] == "ReactivateAllAccounts") || (token[0] == "RAA")) // Done
		{
			if (token.size() != 1) throw (string)"ERROR: Wrong number of parameters for this command.";
			result = bank.reactivateAllAccounts();
		}
		else if ((token[0] == "ShowAccountList") || (token[0] == "SAL")) // Done
		{
			if (token.size() != 1) throw (string)"ERROR: Wrong number of parameters for this command.";
			result = bank.getAccountList();
		}
		else if ((token[0] == "AddRandAccounts") || (token[0] == "ARA")) // Done
		{
			if (token.size() != 2) throw (string)"ERROR: Wrong number of parameters for this command.";
			result = bank.addRandAct(stringToInt(token[1]));
		}
		else if ((token[0] == " AssociateCustomerAndAccount") || (token[0] == "ACAA")) // Done
		{
			if (token.size() != 3) throw (string)"ERROR: Wrong number of parameters for this command.";
			result = bank.associateCustomerWithAccount(stringToInt(token[1]), stringToInt(token[2]));
		}
		else if ((token[0] == " UnAssociateCustomerAndAccount") || (token[0] == "UCAA")) // Done
		{
			if (token.size() != 3) throw (string)"ERROR: Wrong number of parameters for this command.";
			result = bank.unassociateCustomerWithAccount(stringToInt(token[1]), stringToInt(token[2]));
		}
		else
		{
			 throw (string)"ERROR: Unrecognized Command.";
		}
		return result;
	}



	catch (string s)
	{
		if (s == "FATAL ERROR") exit(999);
		return s;
	}
	catch (char * s)
	{
		if ((string)s == "FATAL ERROR") exit(999);
		return (string)s;
	}
	catch (...)
	{
		return "Something went wrong but I don't know what!";
	}
}



