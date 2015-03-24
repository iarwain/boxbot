/*
 * VirtualGamePadInput.cpp
 *
 *  Created on: Mar 24, 2015
 *      Author: philippe
 */

#include "VirtualGamePadInput.h"
#include "orxVirtualGamePad.h"

void VirtualGamePadInput::OnCreate()
{
  orxVirtualGamePad::RegisterInput(this);
}

void VirtualGamePadInput::OnDelete()
{
  orxVirtualGamePad::UnregisterInput(this);
}
