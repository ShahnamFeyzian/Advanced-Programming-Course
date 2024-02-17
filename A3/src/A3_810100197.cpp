#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

#define READING_FILE_ERROR "There is a problem in reading input file!! Please check it." 

typedef vector<string> Languages;

struct Time
{
	int hour, min;
};

struct Period
{
	Time start, end;
	int len;
};

struct Translator
{
	string name;
	vector<Period> free_times;
	Languages langs;
	int id;
};

struct Event
{
	string name;
	Period duration;
	Languages langs;
	vector<int> teranslators_id;
};


vector<Translator> read_and_set_translator(string file_address);
vector<Event> read_and_set_event(string file_address);
void set_translator(vector<Translator>&tls, vector<Event>&events);
Languages sort_langs_by_num_of_tls(Languages lang, const vector<Translator>&tls);
vector<Translator> find_tls_by_language(string lang, const vector<Translator>&tls);
void checking_tls_time(vector<Translator>&tls, Period duration);
void choose_tls_by_num_of_langs(vector<Translator>&tls);
void booking_translator_time(Translator&translator, Period event_duration);
void set_event_translator_id(Event&e, string lang, int id);
Translator translator_gen(string line);
Event event_gen(string line);
void line_reader(string line, string&name, int&start_hour, int&start_min,
                 int&end_hour, int&end_min, Languages&langs);
void clack_reader(string formated_clack, int&hour, int&min);
Period period_gen(int start_hour, int start_min, int end_hour, int end_min);
bool check_period(Period total, Period part);
void output_display(const vector<Event>&events, const vector<Translator>&tls);
int minimum_member(const vector<int>&A);
int alphabetical_comparison(string str1, string str2);

int main(int argc, char* argv[])
{
	vector<Translator> translators = read_and_set_translator(argv[1]);
	vector<Event> events = read_and_set_event(argv[1]);
	if (translators.size() == 0 || events.size() == 0) 
	{
		cerr << READING_FILE_ERROR;
		return 1;
	}
	set_translator(translators, events);
	output_display(events, translators);
	return 0;
}



vector<Translator> read_and_set_translator(string file_address)
{
	ifstream input_file(file_address);
	vector<Translator> tls;

	if (!input_file.is_open()) return tls;

	string line;
	getline(input_file, line);
	int tls_num = stoi(line);

	for (int i = 0; i<tls_num; i++)
	{
		getline(input_file, line);
		tls.push_back(translator_gen(line));
		tls[i].id = i + 1;
	}

	input_file.close();
	return tls;
}


vector<Event> read_and_set_event(string file_address)
{
	ifstream input_file(file_address);
	vector<Event> events;

	if (!input_file.is_open()) return events;

	string line;
	getline(input_file, line);
	int num = stoi(line);
	for (int i = 0; i<num + 1; i++) getline(input_file, line); // skipping translators part
	num = stoi(line);

	for (int i = 0; i < num; i++)
	{
		getline(input_file, line);
		events.push_back(event_gen(line));
		events[i].teranslators_id.resize(events[i].langs.size());
	}

	input_file.close();
	return events;
}


void set_translator(vector<Translator>&tls, vector<Event>&events)
{
	for (int i = 0; i < events.size(); i++)
	{
		Languages curent_event = sort_langs_by_num_of_tls(events[i].langs, tls);
		for (int j = 0; j < curent_event.size(); j++)
		{
			vector<Translator> suitable_tls = find_tls_by_language(curent_event[j], tls);
			checking_tls_time(suitable_tls, events[i].duration);
			
			if (suitable_tls.size() == 0)
			{
				set_event_translator_id(events[i], curent_event[j], 0);
				break;
			}

			choose_tls_by_num_of_langs(suitable_tls);
			
			while (suitable_tls.size() > 1)
			{
				if (alphabetical_comparison(suitable_tls[0].name, suitable_tls[1].name) == 2) suitable_tls.erase(suitable_tls.begin());
				else suitable_tls.erase(suitable_tls.begin() + 1);
			}
			
			set_event_translator_id(events[i], curent_event[j], suitable_tls[0].id);
			booking_translator_time(suitable_tls[0], events[i].duration);
			
			for (int i = 0; i < tls.size(); i++)
				if (tls[i].id == suitable_tls[0].id)
				{
					tls[i] = suitable_tls[0];
					break;
				}
		}
	}
}


