#include "orxVirtualGamePad.h"
#include "VirtualGamePadButton.h"

#define MAX_POINTERS 32

static VirtualGamePadInput* spoFocusedInputs[MAX_POINTERS];

static  const orxSTRING szVirtualGamePadButton = "VirtualGamePadButton";
static  const orxSTRING szGroupVirtualGamePad  = "orxVirtualGamePad";

//! Static variables
orxVIEWPORT   *orxVirtualGamePad::spstViewport = orxNULL;
orxCAMERA     *orxVirtualGamePad::spstCamera = orxNULL;
orxLINKLIST    orxVirtualGamePad::sstInputList;

extern "C" orxSTATUS orxFASTCALL orxVirtualGamePad::EventHandler(const orxEVENT *_pstEvent)
{
  orxSTATUS eResult = orxSTATUS_SUCCESS;
  orxSYSTEM_EVENT_PAYLOAD *pstPayload;
  const orxSTRING zInputName;
  orxVECTOR vTouchPos;

  switch(_pstEvent->eID)
  {
  case orxSYSTEM_EVENT_TOUCH_BEGIN:
  case orxSYSTEM_EVENT_TOUCH_MOVE:
    VirtualGamePadInput *poInput;

    pstPayload = (orxSYSTEM_EVENT_PAYLOAD *) _pstEvent->pstPayload;
    orxVector_Set(&vTouchPos, pstPayload->stTouch.fX, pstPayload->stTouch.fY, orxFLOAT_0);
    orxRender_GetWorldPosition(&vTouchPos, spstViewport, &vTouchPos);

    poInput = GetVirutalInput(&vTouchPos);

    if(poInput != orxNULL)
    {
      if(spoFocusedInputs[pstPayload->stTouch.u32ID] == orxNULL)
      {
        spoFocusedInputs[pstPayload->stTouch.u32ID] = poInput;
        zInputName = poInput->GetInputName();
        orxInput_SetPermanentValue(zInputName, orxFLOAT_1);
      }
      else if(spoFocusedInputs[pstPayload->stTouch.u32ID] != poInput)
      {
        zInputName = spoFocusedInputs[pstPayload->stTouch.u32ID]->GetInputName();
        orxInput_ResetValue(zInputName);
        spoFocusedInputs[pstPayload->stTouch.u32ID] = poInput;
        zInputName = poInput->GetInputName();
        orxInput_SetPermanentValue(zInputName, orxFLOAT_1);
      }
    }
    else
    {
      if(spoFocusedInputs[pstPayload->stTouch.u32ID] != orxNULL)
      {
        zInputName = spoFocusedInputs[pstPayload->stTouch.u32ID]->GetInputName();
        orxInput_ResetValue(zInputName);
        spoFocusedInputs[pstPayload->stTouch.u32ID] = orxNULL;
      }
    }

    break;

  case orxSYSTEM_EVENT_TOUCH_END:
    pstPayload = (orxSYSTEM_EVENT_PAYLOAD *) _pstEvent->pstPayload;
    if(spoFocusedInputs[pstPayload->stTouch.u32ID] != orxNULL)
    {
      zInputName = spoFocusedInputs[pstPayload->stTouch.u32ID]->GetInputName();
      orxInput_ResetValue(zInputName);
      spoFocusedInputs[pstPayload->stTouch.u32ID] = orxNULL;
    }

    break;
  default:
    break;
  }

  return eResult;
}

VirtualGamePadInput * orxVirtualGamePad::GetVirutalInput(orxVECTOR *_pvPosition)
{
  VirtualGamePadInput *poResult = orxNULL;
  orxOBJECT *pstTouchObject;

  pstTouchObject = orxObject_Pick(_pvPosition, orxString_GetID(szGroupVirtualGamePad));
  if(pstTouchObject != orxNULL)
  {
    poResult = static_cast<VirtualGamePadInput*>(orxObject_GetUserData(pstTouchObject));
  }

  return poResult;
}

orxSTATUS orxVirtualGamePad::Init(orxVIEWPORT* _pstViewport)
{
  orxSTATUS eResult = orxSTATUS_SUCCESS;

  orxASSERT(_pstViewport != orxNULL);

  spstViewport = _pstViewport;
  spstCamera = orxViewport_GetCamera(spstViewport);
  orxMemory_Zero(&sstInputList, sizeof(orxLINKLIST));

  eResult = orxEvent_AddHandler(orxEVENT_TYPE_SYSTEM, orxVirtualGamePad::EventHandler);

  return eResult;
}

void orxVirtualGamePad::Exit()
{
  orxEvent_RemoveHandler(orxEVENT_TYPE_SYSTEM, orxVirtualGamePad::EventHandler);
}

void orxVirtualGamePad::BindObjects()
{
  ScrollBindObject<VirtualGamePadButton>(szVirtualGamePadButton);
}

orxSTATUS orxVirtualGamePad::RegisterInput(VirtualGamePadInput *_poVirtualGamePadInput)
{
  orxSTATUS eResult = orxSTATUS_SUCCESS;
  orxASSERT(_poVirtualGamePadInput != orxNULL);

  eResult = orxLinkList_AddEnd(&sstInputList, &_poVirtualGamePadInput->mstNode);

  return eResult;
}

orxSTATUS orxVirtualGamePad::UnregisterInput(VirtualGamePadInput *_poVirtualGamePadInput)
{
  orxSTATUS eResult = orxSTATUS_SUCCESS;
  orxASSERT(_poVirtualGamePadInput != orxNULL);

  eResult = orxLinkList_Remove(&_poVirtualGamePadInput->mstNode);

  return eResult;
}
