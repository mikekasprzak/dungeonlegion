// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawLine( const Vector2D& P1, const Vector2D& P2, const ColorType Color = CurrentColor) {
	gfxSetColor( Color );

    float Verts[] = {
		P1.x, P1.y,
		P2.x, P2.y,
    };
    
    glVertexPointer( 2, GL_FLOAT, 0, Verts );
    glDrawArrays( GL_LINES, 0, 2 );

	gfxRestoreColor( Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawLineNormal( const Vector2D& P1, const Vector2D& P2, const Real Length = CurrentNormalLength, const ColorType Color = CurrentColor) {
	gfxSetColor( Color );
	
	Vector2D Ray = (P2-P1);
	Vector2D Normal = Ray.Tangent().Normal();
	
	Vector2D Center = P1 + (Ray * Real::Half);
	Vector2D NormalPos = Center + (Normal * Length);

    float Verts[] = {
		Center.x, Center.y,
		NormalPos.x, NormalPos.y,
    };
    
    glVertexPointer( 2, GL_FLOAT, 0, Verts );
    glDrawArrays( GL_LINES, 0, 2 );

	gfxRestoreColor( Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawArrow( const Vector2D& P1, const Vector2D& P2, const ColorType Color = CurrentColor, const Real HeadLength = CurrentNormalLength ) {
	gfxSetColor( Color );

	Vector2D HeadPoint = P2 - P1;
	HeadPoint.Normalize();
	HeadPoint *= HeadLength;

    float Verts[] = {
		(float)P1.x+0.0f, (float)P1.y+0.1f,
		(float)P2.x-0.1f, (float)P2.y-0.0f,
		(float)P2.x+0.0f, (float)P2.y+0.1f,
		(float)-HeadPoint.Rotate45().x+P2.x+0.0f, (float)-HeadPoint.Rotate45().y+P2.y+0.1f,
		(float)P2.x+0.0f, (float)P2.y+0.1f,
		(float)-HeadPoint.RotateNegative45().x+P2.x+0.0f, (float)-HeadPoint.RotateNegative45().y+P2.y+0.1f,
    };
    
    glVertexPointer( 2, GL_FLOAT, 0, Verts );
    glDrawArrays( GL_LINES, 0, 6 );

	gfxRestoreColor( Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawArrow2( const Vector2D& P1, const Vector2D& P2, const ColorType Color = CurrentColor, const Real HeadLength = CurrentNormalLength ) {
	gfxSetColor( Color );

	Vector2D HeadPoint = P2 - P1;
	HeadPoint.Normalize();
	HeadPoint *= HeadLength;

    float Verts[] = {
		(float)P1.x+0.0f, (float)P1.y+0.1f,
		(float)P2.x-0.1f, (float)P2.y-0.0f,
		(float)P1.x+0.0f, (float)P1.y+0.1f,
		(float)HeadPoint.Rotate45().x+P1.x+0.0f, (float)HeadPoint.Rotate45().y+P1.y+0.1f,
		(float)P1.x+0.0f, (float)P1.y+0.1f,
		(float)HeadPoint.RotateNegative45().x+P1.x+0.0f, (float)HeadPoint.RotateNegative45().y+P1.y+0.1f,
		(float)P2.x+0.0f, (float)P2.y+0.1f,
		(float)-HeadPoint.Rotate45().x+P2.x+0.0f, (float)-HeadPoint.Rotate45().y+P2.y+0.1f,
		(float)P2.x+0.0f, (float)P2.y+0.1f,
		(float)-HeadPoint.RotateNegative45().x+P2.x+0.0f, (float)-HeadPoint.RotateNegative45().y+P2.y+0.1f,
    };
    
    glVertexPointer( 2, GL_FLOAT, 0, Verts );
    glDrawArrays( GL_LINES, 0, 10 );

	gfxRestoreColor( Color );
}
// - ------------------------------------------------------------------------------------------ - //
