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

	static orxSTATUS RegisterInput(VirtualGamePadInput * _poVirtualGamePadInput);
	static void      UnregisterInput(VirtualGamePadInput * _poVirtualGamePadInput);

private:

	static orxVIEWPORT*          spstViewport;
	static orxCAMERA*            spstCamera;
};

#endif
