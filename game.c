#include <game.h>
#include <string.h>

void m_game_print_result(m_314x *m_game, bool m_graphics, bool m_upscale)
{
	int i, j;

	if (!m_graphics && m_upscale)
	{
		printf("Can't upscale text-only board!\n");
	}
	else
	{
		printf("Current game:\n\n");

		printf("┌");
		for (i = 0; i <= (m_game->m_cols) * (m_upscale ? 2 : 1) * (m_graphics ? 1 : 2) + (m_graphics ? 1 : 0); i++) { printf("─"); }
		printf("┐\n");

		for (i = 0; i < m_game->m_rows; i++)
		{
			printf("│ ");
			for (j = 0; j < m_game->m_cols; j++)
			{
				if (m_game->m_board[i * m_game->m_cols + j] == 1)
				{
					if (m_graphics)
					{
						if (m_upscale)
						{
							printf("██");
						}
						else
						{
							printf("█");
						}
						
					}
					else
					{
						if (m_upscale)
						{
							printf("1  ");
						}
						else
						{
							printf("1 ");
						}
					}
					
				}
				else
				{
					if (m_graphics)
					{
						if (m_upscale)
						{
							printf("  ");
						}
						else
						{
							printf(" ");
						}
					}
					else
					{
						if (m_upscale)
						{
							printf("0  ");
						}
						else
						{
							printf("0 ");
						}
					}
				}
				
			}
			if (m_graphics) printf(" ");
			printf("│\n");
		}

		printf("└");
		for (i = 0; i <= (m_game->m_cols) * (m_upscale ? 2 : 1) * (m_graphics ? 1 : 2) + (m_graphics ? 1 : 0); i++) { printf("─"); }
		printf("┘\n");
	}
}

char* m_game_calc_aux_string(char *m_string)
{
	char *m_return;

	int m_num = 0;

	bool m_prev = false;

	printf("Processing: %s\n", m_string);

	while (*m_string != '\0')
	{
		if (*m_string == '1')
		{
			m_num++;
			m_prev = true;
		}
		else
		{
			m_prev = false;
			
			m_num = 0;
		}
		
		if (m_prev)
		{

		}

		// Increment the string pointer
		*m_string++;
	}

	printf("Number of 1's: %d\n", m_num);

	exit(1);

	return m_return;
}

void m_game_calc_rows(m_314x *m_game)
{
	unsigned int m_current_row = 0;


	char *m_current_string, current_char[2];
	current_char[1] = '\0';



	m_game->m_calculated_rows = malloc(m_game->m_rows * sizeof(char*));

	for (int i = 1; i < m_game->m_rows; i++)
	{
		m_current_string = (char *) malloc(2);

		strcpy(m_current_string, "\0");

		for (int j = 0; j < m_game->m_cols; j++)
		{
			current_char[0] = m_game->m_board[i * m_game->m_cols + j] + '0';

			m_current_string = (char *) realloc(m_current_string, strlen(m_current_string) + 2);

			strcat(m_current_string, current_char);
		}

		printf("Current string: %s\n", m_current_string);

		// Now process the string :)

		m_current_string = m_game_calc_aux_string(m_current_string);

		//m_game->m_calculated_rows[m_current_row] = malloc(strlen(m_current_string) * sizeof(char));


		free(m_current_string);

		m_current_row++;
	}

}

void m_game_calc_cols(m_314x *m_game)
{

}

void m_game_calc(m_314x *m_game)
{

	m_game_calc_rows(m_game);
	m_game_calc_cols(m_game);

}
