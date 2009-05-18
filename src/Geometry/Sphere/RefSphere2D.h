// - ------------------------------------------------------------------------------------------ - //
// RefSphere2D //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Geometry_RefSphere2D_H__
#define __Geometry_RefSphere2D_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class RefSphere2D {
public:
	Vector2D* _Center;
	Real _Radius;
	
public:
	RefSphere2D( const Vector2D& __Center, const Real& __Radius ) :
		_Center( &__Center ),
		_Radius( __Radius )
	{	
	}
	
public:
	inline const Vector2D& Center() const {
		return *_Center;
	}
	
	inline const Real& Radius() const {
		return _Radius;
	}
	
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Geometry_RefSphere2D_H__ //
// - ------------------------------------------------------------------------------------------ - //