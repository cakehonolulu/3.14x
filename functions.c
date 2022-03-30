#include <functions.h>

m_314x m_init_engine(FILE *m_file)
{
	m_314x m_picross = {0};

	// Buffer has to account for newlines and null-byte ending string
	char m_line[10];
	char *m_splice;

	fgets(m_line, 10, m_file);
	
	fclose(m_file);

	m_splice = strtok(m_line, " \n");

	for (int i = 0; i < 3; i++)
	{
		printf("%s\n", m_splice);

		if (m_picross.m_rows == 0)
		{
			m_picross.m_rows = atoi(m_splice);
		}
		else
		if (m_picross.m_cols == 0)
		{
			m_picross.m_cols = atoi(m_splice);
		}
		else
		{
			m_picross.m_atms = atoi(m_splice);
		}

		m_splice = strtok(NULL, " \n");
	}

	printf("Rows: %d, Columns: %d, Tries: %d\n", m_picross.m_rows, m_picross.m_cols, m_picross.m_atms);

	return m_picross;
}
