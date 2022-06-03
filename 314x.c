#include <engine.h>
#include <game.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	// File Descriptor holding the game file
	FILE *m_game;

	// Game state skeleton
	m_314x m_picross;
	
	// The result of the game
	unsigned char m_game_result = 0;

	printf("3.14X - A C, Console, Picross Game\n");

	// Check if arguments are provided
	if (argc > 1)
	{
		// Open the file
		m_game = fopen(argv[1], "r");

		// Only continue if fopen() succeeded
		if (m_game != NULL)
		{
			// Try to initialize the game state
			m_picross = m_engine_init(m_game);

			// Sanitazion check in order to continue freely
			if (m_picross.m_cols != -1 && m_picross.m_rows != -1 && m_picross.m_cols != -1)
			{
				printf("Rows: %d, Columns: %d, Tries: %d\n", m_picross.m_rows, m_picross.m_cols, m_picross.m_atms);
				
				// Only continue if we don't recieve other-than-0 returns
				if (m_engine_load_board(&m_picross) == 0)
				{
					if (m_game_calc(&m_picross) == 0)
					{
						// Enter the game loop, assign the game result to a variable
						m_game_result = m_game_loop(&m_picross);

						// Based on that variable, display the status
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

					// Safely close the game engine
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
