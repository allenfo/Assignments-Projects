#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include "wrestler.h"
int main(int argc, char** argv )
{
	/*maps are used so we have a key. The first graph is the rivalries for each key, the second map is the color (White, grey, or black) associated with
	that key, and the third is whether the key gets an even or odd number which will dictate what team they are on.*/
	std::unordered_map <std::string, std::vector<std::string>> graph;
	std::unordered_map <std::string, std::string> color;
	std::unordered_map <std::string, int> team;
	std::ifstream myfile;
	std::string filename=argv[1];
	myfile.open(filename);
	if (!myfile.is_open())
	{
		exit(EXIT_FAILURE);
	}
	int wrestlers;
	int rivalries;
	myfile >> wrestlers;
	/*100 is the max number of wrestlers that the graders would use. Taken from an answer in discussion*/
	std::string W[100];
	/*extracting the names from the txt file*/
	for (int i = 0; i < wrestlers; i++)
	{
		myfile >> W[i];
	}
	myfile >> rivalries;
	std::vector<std::string> x;
	/*In this section we go through filling out the graph using the rivalries. We loop through n times n being the number of rivalries*/
	for (int i = 0; i < rivalries; i++)
	{
		std::string firstName;
		std::string secondName;
		myfile >> firstName;
		myfile >> secondName;
		/*First checking if either name is already in the graph as a key*/
		if (graph.count(firstName) == 0)
		{
			if (graph.count(secondName) == 0)
			{
				graph.emplace(firstName, x);
				color.emplace(firstName, "WHITE");
				team.emplace(firstName, 0);
				
				graph.emplace(secondName, x);
				color.emplace(secondName, "WHITE");
				team.emplace(secondName, 0);
				/*giving the vertices, edges*/
				graph[firstName].push_back(secondName);
				graph[secondName].push_back(firstName);
			}
			else
			{ 
				graph.emplace(firstName, x);
				color.emplace(firstName, "WHITE");
				team.emplace(firstName, 0);

				graph[firstName].push_back(secondName);
				graph[secondName].push_back(firstName);
			}
		}
		/*If the first name is in but the second is not*/
		else if (graph.count(firstName) > 0)
		{
			if (graph.count(secondName) == 0)
			{ 
				graph.emplace(secondName, x);
				color.emplace(secondName, "WHITE");
				team.emplace(secondName, 0);
				
				graph[firstName].push_back(secondName);
				graph[secondName].push_back(firstName);
			}
			/*Both names have already been entered as keys*/
			else
			{
				graph[firstName].push_back(secondName);
				graph[secondName].push_back(firstName);
			}
		}
	}
	/*We call BFS for every wreslter as the start. This covers any unconnected rivalries*/
	for (int i = 0; i <wrestlers; i++)
	{
		BFS(graph, color, team, W[i]);
	}
	/*Once all the spots in the graph have been visited we see if they will work. If there is any failure then the graph fails*/
	for (auto x : graph)
	{
		for (int i = 0; i < x.second.size(); ++i)
		{
			if (team[x.first] % 2 == team[x.second.at(i)] % 2)
			{
				std::cout << "IMPOSSIBLE" << std::endl;
				return 0;
			}
		}
	}
	/*Vectors used because we don't have to dynamiclly allocate memory for arrays. Although an alternative approach is to have set arrays*/
	std::vector<std::string> babyfaces;
	std::vector<std::string> heels;
	//check if babyface or heel
	for (auto v : graph)
	{
		/*checking if babyface or HEEL*/
		if (team[v.first] % 2 == 0)
		{
			babyfaces.push_back(v.first);
		}
		else
		{
			heels.push_back(v.first);
		}
	}
	std::cout << "YES POSSIBLE" << std::endl;
	std::cout << "BABYFACES: ";
	for (auto a : babyfaces)
	{
		std::cout << a<< " ";
	}
	std::cout << std::endl;
	std::cout << "HEELS: ";
	for (auto a : heels)
	{
		std::cout << a << " ";
	}
	std::cout << std::endl;
	return 0;
}
