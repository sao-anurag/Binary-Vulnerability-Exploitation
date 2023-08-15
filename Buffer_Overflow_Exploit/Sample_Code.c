#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_name(char *input){
	long canary= 0x87654321; 
	char buf[16];
	system("/bin/ls");
	strcpy(buf,input);
	

	printf("Welcome group %s.\n", buf);

	
	if (canary!=0x87654321) 
		exit(1); 
	
	
}
int main(int argc, char **argv){
	if(argc!=2)
	{
		printf("Usage:\n%s group_name\n", argv[0]);
		return EXIT_FAILURE;
	}
	get_name(argv[1]);
	return EXIT_SUCCESS;
}


