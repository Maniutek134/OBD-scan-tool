#include "calculator.h"

char dataBuffer[17];
char *data;


void extractData(Command command){
		int strLength1 =17;
		int strLength2=14;
	
		if(command.responseType==1){
			strncpy( dataBuffer , command.response ,strLength1);
			dataBuffer[16]='\0';
		}
		else if(command.responseType==0){
			strncpy( dataBuffer , command.response ,strLength2);
			dataBuffer[13]='\0';
		}
		data=dataBuffer+11;
		
}

int calculateValue(Command command){
	extractData(command);
	int value;
	int a,b,c,d;
	char *A,*B,*C,*D;
	A=data;
	
	switch(command.id){
		case 4:
			break;
			sscanf(A, "%x", &a);
			value=a*100/255;
			return value;
		
		case 5:
			sscanf(A, "%x", &a);
			value = a-40;
			return value;
			break;
			break;
		
		case 10:
			sscanf(A, "%x", &a);
			value=3*a;
			return value;
		
		case 12:
			B=data+2;
			sscanf(A, "%x", &a);
			sscanf(B, "%x", &b);
			value=(256*a+b)/4;
			return value;
			break;
		
		case 13:
			sscanf(A, "%x", &value);
			return value;
			break;
		
		
		case 15:
			sscanf(A, "%x", &a);
			value = a-40;
			return value;
			break;
		
	}
	
			
}