Languages sort_langs_by_num_of_tls(Languages langs, const vector<Translator>&tls)
{
	Languages sorted_langs = langs;
	vector<int> number_of_tls;
	int temp_counter = 0;

	for (int i = 0; i < sorted_langs.size(); i++)
	{
		for (int j = 0; j < tls.size(); j++)
			for (int p = 0; p < tls[j].langs.size(); p++)
				if (sorted_langs[i] == tls[j].langs[p])
				{
					temp_counter++;
					break;
				}
		number_of_tls.push_back(temp_counter);
		temp_counter = 0;
	}

	string temp_lang;

	for(int i = 0; i < sorted_langs.size() - 1; i++)
		for (int j = i + 1; j < sorted_langs.size(); j++)
		{
			if (number_of_tls[i] > number_of_tls[j])
			{
				swap(number_of_tls[i], number_of_tls[j]);
				swap(sorted_langs[i], sorted_langs[j]);  
			}
			else if (number_of_tls[i] == number_of_tls[j])
			{
				int p, z;
				for (p = 0; p < langs.size(); p++)
					if (langs[p] == sorted_langs[i]) break;

				for (z = 0; z < langs.size(); z++)
					if (langs[z] == sorted_langs[j]) break;
								
				if(p > z)
				{
					swap(number_of_tls[i], number_of_tls[j]);
					swap(sorted_langs[i], sorted_langs[j]);   
				}
			}
		}


	return sorted_langs;
}


vector<Translator> find_tls_by_language(string lang, const vector<Translator>&tls)
{
	vector<Translator> suitable_tls;

	for(int i = 0; i < tls.size(); i++)
		for(int j = 0; j < tls[i].langs.size(); j++)
			if (tls[i].langs[j] == lang)
			{
				suitable_tls.push_back(tls[i]);
				break;
			}

	return suitable_tls;
}


void checking_tls_time(vector<Translator>&tls, Period duration)
{
	bool have_time = false;
	for (int i = 0; i < tls.size(); i++)
	{
		for (int j = 0; j < tls[i].free_times.size(); j++)
			if (check_period(tls[i].free_times[j], duration))
			{
				have_time = true;
				break;
			}
		if (have_time == false)
		{
			tls.erase(tls.begin() + i);
			i--;
		}
		have_time = false;
	}
}


void choose_tls_by_num_of_langs(vector<Translator>&tls)
{
	vector<int> langs_counter;

	for (int i = 0; i < tls.size(); i++)
		langs_counter.push_back(tls[i].langs.size());

	int min = minimum_member(langs_counter);

	for (int i = 0; i < langs_counter.size(); i++)
		if (min < langs_counter[i])
		{
			tls.erase(tls.begin() + i);
			langs_counter.erase(langs_counter.begin() + i);
			i--;
		}
}


void booking_translator_time(Translator&translator, Period event_duration)
{
	for (int i = 0; i < translator.free_times.size(); i++)
	{
		if (check_period(translator.free_times[i], event_duration))
		{
			if ((translator.free_times[i].start.hour == event_duration.start.hour) && (translator.free_times[i].start.min == event_duration.start.min))
			{
				translator.free_times[i] = period_gen(event_duration.end.hour, event_duration.end.min, translator.free_times[i].end.hour, 
					                                  translator.free_times[i].end.min);
			}
			else if ((translator.free_times[i].end.hour == event_duration.end.hour) && (translator.free_times[i].end.min == event_duration.end.min))
			{
				translator.free_times[i] = period_gen(translator.free_times[i].start.hour, translator.free_times[i].start.min, event_duration.start.hour,
					                                  event_duration.start.min);
			}
			else
			{
				Period p1 = period_gen(translator.free_times[i].start.hour, translator.free_times[i].start.min, event_duration.start.hour, event_duration.start.min);
				Period p2 = period_gen(event_duration.end.hour, event_duration.end.min, translator.free_times[i].end.hour, translator.free_times[i].end.min);
				translator.free_times.erase(translator.free_times.begin() + i);
				translator.free_times.push_back(p1);
				translator.free_times.push_back(p2);
			}
			break;
		}
	}
}


