#include <engine.h>

m_314x m_engine_init(FILE *m_file)
{
	m_314x m_picross = {0};

	m_picross.m_rows = -1;
	m_picross.m_cols = -1;
	m_picross.m_atms = -1;

	// Buffer has to account for newlines and null-byte ending string
	char m_line[10];
	char *m_splice;

	fgets(m_line, 10, m_file);
	
	fclose(m_file);

	m_splice = strtok(m_line, " \n");

	for (int i = 0; i < 3; i++)
	{
		if (m_picross.m_rows == -1)
		{
			if (atoi(m_splice) < 10)
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
			if (atoi(m_splice) < 10)
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

char m_engine_generate_board(m_314x *m_game)
{
	char m_result = 0;

	printf("Generating a %d by %d board...\n", m_game->m_rows, m_game->m_cols);

	printf("Total space required: %lu bytes\n", (sizeof(unsigned char) * (m_game->m_rows * m_game->m_cols)));

	m_game->m_board = (unsigned char *) malloc( (sizeof(unsigned char) * (m_game->m_rows * m_game->m_cols)) );

	if (m_game->m_board != NULL)
	{
		printf("Successfully initialized the board's memory\n");
		
	}
	else
	{
		printf("Memory exhausted!\nCannot continue execution...\n");
	}

	return 0;
}

void m_engine_close(m_314x *m_game)
{
	printf("Uninitializing the engine...\n");

	if (m_game->m_board != NULL)
	{
		free(m_game->m_board);
	}
}
