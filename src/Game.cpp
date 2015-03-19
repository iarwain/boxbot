/*
 * Game.cpp
 *
 *  Created on: Nov 8, 2013
 *      Author: philippe
 */

#define __SCROLL_IMPL__

#include "Game.h"

static  const orxSTRING szConfigCameraObject            = "CameraObject";

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
      Game::GetInstance().UpdateFrustum();
    }
	break;
  }

  default:
    break;
  }
  return orxSTATUS_SUCCESS;
}

void Game::UpdateFrustum()
{
  orxFLOAT fScreenWidth, fScreenHeight;
  orxFLOAT fFrustumHeight;
  orxAABOX stFrustum;

  orxDisplay_GetScreenSize(&fScreenWidth, &fScreenHeight);

  orxFLOAT fRatio = fScreenWidth / fScreenHeight;
  fFrustumHeight = orx2F(1024) / fRatio;

  orxCamera_GetFrustum( GetMainCamera(), &stFrustum);
  orxCamera_SetFrustum( GetMainCamera(), orx2F(1024), fFrustumHeight, stFrustum.vTL.fZ, stFrustum.vBR.fZ);
}

void Game::OnStartGame()
{
}

void Game::OnStopGame()
{
}

void Game::OnMapLoad()
{
}

void Game::Update(const orxCLOCK_INFO &_rstInfo)
{
}

orxSTATUS Game::Init()
{
  orxSTATUS eResult = orxSTATUS_SUCCESS;

  mbQuit = orxFALSE;

  mpstCameraObject      = orxObject_CreateFromConfig(szConfigCameraObject);
  // Adds camera as child
  orxCamera_SetParent(GetMainCamera(), mpstCameraObject);

  SetMapName("Level1.map");
  LoadMap();

  orxEvent_AddHandler(orxEVENT_TYPE_VIEWPORT, EventHandler);

  UpdateFrustum();

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
}

void Game::BindObjects()
{
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
