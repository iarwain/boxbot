#include "orxVirtualGamePad.h"
#include "VirtualGamePadButton.h"

static const orxSTRING szVirtualGamePadButton = "VirtualGamePadButton";

//! Static variables
orxVIEWPORT *orxVirtualGamePad::spstViewport = orxNULL;
orxCAMERA   *orxVirtualGamePad::spstCamera = orxNULL;

static orxSTATUS orxFASTCALL orxVirtualGamePad_EventHandler(const orxEVENT *_pstEvent)
{
  orxSTATUS eResult = orxSTATUS_SUCCESS;

  switch(_pstEvent->eID)
  {
  case orxSYSTEM_EVENT_TOUCH_BEGIN:
  case orxSYSTEM_EVENT_TOUCH_MOVE:
  case orxSYSTEM_EVENT_TOUCH_END:
    break;
  default:
    break;
  }

  return eResult;
}

orxSTATUS orxVirtualGamePad::Init(orxVIEWPORT* _pstViewport)
{
  orxSTATUS eResult = orxSTATUS_SUCCESS;

  orxASSERT(_pstViewport != orxNULL);

  spstViewport = _pstViewport;
  spstCamera = orxViewport_GetCamera(spstViewport);

  eResult = orxEvent_AddHandler(orxEVENT_TYPE_SYSTEM, orxVirtualGamePad_EventHandler);

  return eResult;
}

void orxVirtualGamePad::Exit()
{
  orxEvent_RemoveHandler(orxEVENT_TYPE_SYSTEM, orxVirtualGamePad_EventHandler);
}

void orxVirtualGamePad::BindObjects()
{
  ScrollBindObject<VirtualGamePadButton>(szVirtualGamePadButton);
}

orxSTATUS orxVirtualGamePad::RegisterInput(VirtualGamePadInput *_poVirtualGamePadInput)
{
  orxSTATUS eResult = orxSTATUS_SUCCESS;

  return eResult;
}

void orxVirtualGamePad::UnregisterInput(VirtualGamePadInput *_poVirtualGamePadInput)
{

}
