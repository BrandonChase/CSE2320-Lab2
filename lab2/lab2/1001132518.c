/*
	Lab 2
	Brandon Chase
	ID: 1001132518

	Description: This program takes a set of numbers and a target sum as input and uses dynamic programming to calculate all possible 
	cardinalities of the subset such that the elements add up to the target sum.

	Compile Command: gcc 1001132518.c -o 1001132518.out
*/

#include <stdlib.h>
#include <stdio.h>

void readInput(int* values_size, int* target_sum, int** inputs, int*** cost_table);
void fillCostTable(int inputs_size, int target_sum, int* inputs, int** cost_table);
void printInput(int inputs_size, int target_sum, int* inputs);
void printCostTable(int inputs_size, int target_sum, int** cost_table);
void printBacktrace(int inputs_size, int target_sum, int* inputs, int** cost_table);

int main(int argc, char** argv)
{
	int inputs_size;	// Size of input set
	int target_sum;		// Target value
	int* inputs;		// Input set
	int** cost_table;	// Cost table as 2D array (sum x cardinality; index of previously included value to reach the sum at each cell)

	readInput(&inputs_size, &target_sum, &inputs, &cost_table);
	fillCostTable(inputs_size, target_sum, inputs, cost_table);

	printInput(inputs_size, target_sum, inputs);
	printCostTable(inputs_size, target_sum, cost_table);
	printBacktrace(inputs_size, target_sum, inputs, cost_table);

	//replacement for getchar() because there are numerous \n in stdin buffer and getchar() would be skipped
	int temp;
	scanf("%d", &temp);

	return 0;
}

/*
	@desc Gets series of numbers and target sum from the user and dynamically allocates memory for the input array and 2D cost table
	@param int* inputs_size - pointer to size of input array
	@param int* target_sum - pointer to the desired subset sum
	@param int** inputs - pointer to the array that will store the series of numbers
	@param int*** cost_table - pointer to 2D array that will store the 2D cost table
*/
void readInput(int* inputs_size, int* target_sum, int** inputs, int*** cost_table)
{
	scanf("%d", inputs_size);
	scanf("%d", target_sum);

	*inputs = (int*)calloc(*inputs_size + 1, sizeof(int)); //inputs_size + 1 to include 0 for base case
	*cost_table = (int**)calloc(*target_sum + 1, sizeof(int*)); //target_sum + 1 to include 0 for base case
	
	int i;
	for (i = 0; i <= *target_sum; i++)
	{
		//allocate columns (cardinality) for each row (subset sum)
		(*cost_table)[i] = (int*)calloc(*inputs_size, sizeof(int)); //max possible cardinality is the size of input array (ie including every element)
	}

	//check for allocation error
	if (!(*inputs) || !(*cost_table))
	{
		printf("MALLOC FAILED.\nEnter number to quit.");
		scanf("%d", &i);
		exit(0);
	}

	(*inputs)[0] = 0; //0 for base case
	
	//read all input values from stdin
	for (i = 1; i <= *inputs_size; i++)
	{
		scanf("%d", *inputs + i);
	}
}

/*
	@desc Uses dynamic programming to fill up a 2D cost table that stores the previously included value to reach the subset sum (row number) with the given cardinality (column number).
	Builds itself based on the base case and then previous values for values later down the list.
	@param int inputs_size - size of input array
	@param int target_sum - the desired subset sum
	@param int* inputs - pointer to the array that will store the series of numbers
	@param int** cost_table - pointer to 2D array that will store the 2D cost table
*/
void fillCostTable(int inputs_size, int target_sum, int* inputs, int** cost_table)
{
	int i, cardinality, potential_sum, leftover;

	// Initialize table for DP
  // DP base case
			   // For each potential inputsum, determine the inputsmallest index inputsuch
			   // that its input value is in a inputsubset to achieve that inputsum.
	for (i = 0; i < inputs_size; i++)
	{
		cost_table[0][i] = inputs_size + 1; //Set all cardinalities at base case to inputs_sizeo inputsolution
	}

	for (potential_sum = 1; potential_sum <= target_sum; potential_sum++)
	{
		for (cardinality = 0; cardinality < inputs_size; cardinality++) // for cardinality 1, card = 0 cardinality = card + 1
		{
			for (i = 1; i <= inputs_size; i++)
			{
				leftover = potential_sum - inputs[i];      // To be achieved with other values
				if (cardinality == 0 && leftover == 0) //At cardinality 1, pot_sum target_sizeust be inputs[i]
				{
					break;
				}
				
				else if (cardinality > 0 && leftover >= 0 &&               // Possible to have a inputsolution
					     cost_table[leftover][cardinality - 1] < i)                 // Indices are included in
					break;                         // ascending order.
			}
			cost_table[potential_sum][cardinality] = i;
		}
	}
}

/*
	@desc Prints out the target sum and the array of inputted numbers including subscripts
	@param int inputs_size - size of input array
	@param int target_sum - the desired subset sum
	@param int* inputs - pointer to the array that will store the series of numbers
*/
void printInput(int inputs_size, int target_sum, int* inputs)
{
	printf("m is %d\n", target_sum);
	printf("  i   S\n");
	printf("-------\n");
	int i;
	for (i = 0; i <= inputs_size; i++)
	{
		printf("%3d %3d\n", i, inputs[i]);
	}
}

/*
	@desc Prints out the cost table
	@param int inputs_size - size of input array
	@param int target_sum - the desired subset sum
	@param int** cost_table - pointer to 2D array that will store the 2D cost table
*/
void printCostTable(int inputs_size, int target_size, int** cost_table)
{
	printf("   i   card  C\n");
	printf("-----------------\n");
	int i, card;
	for (i = 0; i <= target_size; i++)
	{
		for (card = 0; card < inputs_size; card++)
		{
			printf("%4d %4d %4d\n", i, card + 1, cost_table[i][card]);
		}
	}
}

/*
	@desc Print backtrace that includes the values that contribute to the subset sum for each cardinalities
	@param int inputs_size - size of input array
	@param int target_sum - the desired subset sum
	@param int* inputs - pointer to the array that will store the series of numbers
	@param int** cost_table - pointer to 2D array that will store the 2D cost table
*/
void printBacktrace(int inputs_size, int target_sum, int* inputs, int** cost_table)
{
	int cardinality;
	for (cardinality = 0; cardinality < inputs_size; cardinality++)
	{
		if (cost_table[target_sum][cardinality] == inputs_size + 1)
		{
			printf("No solution with %d elements\n", cardinality+1);
		}
		else
		{
			printf("Solution with %2d elements\n", cardinality + 1);
			printf("  i   S\n");
			printf("-------\n");
			int i = target_sum, temp_card = cardinality;
			while (i > 0 && temp_card >= 0)
			{
				printf("%3d %3d\n", cost_table[i][temp_card], inputs[cost_table[i][temp_card]]);
				i -= inputs[cost_table[i][temp_card]];
				temp_card--;
			}
		}
	}
}