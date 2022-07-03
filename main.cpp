#include <iostream>

int main(){
	int *ptr =(int*) malloc(sizeof(int));
	free(ptr);
	return 0;
}
