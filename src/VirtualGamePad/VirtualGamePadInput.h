/*
 * VirtualGamePadInput.h
 *
 *  Created on: Mar 24, 2015
 *      Author: philippe
 */

#ifndef VIRTUALGAMEPADINPUT_H_
#define VIRTUALGAMEPADINPUT_H_

#include "../Scroll/Scroll.h"

class VirtualGamePadInput : public ScrollObject {

friend class orxVirtualGamePad;

public:

      virtual   void            Reset() = 0;
      virtual   void            ProcessTouch(orxVECTOR *_pvPosition) = 0;

};

#endif /* VIRTUALGAMEPADINPUT_H_ */
