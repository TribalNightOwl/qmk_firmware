/*
 * SINGLE_TAP  = /
 * SINGLE_HOLD = |
 * DOUBLE_TAP  = \
 * DOUBLE_HOLD = LALT
 *
 */

#define SINGLE_TAP_KC  {register_code(KC_SLSH);}
#define SINGLE_HOLD_KC {register_code(KC_LSFT); register_code(KC_BSLASH);}
#define DOUBLE_TAP_KC  {register_code(KC_BSLASH);}
#define DOUBLE_HOLD_KC {register_code(KC_LALT);}

//instance of 'tap' for this tap dance.
static tap dance3_state = {
  .is_press_action = true,
  .state = 0
};

void dance3_finished (qk_tap_dance_state_t *state, void *user_data) {
  dance3_state.state = cur_dance(state);
  switch (dance3_state.state) {
    case SINGLE_TAP:  SINGLE_TAP_KC break;
    case SINGLE_HOLD: SINGLE_HOLD_KC break;
    case DOUBLE_TAP:  DOUBLE_TAP_KC break;
    case DOUBLE_HOLD: DOUBLE_HOLD_KC break;
    case DOUBLE_SINGLE_TAP: register_code(KC_SLSH); unregister_code(KC_SLSH); register_code(KC_SLSH);
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void dance3_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (dance3_state.state) {
    case SINGLE_TAP: unregister_code(KC_SLSH); break;
    case SINGLE_HOLD: unregister_code(KC_LSFT), unregister_code(KC_BSLASH); break;
    case DOUBLE_TAP: unregister_code(KC_BSLASH); break;
    case DOUBLE_HOLD: unregister_code(KC_LALT);
    case DOUBLE_SINGLE_TAP: unregister_code(KC_SLSH);
  }
  dance3_state.state = 0;
}

#define TAPDANCE3(x) [x] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance3_finished, dance3_reset)
