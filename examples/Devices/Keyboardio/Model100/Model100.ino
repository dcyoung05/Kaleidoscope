// -*- mode: c++ -*-
// Copyright 2016-2022 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for license details

/**
 * These #include directives pull in the Kaleidoscope firmware core,
 * as well as the Kaleidoscope plugins we use in the Model 100's firmware
 */

// The Kaleidoscope core
#include "Kaleidoscope.h"

// Support for storing the keymap in EEPROM
#include "Kaleidoscope-EEPROM-Settings.h"

// Support for communicating with the host via a simple Serial protocol
#include "Kaleidoscope-FocusSerial.h"

// Support for querying the firmware version via Focus
#include "Kaleidoscope-FirmwareVersion.h"

// Support for keys that move the mouse
#include "Kaleidoscope-MouseKeys.h"

// Support for macros
#include "Kaleidoscope-Macros.h"

// Support for controlling the keyboard's LEDs
#include "Kaleidoscope-LEDControl.h"

// Support for the "Boot greeting" effect, which pulses the 'LED' button for 10s
// when the keyboard is connected to a computer (or that computer is powered on)
#include "Kaleidoscope-LEDEffect-BootGreeting.h"

// Support for an LED mode that makes all the LEDs 'breathe'
#include "Kaleidoscope-LEDEffect-Breathe.h"

// Support for an LED mode that makes a red pixel chase a blue pixel across the keyboard
#include "Kaleidoscope-LEDEffect-Chase.h"

// Support for LED modes that pulse the keyboard's LED in a rainbow pattern
#include "Kaleidoscope-LEDEffect-Rainbow.h"

// Support for an LED mode that lights up the keys as you press them
#include "Kaleidoscope-LED-Stalker.h"

#include "Kaleidoscope-LEDEffect-DigitalRain.h"

// Support for shared palettes for other plugins, like Colormap below
#include "Kaleidoscope-LED-Palette-Theme.h"

// Support for an LED mode that lets one configure per-layer color maps
#include "Kaleidoscope-Colormap.h"

// Support for turning the LEDs off after a certain amount of time
#include "Kaleidoscope-IdleLEDs.h"

// Support for overlaying colors
#include "Kaleidoscope-Colormap-Overlay.h"

// Support for setting and saving the default LED mode
#include "Kaleidoscope-DefaultLEDModeConfig.h"

// Support for changing the brightness of the LEDs
#include "Kaleidoscope-LEDBrightnessConfig.h"

// Support for Keyboardio's internal keyboard testing mode
#include "Kaleidoscope-HardwareTestMode.h"

// Support for host power management (suspend & wakeup)
#include "Kaleidoscope-HostPowerManagement.h"

// Support for magic combos (key chords that trigger an action)
#include "Kaleidoscope-MagicCombo.h"

// Support for USB quirks, like changing the key state report protocol
#include "Kaleidoscope-USB-Quirks.h"

// Support for secondary actions on keys
#include "Kaleidoscope-Qukeys.h"

// Support for one-shot modifiers and layer keys
#include "Kaleidoscope-OneShot.h"
#include "Kaleidoscope-Escape-OneShot.h"

/** This 'enum' is a list of all the macros used by the Model 100's firmware
  * The names aren't particularly important. What is important is that each
  * is unique.
  *
  * These are the names of your macros. They'll be used in two places.
  * The first is in your keymap definitions. There, you'll use the syntax
  * `M(MACRO_NAME)` to mark a specific keymap position as triggering `MACRO_NAME`
  *
  * The second usage is in the 'switch' statement in the `macroAction` function.
  * That switch statement actually runs the code associated with a macro when
  * a macro key is pressed.
  */

enum {
  MACRO_VERSION_INFO,
  MACRO_ANY,
};


