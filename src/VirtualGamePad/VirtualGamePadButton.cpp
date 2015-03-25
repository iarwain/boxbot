/*
 * VirutalGamePadButton.cpp
 *
 *  Created on: Mar 24, 2015
 *      Author: philippe
 */

#include "VirtualGamePadButton.h"

static const orxSTRING szConfigInputName = "InputName";

void VirtualGamePadButton::ProcessTouch(orxVECTOR *_pvPosition)
{
  orxInput_SetPermanentValue(mzInputName, orxFLOAT_1);
}

void VirtualGamePadButton::Reset()
{
  orxInput_ResetValue(mzInputName);
}

void VirtualGamePadButton::OnCreate()
{
  mzInputName = orxConfig_GetString(szConfigInputName);
}

void VirtualGamePadButton::OnDelete()
{
}
