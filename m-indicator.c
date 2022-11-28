#include <stdio.h>
#define INFINITY 9999
#define MAX 22
int pos = 0, p = 0, process = 1;
int count;
char *stations[] = {"Kalyan", "Thakurli", "Dombivli", "Kopar", "Diva", "Mumbra", "Kalva", "Thane", "mulund", "nahur", "bhandup", "kanjurmarg", "vikhroli", "Ghatkopar", "vidyavihar"};
int G[MAX][MAX] =
    {
        {0, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {3, 1, 0, 1, 2, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 2, 1, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 3, 0, 2, 0, 1, 0, 2, 0, 0, 0, 0, 3, 0},
        {0, 0, 0, 0, 0, 0, 0, 2, 0, 1, 0, 0, 0, 2, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 3, 2, 0, 0, 0, 1, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},

};
void dijkstra(int G[MAX][MAX], int n, int startnode, int to);
void slowTrain(int from, int to);
void fastTrain(int G[MAX][MAX], int from, int to);
void semiFast(int G[MAX][MAX], int from, int to);

int main()
{

    int i, j, n, from, t;
    printf("Welcome to the  mini m-indicator for Kalyan to Vidyavihar");
    printf("--------------------------------------------------");
    while (process != 0)
    {

        printf("Enter\n1:Kalyan\n2:Thakurli\n3:Dombivli\n4:Kopar\n5:Diva\n6:Mumbra\n7:Kalva\n8:Thane\n9:Mulund\n10:Nahur\n11:Bhandup\n12:Kanjurmarg\n13:Vikhroli\n14:Ghatkopar\n15:Vidyavihar\n");
        printf("\nEnter the starting station:");
        scanf("%d", &from);
        printf("\nEnter the ending station:");
        scanf("%d", &t);
        printf("The stations along the slow track are:\n");
        slowTrain((from - 1), t);
        printf("\n");
        printf("\nThe stations along the fast track are:\n");
        printf("%s->", stations[from - 1]);
        fastTrain(G, (from - 1), t);
        printf("\n");
        printf("\nThe stations along the semi-fast track are:\n");
        printf("%s->", stations[from - 1]);
        semiFast(G, (from - 1), t);
        printf("\n");
        dijkstra(G, MAX, (from - 1), t);
        printf("\n");
        printf("Do you want to continue\nIf yes please press 1 else press 0\nYour choice:");
        scanf("%d", &process);
    }
    return 0;
}

void dijkstra(int G[MAX][MAX], int n, int startnode, int to)
{

    int cost[MAX][MAX], distance[MAX], pred[MAX];
    int visited[MAX], count, mindistance, nextnode, i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (G[i][j] == 0)
                cost[i][j] = INFINITY;
            else
                cost[i][j] = G[i][j];
    for (i = 0; i < n; i++)
    {
        distance[i] = cost[startnode][i];
        pred[i] = startnode;
        visited[i] = 0;
    }
    distance[startnode] = 0;
    visited[startnode] = 1;
    count = 1;
    while (count < n - 1)
    {
        mindistance = INFINITY;
        for (i = 0; i < n; i++)
            if (distance[i] < mindistance && !visited[i])
            {
                mindistance = distance[i];
                nextnode = i;
            }
        visited[nextnode] = 1;
        for (i = 0; i < n; i++)
            if (!visited[i])
                if (mindistance + cost[nextnode][i] < distance[i])
                {
                    distance[i] = mindistance + cost[nextnode][i];
                    pred[i] = nextnode;
                }
        count++;
    }
    for (i = (to - 1); i < to; i++)
    {
        if (i != startnode)
        {
            printf("\nIn Emergency??\nTry the shortest Path=>\t%s", stations[i]);
            j = i;
            do
            {
                j = pred[j];
                printf("<-%s", stations[j]);
            } while (j != startnode);
        }
    }
}

void slowTrain(int from, int to)
{
    if (from <= to)
    {
        for (int i = from; i <= (to - 1); i++)
        {
            if (i == (to - 1))
            {
                printf("%s", stations[i]);
            }
            else
                printf("%s->", stations[i]);
        }
    }
    else if (from >= to)
    {
        for (int i = from; i >= (to - 1); i--)
        {
            if (i == (to - 1))
            {
                printf("%s", stations[i]);
            }
            else
                printf("%s->", stations[i]);
        }
    }
}

void fastTrain(int G[MAX][MAX], int from, int to)
{
    count = 0;
    if (from < to)
    {
        for (int i = from; i < to; i++)
        {
            if (G[from][i] == 3)
            {

                if (i == to)
                {
                    pos = i;
                    printf("%s", stations[pos]);
                }
                else
                {
                    pos = i;
                    printf("%s->", stations[pos]);
                }

                fastTrain(G, pos, to);
            }
        }
    }

    else if (from > to)
    {
        for (int i = from; i >= (to - 1); i--)
        {
            if (G[from][i] == 3)
            {

                if (i == (to - 1))
                {
                    pos = i;
                    printf("%s", stations[pos]);
                }
                else
                {
                    pos = i;
                    printf("%s->", stations[pos]);
                }

                fastTrain(G, pos, to);
            }
        }
    }
}

void semiFast(int G[MAX][MAX], int from, int to)
{

    if (from < to)
    {
        for (int i = from; i < (to - 1); i++)
        {
            if (G[from][i] == 2)
            {
                if (i == 7)
                {
                    pos = i;
                    printf("%s", stations[pos]);
                }
                else
                {
                    pos = i;
                    printf("%s->", stations[pos]);
                }

                semiFast(G, pos, to);
            }
        }
    }
    else if (from > to)
    {
        for (int i = from; i >= (to - 1); i--)
        {
            if (G[from][i] == 2)
            {
                if (i == (to - 1))
                {
                    pos = i;
                    printf("%s", stations[pos]);
                }
                else
                {
                    pos = i;
                    printf("%s->", stations[pos]);
                }

                semiFast(G, pos, to);
            }
        }
    }
}