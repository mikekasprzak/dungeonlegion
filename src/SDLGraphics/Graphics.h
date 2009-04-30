// - ------------------------------------------------------------------------------------------ - //
#ifndef __SDLGraphics_Graphics_H__
#define __SDLGraphics_Graphics_H__
// - ------------------------------------------------------------------------------------------ - //
#ifdef SDL_BUILD
// - ------------------------------------------------------------------------------------------ - //
#include <SDL/SDL.h>
// ---------------------------------------------------------------------------------------------- //
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
// - ------------------------------------------------------------------------------------------ - //
#else // SDL_BUILD //
// - ------------------------------------------------------------------------------------------ - //
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
// - ------------------------------------------------------------------------------------------ - //
#endif // SDL_BUILD //
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Matrix.h>
#include <Geometry/Rect.h>
// - ------------------------------------------------------------------------------------------ - //
#include "TexturePool.h"
#include "UV.h"
// - ------------------------------------------------------------------------------------------ - //
typedef int ColorType;

#define RGB(_r,_g,_b)		((_r)|((_g)<<8)|((_b)<<16)|((255)<<24))
#define RGBA(_r,_g,_b,_a)	((_r)|((_g)<<8)|((_b)<<16)|((_a)<<24))

#define GET_R(c)	(((c))&255)
#define GET_G(c)	(((c)>>8)&255)
#define GET_B(c)	(((c)>>16)&255)
#define GET_A(c)	(((c)>>24)&255)


#define RGB_BLACK	RGB(0,0,0)
#define RGB_GREY	RGB(127,127,127)
#define RGB_WHITE	RGB(255,255,255)

#define RGB_RED		RGB(255,0,0)
#define RGB_GREEN	RGB(0,255,0)
#define RGB_BLUE	RGB(0,0,255)

#define RGB_MAGENTA	RGB(255,0,255)
#define RGB_YELLOW	RGB(255,255,0)
#define RGB_CYAN	RGB(0,255,255)

#define RGB_ORANGE	RGB(255,127,0)
#define RGB_PINK	RGB(255,0,127)
#define RGB_PURPLE	RGB(127,0,255)
#define RGB_PUKE	RGB(127,255,0)
#define RGB_MINT	RGB(0,255,127)
#define RGB_SKY		RGB(0,127,255)
// - ------------------------------------------------------------------------------------------ - //
inline ColorType HSV( float Hue, float Sat, float Val ) {
	float r,g,b;

	while (Hue < 0)
		Hue += 360;
	while (Hue > 360)
		Hue -= 360;
		
	if ( Sat > 1.0f ) 
		Sat = 1.0f;
	else if ( Sat < 0.0f )
		Sat = 0.0f;
		
	if ( Val > 1.0f ) 
		Val = 1.0f;
	else if ( Val < 0.0f )
		Val = 0.0f;

	if (Hue < 120) {
		r = (120 - Hue) / 60.0f;
		g = Hue / 60.0f;
		b = 0;
	}
	else if (Hue < 240) {
		r = 0;
		g = (240 - Hue) / 60.0f;
		b = (Hue - 120) / 60.0f;
	}
	else {
		r = (Hue - 240) / 60.0f;
		g = 0;
		b = (360 - Hue) / 60.0f;
	}
	
	r = (r > 1)?1:r;
	g = (g > 1)?1:g;
	b = (b > 1)?1:b;

	r = (1 - Sat + Sat * r) * Val;
	g = (1 - Sat + Sat * g) * Val;
	b = (1 - Sat + Sat * b) * Val;

	return RGB( (int)(r * 255.0f), (int)(g * 255.0f), (int)(b * 255.0f) );
}
// - ------------------------------------------------------------------------------------------ - //
#ifdef SDL_BUILD
extern SDL_Surface* Buffer;
#endif // SDL_BUILD //

extern bool ShutdownGame;

extern Matrix3x3 Matrix;
extern std::vector<Matrix3x3>* MatrixStack;
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


// Non resulotion globals //
namespace System {
	extern ColorType Color;
	extern ColorType NormalColor;
	extern Real NormalLength;

