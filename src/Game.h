/*
 * Game.h
 *
 *  Created on: Nov 8, 2013
 *      Author: philippe
 */

#ifndef GAME_H_
#define GAME_H_

#include "Scroll/Scroll.h"

class Game: public Scroll<Game> {

public:
	void            UpdateFrustum();

private:

    void            Update(const orxCLOCK_INFO &_rstInfo);
    orxSTATUS       Init();
    orxSTATUS       Run();
    void            Exit();
    void            BindObjects();

    void            OnStartGame();
    void            OnStopGame();
    void            OnMapLoad();

	orxOBJECT      *mpstCameraObject;
    orxBOOL         mbQuit;
};

#endif /* GAME_H_ */
