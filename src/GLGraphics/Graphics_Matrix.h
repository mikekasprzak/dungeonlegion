
#include <vector>
#include <Math/Matrix.h>

extern Matrix3x3 Matrix;
extern std::vector<Matrix3x3>* MatrixStack;


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
