/*
		Creator: Richard Chaidez
		Date: September 18 2016
		Project: Project 1, Logging Utility
		Description: 
			Program implements the logging utility whose template is provided in program 2.13 in the textbook "Unix systems programming" 
			This program is meant for debugging purposes. If for example a file does not exist in the directory, the system will display and
			log the error message using the utilites provided.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>  
#include "log.h"
 
 /* gives the useful message describing the function of all the command line arguments*/
void hOpt(void)
{
	printf("-h: a useful message describing the function of all the command line arguments should be displayed\n");
	printf("-n: command line parameter that should set a variable in your program to the integer x\n");
	printf("	default value of this variable should be 42\n");
	printf("-l: filename command will set the name of the log file\n");
	
	return;
}
 
int main( int argc, char * argv[] )
{
	extern char *optarg;
	extern int optind;
	int c, err = 0; 
	int nvar = 42;	/*default value of x variable*/
	char *fname = "logfile.txt";	/*default value of filename*/
	
	/*using getpot has options for -h with no arg -n and -l with args*/
	while ((c = getopt(argc, argv, "hn:l:")) != -1)
		switch (c) {
		case 'h':
			hOpt();
			break;
		case 'n':
			nvar = atoi(optarg);
			break;
		case 'l':
			fname = optarg;
			break;
		case '?':
			err = 1;
			break;
		}

	/*testing variables */
	if (optind < argc)	/* more arguments than asked for */
		for (; optind < argc; optind++)
			printf("argument: \"%s\"\n", argv[optind]);
	else {
		printf("no arguments left to process\n");
	}
	/*create new data set*/
	data_t test;
    int return_value;
	 
	char xnum[3];
	itoa(nvar, xnum, 10);
	test.string = ("x variable = %d\n", xnum);
	addmsg(test);
	/*open file*/
	FILE *fp;

   /* now let's try to open same file that does not exist */
   fp = fopen("file.txt", "r");
   int errnum;
   if( fp == NULL ) 
   {
	  
    errnum = errno;
    perror("Error: ");
	test.string = (stderr, strerror( errnum ));
	addmsg((test));
   }
	/*close file*/
   fclose(fp);
   
   /*dividing by zero example*/
   int dividend = 15;
   int divisor = 0;
   int quot;
   int errnum2;
   if(divisor == 0)
   {
	errnum2 = errno;
	perror("Error: Can't divid by zero! ");
	test.string = (stderr, strerror(errnum2));
	addmsg(test);
   }
  
   
	if((return_value = savelog(argv,fname)) == -1)
	{
		test.string = "something went wrong with the text file\n";
		addmsg(test);
	}
	printf("\nREVIECED FROM LOG FILE\n");
	char *msgs = getlog();
    printf("%s\n", msgs);
    free(msgs);
	clearlog();
    return 0;
}