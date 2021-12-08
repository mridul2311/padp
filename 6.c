#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<string.h>

char words[4][20]={"dolorem","bye","go","temp"};
int count[4];
char *fwords[1000];


void create(char *fn)
{
	FILE *fp=fopen(fn,"r");
	for(int i=0;i<1000;i++)
	{
		fwords[i]=malloc(128);
		fscanf(fp,"%s",fwords[i]);
	}
fclose(fp);
}

int determine(char *key)
{
	int wcount=0;
	for(int i=0;i<1000;i++)
	{
		if(strcmp(key,fwords[i])==0){
		wcount++;
		}	
	}
return wcount;
}

int main(int argc,char *argv[])
{
	printf("filename\ttime\tthreads\t\n");
	for(int k=1;k<=3;k++){
		create(argv[k]);
		for(int nt=1;nt<=8;nt=nt*2)
		{
			double start=omp_get_wtime();
			#pragma omp parallel for num_threads(nt)
			for(int i=0;i<4;i++)
				count[i]=determine(words[i]);
		
			double end=omp_get_wtime();
			printf("%s\t%lf\t%d\t\n",argv[k],(end-start),nt);
			printf("words matched = \t\n");
			for(int j=0;j<4;j++){
				printf("%s = %d\n",words[j],count[j]);
			}
		}
	for(int i=0;i<1000;i++)
		{
			free(fwords[i]);
		}
	}
}
