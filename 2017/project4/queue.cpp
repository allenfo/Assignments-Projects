#include"character.hpp"
#include"queue.hpp"
Queue::Queue()
{
	head = NULL;
	tail = head;
}
Queue::~Queue()
{
	while (head != NULL)
	{
		if (head == NULL&&tail == NULL)
		{
			return;
		}
		else if (head->next == NULL)
		{
			playerList *node1 = head;
			head = NULL;
			tail = NULL;
			delete node1->c;
			delete node1;
		}
		else
		{
			playerList *node1 = head;
			playerList *node2 = head->next;
			head = node2;
			delete node1->c;
			delete node1;
			head->prev = NULL;
		}
	}
	delete head;
	delete tail;

}
void Queue::addPlayer(Character *c)
{
	if (head == NULL)
	{
		head = new playerList(c);
		tail = head;
	}
	else
	{
		playerList * node;
		node = head;
		while (node->next != NULL)
		{
			node = node->next;
		}
		node->next = new playerList(c);
		tail = node->next;
	}
}
void Queue::trashPlayer(Character *c)
{
	if (head == NULL)
	{
		head = new playerList(c);
		tail = head;
	}
	else
	{
		playerList * node = head;

		while (node->prev != NULL)
		{
			node = node->prev;
		}
		node->prev = new playerList(c);
		playerList *temp = head;
		head = node->prev;
		node = temp;
		head->next = node;
	}

}
void Queue::removePlayer()
{
	if (head == NULL&&tail == NULL)
	{
		std::cout << "There was nothing to delete.\n";
	}
	else if (head->next == NULL)
	{
		playerList *node = head;
		head = NULL;
		tail = NULL;
		delete node;
	}
	else
	{
		playerList *node1 = head;
		playerList *node2 = head->next;
		head = node2;
		delete node1;
		head->prev = NULL;
	}

}
void Queue::move2Back()
{
	playerList *node = head;
	addPlayer(node->c);
	removePlayer();
}
Character* Queue::getTop()
{
	return head->c;
}
bool Queue::isEmpty()
{
	if (head == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}

}
void Queue::print()
{
	if (head == NULL)
	{
		std::cout << "This list is empty.\n";
	}
	else
	{
		playerList *node = head;
		while (node != NULL)
		{
			node->c->info();
			node = node->next;
		}
	}
}
