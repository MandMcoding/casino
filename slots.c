#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
// #include unicode? UTF-8?

#define sym_num 3
#define col_num 3

int checkWin(char* state);

void print_help(char* exe_name);

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
    
int main(int argc, char** argv){
	// IO
	if (argc > 1) {
		if (strcmp(argv[1], "--help") == 0) {
			print_help(argv[0]);
			return 0;
		} else if (strcmp(argv[1], "--version") == 0) {
			printf("myprogram version 1.0.0\n");
			return 0;
		} else {
			printf("Unknown option: %s\n", argv[1]);
			printf("Try '--help' for more information.\n");
			return 1;
		}
	}

	// Setup
	time_t current_time = time(NULL);
	if(current_time == (time_t)-1){ perror("time"); return 0;} // Error check

	char input = '0';
	int wins = 0;
	int money = 0;

	printf("Welcome to slots!\nType q to stop, press anything to SPIN!!!\n");
	printf("First, how much money do you have?\nMoney: $");
	if(scanf(" %10d", &money) < 1) return 1;

	// Start and Continue spinning if you have money or stop if you quit
	while(money > 0 && (input != 'q' && input != 'Q')){
		// Input
		if(scanf(" %c", &input) < 1) return 1;
		clear_screen()

		//char symbols[sym_num] = {💀, 🧌, 🔫}; // UTF attempt
		char symbols[sym_num] = {'a', 'b', 'c'}; // Possible symbols/outcomes in a column
		char* outcome = (char*)calloc(col_num, sizeof(char)); // Array of char to save an outcome

		// One spin
		for(int col = 0; col < col_num; col++){
			outcome[col] = symbols[rand() % sym_num];
			printf("%c ", outcome[col]);
		}
		printf("\n");
		
		// Check if the spin is a win
		if(checkWin(outcome)){ 
			wins++;
			money += 5;
			printf("CONGRATS!!!\nYOU ARE AT %d WINS!!!\nYou won $5 and now have $%d\n", wins, money);
		}
		else{
			money -= 1;
			printf("$%d\n", money);
		}
	}
	printf("Total Wins: %d\n", wins);
	return 0;
}

// Checks if the outcome was a win (1) or not (0) using col_num
// WARNING: col_num must match the size of the state array
int checkWin(char* state){
	if(col_num <= 1) return 0; // Check if valid amount
	// To check a win with a variable number of columns, check if each symbol matches the last until the end
	// You can't do outcome[0] == outcome[1] == outcome[n]
	for(int col = 1; col < col_num; col++){
		if(state[col-1] != state[col]) return 0;
	}
	return 1;
}

// TODO all these IO features 😂
void print_help(char* exe_name) {
	printf("Usage: %s [OPTIONS]\n"
		"A terminal slot machine program.\n"
		"For normal terminal usage, put no arguments\n"
		"In the input file the format is the same as the IO / command line usage.\n\n"
		"Options:\n"
		"  --help       Display this help and exit\n"
		"  --version    Display version information and exit\n"
		"  -i           Input file\n"
		"  -o           Output file\n"
		"  -m           Starting money (-1 or none for until spins run out)\n"
		"  -s           Number of spins (-1 or none for until money runs out)\n"
		"  --reels or columns or spinners Set how many reels are used\n"
		"  --symbols    Define your own symbol set by using the format [sym1,sym2,...,symn]\n", exe_name);
}
