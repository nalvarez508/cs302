//Project 7, Nick Alvarez, CS302, Fall 2019.

#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

const int NUMBER_CITIES = 5;
int BEST_ROUTE = 0;

int TSP(int array[][NUMBER_CITIES], int s);
void printCity(int k);

int main()
{
  int cityArray[][NUMBER_CITIES] = {{0, 218, 518, 704, 439},    //Reno
                                    {218, 0, 736, 808, 569},    //San Francisco
                                    {518, 739, 0, 840, 421},    //Salt Lake City
                                    {704, 808, 840, 0, 1125},   //Seattle
                                    {439, 569, 421, 1125, 0} }; //Las Vegas
  int source = 0;
  int output = TSP(cityArray, source);
  cout << endl << output << " Miles, Route " << BEST_ROUTE << endl;
}

int TSP(int array[][NUMBER_CITIES], int s)
{
  //Total vertexes that are not the source
  vector<int> vtx;
  for (int i=0; i < NUMBER_CITIES; i++)
  {
    if (i != s)
    {
      vtx.push_back(i);
    }
  }

  bool routeFound = 0;
  int minPath = INT_MAX;
  int min1 = 0;
  int min2 = 0;
  int trial = 1;
  do
  {
    cout << "Route " << trial++ << ": \t";
    printCity(0);
    int currWeight = 0;
    int k = s;
    for (int i=0; i < vtx.size(); i++)
    {
      currWeight += array[k][vtx[i]];
      k = vtx[i];
      printCity(k);
    }
    currWeight += array[k][s];
    min1 = minPath;
    minPath = min(minPath, currWeight);
    min2 = minPath;
    cout << "\t" << currWeight << " Miles";
    if (min1 == min2 && !routeFound)
    {
      BEST_ROUTE = trial - 2;
      routeFound = 1;
    }
    cout << endl;
  } while (next_permutation(vtx.begin(), vtx.end()));
  return minPath;
}

void printCity(int k)
{
  switch (k)
  {
  case 0:
  {
    cout << "RNO ";
    break;
  }

  case 1:
  {
    cout << "SFO ";
    break;
  }

  case 2:
  {
    cout << "SLC ";
    break;
  }

  case 3:
  {
    cout << "SEA ";
    break;
  }

  case 4:
  {
    cout << "LVS ";
    break;
  }
  
  default:
    cout << k;
  }
}