/** The Model 100's key layouts are defined as 'keymaps'. By default, there are three
  * keymaps: The standard QWERTY keymap, the "Function layer" keymap and the "Numpad"
  * keymap.
  *
  * Each keymap is defined as a list using the 'KEYMAP_STACKED' macro, built
  * of first the left hand's layout, followed by the right hand's layout.
  *
  * Keymaps typically consist mostly of `Key_` definitions. There are many, many keys
  * defined as part of the USB HID Keyboard specification. You can find the names
  * (if not yet the explanations) for all the standard `Key_` defintions offered by
  * Kaleidoscope in these files:
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/kaleidoscope/key_defs/keyboard.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/kaleidoscope/key_defs/consumerctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/kaleidoscope/key_defs/sysctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/kaleidoscope/key_defs/keymaps.h
  *
  * Additional things that should be documented here include
  *   using ___ to let keypresses fall through to the previously active layer
  *   using XXX to mark a keyswitch as 'blocked' on this layer
  *   using ShiftToLayer() and LockLayer() keys to change the active keymap.
  *   keeping NUM and FN consistent and accessible on all layers
  *
  * The PROG key is special, since it is how you indicate to the board that you
  * want to flash the firmware. However, it can be remapped to a regular key.
  * When the keyboard boots, it first looks to see whether the PROG key is held
  * down; if it is, it simply awaits further flashing instructions. If it is
  * not, it continues loading the rest of the firmware and the keyboard
  * functions normally, with whatever binding you have set to PROG. More detail
  * here: https://community.keyboard.io/t/how-the-prog-key-gets-you-into-the-bootloader/506/8
  *
  * The "keymaps" data structure is a list of the keymaps compiled into the firmware.
  * The order of keymaps in the list is important, as the ShiftToLayer(#) and LockLayer(#)
  * macros switch to key layers based on this list.
  *
  *

  * A key defined as 'ShiftToLayer(FUNCTION)' will switch to FUNCTION while held.
  * Similarly, a key defined as 'LockLayer(NUMPAD)' will switch to NUMPAD when tapped.
  */

/**
  * Layers are "0-indexed" -- That is the first one is layer 0. The second one is layer 1.
  * The third one is layer 2.
  * This 'enum' lets us use names like QWERTY, FUNCTION, and NUMPAD in place of
  * the numbers 0, 1 and 2.
  *
  */

enum {
  QWERTY,
  MEDIA,
  NAV,
  MOUSE,
  SYMBOL,
  NUMBER,
  FUNCTION
}; // layers


#define Key_Excl        LSHIFT(Key_1)
#define Key_At          LSHIFT(Key_2)
#define Key_Hash        LSHIFT(Key_3)
#define Key_Dollar      LSHIFT(Key_4)
#define Key_Pct         LSHIFT(Key_5)
#define Key_Caret       LSHIFT(Key_6)
#define Key_Amp         LSHIFT(Key_7)
#define Key_Star        LSHIFT(Key_8)
#define Key_Plus        LSHIFT(Key_Equals)

#define Key_LArrow Key_LeftArrow
#define Key_DnArrow Key_DownArrow
#define Key_RArrow Key_RightArrow

#define Key_mScrL Key_mouseScrollL
#define Key_mScrDn Key_mouseScrollDn
#define Key_mScrUp Key_mouseScrollUp
#define Key_mScrR Key_mouseScrollR
#define Key_mBtnR Key_mouseBtnR

#define Key_LCurly LSHIFT(Key_LBracket)  
#define Key_RCurly LSHIFT(Key_RBracket)
#define Key_Colon LSHIFT(Key_Semicolon) 
#define Key_Plus LSHIFT(Key_Equals)
#define Key_Tilde LSHIFT(Key_Backtick)  
#define Key_Pipe LSHIFT(Key_Backslash)
#define Key_LParen Key_LeftParen
#define Key_RParen Key_RightParen
#define Key_UScore LSHIFT(Key_Minus)

#define Key_PrScrn Key_PrintScreen
#define Key_ScrLk Key_ScrollLock

#define C_Prev Consumer_ScanPreviousTrack
#define C_Next Consumer_ScanNextTrack
#define C_VolUp Consumer_VolumeIncrement
#define C_VolDn Consumer_VolumeDecrement
#define C_Stop Consumer_Stop
#define C_PP Consumer_PlaySlashPause
#define C_Mute Consumer_Mute

#define MO(n) ShiftToLayer(n)

#define Key_LedNext Key_LEDEffectNext

/* This comment temporarily turns off astyle's indent enforcement
 *   so we can make the keymaps actually resemble the physical key layout better
 */
// clang-format off

