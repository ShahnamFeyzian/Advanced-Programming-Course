#include <iostream>
#include <string>
using namespace std;


bool is_subset(string str1, string str2, string sub);
bool head_checker(string a, string b);

int main()
{
	string str1, str2, sub;
	cin >> str1 >> str2 >> sub;
	if (is_subset(str1, str2, sub))
		cout << "Interleaving";
	else 
		cout << "Not Interleaving";
}


bool is_subset(string str1, string str2, string sub)
{
	if ((str1.length() == 0) && (str2.length() == 0) && (sub.length() == 0)) 
		return true;

	if (head_checker(str1, sub) && head_checker(str2, sub))
	{
		sub = sub.substr(1);
		return is_subset(str1.substr(1), str2, sub) || is_subset(str1, str2.substr(1), sub);
	}
	
	if (head_checker(str1, sub)) 
		str1 = str1.substr(1);
	else if (head_checker(str2, sub))
		str2 = str2.substr(1);
	else 
		return false;

	sub = sub.substr(1);
	return is_subset(str1, str2, sub);
}

bool head_checker(string a, string b)
{
	if ((a[0] == b[0]) && (a.length() != 0) && (b.length() != 0)) return true;
	else return false;
}