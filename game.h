#include <314x.h>
#include <ctype.h>
#include <unistd.h>
#include <stdbool.h>

/* Function definitions */
void m_game_print_result(m_314x *m_game, bool m_graphics, bool m_upscale, bool m_have_calc_data, bool m_hide_output);
void m_game_calc_rows(m_314x *m_game);
void m_game_calc_cols(m_314x *m_game);
unsigned char m_game_calc(m_314x *m_game);
unsigned char m_game_calc_max_hint_len(m_314x *m_game, bool m_rows);
unsigned char m_game_loop(m_314x *m_game);
void m_game_clear_screen(void);
unsigned int m_game_sanitized_input(m_314x *m_game, bool m_coord, bool m_x, bool m_check, bool m_val, int x, int y);
void m_game_coordinate_selection(void);
void m_game_update_coords(m_314x *m_game);
bool m_game_validate(m_314x *m_game);
