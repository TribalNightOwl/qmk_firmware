// 1 tap , 2 tap ;
void dance_comm_scln_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_COMM);
  } else {
    register_code (KC_SCLN);
  }
}

void dance_comm_scln_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_COMM);
  } else {
    unregister_code (KC_SCLN);
  }
}

#define TAPDANCE2 [CT_COMM_SCLN] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_comm_scln_finished, dance_comm_scln_reset)
