#include <engine.h>
#include <game.h>
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
			m_picross = m_engine_init(m_game);

			if (m_picross.m_cols != -1 && m_picross.m_rows != -1 && m_picross.m_cols != -1)
			{
				printf("Rows: %d, Columns: %d, Tries: %d\n", m_picross.m_rows, m_picross.m_cols, m_picross.m_atms);
				m_engine_load_board(&m_picross);

				m_game_print_result(&m_picross, true, true);

				m_game_calc(&m_picross);

				m_engine_close(&m_picross);
			}
			else
			{
				printf("There was an error parsing your file...\nExiting...\n");
			}
			// Mock-up
			// m_print_game(m_picross);

			// Mock-up
			// m_start_game(m_picross);
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
