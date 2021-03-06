/*
 * Game.h
 *
 *  Created on: Nov 8, 2013
 *      Author: philippe
 */

#ifndef GAME_H_
#define GAME_H_

#include "Scroll/Scroll.h"

class Player;

class Game: public Scroll<Game> {

public:
	void            UpdateFrustum(orxVIEWPORT* _pstViewport);

	void            RegisterPlayer(Player &_roPlayer);
	void            UnregisterPlayer() { mpoPlayer = orxNULL; }

private:

	void            CameraUpdate(const orxCLOCK_INFO &_rstInfo);
    void            Update(const orxCLOCK_INFO &_rstInfo);
    orxSTATUS       Init();
    orxSTATUS       Run();
    void            Exit();
    void            BindObjects();

    void            OnStartGame();
    void            OnStopGame();
    void            OnMapLoad();

    Player         *mpoPlayer;
	orxOBJECT      *mpstCameraObject;
    orxBOOL         mbQuit;

    orxCAMERA      *mpstLeftCamera;
    orxCAMERA      *mpstRightCamera;

    orxVIEWPORT    *mpstUIViewport;
    orxCAMERA      *mpstUICamera;
};

#endif /* GAME_H_ */
