#include "Header.h"

using std::string;

bool compare(const std::pair<string, int>& pair_1, const std::pair<string, int>& pair_2) {
	if (pair_1.second == pair_2.second)
		return (pair_1.first.length() < pair_2.first.length());
	return(pair_1.second > pair_2.second);
}

string prepare(const string& str) {
	string result;
	result = str;
	std::transform(result.begin(), result.end(), result.begin(), tolower);
	if (!isalpha(result[result.length() - 1]))
		result.pop_back();
	return result;
}