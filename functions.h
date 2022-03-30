#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
	// Game's Rows
	unsigned char m_rows;
	
	// Game's Columns
	unsigned char m_cols;

	// Attempts
	unsigned char m_atms;
} m_314x;

/* Function definitions */
m_314x m_init_engine(FILE *m_file);
