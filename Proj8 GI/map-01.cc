/*
 * map-01.cc    Standard Library, std::map, exercise 1.
 */
#include <iostream>
#include <algorithm>
#include <iterator>
#include <map>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

typedef map<string, vector<int>> Xref;

void make_xref(istream& is, const vector<string>& entries, Xref& xref)
{
   // insert the given words into xref; the associated vectors are
   // default initialized by operator[].
   for (const auto& s : entries)
   {
      xref[s];
   }

   string line, word;
   int    line_number{ 0 };

   while (getline(is, line)) 
   {
      ++line_number;
      istringstream words{ line };
      while (words >> word) 
      {
	 Xref::iterator p{ xref.find(word) };
	 if (p != xref.end())
	 {
	    p->second.push_back(line_number);
	 }
      }
   }
}

void print_xref(ostream& os, const Xref& xref)
{
   vector<int>::const_iterator first, last;

   for (const auto& entry : xref)
   {
      os << entry.first << "  ";
      first = entry.second.cbegin();
      last  = entry.second.cend() - 1;
      copy(first, last, ostream_iterator<int>(os, ", "));
      os << *last << ".\n";
   }
}

int main()
{
   vector<string> entries{ "algorithms", "containers", "functions", "objects" };

   Xref cross_ref;

   make_xref(cin, entries, cross_ref);
   print_xref(cout, cross_ref);

   return 0;
}
