#ifndef E14X_H
#define E14X_H

#include <stdlib.h>
#include <stdio.h>

typedef struct {
	// Game's Rows
	char m_rows;
	
	// Game's Columns
	char m_cols;

	// Attempts
	char m_atms;

	// Mock-up
	FILE *m_board_file;
	unsigned char *m_board;

	char **m_calculated_rows;
	char **m_calculated_cols;

} m_314x;

#endif /* E14X_H */
