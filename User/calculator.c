#include "calculator.h"

char *data;

void extractData(Command command){
		data=command.answer+6;
}

int calculateValue(Command command){
	extractData(command);
	int value;
	int a,b,c,d;
	char *A,*B,*C,*D;
	
	switch(command.id){
		case 13:
			A=data;
			sscanf(A, "%x", &value);
			return value;
			break;
		case 12:
			A=data;
			B=data+2;
			sscanf(A, "%x", &a);
			sscanf(B, "%x", &b);
			value=(256*a+b)/4;
			return value;
			break;
	}
	
			
}



