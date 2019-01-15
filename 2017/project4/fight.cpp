#include"fight.hpp"
#include "gameplay.hpp"
#include"character.hpp"
#include<cstdlib>
void fight(Queue &q1, Queue &q2, Queue &trash)
{
	int battle = 1;
	int p1Score = 0;
	int p2Score = 0;
	while (q1.isEmpty() == false && q2.isEmpty() == false)
	{
		std::cout << "Battle: " << battle << std::endl;
		gameplay(q1.getTop(), q2.getTop());
		if (q1.getTop()->strengthPoint <= 0)
		{
			trash.trashPlayer(q1.getTop());
			q1.removePlayer();
			int recover = 0.3*q2.getTop()->strengthPoint;
			q2.getTop()->strengthPoint = q2.getTop()->strengthPoint + recover;
			std::cout << "Player 2's " << q2.getTop()->getType() << " has recovered " << recover << " health and has a new strength point of:" << q2.getTop()->strengthPoint << std::endl;
			q2.move2Back();
			std::cout << "One point is added to player 2's score.\n";
			p2Score++;
		}
		else if (q2.getTop()->strengthPoint <= 0)
		{
			trash.trashPlayer(q2.getTop());
			q2.removePlayer();
			int recover = 0.3*q1.getTop()->strengthPoint;
			q1.getTop()->strengthPoint += recover;
			std::cout << "Player 1's " << q1.getTop()->getType() << " has recovered " << recover << " health and has a new strength point of:" << q1.getTop()->strengthPoint << std::endl;
			q1.move2Back();
			std::cout << "One point is added to player 1's score.\n";
			p1Score++;
		}
		battle++;
		std::cout << std::endl;
	}
	std::cout << "Player 1 final score:" << p1Score << std::endl;
	std::cout << "Player 2 final score:" << p2Score << std::endl;
	if (p1Score > p2Score)
	{
		std::cout << "Player 1 wins the game!\n";
	}
	else if (p2Score > p1Score)
	{
		std::cout << "Player 2 wins the game!\n";
	}
	else if (p1Score == p2Score)
	{
		std::cout << "The game was a tie.\n";
	}

}
