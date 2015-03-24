#ifndef VIRTUAL_GAMEPAD_H_
#define VIRTUAL_GAMEPAD_H_

#include "../Scroll/Scroll.h"

class orxVirtualGamePad {

public:

	static orxSTATUS Init(orxVIEWPORT* _pstViewport);
	static void      Exit();
	static void      BindObjects();

private:

	static orxVIEWPORT*          spstViewport;
	static orxCAMERA*            spstCamera;
};

#endif
