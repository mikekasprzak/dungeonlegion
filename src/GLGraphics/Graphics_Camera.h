#include <Math/Matrix.h>
#include <Geometry/Rect.h>

/*
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
*/

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
