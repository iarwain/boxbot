#ifndef VIRTUAL_GAMEPAD_H_
#define VIRTUAL_GAMEPAD_H_

#include "../Scroll/Scroll.h"

#include "VirtualGamePadButton.h"

template class ScrollObjectBinder<VirtualGamePadButton>;

class orxVirtualGamePad {

public:

	static orxSTATUS Init(orxVIEWPORT* _pstViewport);
	static void      Exit();
	static void      BindObjects();

private:

	static orxSTATUS orxFASTCALL  EventHandler(const orxEVENT *_pstEvent);
	static VirtualGamePadInput *  GetVirutalInput(orxVECTOR *_pvPosition);

	static orxVIEWPORT *                spstViewport;
};

#endif