KEYMAPS(
  [QWERTY] = KEYMAP_STACKED
  (
       ___          ,___          ,___          ,___          ,___          ,___          ,Key_LedNext
      ,___          ,Key_Q        ,Key_W        ,Key_E        ,Key_R        ,Key_T        ,___
      ,___          ,Key_A        ,Key_S        ,Key_D        ,Key_F        ,Key_G
      ,___          ,Key_Z        ,Key_X        ,Key_C        ,Key_V        ,Key_B        ,___
      ,MO(MEDIA)    ,MO(NAV)      ,MO(MOUSE)    ,Key_LShift
      ,___
                                
      
      ,___          ,___          ,___          ,___          ,___          ,___          ,___ 
      ,___          ,Key_Y        ,Key_U        ,Key_I        ,Key_O        ,Key_P        ,___
                    ,Key_H        ,Key_J        ,Key_K        ,Key_L        ,Key_Quote    ,___
      ,___          ,Key_N        ,Key_M        ,Key_Comma    ,Key_Period   ,Key_Slash    ,___
      ,Key_LShift   ,MO(SYMBOL)   ,MO(NUMBER)   ,MO(FUNCTION) 
      ,___
  ),

  [MEDIA] = KEYMAP_STACKED
  (
       ___          ,___          ,___          ,___          ,___          ,___          ,___
      ,___          ,LCTRL(Key_Z) ,LCTRL(Key_X) ,LCTRL(Key_C) ,LCTRL(Key_V) ,LCTRL(Key_Y) ,___        
      ,___          ,Key_LGui     ,Key_LAlt     ,Key_LCtrl    ,Key_LShift   ,___  
      ,___          ,___          ,___          ,___          ,___          ,___          ,___
      ,___          ,___          ,___          ,___
      ,___
                                
      
      ,___          ,___          ,___          ,___          ,___          ,___          ,___ 
      ,___          ,___          ,___          ,___          ,___          ,___          ,___ 
                    ,___          ,C_Prev       ,C_VolDn      ,C_VolUp      ,C_Next       ,___
      ,___          ,___          ,___          ,___          ,___          ,___          ,___ 
      ,___          ,C_Stop       ,C_PP         ,C_Mute       
      ,___
  ),

  [NAV] = KEYMAP_STACKED
  (
       ___          ,___          ,___          ,___          ,___          ,___          ,___
      ,___          ,LCTRL(Key_Z) ,LCTRL(Key_X) ,LCTRL(Key_C) ,LCTRL(Key_V) ,LCTRL(Key_Y) ,___        
      ,___          ,Key_LGui     ,Key_LAlt     ,Key_LCtrl    ,Key_LShift   ,___  
      ,___          ,___          ,___          ,___          ,___          ,___          ,___
      ,___          ,___          ,___          ,___
      ,___
                                
      
      ,___          ,___          ,___          ,___          ,___          ,___          ,___ 
      ,___          ,LCTRL(Key_Y) ,LCTRL(Key_V) ,LCTRL(Key_C) ,LCTRL(Key_X) ,LCTRL(Key_Z) ,___ 
                    ,Key_CapsLock ,Key_LArrow   ,Key_DnArrow  ,Key_UpArrow  ,Key_RArrow   ,___
      ,___          ,Key_Insert   ,Key_Home     ,Key_PageDown ,Key_PageUp   ,Key_End      ,___ 
      ,___          ,Key_Enter    ,Key_Backspace,Key_Delete   
      ,___
  ),

  [MOUSE] = KEYMAP_STACKED
  (
       ___          ,___          ,___          ,___          ,___          ,___          ,___
      ,___          ,LCTRL(Key_Z) ,LCTRL(Key_X) ,LCTRL(Key_C) ,LCTRL(Key_V) ,LCTRL(Key_Y) ,___        
      ,___          ,Key_LGui     ,Key_LAlt     ,Key_LCtrl    ,Key_LShift   ,___  
      ,___          ,___          ,___          ,___          ,___          ,___          ,___
      ,___          ,___          ,___          ,___
      ,___
                                
      
      ,___          ,___          ,___          ,___          ,___          ,___          ,___ 
      ,___          ,LCTRL(Key_Y) ,LCTRL(Key_V) ,LCTRL(Key_C) ,LCTRL(Key_X) ,LCTRL(Key_Z) ,___ 
                    ,___          ,Key_mouseL   ,Key_mouseDn  ,Key_mouseUp  ,Key_mouseR   ,___
      ,___          ,___          ,Key_mScrL    ,Key_mScrDn   ,Key_mScrUp   ,Key_mScrR    ,___ 
      ,___          ,Key_mouseBtnR,Key_mouseBtnL,Key_mouseBtnM
      ,___
  ),

  [SYMBOL] = KEYMAP_STACKED
  (
       ___          ,___          ,___          ,___          ,___          ,___          ,___
      ,___          ,Key_LCurly   ,Key_Amp      ,Key_Star     ,Key_LParen   ,Key_RCurly   ,___        
      ,___          ,Key_Colon    ,Key_Dollar   ,Key_Pct      ,Key_Caret    ,Key_Plus
      ,___          ,Key_Tilde    ,Key_Excl     ,Key_At       ,Key_Hash     ,Key_Pipe     ,___
      ,Key_LParen   ,Key_RParen   ,Key_UScore   ,___
      ,___
                                
      
      ,___          ,___          ,___          ,___          ,___          ,___          ,___ 
      ,___          ,LCTRL(Key_Y) ,LCTRL(Key_V) ,LCTRL(Key_C) ,LCTRL(Key_X) ,LCTRL(Key_Z) ,___ 
                    ,___          ,Key_LShift   ,Key_LCtrl    ,Key_LAlt     ,Key_LGui     ,___
      ,___          ,___          ,___          ,___          ,___          ,___          ,___ 
      ,___          ,___          ,___          ,___          
      ,___
  ),

  [NUMBER] = KEYMAP_STACKED
  (
       ___          ,___          ,___          ,___          ,___          ,___          ,___
      ,___          ,Key_LBracket ,Key_7        ,Key_8        ,Key_9        ,Key_RBracket ,___        
      ,___          ,Key_Semicolon,Key_4        ,Key_5        ,Key_6        ,Key_Equals
      ,___          ,Key_Backtick ,Key_1        ,Key_2        ,Key_3        ,Key_Backslash,___
      ,Key_Period   ,Key_0        ,Key_Minus    ,___
      ,___
                                
      
      ,___          ,___          ,___          ,___          ,___          ,___          ,___ 
      ,___          ,LCTRL(Key_Y) ,LCTRL(Key_V) ,LCTRL(Key_C) ,LCTRL(Key_X) ,LCTRL(Key_Z) ,___ 
                    ,___          ,Key_LShift   ,Key_LCtrl    ,Key_LAlt     ,Key_LGui     ,___
      ,___          ,___          ,___          ,___          ,___          ,___          ,___ 
      ,___          ,___          ,___          ,___          
      ,___
  ),

  [FUNCTION] = KEYMAP_STACKED
  (
       ___          ,___          ,___          ,___          ,___          ,___          ,___
      ,___          ,Key_F12      ,Key_F7       ,Key_F8       ,Key_F9       ,Key_PrScrn   ,___        
      ,___          ,Key_F11      ,Key_F4       ,Key_F5       ,Key_F6       ,Key_ScrLk 
      ,___          ,Key_F10      ,Key_F1       ,Key_F2       ,Key_F3       ,Key_Pause    ,___
      ,Key_Esc      ,Key_Space    ,Key_Tab      ,___
      ,___
                                
      
      ,___          ,___          ,___          ,___          ,___          ,___          ,___ 
      ,___          ,LCTRL(Key_Y) ,LCTRL(Key_V) ,LCTRL(Key_C) ,LCTRL(Key_X) ,LCTRL(Key_Z) ,___ 
                    ,___          ,Key_LShift   ,Key_LCtrl    ,Key_LAlt     ,Key_LGui     ,___
      ,___          ,___          ,___          ,___          ,___          ,___          ,___ 
      ,___          ,___          ,___          ,___          
      ,___
  )
) // KEYMAPS(

