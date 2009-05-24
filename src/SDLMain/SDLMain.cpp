// - ------------------------------------------------------------------------------------------ - //
#include <Graphics.h>
#include <GraphicsDraw.h>
// - ------------------------------------------------------------------------------------------ - //
#include <cstdlib>
// - ------------------------------------------------------------------------------------------ - //
#ifdef WINDOWS_BUILD
#include "WindowsTime.h"
#else
#include "UnixTime.h"
#endif // WINDOWS_BUILD //
// - ------------------------------------------------------------------------------------------ - //
#include "Game.h"
//#include "Sound/SoundPlayer.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
bool IsActive = true;
// - ------------------------------------------------------------------------------------------ - //
void PollEvents() {
	SDL_Event event;
	// Do Event Polling //
    while ( SDL_PollEvent( &event ) ) {
	    switch( event.type ) {
			case SDL_ACTIVEEVENT: {
				IsActive = event.active.gain != 0;
		    	
		    	break;
		    }
		    case SDL_KEYDOWN: {
			    switch(event.key.keysym.sym) {
			    	case SDLK_ESCAPE: {
			    		System::CloseButtonPressed = true;
			    		break;
					}
			    	case SDLK_F10: {
			    		System::CloseButtonPressed = true;
			    		break;
					}
					
			    	case SDLK_UP: {
			    		System::UpKey = 1;
			    		break;
					}
			    	case SDLK_DOWN: {
			    		System::DownKey = 1;
			    		break;
					}
			    	case SDLK_LEFT: {
			    		System::LeftKey = 1;
			    		break;
					}
			    	case SDLK_RIGHT: {
			    		System::RightKey = 1;
			    		break;
					}
			    }
			    break;
			}
		    case SDL_KEYUP: {
			    switch(event.key.keysym.sym) {
			    	case SDLK_UP: {
			    		System::UpKey = 0;
			    		gfxOrtho();
			    		break;
					}
			    	case SDLK_DOWN: {
			    		System::DownKey = 0;
			    		gfxPerspective();
			    		break;
					}
			    	case SDLK_LEFT: {
			    		System::LeftKey = 0;
			    		break;
					}
			    	case SDLK_RIGHT: {
			    		System::RightKey = 0;
			    		break;
					}
			    }
			    break;
			}
//	    	case SDL_MOUSEBUTTONDOWN: {
//	    		if ( event.button.button == 4 ) {
//	    			Mouse.Wheel--;
//	    		}
//	    		else if ( event.button.button == 5 ) {
//	    			Mouse.Wheel++;
//	    		}
//	    		
//	    		break;
//	    	}

		case SDL_QUIT:
			System::CloseButtonPressed = true;
		    break;

		default:
		    break;
		}
	}

	System::UpdateStick();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
int main( int argc, char* argv[] ) {
	bool DepthBuffer = true;

	// Note: FullScreen'ing should be handled in some user configurable way... hardcoded for debugging.
#ifdef WINDOWS_BUILD
	bool FullScreen = false;

	gfxInit( 400, 300, 800, 600, FullScreen, DepthBuffer );
	//gfxInit( 400, 300, 1920, 1200, FullScreen, DepthBuffer );
#else // WINDOWS_BUILD //
	FullScreen = true;

	gfxInit( 400, 300, 1024, 600, FullScreen, DepthBuffer );
#endif // WINDOWS_BUILD //
	
	// Trying to solve window focus bug from MSys... didn't help //	
//	{
//		SDL_Event MyEvent;
//		MyEvent.active.type = SDL_ACTIVEEVENT;
//		MyEvent.active.gain = 1;
//		MyEvent.active.state = SDL_APPMOUSEFOCUS | SDL_APPINPUTFOCUS;// | SDL_APPACTIVE;
//		
//		SDL_PushEvent( &MyEvent );
//	}
	
//	gfxOrtho();
	gfxPerspective();


//	sndInit();
//	SDL_InitSubSystem( SDL_INIT_AUDIO );
	
	
//	SDL_InitSubSystem( SDL_INIT_JOYSTICK );

	{
		cGame Game;

		SetFramesPerSecond( 60 );
		TIMEVALUE WorkTime = GetTimeNow();

		while( !gfxHasShutdown() ) {	
			TIMEVALUE TimeDiff = SubtractTime( GetTimeNow(), WorkTime );
			int FramesOfWork = GetFrames( &TimeDiff );
	
			for ( int Frame = 0; Frame < FramesOfWork; Frame++ ) {
				PollEvents();
				
				Mouse.Update();
//				Camera.Update();
				
				Game.Step();
				
				AddFrame( &WorkTime );
			}
			
			//if ( FramesOfWork > 0 )
			{
				Game.Draw();

				gfxSwapBuffer();
			}
		}
	}
	
//	sndFree();
	// Not required because of the quit call below, but this can be used to re-init audio // 
//	SDL_QuitSubSystem( SDL_INIT_AUDIO );
	
	gfxExit();
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
