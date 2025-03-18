#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>
using namespace std;

class clsBankClient : public clsPerson
{
private:

	enum enMode{EmptyMode = 0, UpDateMode = 1};
	enMode _Mode;

	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;

	static clsBankClient _ConvertLinetoClientObject(string Line, string Seprator = "#//#")
	{
		vector<string> vClientData;
		vClientData = clsString::Split(Line, Seprator);
		return clsBankClient(enMode::UpDateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
	}
	static clsBankClient _GetEmptyObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}
public:
	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, float AccountBalnace) :
		clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;

		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalnace;
	}
	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}
	//read only
	string AccountNumber()
	{
		return _AccountNumber;
	}
	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}
	string GetPinCode()
	{
		return _PinCode;
	}
	__declspec(property(get = GetPinCode, put = SetPinCode))string PinCode;
	void SetAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}
	float GetAccountBalance()
	{
		return _AccountBalance;
	}
	__declspec(property(get = GetAccountBalance, put = SetAccountBalance))float AccountBalance;
	void Print()
	{
		cout << "\nClient Card : ";
		cout << "\n------------------------------";
		cout << "\nFirstName         : " << FirstName;
		cout << "\nLastName          : " << LastName;
		cout << "\nFull Name         : " << FullName();
		cout << "\nEmail             : " << Email;
		cout << "\nPhone             : " << Phone;
		cout << "\nAcc.Number        : " << _AccountNumber;
		cout << "\nPassword          : " << _PinCode;
	    cout << "\nBalance           : " << _AccountBalance;
		cout << "\n-------------------------------\n";
	 }
	static clsBankClient Find(string AccountNumber)
	{
		vector<clsBankClient> vClients;
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLinetoClientObject(Line);
				if (Client.AccountNumber() == AccountNumber)
				{
					MyFile.close();
					return Client;
				}
				vClients.push_back(Client);
					

			}
			MyFile.close();
		}
		return _GetEmptyObject();
	}
	static clsBankClient Find(string AccountNumber, string PinCode)
	{
		vector<clsBankClient> vCLients;
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLinetoClientObject(Line);
				if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
				{
					MyFile.close();
					return Client;
				}
				vCLients.push_back(Client);
			}
			MyFile.close();
		}
		return _GetEmptyObject();
	}
	static bool IsExistClient(string AccountNumber)
	{
		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		return (!Client1.IsEmpty());
	}
};