/* Re-enable astyle's indent enforcement */
// clang-format on

#define RGB_UNSET CRGB(0x00, 0x00, 0x00)
#define RGB_RED   CRGB(0xff, 0x00, 0x00)

// Set up a default palette to be use for the Colormap and Colormap-Overlay
// plugins
PALETTE(
  RGB_UNSET,
  RGB_UNSET,
  RGB_UNSET,
  RGB_UNSET,
  RGB_UNSET,
  RGB_UNSET,
  RGB_UNSET,
  RGB_UNSET,
  RGB_UNSET,
  RGB_UNSET,
  RGB_UNSET,
  RGB_UNSET,
  RGB_UNSET,
  RGB_UNSET,
  RGB_UNSET,
  RGB_UNSET,
  RGB_UNSET,
  RGB_UNSET,
  RGB_UNSET,
  RGB_UNSET,
  RGB_UNSET,
  RGB_UNSET,
  RGB_UNSET,
  RGB_RED)  // PALETTE(

/** versionInfoMacro handles the 'firmware version info' macro
 *  When a key bound to the macro is pressed, this macro
 *  prints out the firmware build information as virtual keystrokes
 */

static void versionInfoMacro(uint8_t key_state) {
  if (keyToggledOn(key_state)) {
    Macros.type(PSTR("Keyboardio Model 100 - Firmware version "));
    Macros.type(PSTR(KALEIDOSCOPE_FIRMWARE_VERSION));
  }
}

