#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void read_input(FILE* input, int*** classTimeArrays, int*** classLength Arrays, int numClasses, int numDays, char firstDay, int numHours, int firstHour, int firstMin , int periodsPerHour);
void generate_schedule(int numClasses, int numDays, int numHours, int periodsPerHour, int* numOptions, int*** classTimeArrays, int*** classLengthArrays, int** schedule);
int** blank_schedule(int numDays, int numHours, int periodsPerHour);
void free_schedule(int** schedule, int numDays);
void print_schedule(int** schedule, int numDays, int numHours, int periodsPerHour);
void free_class_times(int*** classTimes, int numClasses, int numDays);


const FILE* output = fopen("output_schedule.txt", "w");

int main(int argc, const char* argv[]) {
	if (argc < 1) {
		printf("Error, no input file name.\n");
		return EXIT_FAILURE;
	}
	FILE* input = fopen(argv[1], "r");
	if (input == NULL) {
		printf("Error, could not open input file.\n");
		return EXIT_FAILURE;
	}
	int numClasses = 1;
	int numDays = 5;
	int numHours = 10;
	int periodsPerHour = 2;
	int** schedule = blank_schedule(numDays, numHours, periodsPerHour);
	int numOptions[] = {
		6
	};
	int*** classTimeArrays = (int***)malloc(sizeof(*classTimeArrays) * numClasses);
	for (int i = 0; i < numClasses; ++i) {
		classTimeArrays[i] = (int**)malloc(sizeof(*classTimeArrays[i]) * numDays);
		for (int j = 0; j < numDays; ++j) {
			classTimeArrays[i][j] = (int*)malloc(sizeof(*classTimeArrays[i][j]) * numOptions[i]);
		}
	}

	int*** classLengthArrays = (int***)malloc(sizeof(*classLengthArrays) * numClasses);
	for (int i = 0; i < numClasses; ++i) {
		classLengthArrays[i] = (int**)malloc(sizeof(*classLengthArrays[i]) * numDays);
		for (int j = 0; j < numDays; ++j) {
			classLengthArrays[i][j] = (int*)malloc(sizeof(*classLengthArrays[i][j]) * numOptions[i]);
		}
	}

	read_input(input, NULL, NULL, 1, 5, 'M', 10, 8, 30, 2);
	// generate_schedule(numClasses, numDays, numHours, periodsPerHour, numOptions, classTimeArrays, classLengthArrays, schedule);
	free(schedule);
	free_class_times(classTimeArrays, numClasses, numDays);
	free_class_times(classLengthArrays, numClasses, numDays);
	fclose(input);
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
			fprintf(output, "%d ", schedule[j][i]);
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
			/* Check for overlap */
			for (int j = 0; j < numDays; ++j) {
				abort = false;
				int start = classTimeArrays[numClasses - 1][j][i];
				int end = start + classLengthArrays[numClasses - 1][j][i];
				for (int k = start; k < end; ++k) {
					if (schedule[j][k] != 0) {
						abort = true;
						break;
					}
				}
				if (abort) {
					break;
				}
			}
			/* Add if no overlap */
			if (!abort) {
				for (int j = 0; j < numDays; ++j) {
					int start = classTimeArrays[numClasses - 1][j][i];
					int end = start + classLengthArrays[numClasses - 1][j][i];
					for (int k = start; k < end; ++k) {
						schedule[j][k] = numClasses;
					}
				}
			}
			else {
				continue;
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

void read_input(FILE* input, int*** classTimeArrays, int*** classLengthArrays, int numClasses, int numDays, char firstDay, int numHours, int firstHour, int firstMin, int periodsPerHour) {
	int numLines = _count_lines(input);
	int lineLen = 8 + 5 + 1 + 5;
	char** lines = malloc(sizeof(*lines) * numLines);
	for (int i = 0; i < numLines; ++i) {
		lines[i] = malloc(sizeof(*lines[i]) * lineLen);
		fgets(lines[i], lineLen, input);
		printf("%s", lines[i]);
	}
}

int _count_lines(FILE* file) {
	int count = 0;
	int pos = SEEK_CUR;
	fseek(file, 0, SEEK_SET);
	while (!feof(file)) {
		char temp = fgetc(file);
		if (temp == '\n') {
			++count;
		}
	}
	fseek(file, 0, pos);
	return count;
}

int _round_to(int value, int round) {
	int lower = (value % round) * round;
	int upper = lower + round;
	if (abs(lower - value) < abs(upper - value)) {
		return lower;
	}
	else {
		return upper;
	}
}