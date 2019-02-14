/*Forrest Allen
 * 2/13/2019
 * Assignment2: adventure*/

#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
/*Global variables*/
#define MIN_CONNECTIONS 3
#define MAX_CONNECTIONS 6
#define GAME_ROOMS 7

/*Room names are cities in the Bay Area*/

char * room_names[10]={
	"Oakland",
	"Frisco",
	"Moraga",
	"Orinda",
	"Hayward",
	"Berkeley",
	"Alameda",
	"San_Jo",
	"Vallejo",
	"The_Dro"};
enum room_type
{
	START_ROOM,
	MID_ROOM,
	END_ROOM
};

struct ROOM
{
	char name[50];
	int totalConn;
	struct ROOM * outBoundConnections[MAX_CONNECTIONS];
	enum room_type whatIsIt;
};

struct ROOM gameRooms[GAME_ROOMS];
char dirName[256];
int usedRooms[10];

/*Functions from 2.2 lecture on outline for assignment*/
int fullConnection(int index)
{
	if(gameRooms[index].totalConn == MAX_CONNECTIONS)
	{
		/*if full return true*/
		return 0;
	}
	else
	{
		/*return false otherwise*/
		return 1;
	}
}
/*Rooms can be looked at by index so if x and y are equal then they are the same*/
int isSameRoom(int x, int y)
{
	if(x==y)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
int getRandomRoom()
{
	int i= rand() %7;
	return i;
} 
void connectRoom(int room1, int room2)
{
	int i=gameRooms[room1].totalConn;
	gameRooms[room1].outBoundConnections[i]= &gameRooms[room2];
	gameRooms[room1].totalConn++;
}
int isConnected(int room1, int room2)
{
	int i;
	for(i=0;i<gameRooms[room1].totalConn;i++)
	{
		if(gameRooms[room1].outBoundConnections[i]==NULL)
		{
			return 1; //false
		}
		else if(strcmp(gameRooms[room1].outBoundConnections[i]->name, gameRooms[room2].name)==0)
		{
			return 0; //true
		}
	}
	return 1; //1 for false
}
void addRandomConnection(int base_room)
{
	int room_a;
	int room_b;
	int i=0;//makes it true
	while(i==0)
	{
		room_a=base_room;
		if(fullConnection(room_a)==0)
		{
			break;
		}
		i=1;
	}
	do
	{
		room_b=getRandomRoom();
		i++;
	}
	while(fullConnection(room_b)==0 || isSameRoom(room_a, room_b)==0 || isConnected(room_a,room_b)==0&&i<21);
	connectRoom(room_a,room_b); //conecting a to b
	connectRoom(room_b,room_a); //connecting b to a
}

void initOutBoundConnections(int index)
{
	int i;
	for(i=0; i<MAX_CONNECTIONS;i++)
	{	
		gameRooms[index].outBoundConnections[i]=NULL;
	}
}
int inGameRooms(index)
{
	int i;
	for(i=0;i<GAME_ROOMS;i++)
	{
		if(usedRooms[i]==index)
		{
			return 0; //room is already in game
		}
	}
	return 1; //if room is not in the game
}
void getGameRooms()
{

	int i=0;
	while(i<7)
	{
		int j=rand()%10;
		if(inGameRooms(j)==1)//room is not in the array
		{
			memset(gameRooms[i].name,'\0',sizeof(gameRooms[i].name));
			strcpy(gameRooms[i].name,room_names[j]);
			initOutBoundConnections(i);
			gameRooms[i].whatIsIt=MID_ROOM;
			usedRooms[i]=j;
			i++;
		}
	}
	gameRooms[0].whatIsIt = START_ROOM;//Setting start room
	gameRooms[6].whatIsIt = END_ROOM;// setting end room	
	int k;
	int l;
	for(k=0;k<7;k++)
	{
		while(gameRooms[k].totalConn<4)
		{
			addRandomConnection(k);
		}
	}
	
}
/*Builds the most current dir for the game*/
void buildGameFiles()
{
	int result;	
	char  actualName[256];
	char * nameof="allenfo.rooms.";
	int pid= getpid();
	memset(actualName,'\0', sizeof(actualName));
	sprintf(actualName, "%s%d",nameof,pid);
	result = mkdir(actualName, 0775);
	chdir(actualName);
	FILE * fileptr;
	char dirName[256];
	sprintf(dirName, "./allenfo.rooms.%d",getpid());
	int i;
	int j;
	    for(i = 0; i < 7; i++){
        fileptr = fopen(gameRooms[i].name,"w");

        fprintf(fileptr,"ROOM NAME: %s\n", gameRooms[i].name);
        for(j = 0; j < gameRooms[i].totalConn; j++){
            fprintf(fileptr,"CONNECTION %d: %s\n", j+1, gameRooms[i].outBoundConnections[j]->name);
        }
        
        if(gameRooms[i].whatIsIt == START_ROOM){
            fprintf(fileptr,"ROOM TYPE: %s\n", "START_ROOM");
        }
        else if(gameRooms[i].whatIsIt == MID_ROOM){
            fprintf(fileptr,"ROOM TYPE: %s\n", "MID_ROOM");
        }
        else if(gameRooms[i].whatIsIt == END_ROOM){
            fprintf(fileptr,"ROOM TYPE: %s\n", "END_ROOM");
        }
        else{
            fprintf(fileptr,"ROOM TYPE: %s\n", "NULL");
        }
        fclose(fileptr);
    }
}
int main()
{
	srand(time(NULL));
	getGameRooms();
	buildGameFiles();
	return 0;
}

			

