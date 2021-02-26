#include<stdio.h>

int c1 = 17;

int main(){
	int c2 = 25;
	int c3 = c1 + c2;
	int *p1=&c2, p2;
	int out;
	c2=3;
	if(c3>41){
		out = c2;
		p2 = *p1;
	}
	else{
		out = c1;
		p1=&c3;
		p2 = out;
	}
	printf("C3= %d\n", c3);
	printf("Pointer= %d\n", *p1);
	printf("Output= %d\n", out);
	return 0;
}
