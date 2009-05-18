// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawClosedPolygon( const Vector2D* Poly, const size_t PolyCount, const ColorType Color = CurrentColor ) {
	gfxSetColor( Color );
        
    glVertexPointer( 2, GL_FLOAT, 0, (const float*)Poly );
    glDrawArrays( GL_LINE_LOOP, 0, PolyCount );
    
    gfxRestoreColor( Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawOpenPolygon( const Vector2D* Poly, const size_t PolyCount, const ColorType Color = CurrentColor ) {
	gfxSetColor( Color );
        
    glVertexPointer( 2, GL_FLOAT, 0, (const float*)Poly );
    glDrawArrays( GL_LINE_STRIP, 0, PolyCount );

	gfxRestoreColor( Color );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawClosedPolygonNormals( const Vector2D* Poly, const size_t PolyCount, const Real NormalLength = CurrentNormalLength, const ColorType NormalColor = CurrentNormalColor ) {
//	MatrixClosedPolygonNormals( Buffer, Matrix, Poly, PolyCount, NormalLength, NormalColor );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawOpenPolygonNormals( const Vector2D* Poly, const size_t PolyCount, const Real NormalLength = CurrentNormalLength, const ColorType NormalColor = CurrentNormalColor ) {
//	MatrixOpenPolygonNormals( Buffer, Matrix, Poly, PolyCount, NormalLength, NormalColor );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawClosedPolygonInvNormals( const Vector2D* Poly, const size_t PolyCount, const Real NormalLength = CurrentNormalLength, const ColorType NormalColor = CurrentNormalColor ) {
//	MatrixClosedPolygonInvNormals( Buffer, Matrix, Poly, PolyCount, NormalLength, NormalColor );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawOpenPolygonInvNormals( const Vector2D* Poly, const size_t PolyCount, const Real NormalLength = CurrentNormalLength, const ColorType NormalColor = CurrentNormalColor ) {
//	MatrixOpenPolygonInvNormals( Buffer, Matrix, Poly, PolyCount, NormalLength, NormalColor );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawClosedPolygonWithNormals( const Vector2D* Poly, const size_t PolyCount, const ColorType Color = CurrentColor, const Real NormalLength = CurrentNormalLength, const ColorType NormalColor = CurrentNormalColor ) {
	gfxDrawClosedPolygon(Poly, PolyCount, Color );
	gfxDrawClosedPolygonNormals(Poly, PolyCount, NormalLength, NormalColor );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawOpenPolygonWithNormals( const Vector2D* Poly, const size_t PolyCount, const ColorType Color = CurrentColor, const Real NormalLength = CurrentNormalLength, const ColorType NormalColor = CurrentNormalColor ) {
	gfxDrawOpenPolygon(Poly, PolyCount, Color );
	gfxDrawOpenPolygonNormals(Poly, PolyCount, NormalLength, NormalColor );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawClosedPolygonWithInvNormals( const Vector2D* Poly, const size_t PolyCount, const ColorType Color = CurrentColor, const Real NormalLength = CurrentNormalLength, const ColorType NormalColor = CurrentNormalColor ) {
	gfxDrawClosedPolygon(Poly, PolyCount, Color );
	gfxDrawClosedPolygonInvNormals(Poly, PolyCount, NormalLength, NormalColor );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawOpenPolygonWithInvNormals( const Vector2D* Poly, const size_t PolyCount, const ColorType Color = CurrentColor, const Real NormalLength = CurrentNormalLength, const ColorType NormalColor = CurrentNormalColor ) {
	gfxDrawOpenPolygon(Poly, PolyCount, Color );
	gfxDrawOpenPolygonInvNormals(Poly, PolyCount, NormalLength, NormalColor );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawPolygonEdge( const int Index, const Vector2D* Poly, const size_t PolyCount, const ColorType Color = CurrentColor ) {
	int NextIndex = Index+1;
	if ( NextIndex >= PolyCount ) 
		NextIndex = 0;
	gfxDrawLine( Poly[Index], Poly[NextIndex], Color );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawEdgedPolygonNormals( const Vector2D* Poly, const bool* PolygonEnabled, const size_t PolyCount, const Real NormalLength = CurrentNormalLength, const ColorType NormalColor = CurrentNormalColor ) {
//	MatrixEdgedPolygonNormals( Buffer, Matrix, Poly, PolygonEnabled, PolyCount, NormalLength, NormalColor );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawEdgedPolygonInvNormals( const Vector2D* Poly, const bool* PolygonEnabled, const size_t PolyCount, const Real NormalLength = CurrentNormalLength, const ColorType NormalColor = CurrentNormalColor ) {
//	MatrixEdgedPolygonInvNormals( Buffer, Matrix, Poly, PolygonEnabled, PolyCount, NormalLength, NormalColor );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawEdgedPolygon( const Vector2D* Poly, const bool* PolygonEnabled, const size_t PolyCount, const ColorType Color = CurrentColor ) {
//	MatrixEdgedPolygon( Buffer, Matrix, Poly, PolygonEnabled, PolyCount, Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawEdgedPolygonWithNormals( const Vector2D* Poly, const bool* PolygonEnabled, const size_t PolyCount, const ColorType Color = CurrentColor, const Real NormalLength = CurrentNormalLength, const ColorType NormalColor = CurrentNormalColor ) {
//	MatrixEdgedPolygonWithNormals( Buffer, Matrix, Poly, PolygonEnabled, PolyCount, Color, NormalLength, NormalColor );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawEdgedPolygonWithInvNormals( const Vector2D* Poly, const bool* PolygonEnabled, const size_t PolyCount, const ColorType Color = CurrentColor, const Real NormalLength = CurrentNormalLength, const ColorType NormalColor = CurrentNormalColor ) {
//	MatrixEdgedPolygonWithInvNormals( Buffer, Matrix, Poly, PolygonEnabled, PolyCount, Color, NormalLength, NormalColor );
}
// - ------------------------------------------------------------------------------------------ - //
