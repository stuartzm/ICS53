#include <stdio.h>
#include <string.h>

struct room
{
	int roomNumber;
	char description[300];
	int north;
	int south;
	int east;
	int west;
};

int getRooms(FILE* file, struct room* roomlist)
{
	struct room* roomsList = &(roomlist[0]);
	struct room currentRoom;
	int count = 0;
	if (file != NULL)
	{
	    char line[90];
	    while (fgets(line, sizeof(line), file) != NULL)
	    {
	    	struct room returnRoom;
	    	int errorCode = sscanf(line, "%d $%[^'$']$ %d %d %d %d", &returnRoom.roomNumber, &returnRoom.description, &returnRoom.north, &returnRoom.south, &returnRoom.east, &returnRoom.west);
	    	roomlist[count] = returnRoom;
	    	if (errorCode == EOF)
	    	{
	    		printf("The file is Incorrectly formated\n");
	    		fclose(file);
	    		return 0;
	    	}
	    	count++;
	    }
	}
	else
	{
	    printf("%s\n", "The File was loaded Incorrectly");
	    fclose(file);
	}
	return count;
}

void checkFileExists(FILE* file)
{
	if (file == NULL)
	{
		printf("You must first load a dungeon!\n");
	}
}

struct room move(char command, struct room currentRoom, struct room *roomlist, int size)
{
	struct room* roomsList = &(roomlist[0]);
	if (command == 'N')
	{
		if (currentRoom.north == -1)
		{
			printf("You can't go there.\n");
			return currentRoom;
		}
		else
		{
			int i;
			for (i = 0; i < size; i++)
			{
				if (currentRoom.north == roomsList[i].roomNumber)
				{
					printf("%s\n", roomsList[i].description);
					return roomsList[i];
				}
			}
		}
	}
	else if (command == 'E')
	{
		if (currentRoom.east == -1)
		{
			printf("You can't go there.\n");
			return currentRoom;
		}
		else
		{
			int i;
			for (i = 0; i < size; i++)
			{
				if (currentRoom.east == roomsList[i].roomNumber)
				{
					printf("%s\n", roomsList[i].description);
					return roomsList[i];
				}
			}
		}
	}
	else if (command == 'S')
	{
		if (currentRoom.south == -1)
		{
			printf("You can't go there.\n");
			return currentRoom;
		}
		else
		{
			int i;
			for (i = 0; i < size; i++)
			{
				if (currentRoom.south == roomsList[i].roomNumber)
				{
					printf("%s\n", roomsList[i].description);
					return roomsList[i];
				}
			}
		}
	}
	else if (command == 'W')
	{
		if (currentRoom.west == -1)
		{
			printf("You can't go there.\n");
			return currentRoom;
		}
		else
		{
			int i;
			for (i = 0; i < size; i++)
			{
				if (currentRoom.west == roomsList[i].roomNumber)
				{
					printf("%s\n", roomsList[i].description);
					return roomsList[i];
				}
			}
		}
	}
	else
	{
		printf("Something went wrong.\n");
	}
}

int main()
{
	char raw[100];
	char firstWord[50];
	char secondWord[50];
	struct room roomList[100];
	int size;
	int i;
	for (i = 0 ; i < 100; i++)
	{
		memset(roomList[i].description, 0, sizeof(roomList[i].description));
	}
	struct room currentRoom;
	FILE* file;
	file = fopen('\0',"r"); //This was a weird bug. Even tho I never assigned something, it had a length of 8. 
	
	while(1)
	{
		memset(firstWord, 0, sizeof(firstWord));
		memset(secondWord, 0, sizeof(secondWord));

		printf("$ ");
		fgets(raw, 200, stdin);

		if (!strcmp(raw,"\0"))
		{
			printf("Invalid Entry\n");
			continue;
		}

		sscanf(raw, "%50s %50s", firstWord, secondWord);

		if (!strcmp(firstWord,"loaddungeon"))
		{
			file = fopen(secondWord, "r");
			if (file == NULL)
			{
				printf("File incorrect\n");
				continue;
			}
			size = getRooms(file, roomList);
			currentRoom = roomList[0];
			printf("%s\n", currentRoom.description);
		}

		else if(!strcmp(secondWord,"\0") && !strcmp(firstWord,"north"))
		{
			checkFileExists(file);
			currentRoom = move('N', currentRoom, roomList, size);

		}

		else if (!strcmp(secondWord,"\0") && !strcmp(firstWord,"east"))
		{
			checkFileExists(file);
			currentRoom = move('E', currentRoom, roomList, size);		
		}

		else if (!strcmp(secondWord,"\0") && !strcmp(firstWord,"south"))
		{
			checkFileExists(file);
			currentRoom = move('S', currentRoom, roomList, size);		
		}

		else if (!strcmp(secondWord,"\0") && !strcmp(firstWord,"west"))
		{
			checkFileExists(file);
			currentRoom = move('W', currentRoom, roomList, size);		
		}

		else if (!strcmp(secondWord,"\0") && !strcmp(firstWord,"quit"))
		{
			break;			
		}

		else
		{
			printf("%s\n", "Invalid Command");			
		}
	}
	fclose(file);
	return 0;
}