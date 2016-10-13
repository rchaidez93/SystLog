#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "log.h"

typedef struct list_struct {
    data_t item;
    struct list_struct *next;
} log_t;

/* Declarations of variables to track the head and tail of the linked list.*/
static log_t * headptr = NULL;
static log_t * tailptr = NULL;
 
/*allocate node for data and add to end of list*/
int addmsg( data_t data )
{
 
        /*Variable declaration*/
        log_t * newnode;
        int nodesize;
 
        /* Allocation of space for new node*/
        nodesize = sizeof( log_t ) + strlen( data.string ) + 1;
		/* Couldn't allocate space for new node*/
        if( ( newnode = ( log_t * )( malloc( nodesize ) ) ) == NULL ){
                return -1; 
		}
        /* Copying of data to newnode*/
        newnode->item.time = data.time;
        newnode->item.string = ( char * )newnode + sizeof( log_t );
        strcpy( newnode->item.string, data.string );
        newnode->next = NULL;
 
        /*Placement of newnode in the linked list*/
        if( headptr == NULL )
                headptr = newnode;
        else
                tailptr->next = newnode;
        tailptr = newnode;
 
        /* if function allocates memory successfully it returns 0*/
        return 0;
}
 /*Clear log */
void clearlog( void )
{
    log_t *next = headptr;
    while (next != NULL) {
        next = headptr->next;
        free(headptr);
        headptr = next;
    }
}
/*getlog*/
char * getlog(void)
{
    size_t len = 0;
    size_t msglen;
    size_t offset;
    log_t *node = headptr;
    char *log;
    while (node != NULL) {
        len += strlen(node->item.string);
        len++;
        node = node->next;
    }
    log = malloc(len);
    if (log == NULL) {
        perror("malloc failed while allocating memory for getlog");
        return NULL;
    }
    node = headptr;
    offset = 0;
    while(node) {
        msglen = strlen(node->item.string);
        memcpy(log + offset, node->item.string, msglen);
        offset += msglen;
        memcpy(log + offset, "\n", 1);
        offset++;
        node = node->next;
    }
    memcpy(log + offset - 1, "\0", 1);
    return log;
}
/*save log to file name logfile.txt*/
int savelog (char **argv, char* filename) 
{
	FILE *f;
    int error;
    log_t *node;
    if (filename == NULL) {
        errno = EINVAL;
        return -1;
    }
    f = fopen(filename, "w");
    if (f == NULL) {
        error = errno;
        perror("Failed to open");
        errno = error;
        return -1;
    }
    node = headptr;
    while (node) {
        char *time = ctime(&node->item.time);
        time[strlen(time) - 1] = 0;
        fprintf(f, "%s: %s: Error: %s\n",argv[0], time, node->item.string);

        node = node->next;
    }
    if (fclose(f)) {
        error = errno;
        perror("fclose failed in savelog");
        errno = error;
        return -1;
    }
   return 0;
}