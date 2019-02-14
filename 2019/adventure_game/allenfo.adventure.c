/*Forrest Allen
 * 2/13/2019
 * Assignment 2: Adventure
 * */

#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <pthread.h>
#include <assert.h>

#define MIN_CONNECTIONS 3
#define MAX_CONNECTIONS 6
#define GAME_ROOMS 7

/*Room names are cities in the Bay Area*/
/*Time functions. Gets local time and writes it to currentTime.txt*/
void * getTime()
{
	FILE *fileptr;
	fileptr=fopen("currentTime.txt","w+");
	struct tm *ptr;
	time_t t;
	char str[100];
	memset(str,'\0',sizeof(str));
	t=time(NULL);
	ptr=localtime(&t);
	strftime(str,100,"%I:%M%p, %A, %B %d, %G\n",ptr);
	fputs(str,fileptr);
	fclose(fileptr);
	return NULL;
}
/*grabs the data from currentTime.txt and displays it*/
void  displayTime()
{
	char theTime[100];
	FILE *myFile;
	myFile=fopen("currentTime.txt","r");
	if(myFile==NULL)
	{
		printf("ERROR\n");
	}
	else
	{
		fgets(theTime,100, myFile);
		printf("\n%s\n",theTime);
	}	
	fclose(myFile);
}
/*Creates a thread and stops the process to run this one? still working on understanding that*/
int threading()
{
	pthread_t timeThread;
	int result_code;
	pthread_mutex_t myMutex;
	result_code=pthread_create(&timeThread,NULL,getTime,NULL);
	assert(0==result_code);
	pthread_mutex_unlock(&myMutex);
	result_code = pthread_join(timeThread,NULL);
	pthread_mutex_lock(&myMutex);
	return 1;
	pthread_mutex_destroy(&myMutex);
	
} 
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
        "Th_ Dro"};
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
initGameRooms()
{
	int i=0;
	for(i=0;i<GAME_ROOMS;i++)
	{
		gameRooms[i].totalConn=0;
	}
}
/*Returns the name of the dir so we can access it*/
char *folderName()
{
	time_t t;
	int i=0;
	
	/*From Lecture minus the print statements*/
	int newestDirTime=-1;
	char targetDirPrefix[32] = "allenfo.rooms.";
	char newestDirName[256];
	memset(newestDirName, '\0', sizeof(newestDirName));
	DIR * dirToCheck;
	struct dirent *fileInDir;
	struct stat dirAttributes;
	dirToCheck = opendir(".");
	if(dirToCheck >0)
	{
		while((fileInDir= readdir(dirToCheck))!=NULL)
		{
			if(strstr(fileInDir->d_name,targetDirPrefix)!=NULL)
			{
        			stat(fileInDir->d_name, &dirAttributes);
				if ((int)dirAttributes.st_mtime > newestDirTime)
				{
					newestDirTime = (int)dirAttributes.st_mtime;
          				memset(newestDirName, '\0', sizeof(newestDirName));
          				strcpy(newestDirName, fileInDir->d_name);
        			}
      			}
    		}
  	}

  closedir(dirToCheck);
return newestDirName;
}
/*Once we have the most current dir name we can run through it and get the files to populate the array we have
 * This is probably not the most effective way to this but it made sense in my head*/
