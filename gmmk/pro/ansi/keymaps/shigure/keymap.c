/* Copyright 2021 Shigure<frozen0416@gmail.com> 

ver. 08/01/2021
Some functions modified based on jonavin's keymap and Gigahawk's keymap 

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
#include "rgb_matrix_map.h"

#define ARRAYSIZE(arr) sizeof(arr) / sizeof(arr[0])

#define _BASE 0
#define _L1 1
#define _L2 2
#define _L3 3

void matrix_init_user(void) {
  rgb_matrix_sethsv(0, 0, 125);
};

enum custom_keycodes
{
  KC_WINLCK = SAFE_RANGE, //Toggles Win key on and off, this custom keycode will be replaced in the future.
  TSK_MGR,
  RSFT_L3
};

bool _isWinKeyDisabled = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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
    }
    return true;
};

typedef enum
{ // quad function tap-dance
  TD_NONE,
  TD_UNKNOWN,
  TD_SINGLE_TAP,
  TD_SINGLE_HOLD,
  TD_DOUBLE_TAP
} td_state_t;

typedef struct
{
  bool is_press_action;
  td_state_t state;
} td_tap_t;

enum custom_tap_dance
{
  CAPS_LAYR,
  RSFT_LAY3,
};

// Declare the functions to be used with your tap dance key(s)

// Function associated with all tap dances
td_state_t cur_dance(qk_tap_dance_state_t *state);

// Functions associated with individual tap dances
void ql_finished(qk_tap_dance_state_t *state, void *user_data);
void ql_reset(qk_tap_dance_state_t *state, void *user_data);

#define CAP_LYR TD(CAPS_LAYR)
#define RSFT_L3 TD(RSFT_LAY3)
#define TSK_MGR C(S(KC_ESC))
#define OSK_ALT OSM(MOD_LALT) // one shot mods


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
    [0] = LAYOUT( //base
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,           KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_HOME,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
        CAP_LYR, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGDN,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          RSFT_L3, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, OSK_ALT,                            KC_SPC,                             KC_RALT, TT(2),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
	
    [1] = LAYOUT( // function and numpad
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PSCR,          _______,
        _______, _______, _______, _______, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   _______, KC_PMNS, KC_PPLS, KC_INS,           _______,
        _______, KC_HOME, KC_UP,   KC_END,  KC_PGUP, _______, _______, KC_P4,   KC_P5,   KC_P6,   KC_PENT, KC_PAST, KC_PSLS, _______,          _______,
        TO(0),   KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______, _______, KC_P1,   KC_P2,   KC_P3,   _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, KC_P0,   KC_P0,   KC_PDOT, KC_NLCK,          _______, _______, _______,
        _______, KC_WINLCK, _______,                          _______,                            _______, _______, CTL_T(KC_APP), _______, _______, _______
    ),
	
    [2] = LAYOUT( // rgb and media
        _______, RGB_TOG, RGB_M_P, _______, NK_TOGG, KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP, KC_VOLD, KC_VOLU, _______, _______, KC_SLEP,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          RGB_SAI,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET,            RGB_SAD,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          RGB_HUI,
        _______,          _______, _______, KC_CALC, _______, _______, _______, TSK_MGR, _______, _______, _______,          _______, RGB_MOD, RGB_HUD,
        _______, KC_WINLCK, _______,                          _______,                            _______, TO(0),   _______, RGB_VAD, RGB_RMOD, RGB_VAI
    ),

    [3] = LAYOUT( //mouse keys
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, KC_MS_U, _______, _______, _______, _______, _______, KC_WH_U, _______, _______, _______, _______, _______,          _______,
        _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______, _______, KC_WH_L, KC_WH_D, KC_WH_R, _______, _______,          KC_BTN1,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          TO(0),   _______, _______,
        _______, KC_WINLCK, _______,                          _______,                            _______, _______, _______, _______, _______, _______
    ),

};

// different layer will have different backlight, capslock only light up on base layer, winlock will light up in all all layers
void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max)
{
  if (_isWinKeyDisabled)
  {
    rgb_matrix_set_color(LED_LWIN, RGB_RED); //light up Win key when disabled
  }
  switch (get_highest_layer(layer_state))
  {
  case _BASE:
    if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK))
    {
      for (uint8_t i = 0; i < ARRAYSIZE(LED_SIDE); i++)
      {
        rgb_matrix_set_color(LED_SIDE[i], 0x00, 0x66, 0xbb);
      }
    }
    else
    {
      for (uint8_t i = 0; i < ARRAYSIZE(LED_SIDE); i++)
      {
        rgb_matrix_set_color(LED_SIDE[i], 0xFF, 0xFF, 0xFF);
      }
    }
    break;
  case _L1:
    rgb_matrix_set_color_all(0, 0, 0);
    for (uint8_t i = 0; i < ARRAYSIZE(LED_LAYER1); i++)
    {
      rgb_matrix_set_color(LED_LAYER1[i], 0xaa, 0xcc, 0x11);
    }
    for (uint8_t i = 0; i < ARRAYSIZE(LED_NUMPAD); i++)
    {
      rgb_matrix_set_color(LED_NUMPAD[i], 0xee, 0x00, 0x77);
    }
    break;
  case _L2:
    rgb_matrix_set_color_all(0, 0, 0);
    for (uint8_t i = 0; i < ARRAYSIZE(LED_LAYER2); i++)
    {
      rgb_matrix_set_color(LED_LAYER2[i], 0xff, 0x99, 0x00);
    }
    break;
  case _L3:
    rgb_matrix_set_color_all(0, 0, 0);
    for (uint8_t i = 0; i < ARRAYSIZE(LED_LAYER3); i++)
    {
      rgb_matrix_set_color(LED_LAYER3[i], 0xee, 0x00, 0x77);
    }
    break;
  default:
    break;
  }
}

#ifdef ENCODER_ENABLE // Encoder Functionality
bool encoder_update_user(uint8_t index, bool clockwise)
{
  if (clockwise)
  {
    if (keyboard_report->mods & MOD_BIT(KC_LCTL))
    { // if holding Left Ctrl, scroll up and down
      unregister_mods(MOD_BIT(KC_LCTL));
      register_code(KC_PGDN);
      register_mods(MOD_BIT(KC_LCTL));
    }
    else if (keyboard_report->mods & MOD_BIT(KC_LSFT))
    { // If you are holding L shift, scroll left and right
      tap_code16(KC_WH_R);
    }
    else if (keyboard_report->mods & MOD_BIT(KC_LALT))
    { // if holding Left Alt, change media next track
      tap_code(KC_MEDIA_NEXT_TRACK);
    }
    else
    {
      tap_code(KC_VOLU); // Otherwise it just changes volume
    }
  }
  else
  {
    if (keyboard_report->mods & MOD_BIT(KC_LCTL))
    {
      unregister_mods(MOD_BIT(KC_LCTL));
      register_code(KC_PGUP);
      register_mods(MOD_BIT(KC_LCTL));
    }
    else if (keyboard_report->mods & MOD_BIT(KC_LSFT))
    {
      tap_code16(KC_WH_L);
    }
    else if (keyboard_report->mods & MOD_BIT(KC_LALT))
    {
      tap_code(KC_MEDIA_PREV_TRACK);
    }
    else
    {
      tap_code(KC_VOLD);
    }
  }
  return true;
}
#endif

// Determine the current tap dance state
td_state_t cur_dance(qk_tap_dance_state_t *state)
{
  if (state->count == 1)
  {
    if (!state->pressed)
      return TD_SINGLE_TAP;
    else
      return TD_SINGLE_HOLD;
  }
  else if (state->count == 2)
    return TD_DOUBLE_TAP;
  else
    return TD_UNKNOWN;
}

// Initialize tap structure associated with example tap dance key
static td_tap_t ql_tap_state = {
    .is_press_action = true,
    .state = TD_NONE};

// Functions that control what our tap dance key does
void ql_finished(qk_tap_dance_state_t *state, void *user_data)
{
  ql_tap_state.state = cur_dance(state);
  switch (ql_tap_state.state)
  {
  case TD_SINGLE_TAP:
    tap_code(KC_CAPS);
    break;
  case TD_SINGLE_HOLD:
    layer_on(_L1);
    break;
  case TD_DOUBLE_TAP:
    // Check to see if the layer is already set
    if (layer_state_is(_L1))
    {
      // If already set, then switch it off
      layer_off(_L1);
    }
    else
    {
      // If not already set, then switch the layer on
      layer_on(_L1);
    }
    break;
  default:
    break;
  }
}

void ql_reset(qk_tap_dance_state_t *state, void *user_data)
{
  // If the key was held down and now is released then switch off the layer
  if (ql_tap_state.state == TD_SINGLE_HOLD)
  {
    layer_off(_L1);
  }
  ql_tap_state.state = TD_NONE;
}

// Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    [CAPS_LAYR] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, ql_finished, ql_reset, 275),
    [RSFT_LAY3] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_RSFT, _L3)
};

void keyboard_post_init_user(void)
{
  if (IS_HOST_LED_ON(USB_LED_NUM_LOCK))
  { // turn on Num lock by defautl
    tap_code(KC_NUMLOCK);
  }
}

const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPACE, KC_DELETE);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &delete_key_override,
    NULL // Null terminate the array of overrides!
};
