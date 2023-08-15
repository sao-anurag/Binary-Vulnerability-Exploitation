#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <link.h>

#define SIZE 11

struct _users_t{
	char *name;
	int lvl;
} users[SIZE];

void adduser()
{
	int i=0, lvli;
	char *p = (char *) malloc(16);
	char lvl[2];

	printf("Enter user name\n");
	gets(p);

	printf("Enter user privilege level from 1 (highest) to 4 (lowest)\n");

	gets(lvl);
	lvli = atoi(lvl);

	while(i != SIZE){
		if(users[i].lvl == 0){
			users[i].name = p;
			users[i].lvl = lvli;
			p = NULL;
			break;
		}
		i++;
	}
	if (p != NULL){
		printf("Userlist full... user not added\n");
	}
}

void printuser()
{
	int i, j=1;

	for(i=0; i<SIZE; ++i){
		if (users[i].lvl != 0){
			printf("%d %s (%d) \n", j++, users[i].name, users[i].lvl);	
		}
	}
}

void removeuser()
{
	char n[2];
	int ni;

	printf("Enter user number to remove : ");
	gets(&n);
	ni = atoi(n)-1;
	if (ni >= SIZE){
		printf("Invalid number\n");
		return;	
	}

	free(users[ni].name);
	users[ni].lvl = 0;
}

int main(int argc, char **argv)
{
	struct link_map *lm = (struct link_map*) dlopen("libc.so.6", RTLD_NOW);
	printf("The libc is at %p\n", lm->l_addr);

    printf("What would you like to do?\n");

    char end=0;
	char option;

	while(!end){
		printf("....................\n");
		printf("[a]dd a user\n");
		printf("[r]emove a user\n");
		printf("[p]rint all users\n");
		printf("e[x]it program\n");
		gets(&option);

		switch(option){
		case 'a': adduser(); break;
		case 'r': removeuser(); break;
		case 'p': printuser("p\n"); break;
		case 'x': printf("That's all folks!\n"); end=1; break;
		default : printf("Invalid option\n"); break;
		}
	}
}