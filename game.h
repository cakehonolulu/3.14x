#include <314x.h>
#include <stdbool.h>

void m_game_print_result(m_314x *m_game, bool m_graphics, bool m_upscale, bool m_have_calc_data);
void m_game_calc_rows(m_314x *m_game);
void m_game_calc_cols(m_314x *m_game);
void m_game_calc(m_314x *m_game);
unsigned char m_game_calc_max_hint_len(m_314x *m_game);
