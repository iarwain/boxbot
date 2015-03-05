/*
 * Game.cpp
 *
 *  Created on: Nov 8, 2013
 *      Author: philippe
 */

#define __SCROLL_IMPL__

#include "Game.h"

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

  // Done!
  return eResult;
}

orxSTATUS Game::Run()
{
  orxSTATUS eResult = orxSTATUS_SUCCESS;

  // Done!
  return eResult;
}

void Game::Exit()
{
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
