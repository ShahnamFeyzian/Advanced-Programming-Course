#include <iostream>
#include <string>
using namespace std;


string series_maker(int n);
string convertor(string s);

int main()
{
	int n, k;
	cin >> n >> k;
	string series = series_maker(n);
	cout << series[k - 1];
	return 0;
}


string series_maker(int n)
{
	if (n <= 1) return "0";
	string str1 = series_maker(n - 1);
	string str2 = convertor(str1);
	return (str1 + str2);
}

string convertor(string s)
{
	string convert_str="", convert_char;
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == '0') convert_char = "1";
		else convert_char = "0";
		convert_str += convert_char;
	}
	return convert_str;
}