//Grade improvement assignment for Nick Alvarez, Fall 2019

/*
Assignment Topic: Standard Template Library - MAPS & UNORDERED MAPS
Purpose: This exercise is supposed to show STL components and some own coding can be combined to solve a rather complicated operation in a fairly concise way. You are expected to gain experience about the proper use of STL. 

Link to CPP reference: https://en.cppreference.com/w/cpp/container/map (Links to an external site.) & https://en.cppreference.com/w/cpp/container/unordered_map (Links to an external site.)

Write a function called make_xref(), which given an input stream, namely a vector <string> with given words and an empty map<string, vector<int> > (or an unordered map), creates a cross-reference in the map (or the unordered map) for the given words. The input stream is supposed to be a text with words and separating white space only.

When all words in the input stream have been read, the map (or the unordered map) shall, for each given word, store the lines in the input where the word was found.

Also write a function print_xref(), for printing the cross reference map (or the unordered map) created by make_xref().

print_xref() shall take an output stream and the cross-reference map (or the unordered map). If the given words were “algorithms”, “containers”, “functions”, and “objects”, the output from print_xref() could be as follows:

algorithms 2, 7, 8.
containers 1, 4, 5.
functions 9.
objects 2,7.*/

void make_xref(istream &input, vector<string>& words, map<string, vector<int>> map)
{
	for (auto i = words.begin(); i != words.end(); i++)
	{
		map[i];
	}
	string line, word;
	int numLine = 0;
	while (getline(input, line))
	{
		numLine++;
		istringstream words = line;
		while (words >> word)
		{
			map<string, vector<int>>::iterator s = map.find(word);
			if (s != map.end())
			{
				s->second.push_back(numLine);
			}
		}
	}
}
void print_xref(ostream &output, const map<string, vector<int>> map)
{
	vector<int>::const_iterator f, l;
	for (auto w = map.begin(); w != map.end(); w++)
	{
		output << w.f << " ";
		f = w.second.cbegin();
		l = w.second.cend() - 1;
		copy(f, l, ostream_iterator<int>(output, ", "));
		output << *l << "." << endl;
	}
}