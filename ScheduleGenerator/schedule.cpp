#include <stdio.h>
#include <stdlib.h>

void generate_schedule(int numClasses, int* numOptions, int** classTimeArrays, int** schedule);
int** blank_schedule();

int main(int argc, char* argv[]) {
	return EXIT_SUCCESS;
}

int** blank_schedule() {
	int numDays = 5;
	int numHours = 10;
	int periodsPerHour = 2;
	int** schedule = malloc(sizeof(*schedule) * numDays));
	for (int i = 0; i < numDays; ++i) {
		schedule[i] = malloc(sizeof(*schedule[i]) * numHours * periodsPerHour);
		for (int j = 0; j < numHours * periodsPerHour; ++j) {
			schedule[i][j] = 0;
		}
	}
	return schedule;
}

void generate_schedule(int numClasses, int* numOptions, int** classTimeArrays, int** schedule) {

}