/* -*- mode: c++ -*-
 * Atreus -- Chrysalis-enabled Sketch for the Keyboardio Atreus
 * Copyright (C) 2018, 2019  Keyboard.io, Inc
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built on " __DATE__ " at " __TIME__
#endif

#include "Kaleidoscope.h"
#include "Kaleidoscope-MouseKeys.h"
#include "Kaleidoscope-Qukeys.h"


#define MO(n) ShiftToLayer(n)
#define TG(n) LockLayer(n)

enum {
  MACRO_QWERTY,
  MACRO_VERSION_INFO
};

#define Key_Excl        LSHIFT(Key_1)
#define Key_At          LSHIFT(Key_2)
#define Key_Hash        LSHIFT(Key_3)
#define Key_Dollar      LSHIFT(Key_4)
#define Key_Pct         LSHIFT(Key_5)
#define Key_Caret       LSHIFT(Key_6)
#define Key_Amp         LSHIFT(Key_7)
#define Key_Star        LSHIFT(Key_8)
#define Key_Plus        LSHIFT(Key_Equals)

#define C_Prev Consumer_ScanPreviousTrack
#define C_Next Consumer_ScanNextTrack
#define C_VolUp Consumer_VolumeIncrement
#define C_VolDn Consumer_VolumeDecrement
#define C_Stop Consumer_Stop
#define C_PP Consumer_PlaySlashPause
#define C_Mute Consumer_Mute

enum {
  QWERTY,
  MEDIA,
  NAV,
  MOUSE,
  SYMBOL,
  NUMBER,
  FUNCTION
};

// clang-format off
KEYMAPS(
  [QWERTY] = KEYMAP_STACKED
  (
       Key_Q        ,Key_W        ,Key_E        ,Key_R                 ,Key_T
      ,GUI_T(A) ,ALT_T(S) ,CTL_T(D) ,SFT_T(F)          ,Key_G
      ,Key_Z        ,Key_X        ,Key_C        ,Key_V                 ,Key_B              , ___
      ,___          ,___          ,___          ,ShiftToLayer(MEDIA)   ,ShiftToLayer(NAV)  ,ShiftToLayer(MOUSE)
                                
                              ,Key_Y                     ,Key_U                    ,Key_I        ,Key_O        ,Key_P
                              ,Key_H                     ,SFT_T(J)             ,CTL_T(K) ,ALT_T(L) ,GUI_T(Quote)
       ,___                   ,Key_N                     ,Key_M                    ,Key_Comma    ,Key_Period   ,Key_Slash
       ,ShiftToLayer(SYMBOL)  ,ShiftToLayer(NUMBER)      ,ShiftToLayer(FUNCTION) ,___          ,___          ,___
  ),

  [MEDIA] = KEYMAP_STACKED
  (
       LCTRL(Key_Z) ,LCTRL(Key_X) ,LCTRL(Key_C)     ,LCTRL(Key_V)   ,LCTRL(Key_Y)
      ,Key_LGui ,Key_LAlt ,Key_LCtrl ,Key_LShift ,___
      ,___      ,___      ,___          ,___        ,___     ,___
      ,___      ,___      ,___          ,___        ,___     ,___

                     ,___     ,___      ,___     ,___      ,___
                     ,___     ,C_Prev   ,C_VolDn ,C_VolUp  ,C_Next
       ,___          ,___     ,___      ,___     ,___      ,___
       ,C_Stop       ,C_PP    ,C_Mute   ,___     ,___      ,___
  ),

  [NAV] = KEYMAP_STACKED
  (
       LCTRL(Key_Z) ,LCTRL(Key_X) ,LCTRL(Key_C)     ,LCTRL(Key_V)   ,LCTRL(Key_Y)
      ,Key_LGui ,Key_LAlt ,Key_LCtrl ,Key_LShift ,___
      ,___      ,___      ,___          ,___        ,___     ,___
      ,___      ,___      ,___          ,___        ,___     ,___

                     ,LCTRL(Key_Y)     ,LCTRL(Key_V)     ,LCTRL(Key_C)     ,LCTRL(Key_X)   ,LCTRL(Key_Z)
                     ,Key_CapsLock ,Key_LeftArrow,Key_DownArrow,Key_UpArrow,Key_RightArrow
       ,___          ,Key_Insert   ,Key_Home     ,Key_PageDown ,Key_PageUp ,Key_End
       ,Key_Enter    ,Key_Backspace,Key_Delete   ,___          ,___        ,___
   ),

  [MOUSE] = KEYMAP_STACKED
  (
       LCTRL(Key_Z) ,LCTRL(Key_X) ,LCTRL(Key_C)     ,LCTRL(Key_V)   ,LCTRL(Key_Y)
      ,Key_LGui ,Key_LAlt ,Key_LCtrl ,Key_LShift ,___
      ,___      ,___      ,___          ,___        ,___     ,___
      ,___      ,___      ,___          ,___        ,___     ,___

                     ,LCTRL(Key_Y)     ,LCTRL(Key_V)     ,LCTRL(Key_C)     ,LCTRL(Key_X)   ,LCTRL(Key_Z)
                     ,___              ,Key_mouseL       ,Key_mouseDn      ,Key_mouseUp    ,Key_mouseR
       ,___          ,___              ,Key_mouseScrollL ,Key_mouseScrollDn,Key_mouseScrollUp,Key_mouseScrollR
       ,Key_mouseBtnR,Key_mouseBtnL,Key_mouseBtnM,___          ,___        ,___
   ),

  [SYMBOL] = KEYMAP_STACKED
  (
       LSHIFT(Key_LBracket)  ,LSHIFT(Key_7) ,LSHIFT(Key_8) ,LSHIFT(Key_9) ,LSHIFT(Key_RBracket)
      ,LSHIFT(Key_Semicolon) ,LSHIFT(Key_4) ,LSHIFT(Key_5) ,LSHIFT(Key_6) ,LSHIFT(Key_Equals)
      ,LSHIFT(Key_Backtick)  ,LSHIFT(Key_1) ,LSHIFT(Key_2) ,LSHIFT(Key_3) ,LSHIFT(Key_Backslash) ,___
      ,___                   ,___           ,___           ,Key_LeftParen ,Key_RightParen        ,LSHIFT(Key_Minus)

                     ,LCTRL(Key_Y)     ,LCTRL(Key_V)     ,LCTRL(Key_C)     ,LCTRL(Key_X)   ,LCTRL(Key_Z)
                     ,___          ,Key_LShift   ,Key_LCtrl ,Key_LAlt   ,Key_LGui
       ,___          ,___          ,___          ,___          ,___        ,___
       ,___          ,___          ,___          ,___          ,___        ,___
   ),

  [NUMBER] = KEYMAP_STACKED
  (
       Key_LBracket  ,Key_7 ,Key_8 ,Key_9         ,Key_RBracket
      ,Key_Semicolon ,Key_4 ,Key_5 ,Key_6         ,Key_Equals
      ,Key_Backtick  ,Key_1 ,Key_2 ,Key_3         ,Key_Backslash  ,___
      ,___           ,___   ,___   ,Key_Period    ,Key_0          ,Key_Minus

                     ,LCTRL(Key_Y)     ,LCTRL(Key_V)     ,LCTRL(Key_C)     ,LCTRL(Key_X)   ,LCTRL(Key_Z)
                     ,___          ,Key_LShift   ,Key_LCtrl ,Key_LAlt   ,Key_LGui
       ,___          ,___          ,___          ,___          ,___        ,___
       ,___          ,___          ,___          ,___          ,___        ,___
   ),

  [FUNCTION] = KEYMAP_STACKED
  (
       Key_F12  ,Key_F7 ,Key_F8 ,Key_F9         ,Key_PrintScreen
      ,Key_F11  ,Key_F4 ,Key_F5 ,Key_F6         ,Key_ScrollLock
      ,Key_F10   ,Key_F1 ,Key_F2 ,Key_F3         ,Key_Pause        ,___
      ,___      ,___    ,___    ,Key_Esc        ,Key_Space        ,Key_Tab

                     ,LCTRL(Key_Y)     ,LCTRL(Key_V)     ,LCTRL(Key_C)     ,LCTRL(Key_X)   ,LCTRL(Key_Z)
                     ,___          ,Key_LShift   ,Key_LCtrl ,Key_LAlt   ,Key_LGui
       ,___          ,___          ,___          ,___          ,___        ,___
       ,___          ,___          ,___          ,___          ,___        ,___
   )
)
// clang-format on

KALEIDOSCOPE_INIT_PLUGINS(
  Qukeys,
  MouseKeys
);

void setup() {
  Kaleidoscope.setup();
  
  Qukeys.setOverlapThreshold(80);
  Qukeys.setMinimumHoldTime(50);
  Qukeys.setMinimumPriorInterval(75);
  Qukeys.setMaxIntervalForTapRepeat(0);

  QUKEYS(
    kaleidoscope::plugin::Qukey(QWERTY, KeyAddr(3, 3), Key_Escape),
    kaleidoscope::plugin::Qukey(QWERTY, KeyAddr(3, 4), Key_Space),
    kaleidoscope::plugin::Qukey(QWERTY, KeyAddr(3, 5), Key_Tab),
    kaleidoscope::plugin::Qukey(QWERTY, KeyAddr(3, 6), Key_Enter),
    kaleidoscope::plugin::Qukey(QWERTY, KeyAddr(3, 7), Key_Backspace),
    kaleidoscope::plugin::Qukey(QWERTY, KeyAddr(3, 8), Key_Delete)
  );

  MouseKeys.setWarpGridSize(MOUSE_WARP_GRID_3X3);
}

void loop() {
  Kaleidoscope.loop();
}
