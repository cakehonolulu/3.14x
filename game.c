#include <game.h>
#include <string.h>

/*
	m_game_print_result

	Requires a m_game struct.

	There are different booleans that control the different ways of mangling the matrix data:
	m_graphics -> ASCII-way of displaying the matrix
	m_upscale (Depends on m_graphics == true) -> Upscales by 2 the matrix
	m_have_calc_data -> Prints hint rows/columns only if the data exists
	m_hide_output -> In-game use, displays the game's matrix (Filled with user interactions)
*/
void m_game_print_result(m_314x *m_game, bool m_graphics, bool m_upscale, bool m_have_calc_data, bool m_hide_output)
{
	unsigned long m_max_len = 0, i, j, k;

	// Sanity check
	if (!m_graphics && m_upscale)
	{
		printf("Can't upscale text-only board!\n");
	}
	else
	{
#ifdef DEBUG
		printf("Current game:\nGraph? %d; Upscale?  %d\n\n", m_graphics, m_upscale);
#endif

		// Check if we have calc'd data for in-game row/col hints
		if (m_have_calc_data)
		{
			// Calculate the max length of the rows
			m_max_len = m_game_calc_max_hint_len(m_game, false);

			// Start printing the UI
			printf("┌");
			for (i = 0; i <= ((unsigned long) ((m_game->m_cols) * (m_upscale ? 2 : 1) * (m_graphics ? 1 : 2) + (m_graphics ? 1 : 0))); i++) { printf("─"); }
			printf("┐\n");

			// Column hint printing algorithm
			for (j = 0; j <= m_max_len; j += 2)
			{
				printf("│ ");

				for (k = 0; k < ((unsigned long) m_game->m_cols); k++)
				{
					// Prevent heap-buffer-overflows
					if (strlen(m_game->m_calculated_cols[k]) >= j)
					{
						// Check if the currently processed number is a digit
						if (isdigit(m_game->m_calculated_cols[k][j]) != 0)
						{
							// Print it based on the functions flags
							if (m_graphics == false && m_upscale == false)
							{
								printf("%c ", m_game->m_calculated_cols[k][j]);
							}
							else
							if (m_graphics == true && m_upscale == false)
							{
								printf("%c ", m_game->m_calculated_cols[k][j]);
							}
							else
							if (m_graphics == true && m_upscale == true)
							{
								printf("%c  ", m_game->m_calculated_cols[k][j]);
							}
						}
					}
					else
					{
						// Print spaces if needed too
						if (m_graphics == false && m_upscale == false)
						{
							printf("  ");
						}
						else
						if (m_graphics == true && m_upscale == false)
						{
							printf("  ");
						}
						else
						if (m_graphics == true && m_upscale == true)
						{
							printf("   ");
						}
					}
				}
				
				// Print the ending graphic for columns
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

			m_max_len = m_game_calc_max_hint_len(m_game, true);

			printf("┌");
			for (i = 0; i <= ((m_game->m_cols) * (m_upscale ? 2 : 1) * (m_graphics ? 1 : 2) + (m_graphics ? 1 : 0) + (m_max_len + 3)); i++) { printf("─"); }
			printf("┐\n");
		}
		else
		{
			printf("┌");
			for (i = 0; i <= ((unsigned long) ((m_game->m_cols) * (m_upscale ? 2 : 1) * (m_graphics ? 1 : 2) + (m_graphics ? 1 : 0))); i++) { printf("─"); }
			printf("┐\n");
		}

		// If no calc data, print the matrix right away (Be it blank or loaded matrix)
		for (i = 0; i < ((unsigned long) m_game->m_rows); i++)
		{	
			printf("│ ");
			
			for (j = 0; j < ((unsigned long) m_game->m_cols); j++)
			{
				if ((m_hide_output ? m_game->m_blank_board[i * m_game->m_cols + j] : m_game->m_board[i * m_game->m_cols + j] ) == 1)
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
			
			// Print the calculated row hints, this one is far easier than columns as we can pretty much ignore \n's
			if (m_have_calc_data)
			{
				m_max_len = m_game_calc_max_hint_len(m_game, true);

				printf("│ %s ", m_game->m_calculated_rows[i]);

				// Always check boundiness!
				if (strlen(m_game->m_calculated_rows[i]) < m_max_len)
				{
					// Accomodate low-weighting strings on the UI with whitespaces before printing the ASCII block
					for (k = strlen(m_game->m_calculated_rows[i]); k < m_max_len; k++)
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

		// Depending of the calc_data, print the ending ASCII block differently
		if (m_have_calc_data)
		{
			for (i = 0; i <= ((m_game->m_cols) * (m_upscale ? 2 : 1) * (m_graphics ? 1 : 2) + (m_graphics ? 1 : 0) + (m_max_len + 3)); i++) { printf("─"); }
		}
		else
		{
			for (i = 0; i <= ((unsigned long) (m_game->m_cols) * (m_upscale ? 2 : 1) * (m_graphics ? 1 : 2) + (m_graphics ? 1 : 0)); i++) { printf("─"); }
		}

		printf("┘\n");
	}
}
/*
	m_game_calc_aux_string

	This functions grabs a m_string and modifies it accordingly with the hint aux string
*/
char *m_game_calc_aux_string(char *m_string, char *m_return)
{
	int m_num = 0, i, m_str_len;

	bool m_prev = false;

	// This char array will hold the value to be strcat()'d to the return string
	char current_char[2];

	// Append a null byte, else it'll crash string related functions
	current_char[1] = '\0';
	
	// Add a ending null byte on the string just in case we get inputted a poisoned string
	strcpy(m_return, "\0");

	// Always check strlen out-of-loops
	m_str_len = strlen(m_string);

	// Do this as long as we have a string
	for (i = 0; i < m_str_len; i++)
	{
		// Check if it's 1
		if (m_string[i] == '1')
		{
			// Increase the current number
			m_num++;

			// Append the number (as char, + '0') to the current char before the null byte
			current_char[0] = m_num + '0';

			// Set m_prev
			m_prev = true;
		}
		else
		{
			// If m_prev; flush the number to the return string
			if (m_prev == true)
			{
				// Append it to the char
				current_char[0] = m_num + '0';

				// Concatenate it to the return string
				strcat(m_return, current_char);

				// We can re-allocate the string to fit our needs to not waste memory
				m_return = realloc(m_return, (strlen(m_return) + 3));

				// Strcat a space
				strcat(m_return, " ");

				// Set the num to 0 again
				m_num = 0;
			}

			m_prev = false;
		}
	}

	// Flush the number if it's not 0
	if (m_num != 0)
	{
		strcat(m_return, current_char);
	}

	// Flush 0 if we don't have input
	if (strlen(m_return) == 0)
	{
		strcat(m_return, "0");
	}

	// Substitute last char w/null-byte
	if (m_return[strlen(m_return) - 1] == ' ')
	{
		m_return[strlen(m_return) - 1] = '\0';
	}

	// Return the string
	return m_return;
}

/*
	m_game_calc_line

	Expects a game state struct

	m_rows = true; process rows
	m_rows = false; process cols
*/
unsigned m_game_calc_line(m_314x *m_game, bool m_rows)
{
	char *m_current_string, *m_return, current_char[2];
	unsigned char m_err = 0;
	
	// Same technique as before, null-byte to make string functions work
	current_char[1] = '\0';

	int i, j;

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

	// Allocate only the needed bytes for rows or cols
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

	// Continue only if the malloc() succeeded
	if ((m_rows ? m_game->m_calculated_rows : m_game->m_calculated_cols) != NULL)
	{
		for (i = 0; i < (m_rows ? m_game->m_rows : m_game->m_cols); i++)
		{
			// Allocate 2 bytes for each string (char + '\0')
			m_return = (char *) malloc(2);
			m_current_string = (char *) malloc(2);

			// Sanitize checks
			if (m_return != NULL)
			{
				if (m_current_string != NULL)
				{
					// Append a null byte to the string
					strcpy(m_current_string, "\0");

					// Process the matrix
					for (j = 0; j < (m_rows ? m_game->m_cols : m_game->m_rows); j++)
					{
						// The offsetting method differs from rows to cols, differentiate it
						if (m_rows)
						{
							current_char[0] = m_game->m_board[i * m_game->m_cols + j] + '0';
						}
						else
						if (!m_rows)
						{
							current_char[0] = m_game->m_board[i + m_game->m_cols * j] + '0';
						}

						// Give it more space to fit more characters							
						m_current_string = (char *) realloc(m_current_string, (strlen(m_current_string) + 2));

						// Concatenate the character to the string
						strcat(m_current_string, current_char);
					}

#ifdef DEBUG
					printf("Current string: %s, Length: %lu\n", m_current_string, strlen(m_current_string));
#endif
					
					// Calculate the auxiliar string and assign it to m_return
					m_return = m_game_calc_aux_string(m_current_string, m_return);

					// Free the string
					free(m_current_string);

					// Continue only if we're in a sane environ.
					if (m_return != NULL)
					{
#ifdef DEBUG
						printf("Modified string: %s, Length: %lu\n", m_return, strlen(m_return));
#endif

						// Allocate space for the strings...
						if (m_rows)
						{
							m_game->m_calculated_rows[i] = malloc((strlen(m_return) + 1) * sizeof(char));
						}
						else
						if (!m_rows)
						{
							m_game->m_calculated_cols[i] = malloc((strlen(m_return) + 1) * sizeof(char));
						}
							
						// ...and copy them over there...
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
							printf("Calculated %d row: %s, length: %lu\n\n\n", i + 1, m_game->m_calculated_rows[i], strlen(m_game->m_calculated_rows[i]));
						}
						else
						if (!m_rows)
						{
							printf("Calculated %d col: %s, length: %lu\n\n\n", i + 1, m_game->m_calculated_cols[i], strlen(m_game->m_calculated_cols[i]));
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

// m_game_calc runs the aux string calcs on the game structure
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
	m_game_print_result(m_game, true, true, true, false);
	m_game_print_result(m_game, true, false, true, false);
	m_game_print_result(m_game, false, false, true, false);
#endif

	return m_err;
}

/*
	m_game_calc_max_hint_len

	Based on m_rows (true = rows; false = cols) it finds the longest
	hint string as an aid for UI printing
*/
unsigned char m_game_calc_max_hint_len(m_314x *m_game, bool m_rows)
{
	unsigned char m_max_len = 0;
	int i;

	// It runs a loop and assigns each string lenght's if the previous are lower than the newer ones
	if (m_rows)
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
	if (!m_rows)
	{
		for (i = 0; i < m_game->m_cols; i++)
		{
			if (strlen(m_game->m_calculated_cols[i]) > m_max_len)
			{
				m_max_len = strlen(m_game->m_calculated_cols[i]);
			}
		}
	}

	// Returns the size
	return m_max_len;
}

// m_game_loop is purely the game loop
unsigned char m_game_loop(m_314x *m_game)
{
	bool m_ingame = true, m_inmenu = true;
	unsigned int m_game_menu_selection = 0;
	char m_return = -1;

	// Allocates a zeroed matrix for the player, this helps a lot on game validation
	m_game->m_blank_board = (unsigned char *) calloc((m_game->m_rows * m_game->m_cols), (sizeof(unsigned char)));

	// Continue if not null
	if (m_game->m_blank_board != NULL)
	{
		// Enter the loop
		while (m_ingame && m_return == -1)
		{
			// Clears the screen
			m_game_clear_screen();

			// Prints the result
			m_game_print_result(m_game, false, false, true, true);

			while (m_inmenu && m_return == -1)
			{
				printf("\nInput your desired option (6, for help): ");

				// Menu selection is sanitized
				m_game_menu_selection = m_game_sanitized_input(m_game, false, false, false, false, 0, 0);

				// Uses a switch to handle each condition
				switch (m_game_menu_selection)
				{
					// Update a cell in the matrix
					case 0:
						m_game_update_coords(m_game);
						m_game_clear_screen();
						m_game_print_result(m_game, false, false, true, true);
						break;

					// Remaining tries
					case 1:
						printf("Remaining tries: %d\n", m_game->m_atms);
						break;
					
					// Tries to validate the matrix, else reduces attempt numbers
					case 2:
						if (m_game_validate(m_game) != true)
						{
							if (m_game->m_atms == 1)
							{
								printf("Failed attempt!\n");
								m_game->m_atms--;
								m_return = 1;
							}
							else
							{
								printf("Failed attempt!\n");
								m_game->m_atms--;
							}
						}
						else
						if (m_game_validate(m_game) == true)
						{
							m_return = 0;
						}
						break;

					// Prints the current game
					case 3:
						m_game_print_result(m_game, false, false, true, true);
						break;

					// Clears the screen and prints the current game
					case 4:
						m_game_clear_screen();
						m_game_print_result(m_game, false, false, true, true);
						break;

					// Exits the game
					case 5:
						m_return = 2;
						break;

					// Help submenu
					case 6:
						printf("\nOptions list:\n");
						printf("[0] Update a position in the table using (x,y) point coordinates\n");
						printf("[1] View remaining tries\n");
						printf("[2] Validate the board\n");
						printf("[3] Print the current game\n");
						printf("[4] Clear the screen\n");
						printf("[5] Exit the game\n");
						printf("[6] View this submenu\n");
						break;
					
					default:
						break;
				}
			}

		}
	}
	else
	{
		printf("Couldn't allocate the game's blank board, exiting...\n");
		m_return = 3;
	}

	return m_return;
}

/*
	m_game_clear_screen
	
	Clears the terminal buffer depending on the OS the program gets compiled to
*/
void m_game_clear_screen(void)
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
		system("cls");
#endif

#if defined (__linux__) || defined(__unix__)
		system("clear");
#endif
}

// m_game_update_coords; simply updates the blank matrix at (x,y) with a value
void m_game_update_coords(m_314x *m_game)
{
	int x, y, val;
	
	printf("\nWhich coordinate you want to manipulate?\n");

	printf("X: ");

	// Grab x and y coords in a sane way
	do {
		x = m_game_sanitized_input(m_game, true, true, true, false, 0, 0);
	} while (x < 0 || x > m_game->m_cols);

	printf("Y: ");

	do {
		y = m_game_sanitized_input(m_game, true, false, true, false, 0, 0);
	} while (y < 0 || y > m_game->m_rows);

	printf("(%d, %d): ", x, y);

	// Grab the 0 or 1 in a sane way too
	val = m_game_sanitized_input(m_game, false, false, false, true, x, y);

	// Flush the value at x,y
	m_game->m_blank_board[x + m_game->m_cols * y] = val;
}

/*
	m_game_sanitized_input

	Based on the different function arguments, it provides a sane way of dealing with user inputs
*/
unsigned int m_game_sanitized_input(m_314x *m_game, bool m_coord, bool m_x, bool m_check, bool m_val, int x, int y)
{
	int m_number = 0, m_return = 0;
	bool m_run = true;
	char m_buffer[10];

	// Do this until...
	while (m_run)
	{
		// I hate scanf()
		if (fgets(m_buffer, sizeof(m_buffer), stdin) != NULL)
		{
			// So we'll use fgets() and sscanf() which use size arguments for a sane way of handling inputs
			if (sscanf(m_buffer, "%d", &m_number) == 1)
			{
				if (m_val)
				{
					if (m_number == 1)
					{
						m_return = m_number;
						m_run = false;
					}
					else
					if (m_number == 0)
					{
						m_return = m_number;
						m_run = false;
					}
					else
					{
						printf("Value must be either 0 or 1\n");
						printf("(%d, %d): ", x, y);
					}
				}
				else
				{
					m_return = m_number;
					m_run = false;
				}
			}
			else
			{
				printf("Verify your input, only numbers are allowed.\n");

				if (!m_check)
				{
					printf("Input your desired option (5, for help): ");
				}
				
				if (m_x && m_coord)
				{
					printf("X: ");
				}
				else
				if (!m_x && m_coord)
				{
					printf("Y: ");
				}
			}

			if (m_x && m_check)
			{
				if (m_number > m_game->m_cols)
				{
					printf("X coordinate can't be higher than max game columns!\nX: ");
				}
				else
				if (m_number < 0)
				{
					printf("X coordinates must be positive!\nX: ");
				}
			}
			else
			if (!m_x && m_check)
			{
				if (m_number > m_game->m_rows)
				{
					printf("Y coordinate can't be higher than max game columns!\nY: ");
				}
				else
				if (m_number < 0)
				{
					printf("Y coordinates must be positive!\nY: ");
				}
			}
		}
	}

	return m_return;
}

// m_game_validate
bool m_game_validate(m_314x *m_game)
{
	int i = 0;
	bool m_check = true;

	// Simple while that iterates as long as there are values left...
	while (i < (m_game->m_rows * m_game->m_cols))
	{
		// ...checking for value disparity
		if (m_game->m_blank_board[i] != m_game->m_board[i])
		{
			m_check = false;
		}

		i++;
	}

	return m_check;
}
