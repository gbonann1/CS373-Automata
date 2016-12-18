#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct State
{
	int stateNumber;
	int accept;
	int reject;
	int start;
}State;

State * makeState(int q, int accept, int reject, int start)
{
	State *newState;
	newState = (State*)malloc(sizeof(State));
	newState->stateNumber = q;
	newState->accept = accept;
	newState->reject = reject;
	newState->start = start;
	return newState;
}

int main(int argc, char **argv)
{
	
	State* allStates[1000];
	State* currentState;
	char* input = argv[1];
	char* inputStr = argv[2];
	int maxTrans = atoi(argv[3]);
	int transCount = -1;
	FILE* inputFile;
	char* transition[maxTrans][5];	
	char* temp0;
	char* temp1;
	char* temp2;
	char* temp3;
	char* temp4;
	int v = 0;
	for (v; v < 1000; v++){
		State* newState = makeState(v, 0, 0, 0);	
		allStates[v] = newState;
	}
	
	inputFile = fopen(input, "r");
	if (inputFile == 0)
	{
		perror("Can't open file\n");
		exit(-1);	
	}
	else
	{
		char next[1000];
		//int counter = 0;
		while (fgets(next, 1000, inputFile) != NULL)
		{
			char *nextWord;
			nextWord = strtok(next, "\t");
			
			if (strcmp(nextWord, "state") == 0)
			{
				
				//counter++;
				nextWord = strtok(NULL, "\t");
				//puts(nextWord);
				int q = atoi(nextWord);
				nextWord = strtok(NULL, "\n");
				//puts(nextWord);
				if (strcmp(nextWord, "accept") == 0)
				{
					State* newState = makeState(q, 1, 0, 0);
					free(allStates[q]);	
					allStates[q] = newState;
				}
				else if (strcmp(nextWord, "reject") == 0)
				{
					State* newState = makeState(q, 0, 1, 0);
					free(allStates[q]);	
					allStates[q] = newState;
				}
				else if (strcmp(nextWord, "start") == 0)
				{
					State* newState = makeState(q, 0, 0, 1);
					free(allStates[q]);	
					allStates[q] = newState;
					currentState = newState;
				} 
				else	
				{
					State* newState = makeState(q, 0, 0, 0);
					free(allStates[q]);	
					allStates[q] = newState;
				}			
			}
			if (strcmp(nextWord, "transition") == 0)
			{
				//printf("\n");
				//setup 2d array of transitions
				transCount++;
				
				
				nextWord = strtok(NULL, "\t");
				temp0 = strdup(nextWord);
				//puts(nextWord);
				transition[transCount][0] = temp0;
				
				//printf("%c", *transition[transCount][0]);
				nextWord = strtok(NULL, "\t");
				temp1 = strdup(nextWord);
				//puts(nextWord);
				transition[transCount][1] = temp1;
				
				//printf("%c", *transition[transCount][1]);
				nextWord = strtok(NULL, "\t");
				temp2 = strdup(nextWord);
				//puts(nextWord);
				transition[transCount][2] = temp2;
				
				//printf("%c", *transition[transCount][2]);
				nextWord = strtok(NULL, "\t");
				temp3 = strdup(nextWord);
				//puts(nextWord);
				transition[transCount][3] = temp3;
				
				//printf("%c", *transition[transCount][3]);
				nextWord = strtok(NULL, "\n");
				temp4 = strdup(nextWord);
				//puts(nextWord);
				transition[transCount][4] = temp4;	
				
				//printf("%c", *transition[transCount][4]);	
				
								
			}
		}
				
	}	
	fclose(inputFile);
	/**
	int u = 0;
	int y = 0;
	char m = 'm';
	for (u = 0; u < 12; u++)
	{
		printf("\n");
		for (y = 0; y < 5; y++)
		{
			//transition[u][y] = &m;
			
			printf("%c", *transition[u][y]);
		

		}
	}**/
	
	int i = -1;
	int j;
	int counter = 1;
	//printf("%s", inputStr);
	//printf("%d", strlen(inputStr));
	int finish = 0;
	printf("%d", currentState->stateNumber);
	while (finish == 0)
	{	
		i++;
		
		if (counter > maxTrans) {
			printf(" quit\n");
			break;
		}

		if (i < 0 || i >= strlen(inputStr))
		{
			
			for (j = 0; j <= transCount; j++)
			{
			
				if ((atoi(transition[j][0]) == currentState->stateNumber) && (transition[j][1][0] == '_'))
				{	
					//printf("%c", transition[j][2]);
					//printf("%d\n", i);
					printf("->");
					currentState = allStates[atoi(transition[j][2])];
					printf("%d", currentState->stateNumber);
					
					if (currentState->accept == 1)
					{
						printf(" accept\n");
						finish = 1;
					
					}
					else if (currentState->reject == 1)
					{
						printf(" reject\n");
						finish = 1;
					}

					//inputStr[i] = transition[j][3][0];
					//printf("%c", transition[j][4][0]);
					if (transition[j][4][0] == 'L'){
						//printf("left");
						i = i - 2;
					}
					j = transCount + 1;
					counter++;
				}
			}
		}
		
		
		//refer to transitions 2d array to determine which state we transition to

		//SEARCHING 2D ARRAY TO FIND ROW CORRESPONDING TO CURRENT STATE AND SYMBOL
		else
		{
			
			for (j = 0; j <= transCount; j++)
			{
			
				//printf("%c", transition[j][1][0]);
				//printf("%c", inputStr[i]);
				//printf("%s", (transition[j][1]));	
				//printf("%d", currentState->stateNumber);		
				//printf("%d", atoi(transition[j][0]));
			
				if ((atoi(transition[j][0]) == currentState->stateNumber) && (transition[j][1][0] == inputStr[i]))
				{	
					//printf("%c", transition[j][2]);
					//printf("%d\n", i);
					printf("->");
					currentState = allStates[atoi(transition[j][2])];
					printf("%d", currentState->stateNumber);
					if (currentState->accept == 1)
					{
						printf(" accept\n");
						finish = 1;
					
					}
					else if (currentState->reject == 1)
					{
						printf(" reject\n");
						finish = 1;
					}

					inputStr[i] = transition[j][3][0];
					//printf("%c", transition[j][4][0]);
					if (transition[j][4][0] == 'L'){
						//printf("left");
						i = i - 2;
					}
					
					j = transCount + 1;
					counter++;
				}
		
			}
		}
			
		
	}
	i = 0;
	for (i; i < 1000; i++) {
		free(allStates[i]);
	}
	int u = 0;
	int y = 0;
	for (u = 0; u < transCount; u++)
	{
		for (y = 0; y < 5; y++)
		{			
			free(transition[u][y]);
		}
	}
	free(temp0);
	free(temp1);
	free(temp2);
	free(temp3);
	free(temp4);
	return 0;
				
}
