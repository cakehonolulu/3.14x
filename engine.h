#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
	// Game's Rows
	char m_rows;
	
	// Game's Columns
	char m_cols;

	// Attempts
	char m_atms;

	// Mock-up
	unsigned char *m_board;

} m_314x;

/* Function definitions */
m_314x m_engine_init(FILE *m_file);
char m_engine_generate_board(m_314x *m_game);
void m_engine_close(m_314x *m_game);
