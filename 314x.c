#include <engine.h>
#include <game.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	FILE *m_game;

	m_314x m_picross;

	printf("3.14X - A C, Console, Picross Game\n");

	unsigned char m_game_result = 0;

	if (argc > 1)
	{
		m_game = fopen(argv[1], "r");

		if (m_game != NULL)
		{
			m_picross = m_engine_init(m_game);

			if (m_picross.m_cols != -1 && m_picross.m_rows != -1 && m_picross.m_cols != -1)
			{
				printf("Rows: %d, Columns: %d, Tries: %d\n", m_picross.m_rows, m_picross.m_cols, m_picross.m_atms);
				
				if (m_engine_load_board(&m_picross) == 0)
				{
					if (m_game_calc(&m_picross) == 0)
					{
						m_game_result = m_game_loop(&m_picross);
						if (m_game_result == 0)
						{
							printf("You won!\n");
						}
						else
						if (m_game_result == 1)
						{
							printf("You lost... Better luck next time!\n");
						}
						else
						if (m_game_result == 2)
						{
							printf("User asked to leave the game; leaving...\n");
						}
						else
						if (m_game_result == 3)
						{
							printf("Program fault, exiting...\n");
						}
					}
					else
					{
						printf("There was an error processing the game files...\nExiting...\n");
					}

					m_engine_close(&m_picross);
				}
				else
				{
					printf("There was an error processing the board...\nExiting...\n");
				}
			}
			else
			{
				printf("There was an error parsing your file...\nExiting...\n");
			}
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
