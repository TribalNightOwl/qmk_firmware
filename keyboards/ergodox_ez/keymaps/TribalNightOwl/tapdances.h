enum {
 CT_DOT_CLN= 0,
 CT_COMM_SCLN,
 CT_SLSH_PIPE_BSLSH,
 CT_CLN,
 CT_EGG,
 CT_FLSH,
 TD_ESC_CAPS
};

#include "tapdance1.h"
#include "tapdance2.h"
#include "tapdance3.h"

void dance_egg (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count >= 4) {
    SEND_STRING ("Safety dance!");
    reset_tap_dance (state);
  }
}

//All tap dance functions would go here. Only showing this one.
qk_tap_dance_action_t tap_dance_actions[] = {
 TAPDANCE1,
 TAPDANCE2,
 TAPDANCE3,
 [CT_EGG] = ACTION_TAP_DANCE_FN (dance_egg),
 [TD_ESC_CAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS)
};
