#include <iostream>
#include "clsBankClient.h"
int main()
{
	clsBankClient client1 = clsBankClient::Find("A101");
	client1.Print();
	clsBankClient client2 = clsBankClient::Find("A102", "1234");
	client2.Print();

	cout << clsBankClient::IsExistClient("A1011") << endl;
	system("pause>0");
	return 0;

}


