/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>

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
        KC_SLEP, RGB_TOG, BL_TOGG, _______, NK_TOGG, KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP, _______, _______, _______, KC_PSCR,  KC_INS,          KC_MUTE,
          TO(0),   TO(1),   TO(2),   TO(3), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          RGB_SAI,
        _______, _______,   KC_UP, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET,            RGB_SAD,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          RGB_HUI,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, RGB_MOD, RGB_HUD,
        _______,   TO(2), _______,                            _______,                            _______,   TO(0), _______, RGB_VAD, RGB_RMOD, RGB_VAI
    ),

    [2] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
          TO(0),   TO(1),   TO(2),   TO(3), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______,   TO(3), _______,                            _______,                            _______,   TO(0), _______, _______, _______, _______
    ),

    [3] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
          TO(0),   TO(1),   TO(2),   TO(3), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______,   TO(0), _______,                            _______,                            _______,   TO(0), _______, _______, _______, _______
    ),


};


void rgb_matrix_indicators_user(void) {
 led_t led_state = host_keyboard_led_state();
  // Change side LEDs, start at index of 82 and end at 97
if (led_state.caps_lock) {
  for (uint8_t i = 82; i < 98; i++)
    {
      rgb_matrix_set_color(i, 0x00, 0x66, 0xbb);
    }
}
else {
	switch(biton32(layer_state)) {
    case _BASE:
      for (uint8_t i = 82; i < 98; i++)
    {
      rgb_matrix_set_color(i, 0xFF, 0xFF, 0xFF); //cyan
    }
      break;
    case _L1:
      for (uint8_t i = 82; i < 98; i++)
    {
      rgb_matrix_set_color(i, 0xaa, 0xcc, 0x11); //lime
    }
      break;
    case _L2:
      for (uint8_t i = 82; i < 98; i++)
    {
	  rgb_matrix_set_color(i, 0xff, 0x99, 0x00); //orange ish
    }
      break;
    case _L3:
      for (uint8_t i = 82; i < 98; i++)
    {
	  rgb_matrix_set_color(i, 0xee, 0x00, 0x77); //magenta
    }
      break;
	}
}
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
      tap_code(KC_VOLU);
    } else {
      tap_code(KC_VOLD);
    }
    return true;
}

// Backlight timeout feature
#define BACKLIGHT_TIMEOUT 15    // in minutes
static uint16_t idle_timer = 0;
static uint8_t halfmin_counter = 0;
static uint8_t old_backlight_level = -1; 
static uint8_t old_rgb_value = -1; 
static bool led_on = true;
static bool rgb_on = true;

void matrix_scan_user(void) {
  // idle_timer needs to be set one time
    if (idle_timer == 0) idle_timer = timer_read();

    #ifdef RGB_MATRIX_ENABLE
        if ( (led_on && timer_elapsed(idle_timer) > 30000) || (rgb_on && timer_elapsed(idle_timer) > 30000)) {
            halfmin_counter++;
            idle_timer = timer_read();
        }

        if ( (led_on && halfmin_counter >= BACKLIGHT_TIMEOUT * 2) || (rgb_on && halfmin_counter >= BACKLIGHT_TIMEOUT * 2)) {
            old_backlight_level = get_backlight_level();
			      old_rgb_hsv[0] = rgblight_get_hue(); 
			      old_rgb_hsv[1] = rgblight_get_sat();
			      old_rgb_hsv[2] = rgblight_get_val();
            backlight_set(0);
			rgblight_disable_noeeprom();
            led_on = false; 
			rgb_on = false;
            halfmin_counter = 0;
        }
    #endif
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        #ifdef RGB_MATRIX_ENABLE
            if (led_on == false || old_backlight_level == -1 || rgb_on == false || old_rgb_value == -1) {
                if (old_backlight_level == -1) old_backlight_level = get_backlight_level();
		if (old_rgb_value == -1) old_rgb_value = 1;
		old_rgb_value = 1;
		rgblight_enable_noeeprom();
                backlight_set(old_backlight_level); 
				
                led_on = true;
		rgb_on = true;
				
				
            }
        #endif
        idle_timer = timer_read();
        halfmin_counter = 0;
    }
    return true;
  }