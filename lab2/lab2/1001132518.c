#include <stdlib.h>
#include <stdio.h>

void readInput(int* n, int* m, int** S, int*** C);
void fillCostTable(int n, int m, int* S, int** C);
void printInput(int n, int m, int* S);
void printCostTable(int n, int m, int** C);
void printBacktrace(int n, int m, int* S, int** C);

int main(int argc, char** argv)
{
	int n;		// Size of input set
	int m;		// Target value
	int* S;		// Input set
	int** C;	// Cost table as 2D array (i x cardinality)

	readInput(&n, &m, &S, &C);
	fillCostTable(n, m, S, C);
	printInput(n, m, S);
	printCostTable(n, m, C);
	printBacktrace(n, m, S, C);
	printf("Enter number to exit: ");
	scanf("%d", &n);
	return 0;
}

void readInput(int* n, int* m, int** S, int*** C)
{
	scanf("%d", n);
	scanf("%d", m);

	*S = (int*)calloc(*n + 1, sizeof(int)); //n+1 to include 0 for base case
	*C = (int**)calloc(*m + 1, sizeof(int*)); //m+1 to include 0 for base case
	int i;
	for (i = 0; i <= *m; i++)
	{
		(*C)[i] = (int*)calloc(*n, sizeof(int));
	}

	if (!(*S) || !(*C))
	{
		printf("MALLOC FAILED.\nEnter number to quit.");
		scanf("%d", &i);
		exit(0);
	}

	(*S)[0] = 0;
	for (i = 1; i <= *n; i++)
	{
		scanf("%d", *S + i);
	}
}

void fillCostTable(int n, int m, int* S, int** C) //TODO: add portable calcCost function
{
	int i, card, potential_sum, leftover;

	// Initialize table for DP
  // DP base case
			   // For each potential sum, determine the smallest index such
			   // that its input value is in a subset to achieve that sum.
	for (i = 0; i < n; i++)
	{
		C[0][i] = n + 1; //Set all cardinalities at base case to no solution
	}

	for (potential_sum = 1; potential_sum <= m; potential_sum++)
	{
		for (card = 0; card < n; card++) // for cardinality 1, card = 0 cardinality = card + 1
		{
			for (i = 1; i <= n; i++)
			{
				leftover = potential_sum - S[i];      // To be achieved with other values
				if (card == 0 && leftover == 0) //At cardinality 1, pot_sum must be S[i]
				{
					break;
				}
				
				else if (card > 0 && leftover >= 0 &&               // Possible to have a solution
					     C[leftover][card - 1] < i)                 // Indices are included in
					break;                         // ascending order.
			}
			C[potential_sum][card] = i;
		}
	}
}

void printInput(int n, int m, int* S)
{
	printf("m is %d\n", m);
	printf("  i   S\n");
	printf("-------\n");
	int i;
	for (i = 0; i <= n; i++)
	{
		printf("%3d %3d\n", i, S[i]);
	}
}

void printCostTable(int n, int m, int** C)
{
	printf("   i   card  C\n");
	printf("-----------------\n");
	int i, card;
	for (i = 0; i <= m; i++)
	{
		for (card = 0; card < n; card++)
		{
			printf("%4d %4d %4d\n", i, card + 1, C[i][card]);
		}
	}
}

void printBacktrace(int n, int m, int* S, int** C)
{
	int card;
	for (card = 0; card < n; card++)
	{
		if (C[m][card] == n + 1)
		{
			printf("No solution with %2d elements\n", card+1);
		}
		else
		{
			printf("Solution with %2d elements\n", card + 1);
			printf("  i   S\n");
			printf("-------\n");
			int i = m, temp_card = card;
			while (i > 0 && temp_card >= 0)
			{
				printf("%3d %3d\n", C[i][temp_card], S[C[i][temp_card]]);
				i -= S[C[i][temp_card]];
				temp_card--;
			}
		}
	}
}