// - ------------------------------------------------------------------------------------------ - //
#ifndef __ExitPortal_H__
#define __ExitPortal_H__
// - ------------------------------------------------------------------------------------------ - //
#include <AllegroGraphics/Graphics.h>
#include <AllegroGraphics/GraphicsDraw.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector.h>
#include <PolyMap/PolyMap.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class cExitPortal { 
public:
	Vector2D Pos;
	Real Radius;

public:
	inline cExitPortal( const Vector2D& _Pos, const Real _Radius = 16 ) :
		Pos( _Pos ),
		Radius( _Radius )
	{
	}
	
public:
	inline void Step() {
		
	}
	
	inline void Draw() { 
		gfxDrawCircle( Pos, Radius, RGB_YELLOW );
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __ExitPortal_H__ //
// - ------------------------------------------------------------------------------------------ - //
