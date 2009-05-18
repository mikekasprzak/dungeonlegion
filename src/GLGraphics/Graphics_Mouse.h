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
