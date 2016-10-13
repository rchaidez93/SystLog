#ifndef LOG_H
#define LOG_H
#include <time.h>

typedef struct data_struct {
    time_t time;
    char *string;
} data_t;

int addmsg(data_t data);
void clearlog(void);
void test_me(void);
char *getlog(void);
int savelog(char **argv,char *filename);

#endif