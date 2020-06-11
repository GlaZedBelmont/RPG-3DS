#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct node{
    int data;
    struct node *next;
}*head[5];

void create(int count, int maxElements)
{
//    int n2 = 6;
    struct node *temp;
    for(int j = 0; j < maxElements; j++)
    {
        if (head[count] == NULL)
        {
            temp = (struct node*)malloc(sizeof(struct node));
            temp->data = j + 5 + count;
            temp->next = NULL;
            head[count] = temp;
        }
        else
        {
            temp->next = (struct node*)malloc(sizeof(struct node));
            temp = temp->next;
            temp->data = j + 5 + count;
            temp->next = NULL;
        }
    }
}

void print(int count, int* length)
{
    struct node *temp;
    temp = head[count];
    //for (int i = 0; i <)
    for (int a = 0; a < count; a++)
    {
        printf("%d %d\n", a, length[a]);
        for (int j = 0; j < length[j]; j++)
        {
            printf("[%d]", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
/*    while (temp != NULL)
    {
        printf("[%d]", temp->data);
        temp = temp->next;
    }*/
}

int main(int argc, char* argv[])
{
    FILE *fp;
    int tile, amount, x, y;
    int count = 0;
    int count2 = 0;
    int linesCount = 0;

    char ch;
    char line[256];
    char *token;


    fp = fopen("test.map", "rb");
    printf("Testing map parsing: \n\n");

    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n')
            linesCount++;
    }
    printf("linesCount: %i\n", linesCount);

    int *map[linesCount];

    int *lenMap = malloc(sizeof(int));

    rewind(fp);

    int i = 0;
    while (fgets(line, sizeof(line), fp)) {
        //printf("Parsing %s", line);
        head[i] = NULL;
        struct node *temp;

        token = strtok(line, "[]\n");
        printf("%i.", count);
        while (token != NULL) { // Each time this breaks, next line is parsed
            if (strcmp(token, " ") != 0) {
                sscanf(token, "%dx%d", &tile, &amount); 
                //printf("[Line #%ix%i]. [%dx%d]\n", count, count2, tile, amount);

                //map[i] = (int *)malloc(amount * sizeof(int));
                
                count2 += amount;
                
                for (int a = 0; a < linesCount; a++)
                {
                    
                    for (int j = 0; j < amount; j++)
                    {
                        //printf("[%d]", tile);
                        
                        
                        if (head[a] == NULL) {
                            
                            temp = (struct node*)malloc(sizeof(struct node));
                            temp->data = tile;
                            temp->next = NULL;
                            head[a] = temp;
                        }
                        else {
                            
                            temp->next = (struct node*)malloc(sizeof(struct node));
                            temp = temp->next;
                            temp->data = tile;
                            temp->next = NULL;
                        }
                    }
                    
                    //map[i][j] = tile;
                    //printf("[%d]", map[i][j]);
                    
                   
                }
                
            }
            
            i++;
            printf(" || ");  
            token = strtok(NULL, "[]\n");
        }
        lenMap[count] = count2;
        count2 = 0;
        printf("\n");
        
        count++;
    }
    printf("\nI see %i blocks\n", i);
    fclose(fp);
    printf("\n");


    for (int h = 0; h < count; h++) {
        printf("%d\n", lenMap[h]);
    }
    
/*    for (int h = 0; h < count; h++) {
        printf("%i.", lenMap[h]);
        for (int j = 0; j < lenMap[h]; j++) {
            printf("[%d]", map[h][j]); 
        }
        printf("\n");
    }*/
    
   for (int i = 0; i < linesCount; i++)
    {
/*        head[i] = NULL;
        struct node *temp;
        for (int j = 0; j < lenMap[i]; j++)
        {
            if (head[i] == NULL)
            {
                temp = (struct node*)malloc(sizeof(struct node));
                temp->data =  j;
                temp->next = NULL;
                head[i] = temp;
            }
            else
            {
                temp->next = (struct node*)malloc(sizeof(struct node));
                temp = temp->next;
                temp->data = j;
                temp->next = NULL;
            }
        }*/
        //create(i, 5);
        print(i, lenMap);
        printf("\n\n");
    }  

    return 0;
}

/* Example of the data structure
    0:  [][]
    1:  [][][]
    2:  [][][][][]
    3:  [][]
    4:  []
*/