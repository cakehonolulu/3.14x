#include <functions.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	FILE *m_game;

	m_314x m_picross;

	printf("3.14X - A C, Console, Picross Game\n");

	if (argc > 1)
	{
		m_game = fopen(argv[1], "r");

		if (m_game != NULL)
		{
			m_picross = m_init_engine(m_game);
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
