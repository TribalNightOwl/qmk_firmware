//instance of 'tap' for this tap dance.
static tap dance4_state = {
  .is_press_action = true,
  .state = 0
};

void dance4_finished (qk_tap_dance_state_t *state, void *user_data) {
  dance4_state.state = cur_dance(state);
  switch (dance4_state.state) {
    case SINGLE_TAP: register_code(KC_MINUS); break;
    case SINGLE_HOLD: register_code(KC_LSFT); register_code(KC_MINUS); break;
    case DOUBLE_TAP: register_code(KC_EQUAL); break;
    case DOUBLE_HOLD: register_code(KC_LALT); break;
    case DOUBLE_SINGLE_TAP: register_code(KC_MINUS); unregister_code(KC_MINUS); register_code(KC_MINUS);
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void dance4_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (dance4_state.state) {
    case SINGLE_TAP: unregister_code(KC_MINUS); break;
    case SINGLE_HOLD: unregister_code(KC_LSFT), unregister_code(KC_MINUS); break;
    case DOUBLE_TAP: unregister_code(KC_EQUAL); break;
    case DOUBLE_HOLD: unregister_code(KC_LALT);
    case DOUBLE_SINGLE_TAP: unregister_code(KC_MINUS);
  }
  dance4_state.state = 0;
}

#define TAPDANCE4(x) [x] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance4_finished, dance4_reset)
