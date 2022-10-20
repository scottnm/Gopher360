#pragma once

#include <windows.h>
#include <xinput.h>
#include <stdint.h>

class CXBOXController
{
private:
  XINPUT_STATE _controllerState;
  int _controllerNum;
public:
  CXBOXController(int playerNumber);
  XINPUT_STATE GetState();
  bool IsConnected();
  void Vibrate(uint16_t leftVal, uint16_t rightVal);
};
