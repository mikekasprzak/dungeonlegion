// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawCircle( const Vector2D& Center, const Real& Radius, const ColorType Color = CurrentColor ) {
	//MatrixCircle( Buffer, Matrix, Center, Radius, Color );
	gfxDrawRect( Center.x-Radius, Center.y-Radius, Center.x+Radius, Center.y+Radius, Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawRadiusBox( const Vector2D& Center, const Real& Radius, const ColorType Color = CurrentColor ) {
	gfxDrawRect( Center.x-Radius, Center.y-Radius, Center.x+Radius, Center.y+Radius, Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawRadiusBox( const Vector2D& Center, const Vector2D& Radius, const ColorType Color = CurrentColor ) {
	gfxDrawRect( Center.x-Radius.x, Center.y-Radius.y, Center.x+Radius.x, Center.y+Radius.y, Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawCircleFill( const Vector2D& Center, const Real& Radius, const ColorType Color = CurrentColor ) {
	//MatrixCircleFill( Buffer, Matrix, Center, Radius, Color );
	gfxDrawRectFill( Center.x-Radius, Center.y-Radius, Center.x+Radius, Center.y+Radius, Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawRadiusBoxFill( const Vector2D& Center, const Real& Radius, const ColorType Color = CurrentColor ) {
	gfxDrawRectFill( Center.x-Radius, Center.y-Radius, Center.x+Radius, Center.y+Radius, Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawRadiusBoxFill( const Vector2D& Center, const Vector2D& Radius, const ColorType Color = CurrentColor ) {
	gfxDrawRectFill( Center.x-Radius.x, Center.y-Radius.y, Center.x+Radius.x, Center.y+Radius.y, Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawCross( const Vector2D& Center, const Real& Radius, const ColorType Color = CurrentColor ) {
	gfxSetColor( Color );
 
    float Verts[] = {
		Center.x-Radius, Center.y,
		Center.x+Radius, Center.y,
		Center.x, Center.y-Radius,
		Center.x, Center.y+Radius,
    };
    
    glVertexPointer( 2, GL_FLOAT, 0, Verts );
    glDrawArrays( GL_LINES, 0, 4 );

	gfxRestoreColor( Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawX( const Vector2D& Center, const Real& Radius, const ColorType Color = CurrentColor ) {
	gfxSetColor( Color );

    float Verts[] = {
		Center.x-Radius, Center.y-Radius,
		Center.x+Radius, Center.y+Radius,
		Center.x+Radius, Center.y-Radius,
		Center.x-Radius, Center.y+Radius,
    };
    
    glVertexPointer( 2, GL_FLOAT, 0, Verts );
    glDrawArrays( GL_LINES, 0, 4 );

	gfxRestoreColor( Color );
}
// - ------------------------------------------------------------------------------------------ - //
