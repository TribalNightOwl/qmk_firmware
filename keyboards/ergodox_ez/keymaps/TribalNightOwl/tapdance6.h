/*
 * SINGLE_TAP  = )
 * SINGLE_HOLD = ]
 * DOUBLE_TAP  = }
 *
 */

//instance of 'tap' for this tap dance.
static tap dance6_state = {
  .is_press_action = true,
  .state = 0
};

void dance6_finished (qk_tap_dance_state_t *state, void *user_data) {
  dance6_state.state = cur_dance(state);
  switch (dance6_state.state) {
    case SINGLE_TAP:  register_code(KC_LSFT); register_code(KC_0);    break;
    case SINGLE_HOLD: register_code(KC_RBRC);                         break;
    case DOUBLE_TAP:  register_code(KC_LSFT); register_code(KC_RBRC); break;
    case DOUBLE_HOLD: register_code(KC_LSFT); register_code(KC_DOT); break;
    case DOUBLE_SINGLE_TAP: register_code(KC_LSFT); register_code(KC_0);  register_code(KC_LSFT); unregister_code(KC_0); register_code(KC_LSFT); register_code(KC_0);
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void dance6_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (dance6_state.state) {
    case SINGLE_TAP:  unregister_code(KC_LSFT); unregister_code(KC_0);    break;
    case SINGLE_HOLD: unregister_code(KC_RBRC);                         break;
    case DOUBLE_TAP:  unregister_code(KC_LSFT); unregister_code(KC_RBRC); break;
    case DOUBLE_HOLD: unregister_code(KC_LSFT); unregister_code(KC_DOT); break;
    case DOUBLE_SINGLE_TAP: unregister_code(KC_LSFT); unregister_code(KC_0);  unregister_code(KC_LSFT); unregister_code(KC_0); unregister_code(KC_LSFT); unregister_code(KC_0);
  }
  dance6_state.state = 0;
}

#define TAPDANCE6(x) [x] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance6_finished, dance6_reset)
