#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <map>

using namespace std;

//test id:23280666842802

//int main(void) {

	//vector<string> test;

	//vector<string>::iterator it = test.begin();

 //   std::map<string, unsigned int> num_toy_mentions;
 //   multimap<unsigned int, string> sorted_toys;

 //   for(map<string, unsigned int>::iterator men_it = num_toy_mentions.begin(); men_it != num_toy_mentions.end(); men_it++)
 //   {
 //       sorted_toys.insert(pair<unsigned int,string>(men_it->second, men_it->first));


 //   }

 //   vector<string> result;
 //   multimap<unsigned int, string>::iterator sorted_it = sorted_toys.rbegin();


 //   for (int i = 0; i < 9; i++)
 //   {
 //       result.push_back(sorted_it->second);
 //       sorted_it++;
 //       if (sorted_it == sorted_toys.rend())
 //           break;
 //   }
    

    struct Line_type {
        string id;
        string line_info;
        bool has_words;
    };

    int main(void) {}
    vector<string> reorderLines(int logFileSize, vector<string> logLines)
    {

        //better to use vector size instead of logFileSize, in case bad input
        Line_type* re_ordered = new Line_type[logLines.size()];

        for (int i = 0; i < logLines.size(); i++)
        {


        }

        delete[] re_ordered;
        //description of order is slightly unclear, but should again use STL with sort and predicate
        //probably build a quick struct to handle the data, and then sort their way
    }

}

