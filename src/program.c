#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <malloc.h>
#include <string.h>

#define RESULT_STRING_LENGTH 32

double calculate_by_rectangle_method(double left_border, double right_border, unsigned int number_of_segments)
{
	double sum = 0;
	double step = (right_border - left_border) / number_of_segments;
	for (unsigned int i = 1; i <= number_of_segments; i++)
	{
		double current_x = left_border + (step * i);
		double previous_x = current_x - step;
		sum += sin((previous_x + current_x) / 2) * step;
	}
	return sum;
}

double calculate_by_simpsons_rule(double left_border, double right_border, unsigned int number_of_segments)
{
	double sum = 0;
	double step = (right_border - left_border) / 2 / number_of_segments;
	for (unsigned int i = 1; i <= number_of_segments * 2; i += 2)
	{
		double current_x = left_border + (step * i);
		double previous_x = current_x - step;
		double next_x = current_x + step;
		sum += ((step / 3) * (sin(previous_x) + 4 * sin(current_x) + sin(next_x)));
	}
	return sum;
}

void free_results(char** results, unsigned int results_count)
{
	for (unsigned int i = 0; i < results_count; i++)
	{
		if (results[i] != NULL)
		{
			free(results[i]);
			results[i] = NULL;
		}
	}
	free(results);
}

char** calculate_and_print(double left_border, double right_border, unsigned int* segments, unsigned int array_length_of_segments)
{
	char** results = (char**)malloc(sizeof(char*) * array_length_of_segments);
	if (!results)
	{
		return NULL;
	}

	for (unsigned int j = 0; j < array_length_of_segments; j++)
	{
		double sum = calculate_by_rectangle_method(left_border, right_border, segments[j]);
		double sum1 = calculate_by_simpsons_rule(left_border, right_border, segments[j]);
		char* result = (char*)malloc(sizeof(char) * RESULT_STRING_LENGTH);

		if (!result)
		{
			free_results(results, array_length_of_segments);
			return NULL;
		}
		results[j] = result;
		sprintf(result, "%-4d %.5lf %.5lf", segments[j], sum, sum1);
	}
	return results;
}

int input_and_calculate(unsigned int* segments, unsigned int array_length_of_segments)
{
	double left_border;
	double right_border;

	printf("Enter the left border of the interval:\n");
	scanf("%lf", &left_border);
	printf("You entered: %lf\n", left_border);

	printf("Enter the right border of the interval:\n");
	scanf("%lf", &right_border);
	printf("You entered: %lf\n", right_border);

	if (left_border < right_border && left_border >= 0 && right_border <= M_PI)
	{
		printf("The left and right borders are entered correctly.\n");
		char** results = calculate_and_print(left_border, right_border, segments, array_length_of_segments);
		if (results == NULL)
		{
			printf("Memory error");
			return 0;
		}

		for (unsigned int i = 0; i < array_length_of_segments; i++)
		{
			printf("%s\n", results[i]);
		}

		free_results(results, array_length_of_segments);
	}
	else
	{
		printf("Please enter the values of the left and right borders in the range 0 <= a < b <= Pi.\n");
	}
	printf("Try again? Enter 1 or 0.\n");

	int x;
	scanf("%d", &x);

	if (x == 1)
		return 1;
	else
		return 0;
}

int main()
{
	unsigned int segments[] = { 6, 10, 20, 100, 500, 1000 };
	int array_length_of_segments = (sizeof(segments) / sizeof(segments[0]));

	while (input_and_calculate(segments, array_length_of_segments));

	return 0;
}
