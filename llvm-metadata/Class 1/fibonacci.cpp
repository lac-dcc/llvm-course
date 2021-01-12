#include<iostream>

int main(int argc, char** argv){
	int i, Current = 1, Previous = 0, PreviousPrevious;
	for(i = 1; i < atoi(argv[1]); i++){
		PreviousPrevious = Previous;
		Previous = Current;
		Current = PreviousPrevious + Previous;
	}

	std::cout << "The " << i <<"nth Fibonacci number is " << Current <<"\n";
	return 0;
}
