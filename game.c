#include <game.h>

void m_game_print_result(m_314x *m_game)
{
    int i, j;

    printf("Current game:\n\n");

    printf("┌");
    for (i = 0; i < (m_game->m_cols) * 2; i++) { printf("─"); }
    printf("┐\n");

    for (i = 0; i < m_game->m_rows; i++)
    {
        printf("│");
        for (j = 0; j < m_game->m_cols; j++)
        {
            if (m_game->m_board[i * m_game->m_cols + j] == 1)
            {
                printf("██");
            }
            else
            {
                printf("  ");
            }
            
        }
        printf("│\n");
    }

    printf("└");
    for (i = 0; i < (m_game->m_cols) * 2; i++) { printf("─"); }
    printf("┘\n");

}
