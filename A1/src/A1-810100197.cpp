#include<iostream>
#include<string>
#include<vector>
using namespace std;



typedef struct TIME
{
	int h, m;
}TIME;

typedef struct PERIOD
{
	TIME start, end;
	int length;
}PERIOD;


vector<PERIOD> get_and_set_event(TIME start, TIME end);
vector<PERIOD> set_free_time(vector<PERIOD> e);
vector<PERIOD> get_and_set_task(vector<PERIOD> f);
void print_task(vector<PERIOD> t);
void print_formated_clock(TIME a);

int main()
{
	// initialize starting and ending time
	TIME start_time, end_time;
	start_time.h = 12;
	start_time.m = 0;
	end_time.h = 20;
	end_time.m = 0;

	vector<PERIOD> fixed_event = get_and_set_event(start_time, end_time);
	vector<PERIOD> free_time = set_free_time(fixed_event);
	vector<PERIOD> task = get_and_set_task(free_time);

	print_task(task);	

	return 0;
}



vector<PERIOD> get_and_set_event(TIME start_time, TIME end_time)
{
	vector<PERIOD> e(1);
	e[0].end.h = start_time.h;
	e[0].end.m = start_time.m;

	string s;
	int i;
	for(i=1;;i++)
	{
		cin >> s;
		e.resize(i+1);
		if(s == "#") break;
		
		
		e[i].start.h = ((int(s[0])-48)*10) + (int(s[1])-48);
		e[i].start.m = ((int(s[3])-48)*10) + (int(s[4])-48);
		e[i].end.h   = ((int(s[6])-48)*10) + (int(s[7])-48);
		e[i].end.m   = ((int(s[9])-48)*10) + (int(s[10])-48);
		e[i].length  = (e[i].end.h - e[i].start.h)*60 + (e[i].end.m - e[i].start.m);
	}
	
	e[i].start.h = end_time.h;
	e[i].start.m = end_time.m;

	return e;
}


vector<PERIOD> set_free_time(vector<PERIOD> e)
{
	vector<PERIOD> f;

	int n = e.size();

	for(int i=0; i<n-1; i++)
	{
		int l = (e[i].end.h - e[i+1].start.h)*60 + (e[i].end.m - e[i+1].start.m);

		if(l != 0)
		{
			f.resize(f.size()+1);
			f[f.size()-1].start.h = e[i].end.h;
			f[f.size()-1].start.m = e[i].end.m;
			f[f.size()-1].end.h   = e[i+1].start.h;
			f[f.size()-1].end.m   = e[i+1].start.m;
			f[f.size()-1].length  = l;
		}
	}

	return f;
}


vector<PERIOD> get_and_set_task(vector<PERIOD> f)
{
	vector<PERIOD> t;

	int len, range, i=0;
	while(cin >> len >> range)
	{
		t.resize(i+1);
		t[i].length  = len;
		t[i].start.h = f[range-1].start.h;
		t[i].start.m = f[range-1].start.m;
		t[i].end.m   = t[i].start.m + len;
		t[i].end.h   = (t[i].end.m/60) + t[i].start.h;
		t[i].end.m   = t[i].end.m%60;
		
		f[range-1].start.h = t[i].end.h;
		f[range-1].start.m = t[i].end.m;
		i++;
	}
	return t;
}

void print_task(vector<PERIOD> t)
{
	int n = t.size();
	for(int i=0; i<n; i++)
	{
		cout << i+1 << " ";
		print_formated_clock(t[i].start);
		cout << "-";
		print_formated_clock(t[i].end);
		cout << endl;
	}

}

void print_formated_clock(TIME a)
{
	if(a.h<10) cout << 0;
	cout << a.h << ":";
	if(a.m<10) cout << 0;
	cout << a.m;
}