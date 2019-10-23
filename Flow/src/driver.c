// driver.c

#include "../inc/graph.h"
#include "../inc/ff.h"
#include "../inc/dinic.h"
#include "../inc/push_relabel.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <ctype.h>

struct Graph DAGerate(int n);
int edgerate(int i, int j, int n);

int main(){
	char fname[25];
	puts("What is the file name?");
	fscanf(stdin,"%s",&fname);
	printf("Will open file:  %s\n",fname);
	int n;
	int num = 0;
	char* c = fname;
	while(1){
		if(!isdigit(*c)){
			//printf("%d\n",atoi(*c));
			if(*c == '\0' || *c == '\n')
				num = 1;
			else
				num = 0;
			break;
		}
		c++;
		//puts("c++");
	}
	if(num == 1){
		puts("number was given, generating random DAG");
		n = atoi(fname);
		struct Graph g = DAGerate(n);
		char outfile[25];
		sprintf(outfile, "%din.txt", n);
		FILE *out = fopen(outfile, "w");
		for(int i = 0; i < n; i++){
			fprintf(out, "%d ", i);
			for(int j = i + 1; j < n; j++){
				if(g.varr[i][j] > 0)
					fprintf(out, "%d:%d", j, g.varr[i][j]);
				if(j == n - 1)
					fprintf(out," ");
			}
			fprintf(out, "\n");
		}
		fclose(out);
		return 0;
	}
	//puts("loading graph...");
	struct Graph *ff = loadGraph(fname);
	//puts("loaded ff");
	struct Graph *dc = loadGraph(fname);
	struct Graph *pr = loadGraph(fname);
	//puts("Graph Loaded!");
	//printGraph(ff);
	
	clock_t start, end;
	double f,d,p;

	puts("starting Ford-Fulkerson...");
	start = clock();
	int flow = FF(*ff);
	end = clock();
	f = ((double)(end - start))/CLOCKS_PER_SEC;
	//printf("ford-fulk flow: %d\n",flow);
	
	puts("starting Dinic's...");
	start = clock();
	int flow2 = dinic(*dc);
	end = clock();
	d = ((double)(end - start))/CLOCKS_PER_SEC;
	//printf("dinic flow: %d\n", flow2);

	puts("starting Push-Relabel...");
	start = clock();
	int flow3 = pushRelabel(*pr);
	end = clock();
	p = ((double)(end - start))/CLOCKS_PER_SEC;
	//printf("push-relabel flow: %d\n",flow3);


	char ofname[50];
	sprintf(ofname, "%sout.txt", fname);
	FILE *out = fopen(ofname, "w");
	fprintf(out, "Ford-Fulkerson: %f\nDinic's: %f\nPush-Relabel: %f\n\nFlow: %d\n",f,d,p,flow2);
	//printf("ford-fulkerson: %d\ndinic's: %d\npush-relabel: %d\n",FF(ff), dinic(d), pushRelabel(pr));
	printf("FLOW: %d\n", flow2);
	fclose(out);
	return 0;
}

int edgerate(int i, int j, int n){
	if((i == 0 && j == 1) || (i == n-2 && j == n-1))
		return (rand() % 19) + 1;
	int zero = rand();
	if(zero > INT_MAX/3)
		return 0;
	else
		return (rand() % 19) + 1;
}

struct Graph DAGerate(int n){
	struct Graph DAG;
	initGraph(&DAG, n);
	int path[n];
	srand(time(0));
	int* hasNext = calloc(n, sizeof(int));
	int* hasPrev = calloc(n,sizeof(int));
	hasPrev[0]++;
	srand(time(0));

	for(int i = 0; i < n - 1;i++){
		for(int j = i + 1; j < n; j++){
			if(j - i <= 1){
				DAG.varr[i][j] = (rand() % 19) + 1;

			}
		}
	}
	//printGraph(DAG);

	/*for(int i = 0; i < n - 1; i++){
		while(hasNext[i] == 0){
			for(int j = i + 1; j < n; j++){
				//printf("%d ", hasPrev[i]);
				if(hasPrev[i] == 0){
					hasPrev[i]++;
					DAG.varr[j][i] = edgerate(0, 1, n);
				}
				
				int edge = edgerate(i, j, n);
				if(edge > 0){
					DAG.varr[i][j] = edge;
					hasNext[i]++;
					hasPrev[j]++;
					printGraph(DAG);
					puts("");
				}
			}
			
		}
	}
	/*do{
		for(int i = 0; i < n - 1; i++){
			//puts("for i...");
			while(hasNext[i] == 0 && nextConnected[i + 1] == 0){
				//puts("hasnext[i]...");
				for(int j = i + 1; j < n; j++){
					//while(nextConnected[j] == 0)
						DAG.varr[i][j] = edgerate(i, j, n);
						printf("[%d][%d] = %d\n",i,j,DAG.varr[i][j]);
						for(int k = 0; k <= i; k++)
							if(DAG.varr[k][i+1] > 0)
								nextConnected[i+1]++;
						if(DAG.varr[i][j] > 0)
							hasNext[i]++;
					//}
				}
			}
		}
	}while(!BFS(&DAG, path));*/
	return DAG;
}