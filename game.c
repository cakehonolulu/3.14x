#include <game.h>
#include <string.h>

void m_game_print_result(m_314x *m_game, bool m_graphics, bool m_upscale, bool m_have_calc_data)
{
	unsigned long m_max_len = 0;

	if (!m_graphics && m_upscale)
	{
		printf("Can't upscale text-only board!\n");
	}
	else
	{
		printf("Current game:\nGraph? %d; Upscale?  %d\n\n", m_graphics, m_upscale);

		if (m_have_calc_data)
		{
			m_max_len = m_game_calc_max_hint_len(m_game, false);

			printf("┌");
			for (int i = 0; i <= ((m_game->m_cols) * (m_upscale ? 2 : 1) * (m_graphics ? 1 : 2) + (m_graphics ? 1 : 0)); i++) { printf("─"); }
			printf("┐\n");

			m_max_len = m_game_calc_max_hint_len(m_game, true);

			//printf("Len: %d\n", m_max_len);
			for (unsigned long p = 0; p < m_max_len ; p += 2)
			{
				printf("│ ");
				for (int x = 0; x < m_game->m_cols; x++)
				{
					//printf("String: %s; Size: %lu\n", m_game->m_calculated_cols[x], strlen(m_game->m_calculated_cols[x]));
					//if (strlen(m_game->m_calculated_cols[x]) < m_max_len)
					//{
					if (isdigit(m_game->m_calculated_cols[x][p]))
					{
						if (m_graphics && !m_upscale)
						{
							printf("%c", m_game->m_calculated_cols[x][p]);
						}
						else
						{
							printf("%c ", m_game->m_calculated_cols[x][p]);
						}							
					}
					else
					{
						if (m_graphics == true && m_upscale == false)
						{
							printf(" ");
						}
						else
						{
							printf("  ");
						}
					}
				}
				
				if (m_graphics == true && m_upscale == false)
				{
					printf(" │\n");
				}
				else
				if (m_graphics == true && m_upscale == true)
				{
					printf(" │\n");
				}
				else
				if (m_graphics == false && m_upscale == false)
				{
					printf("│\n");
				}
			}

			m_max_len = m_game_calc_max_hint_len(m_game, false);

			printf("┌");
			for (unsigned long i = 0; i <= ((m_game->m_cols) * (m_upscale ? 2 : 1) * (m_graphics ? 1 : 2) + (m_graphics ? 1 : 0) + (m_max_len + 3)); i++) { printf("─"); }
			printf("┐\n");
		}
		else
		{
			printf("┌");
			for (int i = 0; i <= ((m_game->m_cols) * (m_upscale ? 2 : 1) * (m_graphics ? 1 : 2) + (m_graphics ? 1 : 0)); i++) { printf("─"); }
			printf("┐\n");
		}

		for (int i = 0; i < m_game->m_rows; i++)
		{	
			printf("│ ");
			
			for (char j = 0; j < m_game->m_cols; j++)
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
			
			if (m_have_calc_data)
			{
				printf("│ %s ", m_game->m_calculated_rows[i]);

				if (strlen(m_game->m_calculated_rows[i]) < m_max_len)
				{
					for (unsigned long x = strlen(m_game->m_calculated_rows[i]); x < m_max_len; x++)
					{
						printf(" ");
					}
				}

				printf("│\n");
			}
			else
			{
				printf("│\n");
			}
		}

		printf("└");
		if (m_have_calc_data)
		{
			for (unsigned long i = 0; i <= ((m_game->m_cols) * (m_upscale ? 2 : 1) * (m_graphics ? 1 : 2) + (m_graphics ? 1 : 0) + (m_max_len + 3)); i++) { printf("─"); }
		}
		else
		{
			for (int i = 0; i <= (m_game->m_cols) * (m_upscale ? 2 : 1) * (m_graphics ? 1 : 2) + (m_graphics ? 1 : 0); i++) { printf("─"); }
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

unsigned m_game_calc_line(m_314x *m_game, bool m_rows)
{
	char *m_current_string, *m_return, current_char[2];
	unsigned char m_err = 0;
	
	current_char[1] = '\0';

#ifdef DEBUG
	if (m_rows)
	{
		printf("Rows: %d\n", m_game->m_rows);
	}
	else
	if (!m_rows)
	{
		printf("Cols: %d\n", m_game->m_cols);
	}
#endif

	if (m_rows)
	{
#ifdef DEBUG
		printf("Row Mem Size: %lu\n", (m_game->m_rows * sizeof(char *)));
#endif
		m_game->m_calculated_rows = malloc(m_game->m_rows * sizeof(char *));
	}
	else
	if (!m_rows)
	{
#ifdef DEBUG
		printf("Col Mem Size: %lu\n", (m_game->m_cols * sizeof(char *)));
#endif
		m_game->m_calculated_cols = malloc(m_game->m_cols * sizeof(char *));
	}

	if ((m_rows ? m_game->m_calculated_rows : m_game->m_calculated_cols) != NULL)
	{
		for (int i = 0; i < (m_rows ? m_game->m_rows : m_game->m_cols); i++)
		{
			m_return = (char *) malloc(2);
			m_current_string = (char *) malloc(2);

			if (m_return != NULL)
			{
				if (m_current_string != NULL)
				{
					strcpy(m_current_string, "\0");

					for (int j = 0; j < (m_rows ? m_game->m_cols : m_game->m_rows); j++)
					{
						if (m_rows)
						{
							current_char[0] = m_game->m_board[i * m_game->m_cols + j] + '0';
						}
						else
						if (!m_rows)
						{
							current_char[0] = m_game->m_board[i + m_game->m_cols * j] + '0';
						}
							
						m_current_string = (char *) realloc(m_current_string, (strlen(m_current_string) + 2));

						strcat(m_current_string, current_char);
					}

#ifdef DEBUG
					printf("Current string: %s, Length: %lu\n", m_current_string, strlen(m_current_string));
#endif
					
					m_return = m_game_calc_aux_string(m_current_string, m_return);

					free(m_current_string);

					if (m_return != NULL)
					{
#ifdef DEBUG
						printf("Modified string: %s, Length: %lu\n", m_return, strlen(m_return));
#endif

						if (m_rows)
						{
							m_game->m_calculated_rows[i] = malloc((strlen(m_return) + 1) * sizeof(char));
						}
						else
						if (!m_rows)
						{
							m_game->m_calculated_cols[i] = malloc((strlen(m_return) + 1) * sizeof(char));
						}
							
						if ((m_rows ? m_game->m_calculated_rows[i] : m_game->m_calculated_cols[i]) != NULL)
						{
							if (m_rows)
							{
								strcpy(m_game->m_calculated_rows[i], m_return);
							}
							else
							if (!m_rows)
							{
								strcpy(m_game->m_calculated_cols[i], m_return);
							}
						}
						else
						{
							if (m_rows)
							{
								printf("Couldn't allocate space for the calculated row!\nExiting...\n");
								m_err = 1;
							}
							else
							if (!m_rows)
							{
								printf("Couldn't allocate space for the calculated column!\nExiting...\n");
								m_err = 1;
							}		
						}

#ifdef DEBUG
						if (m_rows)
						{
							printf("Calculated %d row: %s\n\n\n", i + 1, m_game->m_calculated_rows[i]);
						}
						else
						if (!m_rows)
						{
							printf("Calculated %d col: %s\n\n\n", i + 1, m_game->m_calculated_cols[i]);
						}
#endif

						free(m_return);
					}
					else
					{
						printf("Couldn't reallocate the returning string!\nExiting...\n");
						m_err = 1;
					}
				}
				else
				{
					printf("Couldn't allocate space for the current string!\nExiting...\n");
					m_err = 1;
				}
			}
			else
			{
				printf("Couldn't allocate space for the returned string!\nExiting...\n");
				m_err = 1;
			}
		}
	}
	else
	{
		printf("Couldn't allocate the row pointer array!\nExiting...\n");
		m_err = 1;
	}

	return m_err;
}

unsigned char m_game_calc(m_314x *m_game)
{
	unsigned char m_err = 0;

	if (m_game_calc_line(m_game, true) == 0)
	{
		if (m_game_calc_line(m_game, false) != 0)
		{
			m_err = 1;
		}
	}
	else
	{
		m_err = 1;
	}	

#ifdef DEBUG
	m_game_print_result(m_game, true, true, true);
	m_game_print_result(m_game, true, false, true);
	m_game_print_result(m_game, false, false, true);
#endif

	return m_err;
}

unsigned char m_game_calc_max_hint_len(m_314x *m_game, bool m_rows)
{
	unsigned char m_max_len = 0;
	int i;

	for (i = 0; i < (m_rows ? m_game->m_rows : m_game->m_cols); i++)
	{
		if (strlen((m_rows ? m_game->m_calculated_rows[i] : m_game->m_calculated_cols[i])) > m_max_len)
		{
			m_max_len = strlen((m_rows ? m_game->m_calculated_rows[i] : m_game->m_calculated_cols[i]));
		}
	}

	return m_max_len;
}