void extractData()
{
	char directory[256];
	strcpy(directory, folderName());
	char* start = malloc(sizeof(char) * 20);
	DIR* folder;
	struct dirent* find;
  	int i=0;
	if((folder = opendir(directory)) != NULL)
	{
    		while((find = readdir(folder)) != NULL)
		{	
      			if(!strcmp(find -> d_name, "..") || !strcmp(find -> d_name, "."))
			{
				continue;
      			}
      			strcpy(start, find -> d_name);
			char fileName[100];
			/*Accessing each file here*/
			sprintf(fileName,"./%s/%s",directory,start);
			FILE * myFile;
			myFile= fopen(fileName,"r");
			if(myFile==NULL)
			{
				printf("error\n");
			}
			char getaline[100];
			fgets(getaline,100,myFile);
			char* data;
			/*Getting through the data. Since we know the prompt it was easier to hard code the jumps*/
			data=strtok(getaline, " ");
			data=strtok(NULL, " ");
			data=strtok(NULL, "\n ");
			strcpy(gameRooms[i].name,data);
			fillArray(myFile,i,getaline);
			i++;
			fclose(myFile);
    		}
    		  	}
  	else
	{
    		perror("");
  	}
	closedir(folder);   

}
/*Filling the array with the rest of the data*/
void fillArray(FILE* myfile, int room1, char* getaline)
{
	int k=0;
	while(fgets(getaline,100,myfile))
	{
		char* searcher = strtok(getaline, " ");
		if(strcmp(searcher, "CONNECTION") == 0)
		{
			searcher = strtok(NULL, " ");
      			searcher = strtok(NULL, "\n");
			int j;
			for(j = 0; j < 7; j++)
			{
				if(strcmp(searcher, gameRooms[j].name) == 0)
				{
					gameRooms[room1].outBoundConnections[gameRooms[room1].totalConn]=&gameRooms[j];
					gameRooms[j].outBoundConnections[gameRooms[j].totalConn]=&gameRooms[room1];
					gameRooms[j].totalConn++;
					gameRooms[room1].totalConn++;
				}
			}
		}
		else if(strcmp(searcher,"ROOM")==0)
		{
			searcher = strtok(NULL, " ");
			searcher = strtok(NULL, "\n");
			if(strcmp(searcher, "START_ROOM")==0)
			{
				gameRooms[room1].whatIsIt=START_ROOM;
			}
			else if(strcmp(searcher,"MID_ROOM")==0)
			{
				gameRooms[room1].whatIsIt=MID_ROOM;
			}
			else
			{
				gameRooms[room1].whatIsIt=END_ROOM;
			}
		}
	}
}
/*Checks if the entry was valid and room has that connection*/
int validConnection(int currRoom, char entry[100])
{
	int i;
	for(i=0;i<gameRooms[currRoom].totalConn;i++)
	{
		if(strcmp(gameRooms[currRoom].outBoundConnections[i]->name,entry)==0)
		{
			return 0;	//if true
		}
	}
	return 1;		//if false
}
int changeRooms(char entry[100])
{
	int i;
	for(i=0;i<GAME_ROOMS;i++)
	{
		if(strcmp(gameRooms[i].name,entry)==0)
		{
			return i;
		}
	}
	printf("ERROR: NOT FOUND\n");
	return -1;
}
int setStart()
{
	int i;
	for(i=0;i<GAME_ROOMS;i++)
	{
		if(gameRooms[i].whatIsIt==0)
		{
			return i;
		}
	}
}
/*The function used in main(). Goes through the prompt. */
void playGame()
{
	initGameRooms();
	extractData();
	int isGameOver=1;			//set to false
	int location=setStart();		//where the player is on the map
	int steps=0;
	char entry[100];
	int pathTaken[500];
	do
	{
		printf("\nCURRENT LOCATION: %s\n",gameRooms[location].name);
		printf("POSSIBLE CONNECTIONS: ");
		int i;
		for(i=0;i<gameRooms[location].totalConn;i++)
		{
			if(i==gameRooms[location].totalConn-1)
			{
				printf("%s.\n",gameRooms[location].outBoundConnections[i]->name);
			}
			else
			{
				printf("%s, ",gameRooms[location].outBoundConnections[i]->name);
			}	
		}
		printf("WHERE TO? >");
		scanf("%s",entry);
		if(strcmp(entry,"time")==0)
		{
			threading();
			displayTime();
		}
		else if(validConnection(location, entry)==0)		//if entry was true
		{
			location=changeRooms(entry);
			pathTaken[steps]=location;
			steps++;
		}
		else
		{
			printf("HUH? I DON'T UNDERSTAND THAT INPUT. TRY AGAIN\n");
		}
		if(gameRooms[location].whatIsIt==END_ROOM)
		{
			isGameOver=0;
		}
	}while(isGameOver!=0);
	printf("YOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n");
	if(steps==1)
	{
		printf("YOU TOOK %d STEP. YOUR PATH TO VICTORY WAS:\n",steps);
	}
	else
	{
		printf("YOU TOOK %d STEPS. YOUR PATH TO VICTORY WAS:\n",steps);
	}
	int j;
	for(j=0;j<steps;j++)
	{
		printf("%s\n",gameRooms[pathTaken[j]].name);
	}
}
int main()
{
	playGame();
	return 0;
}
