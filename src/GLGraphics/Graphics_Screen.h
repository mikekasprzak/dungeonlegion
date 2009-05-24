#include <Math/Vector.h>
// - ------------------------------------------------------------------------------------------ - //
#ifdef SDL_BUILD
extern SDL_Surface* Buffer;
#endif // SDL_BUILD //

// - ------------------------------------------------------------------------------------------ - //
namespace Screen {
	extern int Width;
	extern int Height;
	extern int Scalar;
	
	extern Real AspectRatio;

	extern Vector2D Shape;
	extern Vector2D HalfShape;

//	extern ColorType Color;
//	extern ColorType NormalColor;
//	extern Real NormalLength;
	
	extern volatile bool CloseButtonPressed;
//	void CloseButtonHandler();
};
// - ------------------------------------------------------------------------------------------ - //
// Reference Screen //
namespace RefScreen {
	extern int Width;
	extern int Height;
	
	extern Real AspectRatio;

	extern Vector2D Shape;
	extern Vector2D HalfShape;

	extern Real Scalar;
	extern int OffsetX;
	extern int OffsetY;

	extern int DiffX;
	extern int DiffY;
};
// - ------------------------------------------------------------------------------------------ - //
namespace FullRefScreen {
	extern int Width;
	extern int Height;
	
	extern Real AspectRatio;

	extern Vector2D Shape;
	extern Vector2D HalfShape;
};
// - ------------------------------------------------------------------------------------------ - //
namespace ActualScreen {
	extern int Width;
	extern int Height;
	
	extern Real AspectRatio;

	extern Vector2D Shape;
	extern Vector2D HalfShape;
};
// - ------------------------------------------------------------------------------------------ - //
namespace OverscanScreen {
	extern int Width;
	extern int Height;
	
	extern Real AspectRatio;
};
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
inline void gfxSetClip( const int x, const int y, const int w, const int h ) {
//	glEnable( GL_SCISSOR_TEST );

#ifdef IPHONE_BUILD
	glScissor(
		(y) * RefScreen::Scalar,
		//(x + (480-w)) * RefScreen::Scalar,
		((480 - x) - w) * RefScreen::Scalar,
		h * RefScreen::Scalar,
		w * RefScreen::Scalar
		);
#else // !IPHONE_BUILD //
//	glScissor( x * RefScreen::Scalar, y * RefScreen::Scalar, w * RefScreen::Scalar, h * RefScreen::Scalar );
	glScissor( 
		RefScreen::OffsetX + (x * RefScreen::Scalar),
		RefScreen::OffsetY + (y * RefScreen::Scalar), 
		(w * RefScreen::Scalar), 
		(h * RefScreen::Scalar)
		);

#endif // IPHONE_BUILD //

//	glMatrixMode( GL_PROJECTION );
//	glLoadIdentity();
//
//#ifdef SDL_BUILD
//	glOrtho(
//		-(w >> 1)-((480-w)>>1), +(w >> 1)-((480-w)>>1),
//		+(h >> 1)-((320-h)>>1), -(h >> 1)-((320-h)>>1),
//		-1.0f, 1.0f
//		);
//	
//	glMatrixMode( GL_MODELVIEW );
//
//	glViewport(x * Screen::Scalar, y * Screen::Scalar, w * Screen::Scalar, h * Screen::Scalar);
//#else // SDL_BUILD //
//	glOrthof(
//		-(h >> 1)-((320-h)>>1), +(h >> 1)-((320-h)>>1),
//		+(w >> 1)-((480-w)>>1), -(w >> 1)-((480-w)>>1),
//		-1.0f, 1.0f
//		);
//	
//	glMatrixMode( GL_MODELVIEW );
//
//	// Backwards, because of our "special" iPhone orientation //
//	glViewport( (y+((320-h)>>0)) * Screen::Scalar, (x+((480-w)>>0)) * Screen::Scalar, h * Screen::Scalar, (w) * Screen::Scalar);
//#endif // SDL_BUILD //
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxResetClip( ) {
//	glDisable( GL_SCISSOR_TEST );
	glScissor( 
		0,
		0,
		ActualScreen::Width,
		ActualScreen::Height
		);
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gfxClearBuffer( const ColorType Color = RGB_BLACK ) {
	glClearColor( 
		((float)GET_R(Color)) / 255.0f, 
		((float)GET_G(Color)) / 255.0f, 
		((float)GET_B(Color)) / 255.0f, 
		((float)GET_A(Color)) / 255.0f
		);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxSwapBuffer( ) {
#ifdef SDL_BUILD
	SDL_GL_SwapBuffers();
#else // SDL_BUILD //
	glFinish();
#endif // SDL_BUILD //
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
extern ColorType CurrentColor;
extern ColorType CurrentNormalColor;
extern Real CurrentNormalLength;

// - ------------------------------------------------------------------------------------------ - //
inline void gfxApplyColor( const ColorType Color ) {
	glColor4ub( GET_R(Color), GET_G(Color), GET_B(Color), GET_A(Color) );	
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxSetColor( const ColorType Color ) {
	if ( CurrentColor != Color ) {
		CurrentColor = Color;
		gfxApplyColor( CurrentColor );
	}
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxRestoreColor( const ColorType Color ) {
	if ( CurrentColor != Color ) {
		gfxApplyColor( CurrentColor );
	}
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxSetColor( const int r, const int g, const int b, const int a = 255 ) {
	gfxSetColor( RGBA(r,g,b,a) );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxSetNormalColor( const ColorType Color ) {
	CurrentNormalColor = Color;
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxSetNormalColor( const int r, const int g, const int b, const int a = 255 ) {
	CurrentNormalColor = RGBA(r,g,b,a);
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gfxSetNormalLength( const Real NormalLength ) {
	CurrentNormalLength = NormalLength;
}
// - ------------------------------------------------------------------------------------------ - //
