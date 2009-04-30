// - ------------------------------------------------------------------------------------------ - //
#include "Graphics.h"
#include "GraphicsDraw.h"
// - ------------------------------------------------------------------------------------------ - //
#ifdef SDL_BUILD
SDL_Surface* Buffer;
#endif // SDL_BUILD //

bool ShutdownGame;

Matrix3x3 Matrix;

std::vector<Matrix3x3>* MatrixStack;

const Font* CurrentFont;

unsigned int GLCapture;
// - ------------------------------------------------------------------------------------------ - //
namespace Screen {
	// - -------------------------------------------------------------------------------------- - //
	int Width, Height;
	int Scalar;
	
	Real AspectRatio;
	// - -------------------------------------------------------------------------------------- - //
	Vector2D Shape;
	Vector2D HalfShape;
	// - -------------------------------------------------------------------------------------- - //
//	int ClipX, ClipY;
//	int ClipW, ClipH;
	// - -------------------------------------------------------------------------------------- - //
//	ColorType Color;
//	ColorType NormalColor;
//	Real NormalLength;
	// - -------------------------------------------------------------------------------------- - //
	volatile bool CloseButtonPressed;
	// - -------------------------------------------------------------------------------------- - //
//	void CloseButtonHandler()
//	{
//		CloseButtonPressed = true;
//	}
//	END_OF_FUNCTION(CloseButtonHandler)
	// - -------------------------------------------------------------------------------------- - //
};

// Non resulotion globals //
namespace System {
	ColorType Color;
	ColorType NormalColor;
	Real NormalLength;

	volatile bool CloseButtonPressed;
	
	int UpKey, DownKey, RightKey, LeftKey;
	
	int StickX, StickY;
	void UpdateStick() {
		if ( UpKey ) {
			if ( DownKey ) {
				StickY = 0;
			}
			else {
				StickY = 1;
			}
		}
		else if ( DownKey ) {
			StickY = -1;
		}
		else {
			StickY = 0;
		}

		if ( RightKey ) {
			if ( LeftKey ) {
				StickX = 0;
			}
			else {
				StickX = 1;
			}
		}
		else if ( LeftKey ) {
			StickX = -1;
		}
		else {
			StickX = 0;
		}
	}
};

// Reference Screen //
namespace RefScreen {
	int Width, Height;
	
	Real AspectRatio;

	Vector2D Shape;
	Vector2D HalfShape;


	Real Scalar;
	int OffsetX;
	int OffsetY;

	int DiffX;
	int DiffY;
};

// Full Reference Screen (Scaled version of Actual) //
namespace FullRefScreen {
	int Width, Height;
	
	Real AspectRatio;

	Vector2D Shape;
	Vector2D HalfShape;
};

// Actual Screen //
namespace ActualScreen {
	int Width, Height;
	
	Real AspectRatio;

	Vector2D Shape;
	Vector2D HalfShape;
};

// Overscan Screen //
namespace OverScreen {
	int Width, Height;
	
	Real AspectRatio;
};


// - ------------------------------------------------------------------------------------------ - //
cMouse Mouse;
// - ------------------------------------------------------------------------------------------ - //
cCamera Camera;
cCamera* CurrentCamera = &Camera;
// - ------------------------------------------------------------------------------------------ - //
//Vector2D ViewShape;
//Vector2D HalfViewShape;
// - ------------------------------------------------------------------------------------------ - //
ColorType CurrentColor;
ColorType CurrentNormalColor;
Real CurrentNormalLength;
// - ------------------------------------------------------------------------------------------ - //
//Vector2D CameraPos;
//Real CameraScale;
// - ------------------------------------------------------------------------------------------ - //
