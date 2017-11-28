#include <string.h>



typedef struct Command{
	int id;
	char *name;          //eg."speedRq"
	char *request;       //eg. 010C
	char *response;      //eg. 010c 41 00 12
	int responseType;    //0 - one bytes of data, 1- two bytes of data
	char* units;
}Command;

