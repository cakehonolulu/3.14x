#include <stdio.h>

int main(int argc, char **argv)
{
	printf("3.14X - A C, Console, Picross Game\n");

	if (argc > 1)
	{
		FILE *m_game = fopen(argv[1], "r");

		if (m_game != NULL)
		{
		}
		else
		{
			printf("Could not open the file!\n");
		}
	}
	else
	{
		printf("\nUsage:\n");
		printf("314x [filename]\n");
		printf("\nWhere:\n");
		printf("[filename]: File containing the game to play.\n");
	}

	return 0;
}
