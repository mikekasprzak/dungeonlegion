// - ------------------------------------------------------------------------------------------ - //
// RGBASet //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Geometry_RGBASet_H__
#define __Geometry_RGBASet_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template <class T>
class RGBASet {
public:
	T r, g, b, a;

public:
	RGBASet() {
	}

	RGBASet( T _r, T _g, T _b, T _a ) :
		r( _r ),
		g( _g ),
		b( _b ),
		a( _a )
	{
	}
	
	// - -------------------------------------------------------------------------------------- - //
	inline bool operator == ( const RGBASet& _Vs ) const {
		if ( (r - _Vs.r) == 0 )
			if ( (g - _Vs.g) == 0 )
				if ( (b - _Vs.b) == 0 )
					return (a - _Vs.a) == 0;
		return false;
	}

};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Geometry_RGBASet_H__ //
// - ------------------------------------------------------------------------------------------ - //
