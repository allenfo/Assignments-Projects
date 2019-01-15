#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include "wrestler.h"
/*Taken from lecture and modified so that all the maps can be passed by reference. Each spot on the graph is given a number. If it is even the wrestler will be a babyface, odd if its a heel*/
void BFS(std::unordered_map <std::string, std::vector<std::string>> & graph,std::unordered_map <std::string, std::string> & color,std::unordered_map <std::string, int> & team, std::string &start)
{
	std::vector<std::string> Q{start};

	while (!Q.empty())
	{
		std::string u = Q.front();
		Q.erase(Q.begin());

		for (auto v : graph[u])
		{
			if (color[v] == "WHITE")
			{
				color[v] = "GRAY";
				team[v] = team[u] + 1;

				Q.push_back(v);
			}
		}
		color[u] = "BLACK";
	}

	


}

