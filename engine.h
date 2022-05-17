#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include <314x.h>

/* Function definitions */
m_314x m_engine_init(FILE *m_file);
char m_engine_load_board(m_314x *m_game);
void m_engine_close(m_314x *m_game);
