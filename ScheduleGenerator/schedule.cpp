#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define TOTAL_MINUTES 60
#define TOTAL_HOURS   12

struct Time {
	int value;
	struct Time* next;
	struct Time* prev;
};

struct Day {
	char value;
	struct Day* next;
	struct Day* prev;
};

void read_input(FILE* input, int*** classTimeArrays, int*** classLengthArrays, int* optionCount, int numClasses, int numDays, char firstDay, int numHours, int firstHour, int firstMin , int periodsPerHour);
void generate_schedule(int numClasses, int numDays, int numHours, int periodsPerHour, int* numOptions, int*** classTimeArrays, int*** classLengthArrays, int** schedule);
int** blank_schedule(int numDays, int numHours, int periodsPerHour);
void free_schedule(int** schedule, int numDays);
void print_schedule(int** schedule, int numDays, int numHours, int periodsPerHour);
void free_class_times(int*** classTimes, int numClasses, int numDays);
int _count_lines(FILE* file);
void _count_options(char** lines, int numLines, int numClasses, int* optionCount);
int _round_to(int value, int round);
int _count_hours(int start, int stop, struct Time* hour);
int _count_minutes(int start, int stop, struct Time* min);
int _count_days(char start, char stop, struct Day* day);
void _zero_string(char* string, int length);
void _zero_time_array(int*** array, int length, int width, int* depth);
void _zero_array(int* array, int length);

FILE* output = fopen("output_schedule.txt", "w");

