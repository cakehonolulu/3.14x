#include <314x.h>
#include <ctype.h>
#include <unistd.h>
#include <stdbool.h>

void m_game_print_result(m_314x *m_game, bool m_graphics, bool m_upscale, bool m_have_calc_data, bool m_hide_output);
void m_game_calc_rows(m_314x *m_game);
void m_game_calc_cols(m_314x *m_game);
unsigned char m_game_calc(m_314x *m_game);
unsigned char m_game_calc_max_hint_len(m_314x *m_game, bool m_rows);
unsigned char m_game_loop(m_314x *m_game);
void m_game_clear_screen(void);
unsigned int m_game_sanitized_input(bool m_coord, bool m_x);
void m_game_coordinate_selection(void);