/** anyKeyMacro is used to provide the functionality of the 'Any' key.
 *
 * When the 'any key' macro is toggled on, a random alphanumeric key is
 * selected. While the key is held, the function generates a synthetic
 * keypress event repeating that randomly selected key.
 *
 */

static void anyKeyMacro(KeyEvent &event) {
  if (keyToggledOn(event.state)) {
    event.key.setKeyCode(Key_A.getKeyCode() + (uint8_t)(millis() % 36));
    event.key.setFlags(0);
  }
}


/** macroAction dispatches keymap events that are tied to a macro
    to that macro. It takes two uint8_t parameters.

    The first is the macro being called (the entry in the 'enum' earlier in this file).
    The second is the state of the keyswitch. You can use the keyswitch state to figure out
    if the key has just been toggled on, is currently pressed or if it's just been released.

    The 'switch' statement should have a 'case' for each entry of the macro enum.
    Each 'case' statement should call out to a function to handle the macro in question.

 */

const macro_t *macroAction(uint8_t macro_id, KeyEvent &event) {
  switch (macro_id) {

  case MACRO_VERSION_INFO:
    versionInfoMacro(event.state);
    break;

  case MACRO_ANY:
    anyKeyMacro(event);
    break;
  }
  return MACRO_NONE;
}


// These 'solid' color effect definitions define a rainbow of
// LED color modes calibrated to draw 500mA or less on the
// Keyboardio Model 100.


/** macroAction dispatches keymap events that are tied to a macro
    to that macro. It takes two uint8_t parameters.

    The first is the macro being called (the entry in the 'enum' earlier in this file).
    The second is the state of the keyswitch. You can use the keyswitch state to figure out
    if the key has just been toggled on, is currently pressed or if it's just been released.

    The 'switch' statement should have a 'case' for each entry of the macro enum.
    Each 'case' statement should call out to a function to handle the macro in question.

 */

const macro_t *macroAction(uint8_t macro_id, KeyEvent &event) {
  switch (macro_id) {

  case MACRO_VERSION_INFO:
    versionInfoMacro(event.state);
    break;

  case MACRO_ANY:
    anyKeyMacro(event);
    break;
  }
  return MACRO_NONE;
}

/** toggleLedsOnSuspendResume toggles the LEDs off when the host goes to sleep,
 * and turns them back on when it wakes up.
 */
void toggleLedsOnSuspendResume(kaleidoscope::plugin::HostPowerManagement::Event event) {
  switch (event) {
  case kaleidoscope::plugin::HostPowerManagement::Suspend:
  case kaleidoscope::plugin::HostPowerManagement::Sleep:
    LEDControl.disable();
    break;
  case kaleidoscope::plugin::HostPowerManagement::Resume:
    LEDControl.enable();
    break;
  }
}

/** hostPowerManagementEventHandler dispatches power management events (suspend,
 * resume, and sleep) to other functions that perform action based on these
 * events.
 */
void hostPowerManagementEventHandler(kaleidoscope::plugin::HostPowerManagement::Event event) {
  toggleLedsOnSuspendResume(event);
}

/** This 'enum' is a list of all the magic combos used by the Model 100's
 * firmware The names aren't particularly important. What is important is that
 * each is unique.
 *
 * These are the names of your magic combos. They will be used by the
 * `USE_MAGIC_COMBOS` call below.
 */
enum {
  // Toggle between Boot (6-key rollover; for BIOSes and early boot) and NKRO
  // mode.
  COMBO_TOGGLE_NKRO_MODE,
  // Enter test mode
  COMBO_ENTER_TEST_MODE
};