int main(int argc, const char* argv[]) {
	if (!(argc > 1)) {
		printf("Error, no input file name.\n");
		return EXIT_FAILURE;
	}
	FILE* input = fopen(argv[1], "r");
	if (input == NULL) {
		printf("Error, could not open input file.\n");
		return EXIT_FAILURE;
	}
	int numClasses = 6;
	int numDays = 5;
	int numHours = 10;
	int periodsPerHour = 2;
	int** schedule = blank_schedule(numDays, numHours, periodsPerHour);
	int* numOptions = (int*)malloc(sizeof(*numOptions) * numClasses);
	int*** classTimeArrays = (int***)malloc(sizeof(*classTimeArrays) * numClasses);
	for (int i = 0; i < numClasses; ++i) {
		classTimeArrays[i] = (int**)malloc(sizeof(*classTimeArrays[i]) * numDays);
	}

	int*** classLengthArrays = (int***)malloc(sizeof(*classLengthArrays) * numClasses);
	for (int i = 0; i < numClasses; ++i) {
		classLengthArrays[i] = (int**)malloc(sizeof(*classLengthArrays[i]) * numDays);
	}

	read_input(input, classTimeArrays, classLengthArrays, numOptions, numClasses, numDays, 'M', numHours, 7, 30, periodsPerHour);
	generate_schedule(numClasses, numDays, numHours, periodsPerHour, numOptions, classTimeArrays, classLengthArrays, schedule);
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

void read_input(FILE* input, int*** classTimeArrays, int*** classLengthArrays, int* optionCount, int numClasses, int numDays, char firstDay, int numHours, int firstHour, int firstMin, int periodsPerHour) {
	int numLines    = _count_lines(input);
	int lineLen     = 8 + 5 + 1 + 5;
	char** lines    = (char**)malloc(sizeof(*lines) * numLines);
	for (int i = 0; i < numLines; ++i) {
		lines[i] = (char*)malloc(sizeof(*lines[i]) * lineLen);
		_zero_string(lines[i], lineLen);
		fgets(lines[i], lineLen, input);
	}
	_zero_array(optionCount, numClasses);
	_count_options(lines, numLines, numClasses, optionCount);
	for (int i = 0; i < numClasses; ++i) {
		printf("%d: %d\n", i + 1, optionCount[i]);
		for (int j = 0; j < numDays; ++j) {
			classTimeArrays[i][j]   = (int*)malloc(sizeof(*classTimeArrays[i][j]) * optionCount[i]);
			classLengthArrays[i][j] = (int*)malloc(sizeof(*classLengthArrays[i][j]) * optionCount[i]);
		}
	}
	_zero_time_array(classTimeArrays, numClasses, numDays, optionCount);
	_zero_time_array(classLengthArrays, numClasses, numDays, optionCount);
	
	/* Linked Lists of Days, Hours, and Minutes */

	struct Time* hour = (Time*)malloc(sizeof(*hour) * TOTAL_HOURS);
	for (int i = 0; i < TOTAL_HOURS; ++i) {
		hour[i].value = i + 1;
		if ((i + 1) == TOTAL_HOURS) {
			hour[i].next = &hour[0];
		}
		else {
			hour[i].next = &hour[i + 1];
		}
		if (i == 0) {
			hour[i].prev = &hour[TOTAL_HOURS - 1];
		}
		else {
			hour[i].prev = &hour[i - 1];
		}
	}
	struct Time* min = (Time*)malloc(sizeof(*min) * (TOTAL_MINUTES + 1));
	for (int i = 0; i < TOTAL_MINUTES + 1; ++i) {
		min[i].value = i;
		if (i == TOTAL_MINUTES) {
			min[i].next = &min[0];
		}
		else {
			min[i].next = &min[i + 1];
		}
		if (i == 0) {
			min[i].prev = &min[TOTAL_MINUTES];
		}
		else {
			min[i].prev = &min[i - 1];
		}
	}
	struct Day* day = (Day*)malloc(sizeof(*day) * 7);
	day[0].value = 'S';
	day[1].value = 'M';
	day[2].value = 'T';
	day[3].value = 'W';
	day[4].value = 'R';
	day[5].value = 'F';
	day[6].value = 'E';
	for (int i = 0; i < 7; ++i) {
		if ((i + 1) == 7) {
			day[i].next = &day[0];
		}
		else {
			day[i].next = &day[i + 1];
		}
		if (i == 0) {
			day[i].prev = &day[6];
		}
		else {
			day[i].prev = &day[i - 1];
		}
	}

	int   periodLen     = TOTAL_MINUTES / periodsPerHour;
	int   currentClass  = 0;
	int   currentOption = 0;
	char* classInfo     = (char*)malloc(sizeof(*classInfo) * lineLen);
	char* classDays     = (char*)malloc(sizeof(*classDays) * numDays);
	_zero_string(classDays, numDays);
	int   startHour     = 0;
	int   startMin      = 0;
	int   startPeriod   = 0;
	int   endHour       = 0;
	int   endMin        = 0;
	int   endPeriod     = 0;
	for (int i = 0; i < numLines; ++i) {
		if (isdigit(lines[i][0])) {
			currentClass = (int)lines[i][0] - 48;
			currentOption = 0;
		}
		else if (isspace(lines[i][0])) {
			currentClass = 0;
		}
		else if (isalpha(lines[i][0]) && (currentClass > 0 && currentClass <= numClasses)) {
			strcpy(classInfo, lines[i]);
			sscanf(classInfo, "%s %d:%d-%d:%d ", classDays, &startHour, &startMin, &endHour, &endMin);
			startPeriod = (_count_hours(firstHour, startHour, hour) * TOTAL_MINUTES + _count_minutes(firstMin, _round_to(startMin, 30), min)) / periodLen;
			endPeriod   = (_count_hours(firstHour, endHour, hour)   * TOTAL_MINUTES + _count_minutes(firstMin, _round_to(endMin, 30), min)) / periodLen;
			for (int j = 0; j < strlen(classDays); ++j) {
				int dayIndex = _count_days(firstDay, classDays[j], day);
				classTimeArrays[currentClass - 1][dayIndex][currentOption] = startPeriod;
				classLengthArrays[currentClass - 1][dayIndex][currentOption] = endPeriod - startPeriod;
			}
			++currentOption;
		}
	}
	for (int i = 0; i < numLines; ++i) {
		free(lines[i]);
	}
	free(lines);
	free(classInfo);
	free(hour);
	free(min);
	free(day);
}

int _count_lines(FILE* file) {
	int count = 0;
	fseek(file, 0, SEEK_SET);
	while (!feof(file)) {
		char temp = fgetc(file);
		if (temp == '\n') {
			++count;
		}
	}
	fseek(file, 0, SEEK_SET);
	return count;
}

void _count_options(char** lines, int numLines, int numClasses, int* optionCount) {
	int currentClass = 0;
	for(int i = 0; i < numLines; ++i) {
		if (isdigit(lines[i][0])) {
			currentClass = (int)lines[i][0] - 48;
		}
		if (isalpha(lines[i][0]) && (currentClass > 0 && currentClass <= numClasses)) {
			if (currentClass == 2) {
			}
			++(optionCount[currentClass - 1]);
		}
		if (isspace(lines[i][0])) {
			currentClass = 0;
		}
	}
}

int _round_to(int value, int round) {
	int lower = (value / round) * round;
	int upper = lower + round;
	if (abs(lower - value) < abs(upper - value)) {
		return lower;
	}
	else {
		return upper;
	}
}

int _count_hours(int start, int stop, struct Time* hour) {
	struct Time* currentHour = &hour[0];
	while (currentHour->value != start) {
		currentHour = currentHour->next;
	}

	int count = 0;
	while (currentHour->value != stop) {
		currentHour = currentHour->next;
		++count;
	}
	return count;
}

int _count_minutes(int start, int stop, struct Time* min) {
	struct Time* currentMin = &min[0];
	while (currentMin->value != start) {
		currentMin = currentMin->next;
	}

	int count = 0;
	while (currentMin->value != stop) {
		if (currentMin->value == TOTAL_MINUTES) {
			count -= TOTAL_MINUTES;
		}
		currentMin = currentMin->next;
		++count;
	}
	return count;
}

int _count_days(char start, char stop, struct Day* day) {
	struct Day* currentDay = &day[0];
	while (currentDay->value != start) {
		currentDay = currentDay->next;
	}

	int count = 0;
	while (currentDay->value != stop) {
		currentDay = currentDay->next;
		++count;
	}
	return count;
}

void _zero_string(char* string, int length) {
	for (int i = 0; i < length; ++i) {
		string[i] = '\0';
	}
}

void _zero_time_array(int*** array, int length, int width, int* depth) {
	for (int i = 0; i < length; ++i) {
		for (int j = 0; j < width; ++j) {
			for (int k = 0; k < depth[i]; ++k) {
				array[i][j][k] = 0;
			}
		}
	}
}

void _zero_array(int* array, int length) {
	for (int i = 0; i < length; ++i) {
		array[i] = 0;
	}
}