#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void generate_schedule(int numClasses, int* numOptions, int*** classTimeArrays, int** schedule);
int** blank_schedule();

int main(int argc, char* argv[]) {
	int** schedule = blank_schedule();
	generate_schedule(0, NULL, NULL, schedule);
	free(schedule);
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

void generate_schedule(int numClasses, int* numOptions, int*** classTimeArrays, int** schedule) {
	if ((numClasses > 0 && numOptions != NULL) && (classTimeArrays != NULL && schedule != NULL)) {
		for (int i = 0; i < numOptions[numClasses - 1]; ++i) {
			for (int j = 0; j < numDays; ++j) {
				int start = classTimeArrays[numOptions - 1][j][i];
				int end = start + classLengthArrays[numOptions - 1][j][i];
				bool abort = false;
				for (int k = start; k < end; ++k) {
					if (schedule[j][k] == 0) {
						abort = true;
						break;
					}
				}
				if (!abort) {
					for (int k = start; k < end; ++k) {
						schedule[j][k] = numClasses - 1;
					}
				}
				if (numClasses > 1) {
					generate_schedule(numClasses - 1, numOptions, classTimeArrays, schedule);
				}
			}
		}
	}
}