/** Wrappers, to be used by MagicCombo. **/

/**
 * This simply toggles the keyboard protocol via USBQuirks, and wraps it within
 * a function with an unused argument, to match what MagicCombo expects.
 */
static void toggleKeyboardProtocol(uint8_t combo_index) {
  USBQuirks.toggleKeyboardProtocol();
}

/**
 * Toggles between using the built-in keymap, and the EEPROM-stored one.
 */
static void toggleKeymapSource(uint8_t combo_index) {
  Layer.getKey = Layer.getKeyFromPROGMEM;
}

/**
 *  This enters the hardware test mode
 */
static void enterHardwareTestMode(uint8_t combo_index) {
  HardwareTestMode.runTests();
}


/** Magic combo list, a list of key combo and action pairs the firmware should
 * recognise.
 */
USE_MAGIC_COMBOS({.action = toggleKeyboardProtocol,
                  // Left Fn + Esc + Shift
                  .keys = {R3C6, R2C6, R3C7}},
                 {.action = enterHardwareTestMode,
                  // Left Fn + Prog + LED
                  .keys = {R3C6, R0C0, R0C6}},
                 {.action = toggleKeymapSource,
                  // Left Fn + Prog + Shift
                  .keys = {R3C6, R0C0, R3C7}});

// First, tell Kaleidoscope which plugins you want to use.
// The order can be important. For example, LED effects are
// added in the order they're listed here.
KALEIDOSCOPE_INIT_PLUGINS(
  // The EEPROMSettings & EEPROMKeymap plugins make it possible to have an
  // editable keymap in EEPROM.
  EEPROMSettings,

  // Focus allows bi-directional communication with the host, and is the
  // interface through which the keymap in EEPROM can be edited.
  Focus,

  // FocusSettingsCommand adds a few Focus commands, intended to aid in
  // changing some settings of the keyboard, such as the default layer (via the
  // `settings.defaultLayer` command)
  FocusSettingsCommand,

  // FocusEEPROMCommand adds a set of Focus commands, which are very helpful in
  // both debugging, and in backing up one's EEPROM contents.
  FocusEEPROMCommand,

  // The boot greeting effect pulses the LED button for 10 seconds after the
  // keyboard is first connected
  BootGreetingEffect,

  // The hardware test mode, which can be invoked by tapping Prog, LED and the
  // left Fn button at the same time.
  HardwareTestMode,

  // LEDControl provides support for other LED modes
  LEDControl,

  // We start with the LED effect that turns off all the LEDs.
  LEDOff,

  // The rainbow effect changes the color of all of the keyboard's keys at the same time
  // running through all the colors of the rainbow.
  LEDRainbowEffect,

  // The rainbow wave effect lights up your keyboard with all the colors of a rainbow
  // and slowly moves the rainbow across your keyboard
  LEDRainbowWaveEffect,

  // The chase effect follows the adventure of a blue pixel which chases a red pixel across
  // your keyboard. Spoiler: the blue pixel never catches the red pixel
  LEDChaseEffect,

  // The breathe effect slowly pulses all of the LEDs on your keyboard
  LEDBreatheEffect,

  // The stalker effect lights up the keys you've pressed recently
  StalkerEffect,

  LEDDigitalRainEffect,

  // The LED Palette Theme plugin provides a shared palette for other plugins,
  // like Colormap below
  LEDPaletteTheme,

  // The Colormap effect makes it possible to set up per-layer colormaps
  ColormapEffect,

  // The colormap overlay plugin provides a way to set LED colors regardless of
  // the active LED effect. This is used for lighting up the keys assigned in
  // the factory 'numpad' mode
  ColormapOverlay,

  // The MouseKeys plugin lets you add keys to your keymap which move the mouse.
  // The MouseKeysConfig plugin lets Chrysalis configure some aspects of the
  // plugin.
  MouseKeys,
  MouseKeysConfig,

  // The HostPowerManagement plugin allows us to turn LEDs off when then host
  // goes to sleep, and resume them when it wakes up.
  HostPowerManagement,

  // The MagicCombo plugin lets you use key combinations to trigger custom
  // actions - a bit like Macros, but triggered by pressing multiple keys at the
  // same time.
  MagicCombo,

  // The USBQuirks plugin lets you do some things with USB that we aren't
  // comfortable - or able - to do automatically, but can be useful
  // nevertheless. Such as toggling the key report protocol between Boot (used
  // by BIOSes) and Report (NKRO).
  USBQuirks,

  // The Qukeys plugin enables the "Secondary action" functionality in
  // Chrysalis. Keys with secondary actions will have their primary action
  // performed when tapped, but the secondary action when held.
  Qukeys,

  // Enables the "Sticky" behavior for modifiers, and the "Layer shift when
  // held" functionality for layer keys.
  OneShot,
  OneShotConfig,
  EscapeOneShot,
  EscapeOneShotConfig,

  // Turns LEDs off after a configurable amount of idle time.
  IdleLEDs,
  PersistentIdleLEDs,

  // The FirmwareVersion plugin lets Chrysalis query the version of the firmware
  // programmatically.
  FirmwareVersion,

  // Enables setting, saving (via Chrysalis), and restoring (on boot) the
  // default LED mode.
  DefaultLEDModeConfig,

  // Enables controlling (and saving) the brightness of the LEDs via Focus.
  LEDBrightnessConfig);

