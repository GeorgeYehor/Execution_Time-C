#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>


clock_t start_time, finish_time, working_time;

int main(int argc, char** argv)
{
   
   FILE *fp;
   FILE *file_test;
   char *homedir = getenv("HOME");
   char filepath[70];
   char content[256];
   char* temp;
   int dec, sign;
   
   if (argc < 3 || argc > 3)
   {
      printf("Prosze podac argumenty w takiej postaci projekt.o <nazwa_pliku> <dokladnosc>\n");
      printf("Dokladnosc musi byc zapisana litera t lub s\n");
      return 1;
   }

   file_test = fopen(argv[1], "r");
   	if(file_test == NULL)
   	{
   		printf("Problem z uruchomieniem procesu\n");
   		return 1;
   	}
   pid_t pid = fork();
   start_time = clock();
   if(pid == 0)
   {	
   	execl(argv[1], "forked.out", NULL);
   }
   else
   {
   	waitpid(pid, 0, 0);
   }	
   	//printf("Start time %ld\n", start_time);
   	finish_time = clock();
   	//printf("Finish time %ld\n", finish_time);
   	
   	
   if(homedir != NULL)
   {	
   	strcpy(filepath, homedir);
   	strcat(filepath, "/results.txt");
   	fp = fopen(filepath, "a");
   	if(fp == NULL)
   	{
   		printf("Problem z otwarciem pliku\n");
   		return 1;
   	}
   	strcpy(content, "Czas pracy dla: ");
   	strcat(content, argv[1]);
   	strcat(content, " stanowi ");
   	if(strcmp(argv[2], "t") == 0)
   	{
   		working_time = (float)(finish_time - start_time);
   		printf("Czas pracy stanowi %ld tickow \n", working_time);
   	}
   	else if(strcmp(argv[2], "s") == 0)
   	{
   		working_time = (float)(finish_time - start_time)/CLOCKS_PER_SEC;
   		printf("Czas pracy %ld sekund\n", working_time);
   	}
   	else
   	{
   		printf("Wybrales bledna opcje dokladnosci \n");
   		return 1;
   	}
   	int temp1 = (int)working_time;
   	int digit_length = sizeof(temp1)/2;
   	temp = ecvt(working_time, digit_length, &dec, &sign);
   	strcat(content, temp);
   	if(strcmp(argv[2], "t") == 0)
   	{
   		strcat(content, " w 'ticks'");
   	}
   	else if(strcmp(argv[2], "s") == 0)
   	{
   		strcat(content, " w sekundach");
   	}
   	else
   	{
   		printf("Wybrales bledna opcje dokladnosci, nie mozna zapisac informacje do pliku \n");
   		return 1;
   	}
   	fprintf(fp, "%s \n", content);
   	fclose(fp);
   }

   return 0;
}
