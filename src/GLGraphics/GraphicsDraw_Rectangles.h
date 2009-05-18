// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawRect( const Vector2D& P1, const Vector2D& P2, const ColorType Color = CurrentColor ) {
	gfxSetColor( Color );

	float Verts[] = {
		(float)P1.x+0.5f, (float)P1.y+1.5f,
		(float)P1.x+0.5f, (float)P2.y+0.5f,
		(float)P2.x-0.5f, (float)P2.y+0.5f,
		(float)P2.x-0.5f, (float)P1.y+1.5f,
	};
    
    glVertexPointer( 2, GL_FLOAT, 0, Verts );
    glDrawArrays( GL_LINE_LOOP, 0, 4 );

	gfxRestoreColor( Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawRect( const Real P1x, const Real P1y, const Real P2x, const Real P2y, const ColorType Color = CurrentColor ) {
	gfxSetColor( Color );

	float Verts[] = {
		(float)P1x+0.5f, (float)P1y+1.5f,
		(float)P1x+0.5f, (float)P2y+0.5f,
		(float)P2x-0.5f, (float)P2y+0.5f,
		(float)P2x-0.5f, (float)P1y+1.5f,
	};
    
    glVertexPointer( 2, GL_FLOAT, 0, Verts );
    glDrawArrays( GL_LINE_LOOP, 0, 4 );

	gfxRestoreColor( Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawRectFill( const Vector2D& P1, const Vector2D& P2, const ColorType Color = CurrentColor ) {
	gfxSetColor( Color );

    float Verts[] = {
		(float)P1.x+0.5f, (float)P1.y+0.5f,
		(float)P1.x+0.5f, (float)P2.y+0.5f,
		(float)P2.x+0.5f, (float)P1.y+0.5f,
		(float)P2.x+0.5f, (float)P2.y+0.5f,
    };
    
    glVertexPointer( 2, GL_FLOAT, 0, Verts );
    glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );

	gfxRestoreColor( Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawRectFill( const Real P1x, const Real P1y, const Real P2x, const Real P2y, const ColorType Color = CurrentColor ) {
	gfxSetColor( Color );

    float Verts[] = {
		(float)P1x+0.5f, (float)P1y+0.5f,
		(float)P1x+0.5f, (float)P2y+0.5f,
		(float)P2x+0.5f, (float)P1y+0.5f,
		(float)P2x+0.5f, (float)P2y+0.5f,
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