	extern volatile bool CloseButtonPressed;

	extern int UpKey;
	extern int DownKey;
	extern int RightKey;
	extern int LeftKey;
	
	extern int StickX;
	extern int StickY;
	extern void UpdateStick();
};

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

namespace FullRefScreen {
	extern int Width;
	extern int Height;
	
	extern Real AspectRatio;

	extern Vector2D Shape;
	extern Vector2D HalfShape;
};

// Actual Screen //
namespace ActualScreen {
	extern int Width;
	extern int Height;
	
	extern Real AspectRatio;

	extern Vector2D Shape;
	extern Vector2D HalfShape;
};

// Overscan Screen //
namespace OverScreen {
	extern int Width;
	extern int Height;
	
	extern Real AspectRatio;
};

// - ------------------------------------------------------------------------------------------ - //
class cMouse {
public:
	Vector2D Pos;
	Vector2D Old;
	
	int Wheel;
	int WheelOld;
	
	int ButtonCurrent;
	int ButtonLast;
	
public:
	cMouse()
	{
#ifdef SDL_BUILD
		int x, y;
		ButtonCurrent = SDL_GetMouseState( &x, &y );
		ButtonLast = ButtonCurrent;
#else // SDL_BUILD //
		extern int mouse_b;
		
		ButtonCurrent = mouse_b;
		ButtonLast = mouse_b;
#endif // SDL_BUILD //
	}
	
