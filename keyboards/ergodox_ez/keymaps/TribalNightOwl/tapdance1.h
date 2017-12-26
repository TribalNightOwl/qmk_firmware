// 1 tap . 2 tap :
void dance1_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_DOT);
  } else {
	register_code (KC_RSFT);
    register_code (KC_SCLN);
  }
}

void dance1_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_DOT);
  } else {
	unregister_code (KC_RSFT);
    unregister_code (KC_SCLN);
  }
}

#define TAPDANCE1(x) [x] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance1_finished, dance1_reset)
