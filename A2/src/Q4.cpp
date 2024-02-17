#include <iostream>
#include <vector>
using namespace std;


bool check(vector<int>&w, int mass, int n);

int main()
{
	int mass, n, w;
	vector<int> weights;

	cin >> n >> mass;
	for (int i = 0; i < n; i++)
	{
		cin >> w;
		weights.push_back(w);
	}

	if (check(weights, mass, n)) cout << "True";
	else cout << "False";

	return 0;
}


bool check(vector<int>&w, int mass, int n)
{
	if (n == w.size())
		for (int i = 0; i < n; i++)
			if (w[i] == mass) return true;

	for (int i = 0; i < n - 1; i++)
		for (int j = i + 1; j < n; j++)
			if ((w[j] == mass + w[i]) || (w[j] == mass - w[i])) return true;

	for (int i = n - 1; i > 0; i--)
		return (check(w, mass - w[i], i) || check(w, mass + w[i], i));

	return false;
}
