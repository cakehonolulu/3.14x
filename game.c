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
			m_max_len = m_game_calc_max_hint_len(m_game, rows);
			
			for (i = 0; i <= (m_max_len + 2); i++)
			{
				printf(" ");
			}

			printf("┌");
			for (i = 0; i <= ((m_game->m_cols) * (m_upscale ? 2 : 1) * (m_graphics ? 1 : 2) + (m_graphics ? 1 : 0)); i++) { printf("─"); }
			printf("┐\n");
						
			for (i = 0; i <= (m_max_len + 2); i++)
			{
				printf(" ");
			}

			printf("│ ");


			m_max_len = m_game_calc_max_hint_len(m_game, columns);

			i = 0;

			if (m_max_len > 1)
			{
				for (int x = 0; x < m_game->m_cols; x++)
				{
					if (strlen(m_game->m_calculated_cols[x] < 2))
					{
						
					}
				}
			}
			else
			{
				for (int x = 0; x < m_game->m_cols; x++)
				{
					// Graphics no upscale
					if (!m_upscale && m_graphics)
					{
						printf("%s", m_game->m_calculated_cols[x]);
					}
					else
					// Upscaled graphics
					if (m_upscale && m_graphics)
					{
						printf("%s ", m_game->m_calculated_cols[x]);
					}
					else
					// Text mode
					{
						printf("%s ", m_game->m_calculated_cols[x]);
					}			
				}
			}

			if (!m_upscale && m_graphics)
			{
				printf(" ");
			}
			else
			if (m_upscale && m_graphics)
			{
				printf(" ");
			}

			printf("│\n");


			//printf("Max len: %d\n", m_max_len);
			//exit(1);

			m_max_len = m_game_calc_max_hint_len(m_game, rows);

			//printf("m_max_len: %d, m_cols: %d, no_sum: %d, calc: %d\n\n", m_max_len, m_game->m_cols, ((m_game->m_cols) * (m_upscale ? 2 : 1) * (m_graphics ? 1 : 2) + (m_graphics ? 1 : 0)), ((m_game->m_cols) * (m_upscale ? 2 : 1) * (m_graphics ? 1 : 2) + (m_graphics ? 1 : 0) + (m_max_len + 3)));

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

char *m_game_calc_aux_string(char *m_string, char *m_return)
{
	int m_num = 0;

	bool m_prev = false;

	char current_char[2];
	current_char[1] = '\0';
	
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
				m_return = realloc(m_return, (strlen(m_return) + 3));
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

void m_game_calc_line(m_314x *m_game, m_data_type m_type)
{
	char *m_current_string, *m_return, current_char[2];
	current_char[1] = '\0';

#ifdef DEBUG
	if (m_type == rows)
	{
		printf("Rows: %d\n", m_game->m_rows);
	}
	else
	if (m_type == columns)
	{
		printf("Cols: %d\n", m_game->m_cols);
	}
#endif

	if (m_type == rows)
	{
#ifdef DEBUG
		printf("Row Mem Size: %lu\n", (m_game->m_rows * sizeof(char *)));
#endif
		m_game->m_calculated_rows = malloc(m_game->m_rows * sizeof(char *));
	}
	else
	if (m_type == columns)
	{
#ifdef DEBUG
		printf("Col Mem Size: %lu\n", (m_game->m_cols * sizeof(char *)));
#endif
		m_game->m_calculated_cols = malloc(m_game->m_cols * sizeof(char *));
	}

	if (m_type == rows)
	{
		for (int i = 0; i < m_game->m_rows; i++)
		{
			m_return = (char *) malloc(2);
			m_current_string = (char *) malloc(2);

			strcpy(m_current_string, "\0");

			for (int j = 0; j < m_game->m_cols; j++)
			{
				if (m_type == rows)
				{
					current_char[0] = m_game->m_board[i * m_game->m_cols + j] + '0';
				}
				else
				if (m_type == columns)
				{
					current_char[0] = m_game->m_board[i * m_game->m_cols + j] + '0';
				}

				m_current_string = (char *) realloc(m_current_string, (strlen(m_current_string) + 2));

				strcat(m_current_string, current_char);
			}

#ifdef DEBUG
			printf("Current string: %s, Length: %lu\n", m_current_string, strlen(m_current_string));
#endif
			m_return = m_game_calc_aux_string(m_current_string, m_return);

			free(m_current_string);

#ifdef DEBUG
			printf("Modified string: %s, Length: %lu\n", m_return, strlen(m_return));
#endif

			m_game->m_calculated_rows[i] = malloc((strlen(m_return) + 1) * sizeof(char));
			strcpy(m_game->m_calculated_rows[i], m_return);

#ifdef DEBUG
			printf("Calculated %d row: %s\n\n\n", i + 1, m_game->m_calculated_rows[i]);
#endif

			free(m_return);
		}
	}
	else
	if (m_type == columns)
	{
		for (int i = 0; i < m_game->m_cols; i++)
		{
			m_return = (char *) malloc(2);
			m_current_string = (char *) malloc(2);

			strcpy(m_current_string, "\0");

			for (int j = 0; j < m_game->m_rows; j++)
			{
				current_char[0] = m_game->m_board[i * m_game->m_cols + j] + '0';

				m_current_string = (char *) realloc(m_current_string, (strlen(m_current_string) + 2));

				strcat(m_current_string, current_char);
			}

#ifdef DEBUG
			printf("Current string: %s, Length: %lu\n", m_current_string, strlen(m_current_string));
#endif
			m_return = m_game_calc_aux_string(m_current_string, m_return);

			free(m_current_string);

#ifdef DEBUG
			printf("Modified string: %s, Length: %lu\n", m_return, strlen(m_return));
#endif

			m_game->m_calculated_cols[i] = malloc((strlen(m_return) + 1) * sizeof(char));
			strcpy(m_game->m_calculated_cols[i], m_return);

#ifdef DEBUG
			printf("Calculated %d col: %s\n\n\n", i + 1, m_game->m_calculated_cols[i]);
#endif
			free(m_return);
		}
	}
}

void m_game_calc(m_314x *m_game)
{
	m_game_calc_line(m_game, rows);

	m_game_calc_line(m_game, columns);

	m_game_print_result(m_game, true, true, false);

	m_game_print_result(m_game, true, false, false);

	m_game_print_result(m_game, false, false, false);
}

unsigned char m_game_calc_max_hint_len(m_314x *m_game, m_data_type m_type)
{
	unsigned char m_max_len = 0;
	int i = 0;

	if (m_type == rows)
	{
		for (i = 0; i < m_game->m_rows; i++)
		{
			if (strlen(m_game->m_calculated_rows[i]) > m_max_len)
			{
				m_max_len = strlen(m_game->m_calculated_rows[i]);
			}
		}
	}
	else
	if (m_type == columns)
	{
		for (i = 0; i < m_game->m_cols; i++)
		{
			if (strlen(m_game->m_calculated_cols[i]) > m_max_len)
			{
				m_max_len = strlen(m_game->m_calculated_cols[i]);
			}
		}	
	}

	return m_max_len;
}
