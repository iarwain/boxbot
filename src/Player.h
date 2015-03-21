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

private:
	        orxVECTOR          mvVelocity;
	        orxBOOL            mbGrounded;
	        orxBOOL            mbFalling;
	        orxU32             mu32CollisionFlag;

	           void            ApplyGravity(orxFLOAT _fDT);
protected:

               void            OnCreate();
               void            OnDelete();
               void            Update(const orxCLOCK_INFO &_rstInfo);
};

#endif /* PLAYER_H_ */
