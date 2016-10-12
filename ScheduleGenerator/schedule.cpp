#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void generate_schedule(int numClasses, int numDays, int numHours, int periodsPerHour, int* numOptions, int*** classTimeArrays, int*** classLengthArrays, int** schedule);
int** blank_schedule(int numDays, int numHours, int periodsPerHour);
void free_schedule(int** schedule, int numDays);
void print_schedule(int** schedule, int numDays, int numHours, int periodsPerHour);
void free_class_times(int*** classTimes, int numClasses, int numDays);

int main(int argc, char* argv[]) {
	int numClasses = 1;
	int numDays = 5;
	int numHours = 10;
	int periodsPerHour = 2;
	int** schedule = blank_schedule(numDays, numHours, periodsPerHour);
	int numOptions[] = {
		2
	};
	int*** classTimeArrays = (int***)malloc(sizeof(*classTimeArrays) * numClasses);
	for (int i = 0; i < numClasses; ++i) {
		classTimeArrays[i] = (int**)malloc(sizeof(*classTimeArrays[i]) * numDays);
		for (int j = 0; j < numDays; ++j) {
			classTimeArrays[i][j] = (int*)malloc(sizeof(*classTimeArrays[i][j]) * numOptions[i]);
		}
	}
	classTimeArrays[0][0][0] = 0;
	classTimeArrays[0][1][0] = 0;
	classTimeArrays[0][2][0] = 0;
	classTimeArrays[0][3][0] = 0;
	classTimeArrays[0][4][0] = 0;

	classTimeArrays[0][0][1] = 1;
	classTimeArrays[0][1][1] = 0;
	classTimeArrays[0][2][1] = 1;
	classTimeArrays[0][3][1] = 0;
	classTimeArrays[0][4][1] = 1;

	int*** classLengthArrays = (int***)malloc(sizeof(*classLengthArrays) * numClasses);
	for (int i = 0; i < numClasses; ++i) {
		classLengthArrays[i] = (int**)malloc(sizeof(*classLengthArrays[i]) * numDays);
		for (int j = 0; j < numDays; ++j) {
			classLengthArrays[i][j] = (int*)malloc(sizeof(*classLengthArrays[i][j]) * numOptions[i]);
		}
	}
	classLengthArrays[0][0][0] = 2;
	classLengthArrays[0][1][0] = 0;
	classLengthArrays[0][2][0] = 2;
	classLengthArrays[0][3][0] = 0;
	classLengthArrays[0][4][0] = 2;

	classLengthArrays[0][0][1] = 2;
	classLengthArrays[0][1][1] = 0;
	classLengthArrays[0][2][1] = 2;
	classLengthArrays[0][3][1] = 0;
	classLengthArrays[0][4][1] = 2;

	generate_schedule(1, numDays, numHours, periodsPerHour, numOptions, classTimeArrays, classLengthArrays, schedule);
	free(schedule);
	free_class_times(classTimeArrays, numClasses, numDays);
	free_class_times(classLengthArrays, numClasses, numDays);
	return EXIT_SUCCESS;
}

int** blank_schedule(int numDays, int numHours, int periodsPerHour) {
	int** schedule = (int**)malloc(sizeof(*schedule) * numDays);
	for (int i = 0; i < numDays; ++i) {
		schedule[i] = (int*)malloc(sizeof(*schedule[i]) * numHours * periodsPerHour);
		for (int j = 0; j < numHours * periodsPerHour; ++j) {
			schedule[i][j] = 0;
		}
	}
	return schedule;
}

void free_schedule(int** schedule, int numDays) {
	for (int i = 0; i < numDays; ++i) {
		free(schedule[i]);
	}
	free(schedule);
}

void print_schedule(int** schedule, int numDays, int numHours, int periodsPerHour) {
	for (int i = 0; i < numHours * periodsPerHour; ++i) {
		for (int j = 0; j < numDays; ++j) {
			printf("%d", schedule[j][i]);
		}
		printf("\n");
	}
}

void free_class_times(int*** classTimes, int numClasses, int numDays) {
	for (int i = 0; i < numClasses; ++i) {
		for (int j = 0; j < numDays; ++j) {
			free(classTimes[i][j]);
		}
		free(classTimes[i]);
	}
	free(classTimes);
}

void generate_schedule(int numClasses, int numDays, int numHours, int periodsPerHour, int* numOptions, int*** classTimeArrays, int*** classLengthArrays, int** schedule) {
	bool abort = false;
	if ((numClasses > 0 && numOptions != NULL) && (classTimeArrays != NULL && schedule != NULL)) {
		for (int i = 0; i < numOptions[numClasses - 1]; ++i) {
			for (int j = 0; j < numDays; ++j) {
				abort = false;
				int start = classTimeArrays[numClasses - 1][j][i];
				int end = start + classLengthArrays[numClasses - 1][j][i];
				/* Check for overlap */
				for (int k = start; k < end; ++k) {
					if (schedule[j][k] != 0) {
						abort = true;
					}
				}
				/* Add if no overlap */
				if (!abort) {
					for (int k = start; k < end; ++k) {
						schedule[j][k] = numClasses;
					}
				}
				else {
					break;
				}
			}
			if (numClasses > 1) {
				generate_schedule(numClasses - 1, numDays, numHours, periodsPerHour, numOptions, classTimeArrays, classLengthArrays, schedule);
			}
			else {
				print_schedule(schedule, numDays, numHours, periodsPerHour);
				printf("\n");
			}
			/* Undo action */
			for (int j = 0; j < numDays; ++j) {
				int start = classTimeArrays[numClasses - 1][j][i];
				int end = start + classLengthArrays[numClasses - 1][j][i];
				for (int k = start; k < end; ++k) {
					schedule[j][k] = 0;
				}
			}
		}
	}
}