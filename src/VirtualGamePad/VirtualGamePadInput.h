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

        const  orxSTRING        GetInputName() { return mzInputName; }

protected:

                void            OnCreate();
                void            OnDelete();

private:

        orxLINKLIST_NODE        mstNode;
         const  orxSTRING       mzInputName;
};

#endif /* VIRTUALGAMEPADINPUT_H_ */
