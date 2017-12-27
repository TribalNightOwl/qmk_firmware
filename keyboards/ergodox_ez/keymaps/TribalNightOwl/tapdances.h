enum {
 CT_DOT_CLN= 0,
 CT_COMM_SCLN,
 CT_SLSH_PIPE_BSLSH,
 CT_MINUS_UNDSCR_EQUAL,
 CT_LPRN_LBRC_LCBR_LTHAN,
 CT_RPRN_RBRC_RCBR_GTHAN,
 CT_SQTE_DQTE_BQTE_CARET,
 CT_EGG,
 TD_ESC_CAPS
};

//**************** Definitions needed for quad function to work *********************//
//Enums used to clearly convey the state of the tap dance
enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5 //send SINGLE_TAP twice - NOT DOUBLE_TAP
  // Add more enums here if you want for triple, quadruple, etc.
};

typedef struct {
  bool is_press_action;
  int state;
} tap;

int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    //If count = 1, and it has been interrupted - it doesn't matter if it is pressed or not: Send SINGLE_TAP
    if (state->interrupted || state->pressed==0) return SINGLE_TAP;
    else return SINGLE_HOLD;
  }
  //If count = 2, and it has been interrupted - assume that user is trying to type the letter associated
  //with single tap. In example below, that means to send `xx` instead of `Escape`.
  else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  else return 6; //magic number. At some point this method will expand to work for more presses
}
//**************** Definitions needed for quad function to work *********************//


#include "tapdance1.h"
#include "tapdance2.h"
#include "tapdance3.h"
#include "tapdance4.h"
#include "tapdance5.h"
#include "tapdance6.h"
#include "tapdance7.h"

void dance_egg (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count >= 4) {
    SEND_STRING ("Safety dance!");
    reset_tap_dance (state);
  }
}

//All tap dance functions would go here. Only showing this one.
qk_tap_dance_action_t tap_dance_actions[] = {
 TAPDANCE1(CT_DOT_CLN),
 TAPDANCE2(CT_COMM_SCLN),
 TAPDANCE3(CT_SLSH_PIPE_BSLSH),
 TAPDANCE4(CT_MINUS_UNDSCR_EQUAL),
 TAPDANCE5(CT_LPRN_LBRC_LCBR_LTHAN),
 TAPDANCE6(CT_RPRN_RBRC_RCBR_GTHAN),
 TAPDANCE7(CT_SQTE_DQTE_BQTE_CARET),
 [CT_EGG] = ACTION_TAP_DANCE_FN (dance_egg),
 [TD_ESC_CAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS)
};
