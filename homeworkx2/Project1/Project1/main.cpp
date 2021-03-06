/*
позже дедлайна + списано.
*/

#include "Header.h"

int main() {
	std::ifstream file("C:\Users\Roma\Documents\GitHub\practice\homeworkx2\Project1\Project1\file.txt");
	std::ofstream fout("C:\Users\Roma\Documents\GitHub\practice\homeworkx2\Project1\Project1\fout.txt");
	std::map<string, int> map;
	if (file.is_open()) {
		string word;
		while (!file.eof()) {
			file >> word;
			word = prepare(word);
			map[word]++;
		}

		std::vector< std::pair< string, int > > vec(map.begin(), map.end());
		std::sort(vec.begin(), vec.end(), compare);

		for (auto p : vec) {
			std::cout << p.first << ' ' << p.second << std::endl;
			fout << p.first << ' ' << p.second << "\n";
		}
		fout.close();
		file.close();
	}
}
