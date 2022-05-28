#include <engine.h>

m_314x m_engine_init(FILE *m_file)
{
	m_314x m_picross = {0};

	m_picross.m_rows = -1;
	m_picross.m_cols = -1;
	m_picross.m_atms = -1;
	m_picross.m_blank_board = NULL;

	// Buffer has to account for newlines and null-byte ending string
	char m_line[10];
	char *m_splice;

	m_picross.m_board_file = m_file;

	fgets(m_line, 10, m_file);
	
	rewind(m_file);

	m_splice = strtok(m_line, " \n");

	for (int i = 0; i < 3; i++)
	{
		if (m_picross.m_rows == -1)
		{
			if (atoi(m_splice) < 16)
			{
				m_picross.m_rows = atoi(m_splice);
			}
			else
			{
				printf("Invalid rows number!\n");
			}
		}
		else
		if (m_picross.m_cols == -1)
		{
			if (atoi(m_splice) < 16)
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

	return m_picross;
}

unsigned char m_engine_load_board(m_314x *m_game)
{
	int m_coord_val;
	unsigned char m_err = 0;

	printf("Generating a %d by %d board...\n", m_game->m_rows, m_game->m_cols);

	printf("Total space required: %lu bytes\n", (sizeof(unsigned char) * (m_game->m_rows * m_game->m_cols)));

	m_game->m_board = (unsigned char *) malloc( (sizeof(unsigned char) * (m_game->m_rows * m_game->m_cols)) );

	if (m_game->m_board != NULL)
	{
		printf("Successfully initialized the board's memory\n");

		fscanf(m_game->m_board_file, "%*[^\n]");

		for (int i = 0; i < m_game->m_rows; i++)
		{
	    	for (int j = 0; j < m_game->m_cols; j++)
			{
				fscanf(m_game->m_board_file, "%d", &m_coord_val);
				m_game->m_board[i * m_game->m_cols + j] = m_coord_val;
	    	}
		}

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

	return m_err;
}

void m_engine_close(m_314x *m_game)
{
	int i;

	printf("Uninitializing the engine...\n");

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
