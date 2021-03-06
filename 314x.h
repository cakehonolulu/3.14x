#ifndef E14X_H
#define E14X_H

#include <stdlib.h>
#include <stdio.h>

/* Struct Definitions */
typedef struct {
	// Game's Rows
	char m_rows;
	
	// Game's Columns
	char m_cols;

	// Attempts
	char m_atms;

	// File descriptor
	FILE *m_board_file;

	// Game matrices
	unsigned char *m_board;
	unsigned char *m_blank_board;

	// Auxiliary strings for row/col string hints
	char **m_calculated_rows;
	char **m_calculated_cols;

} m_314x;

#endif /* E14X_H */
