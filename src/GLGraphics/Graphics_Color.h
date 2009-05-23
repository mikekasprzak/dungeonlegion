// - ------------------------------------------------------------------------------------------ - //
#ifndef __GLGraphics_Graphics_Color_H__
#define __GLGraphics_Graphics_Color_H__
// - ------------------------------------------------------------------------------------------ - //
#include "Color.h"
// - ------------------------------------------------------------------------------------------ - //
inline void gfxEnableAlphaBlending() {
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
//	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxEnableAddativeBlending() {
	glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDisableBlending() {
	glDisable( GL_BLEND );
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GLGraphics_Graphics_Color_H__ //
// - ------------------------------------------------------------------------------------------ - //
