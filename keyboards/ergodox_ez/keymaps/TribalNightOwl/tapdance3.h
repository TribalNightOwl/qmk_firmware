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

//instanalize an instance of 'tap' for the 'x' tap dance.
static tap xtap_state = {
  .is_press_action = true,
  .state = 0
};

void x_finished (qk_tap_dance_state_t *state, void *user_data) {
  xtap_state.state = cur_dance(state);
  switch (xtap_state.state) {
    case SINGLE_TAP: register_code(KC_SLSH); break;
    case SINGLE_HOLD: register_code(KC_LSFT); register_code(KC_BSLASH); break;
    case DOUBLE_TAP: register_code(KC_BSLASH); break;
    case DOUBLE_HOLD: register_code(KC_LALT); break;
    case DOUBLE_SINGLE_TAP: register_code(KC_SLSH); unregister_code(KC_SLSH); register_code(KC_SLSH);
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void x_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (xtap_state.state) {
    case SINGLE_TAP: unregister_code(KC_SLSH); break;
    case SINGLE_HOLD: unregister_code(KC_LSFT), unregister_code(KC_BSLASH); break;
    case DOUBLE_TAP: unregister_code(KC_BSLASH); break;
    case DOUBLE_HOLD: unregister_code(KC_LALT);
    case DOUBLE_SINGLE_TAP: unregister_code(KC_SLSH);
  }
  xtap_state.state = 0;
}

#define TAPDANCE3 [CT_SLSH_PIPE_BSLSH] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished, x_reset)
