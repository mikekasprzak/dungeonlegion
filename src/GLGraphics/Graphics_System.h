
#include <Math/Vector.h>

#include "UV.h"

extern bool ShutdownGame;

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

		if ( _ZBuffer ) {
			SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 32 );
			//SDL_GL_SetAttribute( SDL_GL_SUGGEST, SDL_GL_Z_DEPTH );
			
		}

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

	glDepthFunc( GL_LESS );

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
	
//	// Set the camera //
//	Camera = cCamera();
//	CurrentCamera = &Camera;
	
//	// Initalize Matrix //
//	gfxSetScreenMatrix();
//
//	// Initalize Matrix Stack //
//	MatrixStack = new std::vector<Matrix3x3>();
		
	
	TexturePool::Init( "Content/textures" );
	TexturePool::AddDirectory( "" );
	
//	gfxInitCapture();

#ifdef WINDOWS_BUILD
	// Adjust Sync Settings //	 
	{
//		typedef void (APIENTRY * WGLSWAPINTERVALEXT) ( int ) ;
//		
//		WGLSWAPINTERVALEXT wglSwapIntervalEXT = (WGLSWAPINTERVALEXT) SDL_GL_GetProcAddress( "wglSwapIntervalEXT" );
		if ( wglSwapIntervalEXT != 0 ) {
			wglSwapIntervalEXT( 0 );
		} 
	}
#endif // WINDOWS_BUILD //
}

// - ------------------------------------------------------------------------------------------ - //
inline void gfxExit( ) {
//	// Kill the matrix stack //
//	delete MatrixStack;

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
