/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>
  Shigure 07/22/2021
  Modified based on jonavin's keymap

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
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,   KC_DEL,          KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_HOME,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGDN,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, TT(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [1] = LAYOUT(
        KC_SLEP, RGB_TOG, _______, _______, NK_TOGG, KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP, _______, _______, _______, KC_PSCR,  KC_INS,          KC_MUTE,
          TO(0),   TO(1),   TO(2),   TO(3), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          RGB_SAI,
        _______, KC_HOME,   KC_UP,  KC_END, KC_PGUP, _______, _______, _______, _______, _______, _______, _______, _______, RESET,            RGB_SAD,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______, _______, _______, _______, _______, _______, _______,          _______,          RGB_HUI,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, RGB_MOD, RGB_HUD,
        _______, KC_WINLCK, _______,                          _______,                            _______,   OSL(1), _______, RGB_VAD, RGB_RMOD, RGB_VAI
    ),

    [2] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_NLCK,          _______,
          TO(0),   TO(1),   TO(2),   TO(3), _______, _______, _______,   KC_P7,   KC_P8,   KC_P9,   KC_P0, KC_PMNS, KC_PPLS, KC_BSPC,          _______,
        _______, _______, _______, _______, _______, _______, _______,   KC_P4,   KC_P5,   KC_P6, _______, KC_PAST, KC_PSLS,  KC_DEL,          _______,
        _______, _______, _______, _______, _______, _______, _______,   KC_P1,   KC_P2,   KC_P3, _______, _______,          KC_PENT,          _______,
        _______,          _______, _______, _______, _______, _______,   KC_P0,   KC_P0, KC_PDOT, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______,   OSL(1), _______, _______, _______, _______
    ),

    [3] = LAYOUT(
        _______, RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, RGB_M_K, RGB_M_X, RGB_M_G, RGB_M_T, RGB_M_TW, _______, _______, _______,       _______,
          TO(0),   TO(1),   TO(2),   TO(3), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______,  OSL(1), _______, _______, _______, _______
    ),


};


void rgb_matrix_indicators_user(void) {
 led_t led_state = host_keyboard_led_state();
  // Change side LEDs, start at index of 82 and end at 97
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
            if (keyboard_report->mods & MOD_BIT(KC_LSFT) ) { // If you are holding L shift, scroll left and right
                tap_code16(KC_WH_R);
            } else if (keyboard_report->mods & MOD_BIT(KC_LCTL)) {  // if holding Left Ctrl, scroll up and down
                unregister_mods(MOD_BIT(KC_LCTL));
                register_code(KC_PGDN);
                register_mods(MOD_BIT(KC_LCTL));
            } else if (keyboard_report->mods & MOD_BIT(KC_LALT)) {  // if holding Left Alt, change media next track
                tap_code(KC_MEDIA_NEXT_TRACK);
            } else  {
                tap_code(KC_VOLU);                                                   // Otherwise it just changes volume
            }
        } else {
            if (keyboard_report->mods & MOD_BIT(KC_LSFT) ) {
                tap_code16(KC_WH_L);
            } else if (keyboard_report->mods & MOD_BIT(KC_LCTL)) {
                unregister_mods(MOD_BIT(KC_LCTL));
                register_code(KC_PGUP);
                register_mods(MOD_BIT(KC_LCTL));
            } else if (keyboard_report->mods & MOD_BIT(KC_LALT)) {
                tap_code(KC_MEDIA_PREV_TRACK);
            } else {
                tap_code(KC_VOLD);
            }
        }
        return true;
    }
#endif