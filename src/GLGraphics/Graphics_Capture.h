#include "UV.h"

// - ------------------------------------------------------------------------------------------ - //
extern unsigned int GLCapture;
// - ------------------------------------------------------------------------------------------ - //
inline void gfxInitCapture() {
	glGenTextures( 1, &GLCapture );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxCapture() {
	// ** TODO ** FIX THIS to scale to screen size //
	glBindTexture( GL_TEXTURE_2D, GLCapture );
	//glCopyTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, 0, 0, 512 * RefScreen::Scalar, 512 * RefScreen::Scalar, 0);
	glCopyTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, 0, 0, ActualScreen::Width, ActualScreen::Height, 0);
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxSetCapture() {
	glBindTexture( GL_TEXTURE_2D, GLCapture );
	gfxSetSmoothTextures();
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawCapture() {
	gfxSetCapture();
	glEnable(GL_TEXTURE_2D);

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	
	{
#ifdef IPHONE_BUILD
//	    float Verts[] = {
//			-160,-240,
//			-160,240,
//			160,-240,
//			160,240,
//		};
		
//		int Height = ((480 * RefScreen::Scalar) * UV_ONE) / (512 * RefScreen::Scalar);
//		int Width = ((320 * RefScreen::Scalar) * UV_ONE) / (512 * RefScreen::Scalar);


	    float Verts[] = {
			-160,-240,
			-160,240,
			160,-240,
			160,240,
		};

		int Height = UV_ONE;//((480 * RefScreen::Scalar) * UV_ONE) / (512 * RefScreen::Scalar);
		int Width = UV_ONE;//((320 * RefScreen::Scalar) * UV_ONE) / (512 * RefScreen::Scalar);
		
		UVType UVs[] = {
			UV_ZERO, Height,
			UV_ZERO, UV_ZERO,
			Width, Height,
			Width, UV_ZERO,
		};
		glPushMatrix();
		glRotatef(-90,0,0,1);
		glVertexPointer(2, GL_FLOAT, 0, Verts);
		glTexCoordPointer(2, GL_UVType, 0, UVs);
	    glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );
		glPopMatrix();
#else
	    float Verts[] = {
			-240,-160,
			-240,160,
			240,-160,
			240,160,
		};
		
		int Width = ((480 * RefScreen::Scalar) * UV_ONE) / (512 * RefScreen::Scalar);
		int Height = ((320 * RefScreen::Scalar) * UV_ONE) / (512 * RefScreen::Scalar);
		
		UVType UVs[] = {
			UV_ZERO, Height,
			UV_ZERO, UV_ZERO,
			Width, Height,
			Width, UV_ZERO,
		};
		
		glVertexPointer(2, GL_FLOAT, 0, Verts);
		glTexCoordPointer(2, GL_UVType, 0, UVs);
	    glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );
#endif // IPHONE_BUILD //
	}	

	glDisable(GL_TEXTURE_2D);
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxFreeCapture() {
	glDeleteTextures( 1, &GLCapture );
	GLCapture = 0;
}
// - ------------------------------------------------------------------------------------------ - //
