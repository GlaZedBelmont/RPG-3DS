#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <ctype.h>

#define NONE 0

struct node {
    int data;
    struct node *next;
}*head[5];

void printMap(int count, int* length, int x1, int x2, int y1, int y2)
{
    struct node *temp;
    
    for (int b = y1; b < (y2 > 0 ? y2 : count); b++)
    {
        temp = head[b];          
        //for (int c = x1; c < length[b]; c++)
        for (int a = 0; a < x1; ++a) {
            temp = temp->next;
        }
        for (int c = 0; c < (x2 > 0 ? x2 : length[b]); c++) // use x2 if it has a value
        { 
            printf("[%d]", temp->data);
            temp = temp->next;   
        }
        printf(" {%i}\n", length[b]);
    }
}

int main(int argc, char* argv[])
{
    FILE *mapFile; // Has the map, will implement selective map obv, we can't only use test.map lol
    int tile, amount; // Index of the tiles and how many times it's repeated
    int count = 0; // Keeps track of which line we're reading and the total amount of lines after the arrays are created
    int i = 0; // I have no real idea what we're using it for tbh, it counts how many [] we have
    int x1 = 0;
    int x2 = 0;
    int y1 = 0;
    int y2 = 0;
 
    char line[256]; // store the line
    char *token; // So we can split line in pieces
    
    int *lenMap = malloc(sizeof(int)); // Keeps track of the total amount per line but we can call it later
    
    struct node *map; // Store the map


    mapFile = fopen("test.map", "rb");
    printf("Testing map parsing: \n");

    while (fgets(line, sizeof(line), mapFile))
    {
        token = strtok(line, "[]\n");
        while (token != NULL) { // Each time this breaks, next line is parsed
            if (strcmp(token, " ") != 0)
            {
                head[i] = NULL;
                sscanf(token, "%dx%d", &tile, &amount);
                lenMap[count] += amount;
                    
                for (int j = 0; j < amount; j++)
                {
                    if (head[count] == NULL)
                    {      
                        map = (struct node*)malloc(sizeof(struct node));
                        map->data = tile;
                        map->next = NULL;
                        head[count] = map;
                    }
                    else
                    {   
                        map->next = (struct node*)malloc(sizeof(struct node));
                        map = map->next;
                        map->data = tile;
                        map->next = NULL;
                    }
                }   
            }
            i++;
            token = strtok(NULL, "[]\n");
        }
        count++;
    }
    printf("\nI see %i blocks in %i columns\n\n", i, count);
    fclose(mapFile);

    for (int h = 0; h < count; h++)
    {
        printf("%d => %d\ttiles\n", h, lenMap[h]);
    }
    printMap(count, lenMap, x1, x2, y1, y2);
    
    free(lenMap);
    return 0;
}


/* Example of the data structure
    0:  [][]
    1:  [][][]
    2:  [][][][][]
    3:  [][]
    4:  []
*/