/** The 'setup' function is one of the two standard Arduino sketch functions.
 * It's called when your keyboard first powers up. This is where you set up
 * Kaleidoscope and any plugins.
 */
void setup() {
  // First, call Kaleidoscope's internal setup function
  Kaleidoscope.setup();

  // Add colormap overlays for all keys of the numpad. This makes sure that
  // all keys of the numpad light up once the numpad layer is active.
  //
  // The call signature is:
  // kaleidoscope::plugin::Overlay(<layer>, <key_address>, <palette_index>)
  //
  // Key address matrix: https://github.com/keyboardio/Kaleidoscope/blob/master/plugins/Kaleidoscope-Hardware-Keyboardio-Model100/src/kaleidoscope/device/keyboardio/Model100.h#L175-L205
  //
  // (0, 0) (0, 1) (0, 2) (0, 3) (0, 4) (0, 5) (0, 6) | (0, 9) (0, 10) (0, 11) (0, 12) (0, 13) (0, 14) (0, 15)
  // (1, 0) (1, 1) (1, 2) (1, 3) (1, 4) (1, 5) (1, 6) | (1, 9) (1, 10) (1, 11) (1, 12) (1, 13) (1, 14) (1, 15)
  // (2, 0) (2, 1) (2, 2) (2, 3) (2, 4) (2, 5)        |        (2, 10) (2, 11) (2, 12) (2, 13) (2, 14) (2, 15)
  // (3, 0) (3, 1) (3, 2) (3, 3) (3, 4) (3, 5) (2, 6) | (2, 9) (3, 10) (3, 11) (3, 12) (3, 13) (3, 14) (3, 15)
  //                      (0, 7) (1, 7) (2, 7) (3, 7) | (3, 8) (2, 8)  (1, 8)  (0, 8)
  //                                           (3, 6) | (3, 9)
  COLORMAP_OVERLAYS(
    kaleidoscope::plugin::Overlay(NUMPAD, KeyAddr(0, 11), 23),  // 7
    kaleidoscope::plugin::Overlay(NUMPAD, KeyAddr(1, 11), 23),  // 4
    kaleidoscope::plugin::Overlay(NUMPAD, KeyAddr(2, 11), 23),  // 1
    kaleidoscope::plugin::Overlay(NUMPAD, KeyAddr(3, 11), 23),  // 0
    kaleidoscope::plugin::Overlay(NUMPAD, KeyAddr(0, 12), 23),  // 8
    kaleidoscope::plugin::Overlay(NUMPAD, KeyAddr(1, 12), 23),  // 5
    kaleidoscope::plugin::Overlay(NUMPAD, KeyAddr(2, 12), 23),  // 2
    kaleidoscope::plugin::Overlay(NUMPAD, KeyAddr(3, 12), 23),  // period
    kaleidoscope::plugin::Overlay(NUMPAD, KeyAddr(0, 13), 23),  // 9
    kaleidoscope::plugin::Overlay(NUMPAD, KeyAddr(1, 13), 23),  // 6
    kaleidoscope::plugin::Overlay(NUMPAD, KeyAddr(2, 13), 23),  // 3
    kaleidoscope::plugin::Overlay(NUMPAD, KeyAddr(3, 13), 23),  // multiply
    kaleidoscope::plugin::Overlay(NUMPAD, KeyAddr(0, 14), 23),  // substract
    kaleidoscope::plugin::Overlay(NUMPAD, KeyAddr(1, 14), 23),  // add
    kaleidoscope::plugin::Overlay(NUMPAD, KeyAddr(2, 14), 23),  // equals
    kaleidoscope::plugin::Overlay(NUMPAD, KeyAddr(3, 14), 23),  // divide
    kaleidoscope::plugin::Overlay(NUMPAD, KeyAddr(3, 15), 23),  // enter
    )                                                           // COLORMAP_OVERLAYS(

  // Set the hue of the boot greeting effect to something that will result in a
  // nice green color.
  BootGreetingEffect.hue = 85;

<<<<<<< HEAD
  // We configure the AlphaSquare effect to use RED letters
  AlphaSquare.color = CRGB(255, 0, 0);

=======
>>>>>>> b1cb8f9a (Imitation Miryoku for M100)
  // Set the rainbow effects to be reasonably bright, but low enough
  // to mitigate audible noise in some environments.
  LEDRainbowEffect.brightness(170);
  LEDRainbowWaveEffect.brightness(160);

  // Set the action key the test mode should listen for to Left Fn
  HardwareTestMode.setActionKey(R3C6);

  // The LED Stalker mode has a few effects. The one we like is called
  // 'BlazingTrail'. For details on other options, see
  // https://github.com/keyboardio/Kaleidoscope/blob/master/docs/plugins/LED-Stalker.md
  StalkerEffect.variant = STALKER(BlazingTrail);

  // We need to tell the Colormap plugin how many layers we want to have custom
  // maps for. To make things simple, we set it to eight layers, which is how
  // many editable layers we have (see above).
  ColormapEffect.max_layers(8);
  DefaultColormap.setup();

  // Unless configured otherwise with Chrysalis, we want to make sure that the
  // firmware starts with LED effects off. This avoids over-taxing devices that
  // don't have a lot of power to share with USB devices
  DefaultLEDModeConfig.activateLEDModeIfUnconfigured(&LEDOff);

  Qukeys.setMaxIntervalForTapRepeat(0);
  Qukeys.setOverlapThreshold(80);
  Qukeys.setMinimumHoldTime(125);
  Qukeys.setMinimumPriorInterval(20);

  QUKEYS(
    kaleidoscope::plugin::Qukey(QWERTY, KeyAddr(0, 7), Key_Escape),
    kaleidoscope::plugin::Qukey(QWERTY, KeyAddr(1, 7), Key_Space),
    kaleidoscope::plugin::Qukey(QWERTY, KeyAddr(2, 7), Key_Tab),
    kaleidoscope::plugin::Qukey(QWERTY, KeyAddr(2, 8), Key_Enter),
    kaleidoscope::plugin::Qukey(QWERTY, KeyAddr(1, 8), Key_Backspace),
    kaleidoscope::plugin::Qukey(QWERTY, KeyAddr(0, 8), Key_Delete),
    kaleidoscope::plugin::Qukey(QWERTY, KeyAddr(2, 4), Key_LShift),
    kaleidoscope::plugin::Qukey(QWERTY, KeyAddr(2, 3), Key_LCtrl),
    kaleidoscope::plugin::Qukey(QWERTY, KeyAddr(2, 2), Key_LAlt),
    kaleidoscope::plugin::Qukey(QWERTY, KeyAddr(2, 1), Key_LGui),
    kaleidoscope::plugin::Qukey(QWERTY, KeyAddr(2, 11), Key_LShift),
    kaleidoscope::plugin::Qukey(QWERTY, KeyAddr(2, 12), Key_LCtrl),
    kaleidoscope::plugin::Qukey(QWERTY, KeyAddr(2, 13), Key_LAlt),
    kaleidoscope::plugin::Qukey(QWERTY, KeyAddr(2, 14), Key_LGui),
  );
}

/** loop is the second of the standard Arduino sketch functions.
  * As you might expect, it runs in a loop, never exiting.
  *
  * For Kaleidoscope-based keyboard firmware, you usually just want to
  * call Kaleidoscope.loop(); and not do anything custom here.
  */

void loop() {
  Kaleidoscope.loop();
}