void set_event_translator_id(Event&e, string lang, int id)
{
	int index;

	for (index = 0; index < e.langs.size(); index++)
		if (e.langs[index] == lang) break;

	e.teranslators_id[index] = id;
}


Translator translator_gen(string line)
{
	Translator A;
	string name;
	Languages langs;
	int start_hour, start_min, end_hour, end_min;

	line_reader(line, name, start_hour, start_min, end_hour, end_min, langs);

	A.name = name;
	A.free_times.push_back(period_gen(start_hour, start_min, end_hour, end_min));
	A.langs = langs;

	return A;
}


Event event_gen(string line)
{
	Event A;
	string name;
	Languages langs;
	int start_hour, start_min, end_hour, end_min;

	line_reader(line, name, start_hour, start_min, end_hour, end_min, langs);

	A.name = name;
	A.duration = period_gen(start_hour, start_min, end_hour, end_min);
	A.langs = langs;

	return A;
}


void line_reader(string line, string&name, int&start_hour, int&start_min,
	int&end_hour, int&end_min, Languages&langs)
{
	int space = line.find(" ");
	name = line.substr(0, space);
	line = line.substr(space + 1);
	clack_reader(line.substr(0, 5), start_hour, start_min);
	clack_reader(line.substr(6, 5), end_hour, end_min);
	line = line.substr(12);

	while (true)
	{
		space = line.find(" ");
		if (space == -1)
		{
			langs.push_back(line);
			break;
		}
		langs.push_back(line.substr(0, space));
		line = line.substr(space + 1);
	}
}


void clack_reader(string formated_clack, int&hour, int&min)
{
	string h = formated_clack.substr(0, 2);
	string m = formated_clack.substr(3);

	hour = stoi(h);
	min = stoi(m);
}


Period period_gen(int start_hour, int start_min, int end_hour, int end_min)
{
	Period p;
	p.start.hour = start_hour;
	p.start.min = start_min;
	p.end.hour = end_hour;
	p.end.min = end_min;
	p.len = (end_hour - start_hour) * 60 + (end_min - start_min);
	return p;
}



bool check_period(Period total, Period part)
{
	if ((total.start.hour > part.start.hour) || (total.end.hour < part.end.hour)) return false;
	else if ((total.start.hour < part.start.hour) && (total.end.hour > part.end.hour)) return true;
	else if ((total.start.hour == part.start.hour) && (total.end.hour > part.end.hour))
	{
		if (total.start.min > part.start.min) return false;
		else return true;
	}
	else if ((total.start.hour < part.start.hour) && (total.end.hour == part.end.hour))
	{
		if (total.end.min < part.end.min) return false;
		else return true;
	}
	else
	{
		if ((total.start.min > part.start.min) || (total.end.min < part.end.min)) return false;
		else return true;
	}
}


void output_display(const vector<Event>&events, const vector<Translator>&tls)
{
	for (int i = 0; i < events.size(); i++)
	{
		cout << events[i].name << endl;
		for (int j = 0; j < events[i].langs.size(); j++)
		{
			cout << events[i].langs[j] << ": ";
			if (events[i].teranslators_id[j] == 0) cout << "Not Found";
			else
			{
				for (int z = 0; z < tls.size(); z++)
					if (tls[z].id == events[i].teranslators_id[j])
					{
						cout << tls[z].name;
						break;
					}
			}
			if ((j != events[i].langs.size() - 1) || (i != events.size() - 1)) cout << endl;
		}
	}
}


int minimum_member(const vector<int>&A)
{
	int min = A[0];

	for (int i = 1; i < A.size(); i++)
		if (min > A[i]) min = A[i];

	return min;
}


int alphabetical_comparison(string str1, string str2)
{
	if (str1 == str2) return 0;
	int index = 0;
	while ((index < str1.size()) && (index < str2.size()))
	{
		if (str1[index] > str2[index]) return 2;
		if (str1[index] < str2[index]) return 1;
		index++;
	}
	if (str1.size() > str2.size()) return 2;
	else return 1;
}



