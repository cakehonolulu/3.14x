#include <game.h>
#include <string.h>

void m_game_print_result(m_314x *m_game, bool m_graphics, bool m_upscale, bool m_have_calc_data)
{
	int i, j, m_max_len = 0;

	if (!m_graphics && m_upscale)
	{
		printf("Can't upscale text-only board!\n");
	}
	else
	{
		printf("Current game:\n\n");

		if (m_have_calc_data)
		{
			m_max_len = m_game_calc_max_hint_len(m_game);

			printf("m_max_len: %d, m_cols: %d, no_sum: %d, calc: %d\n\n", m_max_len, m_game->m_cols, ((m_game->m_cols) * (m_upscale ? 2 : 1) * (m_graphics ? 1 : 2) + (m_graphics ? 1 : 0)), ((m_game->m_cols) * (m_upscale ? 2 : 1) * (m_graphics ? 1 : 2) + (m_graphics ? 1 : 0) + (m_max_len + 3)));

			printf("┌");
			for (i = 0; i <= ((m_game->m_cols) * (m_upscale ? 2 : 1) * (m_graphics ? 1 : 2) + (m_graphics ? 1 : 0) + (m_max_len + 3)); i++) { printf("─"); }
			printf("┐\n");
		}
		else
		{
			printf("┌");
			for (i = 0; i <= ((m_game->m_cols) * (m_upscale ? 2 : 1) * (m_graphics ? 1 : 2) + (m_graphics ? 1 : 0)); i++) { printf("─"); }
			printf("┐\n");
		}

		for (i = 0; i < m_game->m_rows; i++)
		{
			if (m_have_calc_data)
			{
				printf("│ %s ", m_game->m_calculated_rows[i]);

				int x = strlen(m_game->m_calculated_rows[i]);

				if (x < m_max_len)
				{
					for (x; x < m_max_len; x++)
					{
						printf(" ");
					}
				}
			}
			
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
		if (m_have_calc_data)
		{
			for (i = 0; i <= ((m_game->m_cols) * (m_upscale ? 2 : 1) * (m_graphics ? 1 : 2) + (m_graphics ? 1 : 0) + (m_max_len + 3)); i++) { printf("─"); }
		}
		else
		{
			for (i = 0; i <= (m_game->m_cols) * (m_upscale ? 2 : 1) * (m_graphics ? 1 : 2) + (m_graphics ? 1 : 0); i++) { printf("─"); }
		}
		printf("┘\n");
	}
}

char* m_game_calc_aux_string(char *m_string)
{
	char *m_return;

	int m_num = 0;

	bool m_prev = false;

	char current_char[2];
	current_char[1] = '\0';
	
	m_return = (char *) malloc(2);

	strcpy(m_return, "\0");

	while (*m_string != '\0')
	{
		if (*m_string == '1')
		{
			m_num++;
			current_char[0] = m_num + '0';
			m_prev = true;
		}
		else
		{
			if (m_prev == true)
			{
				current_char[0] = m_num + '0';
				strcat(m_return, current_char);
				strcat(m_return, " ");
				m_num = 0;
			}

			m_prev = false;
		}
		
		// Increment the string pointer
		*m_string++;
	}

	if (m_num != 0)
	{
		strcat(m_return, current_char);
	}

	int length = strlen(m_return);

	if (length == 0)
	{
		strcat(m_return, "0");
	}

	if (m_return[strlen(m_return) - 1] == ' ')
	{
		m_return[strlen(m_return) - 1] = '\0';
	}

	return m_return;
}

void m_game_calc_rows(m_314x *m_game)
{
	char *m_current_string, current_char[2];
	current_char[1] = '\0';


	m_game->m_calculated_rows = malloc(m_game->m_rows * sizeof(char*));

	for (int i = 0; i < m_game->m_rows; i++)
	{
		m_current_string = (char *) malloc(2);

		strcpy(m_current_string, "\0");

		for (int j = 0; j < m_game->m_cols; j++)
		{
			current_char[0] = m_game->m_board[i * m_game->m_cols + j] + '0';

			m_current_string = (char *) realloc(m_current_string, strlen(m_current_string) + 2);

			strcat(m_current_string, current_char);
		}

		// Now process the string :)

		m_current_string = m_game_calc_aux_string(m_current_string);

		m_game->m_calculated_rows[i] = malloc(strlen(m_current_string) * sizeof(char));

		strcpy(m_game->m_calculated_rows[i], m_current_string);

		printf("Calculated %d row: %s\n", i + 1, m_game->m_calculated_rows[i]);

		free(m_current_string);
	}

}

void m_game_calc_cols(m_314x *m_game)
{
	char *m_current_string, current_char[2];
	current_char[1] = '\0';

	m_game->m_calculated_cols = malloc(m_game->m_cols * sizeof(char*));

	for (int i = 0; i < m_game->m_rows; i++)
	{

		m_current_string = (char *) malloc(2);

		strcpy(m_current_string, "\0");


		for (int j = 0; j < m_game->m_cols; j++)
		{
			current_char[0] = m_game->m_board[i + m_game->m_rows * j] + '0';

			m_current_string = (char *) realloc(m_current_string, strlen(m_current_string) + 2);

			strcat(m_current_string, current_char);
		}

		// Now process the string :)

		m_current_string = m_game_calc_aux_string(m_current_string);

		m_game->m_calculated_cols[i] = malloc(strlen(m_current_string) * sizeof(char));

		strcpy(m_game->m_calculated_cols[i], m_current_string);

		printf("Calculated %d col: %s\n", i + 1, m_game->m_calculated_cols[i]);

		free(m_current_string);
	}

}

void m_game_calc(m_314x *m_game)
{

	m_game_calc_rows(m_game);

	printf("\n\n");
	
	m_game_calc_cols(m_game);

	m_game_print_result(m_game, true, true, true);

	m_game_print_result(m_game, true, false, true);

	m_game_print_result(m_game, false, false, true);
}

unsigned char m_game_calc_max_hint_len(m_314x *m_game)
{
	unsigned char m_max_len = 0;
	int i = 0;

	for (i = 0; i < m_game->m_rows; i++)
	{
		if (strlen(m_game->m_calculated_rows[i]) > m_max_len)
		{
			m_max_len = strlen(m_game->m_calculated_rows[i]);
		}
	}

	return m_max_len;
}
