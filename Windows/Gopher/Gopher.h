#include <windows.h> // for Beep()
#include <iostream>
#include <vector>
#include <list>
#include <xinput.h> // controller
#include <stdio.h> // for printf
#include <cmath> // for abs()
#include <mmdeviceapi.h> // vol
#include <endpointvolume.h> // vol
#include <tchar.h>
#include <ShlObj.h>

#include <map>

#include "CXBOXController.h"

#pragma once
class Gopher
{
private:
  float DEAD_ZONE = 6000;                 // Thumbstick dead zone to use for mouse movement. Absolute maximum shall be 65534.
  float SCROLL_DEAD_ZONE = 5000;          // Thumbstick dead zone to use for scroll wheel movement. Absolute maximum shall be 65534.
  int TRIGGER_DEAD_ZONE = 0;            // Dead zone for the left and right triggers to detect a trigger press. 0 means that any press to trigger will be read as a button press.
  float SCROLL_SPEED = 0.1f;             // Speed at which you scroll.
  const int FPS = 150;                  // Update rate of the main Gopher loop. Interpreted as cycles-per-second.
  const int SLEEP_AMOUNT = 1000 / FPS;  // Number of milliseconds to sleep per iteration.
  int SWAP_THUMBSTICKS = 0;             // Swaps the function of the thumbsticks when not equal to 0.

  XINPUT_STATE _currentState;

  // Cursor speed settings
  const float SPEED_ULTRALOW = 0.005f;
  const float SPEED_LOW = 0.015f;
  const float SPEED_MED = 0.025f;
  const float SPEED_HIGH = 0.04f;
  float speed = SPEED_MED;
  float acceleration_factor = 0.0f;

  float _xRest = 0.0f;
  float _yRest = 0.0f;

  bool _disabled = false;           // Disables the Gopher controller mapping.
  bool _vibrationDisabled = false;  // Prevents Gopher from producing controller vibrations.
  bool _hidden = false;             // Gopher main window visibility.
  bool _lTriggerPrevious = false;   // Previous state of the left trigger.
  bool _rTriggerPrevious = false;   // Previous state of the right trigger.

  std::vector<float> speeds;	            // Contains actual speeds to choose
  std::vector<std::string> speed_names;   // Contains display names of speeds to display
  unsigned int speed_idx = 0;

  // Mouse Clicks
  DWORD CONFIG_MOUSE_LEFT = NULL;
  DWORD CONFIG_MOUSE_RIGHT = NULL;
  DWORD CONFIG_MOUSE_MIDDLE = NULL;

  // Gopher Settings
  DWORD CONFIG_HIDE = NULL;
  DWORD CONFIG_DISABLE = NULL;
  DWORD CONFIG_DISABLE_VIBRATION = NULL;
  DWORD CONFIG_SPEED_CHANGE = NULL;
  DWORD CONFIG_OSK = NULL;

  // Gamepad bindings
  WORD GAMEPAD_DPAD_UP = NULL;
  WORD GAMEPAD_DPAD_DOWN = NULL;
  WORD GAMEPAD_DPAD_LEFT = NULL;
  WORD GAMEPAD_DPAD_RIGHT = NULL;
  WORD GAMEPAD_START = NULL;
  WORD GAMEPAD_BACK = NULL;
  WORD GAMEPAD_LEFT_THUMB = NULL;
  WORD GAMEPAD_RIGHT_THUMB = NULL;
  WORD GAMEPAD_LEFT_SHOULDER = NULL;
  WORD GAMEPAD_RIGHT_SHOULDER = NULL;
  WORD GAMEPAD_A = NULL;
  WORD GAMEPAD_B = NULL;
  WORD GAMEPAD_X = NULL;
  WORD GAMEPAD_Y = NULL;
  WORD GAMEPAD_TRIGGER_LEFT = NULL;
  WORD GAMEPAD_TRIGGER_RIGHT = NULL;

  // Button press state logic variables
  std::map<DWORD, bool> _xboxClickStateLastIteration;
  std::map<DWORD, bool> _xboxClickIsDown;
  std::map<DWORD, bool> _xboxClickIsDownLong;
  std::map<DWORD, int> _xboxClickDownLength;
  std::map<DWORD, bool> _xboxClickIsUp;

  std::list<WORD> _pressedKeys;

  CXBOXController* _controller;

public:

  Gopher(CXBOXController* controller);

  void loadConfigFile();

  void loop();

  void pulseVibrate(const int duration, const uint16_t l, const uint16_t r) const;

  void toggleWindowVisibility();

  static void setWindowVisibility(const bool& hidden);

  float getDelta(short tx);

  float getMult(float length, float deadzone, float accel);

  void handleMouseMovement();

  void handleDisableButton();

  void handleVibrationButton();

  void handleScrolling();

  void handleTriggers(WORD lKey, WORD rKey);

  bool xboxClickStateExists(DWORD xinput);

  void mapKeyboard(DWORD STATE, WORD key);

  void mapMouseClick(DWORD STATE, DWORD keyDown, DWORD keyUp);

  void setXboxClickState(DWORD state);

  HWND getOskWindow();

private:

  bool erasePressedKey(WORD key);
};
