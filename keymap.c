/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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

#include <stdint.h>
#include <stdbool.h>
#include "keycode.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "keymap.h"

/* 
 * IBM Terminal keyboard 6110345(122keys)/1392595(102keys)
 * http://geekhack.org/showthread.php?10737-What-Can-I-Do-With-a-Terminal-Model-M
 * http://www.seasip.info/VintagePC/ibm_1391406.html
 *
 * Keymap array:
 *     8 bytes
 *   +---------+
 *  0|         |
 *  :|         | 0x00-0x87
 *  ;|         |
 * 17|         |
 *   +---------+
 */
#define KEYMAP( \
                  K08,K10,K18,K20,K28,K30,K38,K40,K48,K50,K57,K5F,                                         \
                  K07,K0F,K17,K1F,K27,K2F,K37,K3F,K47,K4F,K56,K5E,                                         \
                                                                                                           \
    K05,K06,  K0E,K16,K1E,K26,K25,K2E,K36,K3D,K3E,K46,K45,K4E,K55,K5D,K66,  K67,K6E,K6F,  K76,K77,K7E,K84, \
    K04,K0C,  K0D,K15,K1D,K24,K2D,K2C,K35,K3C,K43,K44,K4D,K54,K5B,    K5C,  K64,K65,K6D,  K6C,K75,K7D,K7C, \
    K03,K0B,  K14,K1C,K1B,K23,K2B,K34,K33,K3B,K42,K4B,K4C,K52,    K53,K5A,      K63,      K6B,K73,K74,K7B, \
    K83,K0A,  K12,K13,K1A,K22,K21,K2A,K32,K31,K3A,K41,K49,K4A,    K51,K59,  K61,K62,K6A,  K69,K72,K7A,K79, \
    K01,K09,  K11,    K19,            K29,                    K39,    K58,      K60,      K68,K70,K71,K78  \
) { \
    { KC_NO,    KC_##K01, KC_NO,    KC_##K03, KC_##K04, KC_##K05, KC_##K06, KC_##K07 }, \
    { KC_##K08, KC_##K09, KC_##K0A, KC_##K0B, KC_##K0C, KC_##K0D, KC_##K0E, KC_##K0F }, \
    { KC_##K10, KC_##K11, KC_##K12, KC_##K13, KC_##K14, KC_##K15, KC_##K16, KC_##K17 }, \
    { KC_##K18, KC_##K19, KC_##K1A, KC_##K1B, KC_##K1C, KC_##K1D, KC_##K1E, KC_##K1F }, \
    { KC_##K20, KC_##K21, KC_##K22, KC_##K23, KC_##K24, KC_##K25, KC_##K26, KC_##K27 }, \
    { KC_##K28, KC_##K29, KC_##K2A, KC_##K2B, KC_##K2C, KC_##K2D, KC_##K2E, KC_##K2F }, \
    { KC_##K30, KC_##K31, KC_##K32, KC_##K33, KC_##K34, KC_##K35, KC_##K36, KC_##K37 }, \
    { KC_##K38, KC_##K39, KC_##K3A, KC_##K3B, KC_##K3C, KC_##K3D, KC_##K3E, KC_##K3F }, \
    { KC_##K40, KC_##K41, KC_##K42, KC_##K43, KC_##K44, KC_##K45, KC_##K46, KC_##K47 }, \
    { KC_##K48, KC_##K49, KC_##K4A, KC_##K4B, KC_##K4C, KC_##K4D, KC_##K4E, KC_##K4F }, \
    { KC_##K50, KC_##K51, KC_##K52, KC_##K53, KC_##K54, KC_##K55, KC_##K56, KC_##K57 }, \
    { KC_##K58, KC_##K59, KC_##K5A, KC_##K5B, KC_##K5C, KC_##K5D, KC_##K5E, KC_##K5F }, \
    { KC_##K60, KC_##K61, KC_##K62, KC_##K63, KC_##K64, KC_##K65, KC_##K66, KC_##K67 }, \
    { KC_##K68, KC_##K69, KC_##K6A, KC_##K6B, KC_##K6C, KC_##K6D, KC_##K6E, KC_##K6F }, \
    { KC_##K70, KC_##K71, KC_##K72, KC_##K73, KC_##K74, KC_##K75, KC_##K76, KC_##K77 }, \
    { KC_##K78, KC_##K79, KC_##K7A, KC_##K7B, KC_##K7C, KC_##K7D, KC_##K7E, KC_NO    }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_##K83, KC_##K84, KC_NO,    KC_NO,    KC_NO,   }, \
}

const action_t PROGMEM fn_actions[] = {
    ACTION_MODS_KEY(MOD_RALT, KC_GRAVE),    // FN0 - Switch modes (Kana/Romaji)
    ACTION_MODS_KEY(MOD_LCTL, KC_CAPSLOCK), // FN1 - Switch to Hiragana
    ACTION_MODS_KEY(MOD_RALT, KC_CAPSLOCK)  // FN2 - Switch to Katakana
};


const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: default
     * 
     *               ,-----------------------------------------------.
     *               |F13|F14|F15|F16|F17|F18|F19|F20|F21|F22|F23|BTL|
     *               `-----------------------------------------------' 
     *               ,-----------------------------------------------.
     *               |F1 |F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|
     *               `-----------------------------------------------' 
     * ,-------. ,-----------------------------------------------------------. ,-----------. ,---------------.
     * |Pla|Esc| |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|    BS | |Ins|Hom|PgU| |NmL|  /|  *|PrS|
     * |-------| |-----------------------------------------------------------| |-----------| |---------------|
     * |VlD|VlU| |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \| |Del|End|PgD| |  7|  8|  9|  +|
     * |-------| |-----------------------------------------------------------| `-----------' |-----------|---|
     * |Prv|Nxt| |Ctrl  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|  Return|     |Up |     |  4|  5|  6|  -|
     * |-------| |-----------------------------------------------------------| ,-----------. |---------------|
     * |Fn1|Fn2| |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /|Shift     | |Lef|Dow|Rig| |  1|  2|  3|   |
     * |-------| |-----------------------------------------------------------| `-----------' |-----------|Ent|
     * |Non|CpL| |Ctrl|    |Alt |          Space              |Fn0 |    |RGui|     |Dow|     |      0|  .|   |
     * `-------' `----'    `---------------------------------------'    `----'     `---'     `---------------'
     */

    KEYMAP(
                     F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, BTLD,
                     F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,

    MPLY,ESC,   GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, NO,  BSPC,  INS, HOME,PGUP,  NLCK,PSLS,PAST,PSCR,
    VOLD,VOLU,  TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,     BSLS,  DEL, END, PGDN,  P7,  P8,  P9,  PPLS,
    MPRV, MNXT, LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     NUHS,ENT,        UP,         P4,  P5,  P6,  PMNS,
    FN1, FN2,  LSFT, NO, Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,     RO,  RSFT,  LEFT,DOWN,RGHT,  P1,  P2,  P3,  PENT,
    NO,   CAPS,   LCTL,     LALT,               SPC,                          FN0,     RGUI,       DOWN,        NO,  P0,  PDOT,NO
    ),

     /* Blank
     * 
     *               ,-----------------------------------------------.
     *               |   |   |   |   |   |   |   |   |   |   |   |   |
     *               `-----------------------------------------------' 
     *               ,-----------------------------------------------.
     *               |   |   |   |   |   |   |   |   |   |   |   |   |
     *               `-----------------------------------------------' 
     * ,-------. ,-----------------------------------------------------------. ,-----------. ,---------------.
     * |   |   | |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   | |   |   |   | |   |   |   |   |
     * |-------| |-----------------------------------------------------------| |-----------| |---------------|
     * |   |   | |     |   |   |   |   |   |   |   |   |   |   |   |   |     | |   |   |   | |   |   |   |   |
     * |-------| |-----------------------------------------------------------| `-----------' |-----------|---|
     * |   |   | |      |   |   |   |   |   |   |   |   |   |   |   |        |     |   |     |   |   |   |   |
     * |-------| |-----------------------------------------------------------| ,-----------. |---------------|
     * |   |   | |    |   |   |   |   |   |   |   |   |   |   |   |          | |   |   |   | |   |   |   |   |
     * |-------| |-----------------------------------------------------------| `-----------' |-----------|   |
     * |   |   | |    |    |    |                             |    |    |    |     |   |     |       |   |   |
     * `-------' `----'    `---------------------------------------'    `----'     `---'     `---------------'
     */
/*
    // pseudo ANSI
    KEYMAP(
                     F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24,
                     F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,

    PSCR,ESC,   ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, NO,  BSPC,  INS, HOME,PGUP,  NLCK,PSLS,PAST,PMNS,
    SLCK,INT4,  TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,     NO,    DEL, END, PGDN,  P7,  P8,  P9,  PPLS,
    PAUS,INT5,  LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     BSLS,ENT,        UP,         P4,  P5,  P6,  PCMM,
    APP, INT6,  LSFT,LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,     NO,  RSFT,  LEFT,INT2,RGHT,  P1,  P2,  P3,  PENT,
    RGUI,LGUI,  LCTL,     LALT,               SPC,                          LGUI,     GRV,        DOWN,       NO,  P0,  PDOT,NO
    ),
*/
};
