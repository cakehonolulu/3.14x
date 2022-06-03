#include <engine.h>

// m_engine_init initializes a m_314x struct with m_file's contents and returns the created struct
m_314x m_engine_init(FILE *m_file)
{
	// Declare the struct
	m_314x m_picross = {0};

	// Fail-safe values
	m_picross.m_rows = -1;
	m_picross.m_cols = -1;
	m_picross.m_atms = -1;
	m_picross.m_blank_board = NULL;

	// Buffer has to account for newlines and null-byte ending string
	char m_line[10], *m_splice;

	// Update the file on the structa
	m_picross.m_board_file = m_file;

	// Read the first line of the file
	fgets(m_line, 10, m_file);
	
	// Set the position back to the start
	rewind(m_file);

	// Start tokenizing the string by spaces and newlines
	m_splice = strtok(m_line, " \n");

	// We only need to get 3 things from the line
	for (int i = 0; i < 3; i++)
	{
		// Rows comes first
		if (m_picross.m_rows == -1)
		{
			// Assign rows if max row length < 64
			if (atoi(m_splice) < 64)
			{
				m_picross.m_rows = atoi(m_splice);
			}
			else
			{
				printf("Invalid rows number!\n");
			}
		}
		else
		// Cols come second
		if (m_picross.m_cols == -1)
		{
			// Assign cols if max col length < 64
			if (atoi(m_splice) < 64)
			{
				m_picross.m_cols = atoi(m_splice);
			}
			else
			{
				printf("Invalid columns number!\n");
			}
		}
		else
		{
			// Lastly, attempt numbers if < 10
			if (atoi(m_splice) < 10)
			{
				m_picross.m_atms = atoi(m_splice);
			}
			else
			{
				printf("Invalid attempts number!\n");
			}
		}

		m_splice = strtok(NULL, " \n");
	}

	// Return the struct
	return m_picross;
}

// m_engine_load_board
unsigned char m_engine_load_board(m_314x *m_game)
{
	int m_coord_val;
	unsigned char m_err = 0;

	printf("Generating a %d by %d board...\n", m_game->m_rows, m_game->m_cols);

	printf("Total space required: %lu bytes\n", (sizeof(unsigned char) * (m_game->m_rows * m_game->m_cols)));

	// Allocate only the required number of bytes to hold the matrix
	m_game->m_board = (unsigned char *) malloc( (sizeof(unsigned char) * (m_game->m_rows * m_game->m_cols)) );

	// Continue only if we managed to malloc() the board correctly
	if (m_game->m_board != NULL)
	{
		printf("Successfully initialized the board's memory\n");

		// Start filling the matrix with the file contents
		fscanf(m_game->m_board_file, "%*[^\n]");

		for (int i = 0; i < m_game->m_rows; i++)
		{
	    	for (int j = 0; j < m_game->m_cols; j++)
			{
				// Index each matrix's value using i * max_col + j as we're dealing with a 2D repr. of a 1D array
				fscanf(m_game->m_board_file, "%d", &m_coord_val);
				m_game->m_board[i * m_game->m_cols + j] = m_coord_val;
	    	}
		}

		// Close the descriptor
		fclose(m_game->m_board_file);

#ifdef DEBUG
		for (int i = 0; i < m_game->m_rows; i++)
		{
	    	for (int j = 0; j < m_game->m_cols; j++)
			{
				printf("%d", m_game->m_board[i * m_game->m_cols + j]);
	    	}
			printf("\n");
		}
#endif
	}
	else
	{
		printf("Memory exhausted!\nCannot continue execution...\n");
		m_err = 1;
	}

	// Return if/not err
	return m_err;
}

// m_engine_close safely gets over all the memory-related variables securely
void m_engine_close(m_314x *m_game)
{
	int i;

	printf("Uninitializing the engine...\n");

	// Uninitialize everything that's not NULL
	if (m_game->m_board != NULL)
	{
		free(m_game->m_board);
	}

	if (m_game->m_blank_board != NULL)
	{
		free(m_game->m_blank_board);
	}

	for (i = 0; i < m_game->m_cols; i++)
	{
		if (m_game->m_calculated_cols[i] != NULL)
		{
			free(m_game->m_calculated_cols[i]);
		}
	}

	for (i = 0; i < m_game->m_rows; i++)
	{
		if (m_game->m_calculated_rows[i] != NULL)
		{
			free(m_game->m_calculated_rows[i]);
		}
	}

	if (m_game->m_calculated_cols != NULL)
	{
		free(m_game->m_calculated_cols);
	}

	if (m_game->m_calculated_rows != NULL)
	{
		free(m_game->m_calculated_rows);
	}
}
