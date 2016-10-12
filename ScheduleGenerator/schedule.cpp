#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void generate_schedule(int numClasses, int numDays, int numHours, int periodsPerHour, int* numOptions, int*** classTimeArrays, int*** classLengthArrays, int** schedule);
int** blank_schedule(int numDays, int numHours, int periodsPerHour);
void free_schedule(int** schedule, int numDays);
void print_schedule(int** schedule, int numDays, int numHours, int periodsPerHour);
void free_class_times(int*** classTimes, int numClasses, int numDays);

FILE* output = fopen("output_schedule.txt", "w");

int main(int argc, char* argv[]) {
	int numClasses = 4;
	int numDays = 5;
	int numHours = 10;
	int periodsPerHour = 2;
	int** schedule = blank_schedule(numDays, numHours, periodsPerHour);
	int numOptions[] = {
		2,
		1,
		10,
		1
	};
	int*** classTimeArrays = (int***)malloc(sizeof(*classTimeArrays) * numClasses);
	for (int i = 0; i < numClasses; ++i) {
		classTimeArrays[i] = (int**)malloc(sizeof(*classTimeArrays[i]) * numDays);
		for (int j = 0; j < numDays; ++j) {
			classTimeArrays[i][j] = (int*)malloc(sizeof(*classTimeArrays[i][j]) * numOptions[i]);
		}
	}
	/* ECE 20200 */
	classTimeArrays[0][0][0] = 0;
	classTimeArrays[0][1][0] = 0;
	classTimeArrays[0][2][0] = 0;
	classTimeArrays[0][3][0] = 0;
	classTimeArrays[0][4][0] = 0;

	classTimeArrays[0][0][1] = 0;
	classTimeArrays[0][1][1] = 12;
	classTimeArrays[0][2][1] = 0;
	classTimeArrays[0][3][1] = 12;
	classTimeArrays[0][4][1] = 0;

	/* ECE 270 */
	classTimeArrays[1][0][0] = 18;
	classTimeArrays[1][1][0] = 0;
	classTimeArrays[1][2][0] = 18;
	classTimeArrays[1][3][0] = 0;
	classTimeArrays[1][4][0] = 18;

	classTimeArrays[2][0][0] = 0;
	classTimeArrays[2][1][0] = 0;
	classTimeArrays[2][2][0] = 0;
	classTimeArrays[2][3][0] = 0;
	classTimeArrays[2][4][0] = 0;

	classTimeArrays[2][0][1] = 0;
	classTimeArrays[2][1][1] = 8;
	classTimeArrays[2][2][1] = 0;
	classTimeArrays[2][3][1] = 0;
	classTimeArrays[2][4][1] = 0;

	classTimeArrays[2][0][2] = 0;
	classTimeArrays[2][1][2] = 14;
	classTimeArrays[2][2][2] = 0;
	classTimeArrays[2][3][2] = 0;
	classTimeArrays[2][4][2] = 0;

	classTimeArrays[2][0][3] = 0;
	classTimeArrays[2][1][3] = 0;
	classTimeArrays[2][2][3] = 0;
	classTimeArrays[2][3][3] = 0;
	classTimeArrays[2][4][3] = 0;

	classTimeArrays[2][0][4] = 0;
	classTimeArrays[2][1][4] = 0;
	classTimeArrays[2][2][4] = 6;
	classTimeArrays[2][3][4] = 0;
	classTimeArrays[2][4][4] = 0;

	classTimeArrays[2][0][5] = 0;
	classTimeArrays[2][1][5] = 0;
	classTimeArrays[2][2][5] = 12;
	classTimeArrays[2][3][5] = 0;
	classTimeArrays[2][4][5] = 0;

	classTimeArrays[2][0][6] = 0;
	classTimeArrays[2][1][6] = 0;
	classTimeArrays[2][2][6] = 0;
	classTimeArrays[2][3][6] = 0;
	classTimeArrays[2][4][6] = 0;

	classTimeArrays[2][0][7] = 0;
	classTimeArrays[2][1][7] = 0;
	classTimeArrays[2][2][7] = 0;
	classTimeArrays[2][3][7] = 8;
	classTimeArrays[2][4][7] = 0;

	classTimeArrays[2][0][8] = 0;
	classTimeArrays[2][1][8] = 0;
	classTimeArrays[2][2][8] = 0;
	classTimeArrays[2][3][8] = 0;
	classTimeArrays[2][4][8] = 6;

	classTimeArrays[2][0][9] = 0;
	classTimeArrays[2][1][9] = 0;
	classTimeArrays[2][2][9] = 0;
	classTimeArrays[2][3][9] = 0;
	classTimeArrays[2][4][9] = 12;

	/* ECE 36800 */
	classTimeArrays[3][0][0] = 0;
	classTimeArrays[3][1][0] = 15;
	classTimeArrays[3][2][0] = 0;
	classTimeArrays[3][3][0] = 15;
	classTimeArrays[3][4][0] = 0;

	int*** classLengthArrays = (int***)malloc(sizeof(*classLengthArrays) * numClasses);
	for (int i = 0; i < numClasses; ++i) {
		classLengthArrays[i] = (int**)malloc(sizeof(*classLengthArrays[i]) * numDays);
		for (int j = 0; j < numDays; ++j) {
			classLengthArrays[i][j] = (int*)malloc(sizeof(*classLengthArrays[i][j]) * numOptions[i]);
		}
	}
	/* ECE 20200 */
	classLengthArrays[0][0][0] = 2;
	classLengthArrays[0][1][0] = 0;
	classLengthArrays[0][2][0] = 2;
	classLengthArrays[0][3][0] = 0;
	classLengthArrays[0][4][0] = 2;

	classLengthArrays[0][0][1] = 0;
	classLengthArrays[0][1][1] = 3;
	classLengthArrays[0][2][1] = 0;
	classLengthArrays[0][3][1] = 3;
	classLengthArrays[0][4][1] = 0;

	/* ECE 270 */
	classLengthArrays[1][0][0] = 2;
	classLengthArrays[1][1][0] = 0;
	classLengthArrays[1][2][0] = 2;
	classLengthArrays[1][3][0] = 0;
	classLengthArrays[1][4][0] = 2;

	classLengthArrays[2][0][0] = 0;
	classLengthArrays[2][1][0] = 6;
	classLengthArrays[2][2][0] = 0;
	classLengthArrays[2][3][0] = 0;
	classLengthArrays[2][4][0] = 0;

	classLengthArrays[2][0][1] = 0;
	classLengthArrays[2][1][1] = 6;
	classLengthArrays[2][2][1] = 0;
	classLengthArrays[2][3][1] = 0;
	classLengthArrays[2][4][1] = 0;

	classLengthArrays[2][0][2] = 0;
	classLengthArrays[2][1][2] = 6;
	classLengthArrays[2][2][2] = 0;
	classLengthArrays[2][3][2] = 0;
	classLengthArrays[2][4][2] = 0;

	classLengthArrays[2][0][3] = 0;
	classLengthArrays[2][1][3] = 0;
	classLengthArrays[2][2][3] = 6;
	classLengthArrays[2][3][3] = 0;
	classLengthArrays[2][4][3] = 0;

	classLengthArrays[2][0][4] = 0;
	classLengthArrays[2][1][4] = 0;
	classLengthArrays[2][2][4] = 6;
	classLengthArrays[2][3][4] = 0;
	classLengthArrays[2][4][4] = 0;

	classLengthArrays[2][0][5] = 0;
	classLengthArrays[2][1][5] = 0;
	classLengthArrays[2][2][5] = 6;
	classLengthArrays[2][3][5] = 0;
	classLengthArrays[2][4][5] = 0;

	classLengthArrays[2][0][6] = 0;
	classLengthArrays[2][1][6] = 0;
	classLengthArrays[2][2][6] = 0;
	classLengthArrays[2][3][6] = 6;
	classLengthArrays[2][4][6] = 0;

	classLengthArrays[2][0][7] = 0;
	classLengthArrays[2][1][7] = 0;
	classLengthArrays[2][2][7] = 0;
	classLengthArrays[2][3][7] = 6;
	classLengthArrays[2][4][7] = 0;

	classLengthArrays[2][0][8] = 0;
	classLengthArrays[2][1][8] = 0;
	classLengthArrays[2][2][8] = 0;
	classLengthArrays[2][3][8] = 0;
	classLengthArrays[2][4][8] = 6;

	classLengthArrays[2][0][9] = 0;
	classLengthArrays[2][1][9] = 0;
	classLengthArrays[2][2][9] = 0;
	classLengthArrays[2][3][9] = 0;
	classLengthArrays[2][4][9] = 6;

	/* ECE 36800 */
	classLengthArrays[3][0][0] = 0;
	classLengthArrays[3][1][0] = 3;
	classLengthArrays[3][2][0] = 0;
	classLengthArrays[3][3][0] = 3;
	classLengthArrays[3][4][0] = 0;

	generate_schedule(numClasses, numDays, numHours, periodsPerHour, numOptions, classTimeArrays, classLengthArrays, schedule);
	free(schedule);
	free_class_times(classTimeArrays, numClasses, numDays);
	free_class_times(classLengthArrays, numClasses, numDays);
	fclose(output);
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
			fprintf(output, "%d", schedule[j][i]);
		}
		fprintf(output, "\n");
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
				fprintf(output, "\n");
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