	inline void Update() {
		int x, y;
#ifdef SDL_BUILD
		int _Button = SDL_GetMouseState( &x, &y );
#else // SDL_BUILD //
		extern int mouse_x;
		extern int mouse_y;
		extern int mouse_b;
		
		int _Button = mouse_b;
		x = mouse_y;
		y = 320-mouse_x;
#endif // SDL_BUILD //
		
		Old = Pos;
		Pos = -ActualScreen::HalfShape;
		Pos += Vector2D(x, y);
		Pos /= (RefScreen::Scalar);
//		Pos -= RefScreen::HalfShape;
//		Pos += Vector2D( RefScreen::DiffX, RefScreen::DiffY );
			
//		WheelOld = Wheel;
//		Wheel = mouse_z;
		
		ButtonLast = ButtonCurrent;
		ButtonCurrent = _Button;
	}

public:
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector2D Diff() const {
		return Old - Pos;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const int WheelDiff() const {
		return WheelOld - Wheel;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline const int Button( const int Mask = -1 ) const {
		return ButtonCurrent & Mask;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const int Last( const int Mask = -1 ) const {
		return ButtonLast & Mask;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const bool Pressed( const int Mask = -1 ) const {
		return (ButtonCurrent ^ ButtonLast) & ButtonCurrent & Mask;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const bool Released( const int Mask = -1 ) const {
		return (ButtonCurrent ^ ButtonLast) & ButtonLast & Mask;
	}
	// - -------------------------------------------------------------------------------------- - //

};
// - ------------------------------------------------------------------------------------------ - //
extern cMouse Mouse;
// - ------------------------------------------------------------------------------------------ - //
class cCamera {
public:
	Vector2D Pos;
	Real Scale;

	Vector2D ViewShape;
	Vector2D ViewHalfShape;
	
	Vector2D Mouse;
	
	// TODO: Something to do with clipping //
public:
	cCamera( const Vector2D& _Pos = Vector2D::Zero, const Real& _Scale = Real::One ) :
		Pos( _Pos ),
		Scale( _Scale ),
		ViewShape( RefScreen::Shape * Scale ),
		ViewHalfShape( ViewShape * Real::Half )
	{
	}
	
public:
	inline void Update() {
		Mouse.x = (::Mouse.Pos.x * ViewShape.x) / RefScreen::Shape.x;
		Mouse.y = (::Mouse.Pos.y * ViewShape.y) / RefScreen::Shape.y;
		Mouse -= Pos;
	}

	inline const Matrix3x3 GetMatrix() const {
		Matrix3x3 Matrix = Matrix3x3::Scaling( Real::One / Scale );
		Matrix *= Matrix3x3::Translating( Pos );
		Matrix *= Matrix3x3::Translating( RefScreen::HalfShape * Scale );
		return Matrix;
	}	
};
// - ------------------------------------------------------------------------------------------ - //
extern cCamera Camera;
extern cCamera* CurrentCamera;
// - ------------------------------------------------------------------------------------------ - //
extern ColorType CurrentColor;
extern ColorType CurrentNormalColor;
extern Real CurrentNormalLength;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gfxSetCameraMatrix( const cCamera& _Camera = *CurrentCamera ) {
	Matrix = _Camera.GetMatrix();
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxSetScreenMatrix( ) {
	Matrix = Matrix3x3::Translating( RefScreen::HalfShape );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxSetScreenAspectMatrix( ) {
	// This is a function for setting an aspect ratio constrained Matrix. //
	//   All screen co-ordinates fall in to at least a -1 to +1 range. //
	// TODO: Make it do what the above suggests.  //
	//   Perhaps horizontal is always -1 to 1, and vertical is some aspect ratio refined one. //
	Matrix = Matrix3x3::Translating( RefScreen::HalfShape );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gfxSetCamera( cCamera& _Camera = Camera ) {
	CurrentCamera = &_Camera;
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxSetCameraPos( const Vector2D& v ) {
	CurrentCamera->Pos = v;
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxAddCameraPos( const Vector2D& v ) {
	CurrentCamera->Pos += v;
}
// - ------------------------------------------------------------------------------------------ - //
inline const Vector2D& gfxGetCameraPos() {
	return CurrentCamera->Pos;
}
// - ------------------------------------------------------------------------------------------ - //
inline const Vector2D gfxGetCameraCenter() {
	return Vector2D::Zero - gfxGetCameraPos();
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxSetCameraPos( const Real _x, const Real _y, const Real _z = Real::Zero ) {
	CurrentCamera->Pos = Vector2D( _x, _y );	
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxAddCameraPos( const Real _x, const Real _y, const Real _z = Real::Zero ) {
	CurrentCamera->Pos += Vector2D( _x, _y );	
}
// - ------------------------------------------------------------------------------------------ - //
inline const Real& gfxGetCameraScale() {
	return CurrentCamera->Scale;
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxSetCameraScale( const Real _CameraScale ) {
	CurrentCamera->Scale = _CameraScale;	
	
	CurrentCamera->ViewShape = RefScreen::Shape * CurrentCamera->Scale;
	CurrentCamera->ViewHalfShape = CurrentCamera->ViewShape * Real::Half;
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxAddCameraScale( const Real _CameraScale ) {
	gfxSetCameraScale( gfxGetCameraScale() + _CameraScale );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxConstrainCamera( const Vector2D& P1, const Vector2D& P2 ) {
	// Create a rectangle, contracting it's shape by the current size of the zoomed view //
	Rect2D InnerViewRect = Rect2D::Pair(
		P1 + CurrentCamera->ViewHalfShape,
		P2 - CurrentCamera->ViewHalfShape
		);
	
	// Restrict Camera to Zone //
	CurrentCamera->Pos = InnerViewRect.ClosestPoint( CurrentCamera->Pos );	
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxConstrainCameraScale( const Real Min, const Real Max ) {
	if ( gfxGetCameraScale() < Min )
		gfxSetCameraScale( Min );

	if ( gfxGetCameraScale() > Max )
		gfxSetCameraScale( Max );	
}
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

// This controls how a texture and vertex color mix //
//glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

// - ------------------------------------------------------------------------------------------ - //
inline void gfxSetSmoothTexturesMipMapped() {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxSetSmoothTextures() {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxSetBlockyTexturesMipMapped() {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxSetBlockyTextures() {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	
}
// - ------------------------------------------------------------------------------------------ - //


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


// - ------------------------------------------------------------------------------------------ - //
//inline void gfxInit( const int _Width, const int _Height, const bool _FullScreen = false, const int _ScreenScalar = 1 ) {
inline void gfxInit( const int _RefWidth, const int _RefHeight, const int _ActualWidth, const int _ActualHeight, const bool _FullScreen = false, const bool _ZBuffer = false ) {
	ShutdownGame = false;
	
	// Reference Screen //
	RefScreen::Width = _RefWidth;
	RefScreen::Height = _RefHeight;

	RefScreen::Shape = Vector2D( RefScreen::Width, RefScreen::Height );
	RefScreen::HalfShape = RefScreen::Shape * Real::Half;
		
	RefScreen::AspectRatio = Real( RefScreen::Width ) / Real( RefScreen::Height );
		

	// Actual Screen //
	ActualScreen::Width = _ActualWidth;
	ActualScreen::Height = _ActualHeight;

	ActualScreen::Shape = Vector2D( ActualScreen::Width, ActualScreen::Height );
	ActualScreen::HalfShape = ActualScreen::Shape * Real::Half;

	ActualScreen::AspectRatio = Real( ActualScreen::Width ) / Real( ActualScreen::Height );


	// Final Screen //
	if ( RefScreen::AspectRatio > ActualScreen::AspectRatio ) {
		RefScreen::Scalar = Real( ActualScreen::Width ) / Real( RefScreen::Width );
	}
	else {
		RefScreen::Scalar = Real( ActualScreen::Height ) / Real( RefScreen::Height );
	}
	
	RefScreen::DiffX = (ActualScreen::Width - (int)(Real(RefScreen::Width) * RefScreen::Scalar));
	RefScreen::DiffY = (ActualScreen::Height - (int)(Real(RefScreen::Height) * RefScreen::Scalar));
	
	RefScreen::OffsetX = RefScreen::DiffX >> 1;
	RefScreen::OffsetY = RefScreen::DiffY >> 1;

	// Full Reference Screen //
	FullRefScreen::Width = (int)( Real(ActualScreen::Width) / RefScreen::Scalar );
	FullRefScreen::Height = (int)( Real(ActualScreen::Height) / RefScreen::Scalar );
		
	//printf( "W: %i  H:  %i \n", FullRefScreen::Width, FullRefScreen::Height );
	
		
#ifdef SDL_BUILD
	// Initialize SDL //
    if ( SDL_Init( SDL_INIT_VIDEO /*| SDL_INIT_AUDIO*/ ) ) {
//	    Log( "SDL initialization failed: " << SDL_GetError() );	    
//	    QuitGame( 1 );
	}


	{
		// Get information about our video hardware //    
		const SDL_VideoInfo* VideoInfo = SDL_GetVideoInfo();
		
		// In the incredibly unlikely case that we have no video hardware... //  
		if ( VideoInfo ) {
		
			// Construct our list of SDL video options //
			int VideoFlags = SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_HWPALETTE; // | SDL_RESIZABLE  
	
			if ( _FullScreen )
				VideoFlags |= SDL_FULLSCREEN;
			
			// Depeding on if our hardware supports a hardware framebuffer //
		    if ( VideoInfo->hw_available )
				VideoFlags |= SDL_HWSURFACE;
		    else
				VideoFlags |= SDL_SWSURFACE;
			
			// Hardware blitting support (a good thing) //
		    if ( VideoInfo->blit_hw )
				VideoFlags |= SDL_HWACCEL;
		
			int ColorDepth = 32;
						
			// Pre window creation GL Attributes //
			SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
			SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
			SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
			SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8 );
			
		//	SDL_GL_SetAttribute( SDL_GL_BUFFER_SIZE, 32 );
		
		//	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, true );	
		//	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 32 );
		//	SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE, 32 );
		
		//	SDL_GL_SetAttribute( SDL_GL_ACCUM_RED_SIZE, 8 );
		//	SDL_GL_SetAttribute( SDL_GL_ACCUM_GREEN_SIZE, 8 );
		//	SDL_GL_SetAttribute( SDL_GL_ACCUM_BLUE_SIZE, 8 );
		//	SDL_GL_SetAttribute( SDL_GL_ACCUM_ALPHA_SIZE, 8 );
			
			//SDL_GL_SetAttribute( SDL_GL_MULTISAMPLEBUFFERS, 1 );
			//SDL_GL_SetAttribute( SDL_GL_MULTISAMPLESAMPLES, 4 ); 
		
		//	SDL_GL_SetAttribute( SDL_GL_SUGGEST, SDL_GL_DOUBLEBUFFER | SDL_GL_Z_DEPTH | SDL_GL_RENDERMETHOD | SDL_GL_SAMPLE_BUFFERS | SDL_GL_SAMPLES );

#ifdef WINDOW_TITLE
			SDL_WM_SetCaption( WINDOW_TITLE, NULL );
#else		
			SDL_WM_SetCaption( "Playground GL Graphics", NULL );
#endif // WINDOW_TITLE //	
			
			//	float largest_supported_anisotropy;
			//	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest_supported_anisotropy);
				//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, &largest_supported_anisotropy); 
			//-	Log( LOG_HIGHEST_LEVEL, "largest_supported_anisotropy: " << largest_supported_anisotropy );
				
			// Create our Screen //
			Buffer = SDL_SetVideoMode( ActualScreen::Width, ActualScreen::Height, ColorDepth, VideoFlags );	
		}
	}
	
	//glEnable( GL_TEXTURE_2D );
#endif // SDL_BUILD //	
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

//#else // SDL_BUILD //
//	
//	//glEnable( GL_TEXTURE_2D );
//	 
//	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
//	 
//	glViewport( 0, 0, Screen::Height * Screen::Scalar, Screen::Width * Screen::Scalar);
//#endif // SDL_BUILD //
//	
//	glClear( GL_COLOR_BUFFER_BIT );

	// Set a Transformation Matrix that makes Texture Co-ordinates work from 0-63 //	
	glMatrixMode( GL_TEXTURE );
	glLoadIdentity();
	//glScalef( 0.015625f, 0.015625f, 0.015625f );
	glScalef( 1 / UV_ONE_F, 1 / UV_ONE_F, 1 / UV_ONE_F );

//	glFrontFace( GL_CW );
//	glEnable( GL_CULL_FACE );

    glEnableClientState(GL_VERTEX_ARRAY);

	// Reset Clipping and Set Projection //
	glEnable( GL_SCISSOR_TEST );
	gfxResetClip();
	
	// Set the initial current color defaulting to white //
	// (Note, makecol only works after set_gfx_mode) //
	CurrentColor = RGB_WHITE;
	CurrentNormalColor = RGB_WHITE;
	
	CurrentNormalLength = 8;
	
	// Make sure we have a freshly initialized mouse //
	Mouse = cMouse();
	
	// Set the camera //
	Camera = cCamera();
	CurrentCamera = &Camera;
	
	// Initalize Matrix //
	gfxSetScreenMatrix();

	// Initalize Matrix Stack //
	MatrixStack = new std::vector<Matrix3x3>();
		
	
	TexturePool::Init( "Content" );
	TexturePool::AddDirectory( "" );
	
//	gfxInitCapture();

#ifdef WINDOWS_BUILD
	// Adjust Sync Settings //	 
	{
		typedef void (APIENTRY * WGLSWAPINTERVALEXT) ( int ) ;
		
		WGLSWAPINTERVALEXT wglSwapIntervalEXT = (WGLSWAPINTERVALEXT) SDL_GL_GetProcAddress( "wglSwapIntervalEXT" );
		if ( wglSwapIntervalEXT != 0 ) {
			wglSwapIntervalEXT( 0 );
		} 
	}
#endif // WINDOWS_BUILD //
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxOrtho() {
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	
#ifdef SDL_BUILD
	glViewport( 0, 0, ActualScreen::Width, ActualScreen::Height );

	int RefWidth = RefScreen::Width + (int)(Real(RefScreen::DiffX) / RefScreen::Scalar);
	int RefHeight = RefScreen::Height + (int)(Real(RefScreen::DiffY) / RefScreen::Scalar);

	glOrtho(
		-(RefWidth >> 1),  +(RefWidth >> 1),
		-(RefHeight >> 1), +(RefHeight >> 1),
		-1.0f, 1.0f
		);
#else // NOT SDL_BUILD //
	// TODO: This is wrong.  Does not take in to account the new Aspect Ratio features. //
	glViewport( 0, 0, RefScreen::Height * RefScreen::Scalar, RefScreen::Width * RefScreen::Scalar);
	
	glOrthof(
		-(RefScreen::Height >> 1), +(RefScreen::Height >> 1),
		-(RefScreen::Width >> 1),  +(RefScreen::Width >> 1),
		-1.0f, 1.0f
		);
#endif // SDL_BUILD //

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

#ifdef IPHONE_BUILD
	glRotatef(90,0,0,1);
#endif // IPHONE_BUILD //
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxPerspective() {
	// OpenGL Spec says only Frustum/Ortho/gluPerspective should affect Projection Matrix //
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

#ifdef SDL_BUILD
	glViewport( 0, 0, ActualScreen::Width, ActualScreen::Height );

	int RefWidth = RefScreen::Width + (int)(Real(RefScreen::DiffX) / RefScreen::Scalar);
	int RefHeight = RefScreen::Height + (int)(Real(RefScreen::DiffY) / RefScreen::Scalar);

	// This frustrum configuration places (0,0,0) between the near and far plane //
	// glFrustrum's Near and Far planes get negated by this call //
	glFrustum(
		-(RefWidth / 3.0f),  +(RefWidth / 3.0f),
		-(RefHeight / 3.0f), +(RefHeight / 3.0f),
		100.0f, 200.0f
		);		
#else // NOT SDL_BUILD //
#endif // SDL_BUILD //

	// OpenGL Spec says camera transformations go on the top of the ModelView, not Projection Matrix //
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

#ifdef IPHONE_BUILD
	glRotatef(90,0,0,1);
#endif // IPHONE_BUILD //
	glTranslatef( 0, 0, -150.0f );
}
// - ------------------------------------------------------------------------------------------ - //
//inline void gfxCenterCamera() {
//	
//}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxExit( ) {
	// Kill the matrix stack //
	delete MatrixStack;

	// Shutdown SDL //
#ifdef SDL_BUILD
	if ( Buffer ) { 
		SDL_FreeSurface( Buffer );
	}

	SDL_Quit();
#else // SDL_BUILD //

#endif // SDL_BUILD //
}
// - ------------------------------------------------------------------------------------------ - //
inline bool gfxHasShutdown() {
	if ( System::CloseButtonPressed )
		return true;
	
	return ShutdownGame;
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxShutdown() {
	ShutdownGame = true;
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
	glClear( GL_COLOR_BUFFER_BIT );
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

// - ------------------------------------------------------------------------------------------ - //
inline void gfxInitMatrix() {
	Matrix = Matrix3x3::Identity;	
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxPushMatrix() {
	MatrixStack->push_back( Matrix );	
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxPeepMatrix() {
	Matrix = MatrixStack->back();	
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxPopMatrix() {
	// TODO: Log an error if too many pops //
	gfxPeepMatrix();
	MatrixStack->pop_back();	
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gfxFlipX() {
	Matrix(0,0) = -Matrix(0,0);
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxFlipY() {
	Matrix(1,1) = -Matrix(1,1);
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxTranslate( const Vector2D& v ) {
	Matrix *= Matrix3x3::Translating( v );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxTranslate( const Real _x, const Real _y, const Real _z = Real::Zero ) {
	Matrix *= Matrix3x3::Translating( Vector2D( _x, _y ) );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxScale( const Real Scalar ) {
	Matrix *= Matrix3x3::Scaling( Scalar );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxRotate( const Vector2D& v ) {
	Matrix *= Matrix3x3::Rotating( v );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxRotate( const Real& Angle ) {
	Matrix *= Matrix3x3::Rotating( Angle );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#endif // __SDLGraphics_Graphics_H__ //
// - ------------------------------------------------------------------------------------------ - //
