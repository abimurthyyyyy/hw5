#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void merge(std::set<std::string> s1, std::set<std::string> &s2);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
		std::set<std::string> valid;
		if (in.find('-')==std::string::npos){
			if (dict.find(in)!=dict.end()){
				valid.insert(in);
			}
			return valid;
		}
		if (floating.size()){
			char a = floating.front();
			int found = 0;
			while (in.find('-', found)!=std::string::npos){
				string newin1 = in;
				newin1.replace(newin1.find('-',found),1,1, a);
				found = in.find('-',found) +1;
				string newfloating = floating;
				newfloating.erase(0,1);
				merge(wordle(newin1,newfloating, dict), valid);
			}
		}
		else{
			for (int i = 0; i<26;i++){
				string newin = in;
				char c = 'a' + i;
				newin.replace(newin.find('-'),1,1, c);
				merge(wordle(newin, floating, dict), valid);
				
			}
		}
		return valid;
}

// Define any helper functions here

void merge(std::set<std::string> s1, std::set<std::string> &s2){
	for (std::set<std::string>::iterator it = s1.begin(); it != s1.end(); ++it){
		s2.insert(*it);
	}
}
