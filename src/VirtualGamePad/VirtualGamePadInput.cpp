/*
 * VirtualGamePadInput.cpp
 *
 *  Created on: Mar 24, 2015
 *      Author: philippe
 */

#include "VirtualGamePadInput.h"
#include "orxVirtualGamePad.h"

static const orxSTRING szConfigInputName = "InputName";

void VirtualGamePadInput::OnCreate()
{
  orxMemory_Zero(&mstNode, sizeof(orxLINKLIST_NODE));
  mzInputName = orxConfig_GetString(szConfigInputName);

  orxVirtualGamePad::RegisterInput(this);
}

void VirtualGamePadInput::OnDelete()
{
  orxVirtualGamePad::UnregisterInput(this);
}
