/* Copyright 2021 Shigure<frozen0416@gmail.com> 

ver. 07/27/2021
Some functions modified based on jonavin's keymap

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#define _BASE 0
#define _L1 1
#define _L2 2
#define _L3 3

enum custom_keycodes {
  KC_WINLCK,    //Toggles Win key on and off
  KC_BSDEL,
};

bool _isWinKeyDisabled = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static bool bsdel_mods = false;
    switch (keycode) {
    case KC_WINLCK:
        if (record->event.pressed) {
            _isWinKeyDisabled = !_isWinKeyDisabled; //toggle status
            if(_isWinKeyDisabled) {
                process_magic(GUI_OFF, record);
            } else {
                process_magic(GUI_ON, record);
            }
        } else  unregister_code16(keycode);
        break;

    case KC_BSDEL:
      if (record->event.pressed) {
        if (get_mods() & MOD_BIT(KC_LSFT)) {
          unregister_code(KC_LSFT);
          register_code(KC_DEL);
          bsdel_mods = true;
        } else {
          register_code(KC_BSPC);
        }
      } else {
        if (bsdel_mods) {
          unregister_code(KC_DEL);
          register_code(KC_LSFT);
          bsdel_mods = false;
        } else {
          unregister_code(KC_BSPC);
        }
      }
      return false;
      break;    
    }
    return true;
};

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

enum {
    CAPS_LAYR, 
    TSK_MGR,
};

// Declare the functions to be used with your tap dance key(s)

// Function associated with all tap dances
td_state_t cur_dance(qk_tap_dance_state_t *state);

// Functions associated with individual tap dances
void ql_finished(qk_tap_dance_state_t *state, void *user_data);
void ql_reset(qk_tap_dance_state_t *state, void *user_data);

#define CAP_LYR TD(CAPS_LAYR)
#define TSK_MGR C(S(KC_ESC))
#define OSK_ALT OSM(MOD_LALT)
#define OSK_SFT OSM(MOD_RSFT)
#define OSK_CTL OSM(MOD_LCTL)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt           Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right


    // The FN key by default maps to a momentary toggle to layer 1 to provide access to the RESET key (to put the board into bootloader mode). Without
    // this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
    // cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
    // if that's your preference.
    //
    // To put the keyboard in bootloader mode, use FN+backslash. If you accidentally put it into bootloader, you can just unplug the USB cable and
    // it'll be back to normal when you plug it back in.
    [0] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,           KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSDEL,         KC_HOME,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
        CAP_LYR, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGDN,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          OSK_SFT, KC_UP,   KC_END,
        OSK_CTL, KC_LGUI, OSK_ALT,                            KC_SPC,                             KC_RALT, TT(2),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
	
    [1] = LAYOUT(
        _______, RGB_TOG, _______, _______, NK_TOGG, KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP, _______, _______, _______, KC_PSCR, KC_INS,           KC_MUTE,
          TO(0),   TO(1),   TO(2),   TO(3), _______, _______, _______,   KC_P7,   KC_P8,   KC_P9, KC_P0,   KC_PMNS, KC_PPLS, KC_BSDEL,         _______,
        _______, KC_HOME,  KC_UP,   KC_END, KC_PGUP, _______, _______,   KC_P4,   KC_P5,   KC_P6, KC_PENT, KC_PAST, KC_PSLS, RESET,            _______,
        CAP_LYR, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______, _______,   KC_P1,   KC_P2,   KC_P3, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______,   _______, KC_P0,   KC_P0, KC_PDOT, KC_NLCK,          _______, _______, _______,
        _______, KC_WINLCK, _______,                          _______,                            _______, TO(0), CTL_T(KC_APP), _______, _______, _______
    ),
	
    [2] = LAYOUT(
        _______, RGB_M_P, RGB_M_B, RGB_M_R, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_SLEP,          KC_MUTE,
          TO(0),   TO(1),   TO(2),   TO(3), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          RGB_SAI,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   RESET,          RGB_SAD,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          RGB_HUI,
        _______,          _______, _______, KC_CALC, _______, _______, _______, TSK_MGR, _______, _______, _______,     _______, RGB_MOD, RGB_HUD,
        _______, _______, _______,                            _______,                            _______, TO(0),   _______, RGB_VAD, RGB_RMOD, RGB_VAI
    ),

    [3] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
          TO(0),   TO(1),   TO(2),   TO(3), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, TO(0), _______, _______, _______, _______
    ),


};


void rgb_matrix_indicators_user(void) {
 led_t led_state = host_keyboard_led_state();
if (led_state.caps_lock) {
      rgb_matrix_set_color(67, 0x00, 0x66, 0xbb);
      rgb_matrix_set_color(68, 0x00, 0x66, 0xbb);
      rgb_matrix_set_color(70, 0x00, 0x66, 0xbb);
      rgb_matrix_set_color(71, 0x00, 0x66, 0xbb);
      rgb_matrix_set_color(73, 0x00, 0x66, 0xbb);
      rgb_matrix_set_color(74, 0x00, 0x66, 0xbb);
      rgb_matrix_set_color(76, 0x00, 0x66, 0xbb);
      rgb_matrix_set_color(77, 0x00, 0x66, 0xbb);
      rgb_matrix_set_color(80, 0x00, 0x66, 0xbb);
      rgb_matrix_set_color(81, 0x00, 0x66, 0xbb);
      rgb_matrix_set_color(83, 0x00, 0x66, 0xbb);
      rgb_matrix_set_color(84, 0x00, 0x66, 0xbb);
      rgb_matrix_set_color(87, 0x00, 0x66, 0xbb);
      rgb_matrix_set_color(88, 0x00, 0x66, 0xbb);
      rgb_matrix_set_color(91, 0x00, 0x66, 0xbb);
      rgb_matrix_set_color(92, 0x00, 0x66, 0xbb);
}
else {
	switch(biton32(layer_state)) {
    case _BASE: 
    {//cyan
      rgb_matrix_set_color(67, 0xFF, 0xFF, 0xFF);
      rgb_matrix_set_color(68, 0xFF, 0xFF, 0xFF);
      rgb_matrix_set_color(70, 0xFF, 0xFF, 0xFF);
      rgb_matrix_set_color(71, 0xFF, 0xFF, 0xFF);
      rgb_matrix_set_color(73, 0xFF, 0xFF, 0xFF);
      rgb_matrix_set_color(74, 0xFF, 0xFF, 0xFF);
      rgb_matrix_set_color(76, 0xFF, 0xFF, 0xFF);
      rgb_matrix_set_color(77, 0xFF, 0xFF, 0xFF);
      rgb_matrix_set_color(80, 0xFF, 0xFF, 0xFF);
      rgb_matrix_set_color(81, 0xFF, 0xFF, 0xFF);
      rgb_matrix_set_color(83, 0xFF, 0xFF, 0xFF);
      rgb_matrix_set_color(84, 0xFF, 0xFF, 0xFF);
      rgb_matrix_set_color(87, 0xFF, 0xFF, 0xFF);
      rgb_matrix_set_color(88, 0xFF, 0xFF, 0xFF);
      rgb_matrix_set_color(91, 0xFF, 0xFF, 0xFF);
      rgb_matrix_set_color(92, 0xFF, 0xFF, 0xFF);
    }
      break;
    case _L1:
    {//lime
      rgb_matrix_set_color(67, 0xaa, 0xcc, 0x11);
      rgb_matrix_set_color(68, 0xaa, 0xcc, 0x11);
      rgb_matrix_set_color(70, 0xaa, 0xcc, 0x11);
      rgb_matrix_set_color(71, 0xaa, 0xcc, 0x11);
      rgb_matrix_set_color(73, 0xaa, 0xcc, 0x11);
      rgb_matrix_set_color(74, 0xaa, 0xcc, 0x11);
      rgb_matrix_set_color(76, 0xaa, 0xcc, 0x11);
      rgb_matrix_set_color(77, 0xaa, 0xcc, 0x11);
      rgb_matrix_set_color(80, 0xaa, 0xcc, 0x11);
      rgb_matrix_set_color(81, 0xaa, 0xcc, 0x11);
      rgb_matrix_set_color(83, 0xaa, 0xcc, 0x11);
      rgb_matrix_set_color(84, 0xaa, 0xcc, 0x11);
      rgb_matrix_set_color(87, 0xaa, 0xcc, 0x11);
      rgb_matrix_set_color(88, 0xaa, 0xcc, 0x11);
      rgb_matrix_set_color(91, 0xaa, 0xcc, 0x11);
      rgb_matrix_set_color(92, 0xaa, 0xcc, 0x11);
    }
      break;
    case _L2:
      for (uint8_t i = 82; i < 98; i++)
    {//orange ish
      rgb_matrix_set_color(67, 0xff, 0x99, 0x00);
      rgb_matrix_set_color(68, 0xff, 0x99, 0x00);
      rgb_matrix_set_color(70, 0xff, 0x99, 0x00);
      rgb_matrix_set_color(71, 0xff, 0x99, 0x00);
      rgb_matrix_set_color(73, 0xff, 0x99, 0x00);
      rgb_matrix_set_color(74, 0xff, 0x99, 0x00);
      rgb_matrix_set_color(76, 0xff, 0x99, 0x00);
      rgb_matrix_set_color(77, 0xff, 0x99, 0x00);
      rgb_matrix_set_color(80, 0xff, 0x99, 0x00);
      rgb_matrix_set_color(81, 0xff, 0x99, 0x00);
      rgb_matrix_set_color(83, 0xff, 0x99, 0x00);
      rgb_matrix_set_color(84, 0xff, 0x99, 0x00);
      rgb_matrix_set_color(87, 0xff, 0x99, 0x00);
      rgb_matrix_set_color(88, 0xff, 0x99, 0x00);
      rgb_matrix_set_color(91, 0xff, 0x99, 0x00);
      rgb_matrix_set_color(92, 0xff, 0x99, 0x00);
    }
      break;
    case _L3:
    {//magenta
      rgb_matrix_set_color(67, 0xee, 0x00, 0x77);
      rgb_matrix_set_color(68, 0xee, 0x00, 0x77);
      rgb_matrix_set_color(70, 0xee, 0x00, 0x77);
      rgb_matrix_set_color(71, 0xee, 0x00, 0x77);
      rgb_matrix_set_color(73, 0xee, 0x00, 0x77);
      rgb_matrix_set_color(74, 0xee, 0x00, 0x77);
      rgb_matrix_set_color(76, 0xee, 0x00, 0x77);
      rgb_matrix_set_color(77, 0xee, 0x00, 0x77);
      rgb_matrix_set_color(80, 0xee, 0x00, 0x77);
      rgb_matrix_set_color(81, 0xee, 0x00, 0x77);
      rgb_matrix_set_color(83, 0xee, 0x00, 0x77);
      rgb_matrix_set_color(84, 0xee, 0x00, 0x77);
      rgb_matrix_set_color(87, 0xee, 0x00, 0x77);
      rgb_matrix_set_color(88, 0xee, 0x00, 0x77);
      rgb_matrix_set_color(91, 0xee, 0x00, 0x77);
      rgb_matrix_set_color(92, 0xee, 0x00, 0x77);
    }
      break;
	}
}
}

#ifdef ENCODER_ENABLE       // Encoder Functionality
    bool encoder_update_user(uint8_t index, bool clockwise) {
        if ( clockwise ) {
            if (keyboard_report->mods & MOD_BIT(KC_LCTL)) {  // if holding Left Ctrl, scroll up and down
                unregister_mods(MOD_BIT(KC_LCTL));
                register_code(KC_PGDN);
                register_mods(MOD_BIT(KC_LCTL));
            } else if (keyboard_report->mods & MOD_BIT(KC_LSFT) ) { // If you are holding L shift, scroll left and right
                tap_code16(KC_WH_R);
            } else if (keyboard_report->mods & MOD_BIT(KC_LALT)) {  // if holding Left Alt, change media next track
                tap_code(KC_MEDIA_NEXT_TRACK);
            } else  {
                tap_code(KC_VOLU);                                                   // Otherwise it just changes volume
            }
        } else {
            if (keyboard_report->mods & MOD_BIT(KC_LCTL)) {
                unregister_mods(MOD_BIT(KC_LCTL));
                register_code(KC_PGUP);
                register_mods(MOD_BIT(KC_LCTL));
            } else if (keyboard_report->mods & MOD_BIT(KC_LSFT) ) {
                tap_code16(KC_WH_L);
            } else if (keyboard_report->mods & MOD_BIT(KC_LALT)) {
                tap_code(KC_MEDIA_PREV_TRACK);
            } else {
                tap_code(KC_VOLD);
            }
        }
        return true;
    }
#endif

// Determine the current tap dance state
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) return TD_DOUBLE_TAP;
    else return TD_UNKNOWN;
}

// Initialize tap structure associated with example tap dance key
static td_tap_t ql_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void ql_finished(qk_tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_CAPS);
            break;
        case TD_SINGLE_HOLD:
            layer_on(_L1);
            break;
        case TD_DOUBLE_TAP:
            // Check to see if the layer is already set
            if (layer_state_is(_L1)) {
                // If already set, then switch it off
                layer_off(_L1);
            } else {
                // If not already set, then switch the layer on
                layer_on(_L1);
            }
            break;
        default:
            break;
    }
}

void ql_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (ql_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(_L1);
    }
    ql_tap_state.state = TD_NONE;
}

// Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    [CAPS_LAYR] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, ql_finished, ql_reset, 275)
};