/*
 * Player.h
 *
 *  Created on: Mar 20, 2015
 *      Author: loki
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "Scroll/Scroll.h"

class Player: public ScrollObject {

public:

              void             Left() { mfHorizontalAxis = -orxFLOAT_1; }
              void             Right() { mfHorizontalAxis = orxFLOAT_1; }
              void             Jump(orxBOOL _bJump) { mbJump = _bJump; }
              void             Stop() { mfHorizontalAxis = orxFLOAT_0; }

private:

              enum PlayerState
              {
            	  PlayerStateGrounded = 0,
            	  PlayerStateFalling,
            	  PlayerStateJumping,

            	  PlayerStateNumber,

            	  PlayerStateNone = orxENUM_NONE
              };

            PlayerState        mePlayerState;
	        orxVECTOR          mvVelocity;
	        orxBOOL            mbJump;
	        orxU32             mu32VerticalCollisionFlag;
	        orxU32             mu32HorizontalCollisionFlag;
	        orxFLOAT           mfHorizontalAxis;

	        // Settings

	        orxFLOAT           mfAcceleration;
	        orxFLOAT           mfMaxSpeed;
	        orxFLOAT           mfMaxFall;
	        orxFLOAT           mfReactivityFactor;
	        orxFLOAT           mfFriction;

	        orxFLOAT           mfGravity;
	        orxFLOAT           mfJumpVelocity;
	        orxFLOAT           mfEarlyJumpVelocity;


	           void            ApplyGravity(orxFLOAT _fDT);
	           void            CheckVerticalRays(orxFLOAT _fDT);
	           void            CheckHorizontalRays(orxFLOAT _fDT);
protected:

               void            OnCreate();
               void            OnDelete();
               void            Update(const orxCLOCK_INFO &_rstInfo);
};

#endif /* PLAYER_H_ */
