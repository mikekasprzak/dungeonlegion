// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawRect( const Vector2D& P1, const Vector2D& P2, const ColorType Color = CurrentColor ) {
	gfxSetColor( Color );

	float Verts[] = {
		(float)P1.x, (float)P1.y,
		(float)P1.x, (float)P2.y,
		(float)P2.x, (float)P2.y,
		(float)P2.x, (float)P1.y,
	};
    
    glVertexPointer( 2, GL_FLOAT, 0, Verts );
    glDrawArrays( GL_LINE_LOOP, 0, 4 );

	gfxRestoreColor( Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawRect( const Real P1x, const Real P1y, const Real P2x, const Real P2y, const ColorType Color = CurrentColor ) {
	gfxSetColor( Color );

	float Verts[] = {
		(float)P1x, (float)P1y,
		(float)P1x, (float)P2y,
		(float)P2x, (float)P2y,
		(float)P2x, (float)P1y,
	};
    
    glVertexPointer( 2, GL_FLOAT, 0, Verts );
    glDrawArrays( GL_LINE_LOOP, 0, 4 );

	gfxRestoreColor( Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawRectFill( const Vector2D& P1, const Vector2D& P2, const ColorType Color = CurrentColor ) {
	gfxSetColor( Color );

    float Verts[] = {
		(float)P1.x, (float)P1.y,
		(float)P1.x, (float)P2.y,
		(float)P2.x, (float)P1.y,
		(float)P2.x, (float)P2.y,
    };
    
    glVertexPointer( 2, GL_FLOAT, 0, Verts );
    glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );

	gfxRestoreColor( Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawRectFill( const Real P1x, const Real P1y, const Real P2x, const Real P2y, const ColorType Color = CurrentColor ) {
	gfxSetColor( Color );

    float Verts[] = {
		(float)P1x, (float)P1y,
		(float)P1x, (float)P2y,
		(float)P2x, (float)P1y,
		(float)P2x, (float)P2y,
	};
        
    glVertexPointer( 2, GL_FLOAT, 0, Verts );
    glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );

	gfxRestoreColor( Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawRectNormals( const Vector2D& P1, const Vector2D& P2, const Real NormalLength = CurrentNormalLength, const ColorType NormalColor = CurrentNormalColor ) {
//	MatrixRectNormals( Buffer, Matrix, Rect2D::Pair( P1, P2 ), NormalLength, NormalColor );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawRectWithNormals( const Vector2D& P1, const Vector2D& P2, const ColorType Color = CurrentColor, const Real NormalLength = CurrentNormalLength, const ColorType NormalColor = CurrentNormalColor ) {
	gfxDrawRect( P1, P2, Color );
	gfxDrawRectNormals( P1, P2, NormalLength, NormalColor );
}
// - ------------------------------------------------------------------------------------------ - //
