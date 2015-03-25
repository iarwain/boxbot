/*
 * VirutalGamePadButton.h
 *
 *  Created on: Mar 24, 2015
 *      Author: philippe
 */

#ifndef VIRUTALGAMEPADBUTTON_H_
#define VIRUTALGAMEPADBUTTON_H_

#include "VirtualGamePadInput.h"

class VirtualGamePadButton : public VirtualGamePadInput {

public:

                void            Reset();
                void            ProcessTouch(orxVECTOR *_pvPosition);

protected:

                void            OnCreate();
                void            OnDelete();

private:

    const  orxSTRING       mzInputName;

};

#endif /* VIRUTALGAMEPADBUTTON_H_ */
