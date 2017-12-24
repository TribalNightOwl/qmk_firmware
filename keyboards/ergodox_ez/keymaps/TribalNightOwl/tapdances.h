// Enums defined for all examples:
enum {
 CT_DOT_CLN= 0,
 CT_COMM_SCLN,
 CT_SLSH_PIPE_BSLSH,
 CT_CLN,
 CT_EGG,
 CT_FLSH,
 X_TAP_DANCE,
 TD_ESC_CAPS
};

void dance_egg (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count >= 4) {
    SEND_STRING ("Safety dance!");
    reset_tap_dance (state);
  }
}

// 1 tap . 2 tap :
void dance_dot_cln_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_DOT);
  } else {
	register_code (KC_RSFT);
    register_code (KC_SCLN);
  }
}

void dance_dot_cln_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_DOT);
  } else {
	unregister_code (KC_RSFT);
    unregister_code (KC_SCLN);
  }
}

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



//All tap dance functions would go here. Only showing this one.
qk_tap_dance_action_t tap_dance_actions[] = {
 [CT_DOT_CLN] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_dot_cln_finished, dance_dot_cln_reset),
 [CT_COMM_SCLN] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_comm_scln_finished, dance_comm_scln_reset),
 [X_TAP_DANCE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished, x_reset),
 [CT_EGG] = ACTION_TAP_DANCE_FN (dance_egg),
 [TD_ESC_CAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS)
};
