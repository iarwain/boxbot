/*
 * Game.cpp
 *
 *  Created on: Nov 8, 2013
 *      Author: philippe
 */

#define __SCROLL_IMPL__

#include "Game.h"
#include "Player.h"

#include "VirtualGamePad/orxVirtualGamePad.h"

static  const orxSTRING szConfigCameraObject            = "CameraObject";
static  const orxSTRING szConfigLeftViewport            = "LeftViewport";
static  const orxSTRING szConfigRightViewport           = "RightViewport";
static  const orxSTRING szConfigUIViewport              = "UIViewport";

static  const orxSTRING szInputLeft                     = "Left";
static  const orxSTRING szInputRight                    = "Right";
static  const orxSTRING szInputJump                     = "Jump";
static  const orxSTRING szInputQuit                     = "Quit";

// Event handler
static orxSTATUS orxFASTCALL EventHandler(const orxEVENT *_pstEvent)
{
  // Depending on event type
  switch(_pstEvent->eType)
  {

  case orxEVENT_TYPE_VIEWPORT:
  {
    if(_pstEvent->eID == orxVIEWPORT_EVENT_RESIZE)
    {
      Game::GetInstance().UpdateFrustum((orxVIEWPORT*)_pstEvent->hSender);
    }
	break;
  }

  default:
    break;
  }
  return orxSTATUS_SUCCESS;
}

void Game::UpdateFrustum(orxVIEWPORT *_pstViewport)
{
  if(_pstViewport == mpstUIViewport)
  {
    orxFLOAT fScreenWidth, fScreenHeight;
    orxFLOAT fFrustumWidth, fFrustumHeight;
    orxAABOX stFrustum;

    orxDisplay_GetScreenSize(&fScreenWidth, &fScreenHeight);

    orxConfig_PushSection( "UICamera" );
    fFrustumWidth = orxConfig_GetFloat( "FrustumWidth" );
    fFrustumHeight = orxConfig_GetFloat( "FrustumHeight" );
    orxConfig_PopSection();

    orxFLOAT fRatio = orxMAX( fFrustumWidth / fScreenWidth, fFrustumHeight / fScreenHeight );
    fFrustumWidth = fScreenWidth * fRatio;
    fFrustumHeight = fScreenHeight * fRatio;

    orxCamera_GetFrustum( mpstUICamera, &stFrustum);
    orxCamera_SetFrustum( mpstUICamera, fFrustumWidth, fFrustumHeight, stFrustum.vTL.fZ, stFrustum.vBR.fZ);
  }
}

void Game::RegisterPlayer(Player &_roPlayer)
{
  orxASSERT(mpoPlayer == orxNULL);
  mpoPlayer = &_roPlayer;
}

void Game::OnStartGame()
{
}

void Game::OnStopGame()
{
}

void Game::OnMapLoad()
{
  orxVECTOR vCameraPosition;
  orxFLOAT fZ;

  // get main camera Z
  orxCamera_GetPosition(GetMainCamera(), &vCameraPosition);
  fZ = vCameraPosition.fZ;

  // update left camera Z
  orxCamera_GetPosition(mpstLeftCamera, &vCameraPosition);
  vCameraPosition.fZ = fZ;
  orxCamera_SetPosition(mpstLeftCamera, &vCameraPosition);

  // update right camera Z
  orxCamera_GetPosition(mpstRightCamera, &vCameraPosition);
  vCameraPosition.fZ = fZ;
  orxCamera_SetPosition(mpstRightCamera, &vCameraPosition);
}

void Game::Update(const orxCLOCK_INFO &_rstInfo)
{
  if(mpoPlayer != orxNULL)
  {
    if(orxInput_IsActive(szInputLeft))
    {
      mpoPlayer->Left();
    }
    else if(orxInput_IsActive(szInputRight))
    {
      mpoPlayer->Right();
    }
    else
    {
      mpoPlayer->Stop();
    }

    if(orxInput_IsActive(szInputJump))
    {
      mpoPlayer->Jump(orxTRUE);
    }
    else
    {
      mpoPlayer->Jump(orxFALSE);
    }
  }

  if(!orxInput_IsActive(szInputQuit) && orxInput_HasNewStatus(szInputQuit))
  {
    mbQuit = orxTRUE;
  }
}

orxSTATUS Game::Init()
{
  orxSTATUS eResult = orxSTATUS_SUCCESS;

  mbQuit = orxFALSE;
  mpoPlayer = orxNULL;

  orxVIEWPORT* pstLeftViewport = orxViewport_CreateFromConfig(szConfigLeftViewport);
  orxVIEWPORT* pstRightViewport = orxViewport_CreateFromConfig(szConfigRightViewport);
  mpstUIViewport = orxViewport_CreateFromConfig(szConfigUIViewport);

  orxVirtualGamePad::Init(mpstUIViewport);

  mpstLeftCamera        = orxViewport_GetCamera(pstLeftViewport);
  mpstRightCamera       = orxViewport_GetCamera(pstRightViewport);
  mpstUICamera          = orxViewport_GetCamera(mpstUIViewport);

  mpstCameraObject      = orxObject_CreateFromConfig(szConfigCameraObject);
  // Adds camera as child
  orxCamera_SetParent(GetMainCamera(), mpstCameraObject);
  orxCamera_SetParent(mpstLeftCamera, mpstCameraObject);
  orxCamera_SetParent(mpstRightCamera, mpstCameraObject);

  SetMapName("Level1.map");
  LoadMap();

  orxObject_CreateFromConfig("GameUI");

  orxEvent_AddHandler(orxEVENT_TYPE_VIEWPORT, EventHandler);

  UpdateFrustum(mpstUIViewport);

  // Done!
  return eResult;
}

orxSTATUS Game::Run()
{
  orxSTATUS eResult = orxSTATUS_SUCCESS;

  if(mbQuit == orxTRUE)
  {
    eResult = orxSTATUS_FAILURE;
  }

  // Done!
  return eResult;
}

void Game::Exit()
{
  orxEvent_RemoveHandler(orxEVENT_TYPE_VIEWPORT, EventHandler);
  orxVirtualGamePad::Exit();
}

void Game::BindObjects()
{
  ScrollBindObject<Player>("Player");

  orxVirtualGamePad::BindObjects();
}

int main(int argc, char **argv)
{
  // Executes game
  Game::GetInstance().Execute(argc, argv);

  // Done!
  return EXIT_SUCCESS;
}

#ifdef __orxWINDOWS__

#include "windows.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  // Executes game
  Game::GetInstance().Execute();

  // Done!
  return EXIT_SUCCESS;
}

#endif // __orxWINDOWS__
