/*
 * VirutalGamePadButton.cpp
 *
 *  Created on: Mar 24, 2015
 *      Author: philippe
 */

#include "VirtualGamePadButton.h"

static  const orxSTRING szConfigInputName       = "InputName";
static  const orxSTRING szConfigOnPressedTrack  = "ButtonOnPressedTrack";
static  const orxSTRING szConfigOnReleasedTrack = "ButtonOnReleasedTrack";

void VirtualGamePadButton::ProcessTouch(orxVECTOR *_pvPosition)
{
  orxInput_SetPermanentValue(mzInputName, orxFLOAT_1);

  PushConfigSection();
  if(orxConfig_HasValue(szConfigOnPressedTrack))
  {
    orxObject_AddTimeLineTrack(GetOrxObject(), orxConfig_GetString(szConfigOnPressedTrack));
  }
  PopConfigSection();
}

void VirtualGamePadButton::Reset()
{
  orxInput_ResetValue(mzInputName);

  PushConfigSection();
  if(orxConfig_HasValue(szConfigOnReleasedTrack))
  {
    orxObject_AddTimeLineTrack(GetOrxObject(), orxConfig_GetString(szConfigOnReleasedTrack));
  }
  PopConfigSection();
}

void VirtualGamePadButton::OnCreate()
{
  mzInputName = orxConfig_GetString(szConfigInputName);
}

void VirtualGamePadButton::OnDelete()
{
}
