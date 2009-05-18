// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawCircle( const Vector2D& Center, const Real& Radius, const ColorType Color = CurrentColor, const int Steps = 16 ) {
	gfxSetColor( Color );

	float Verts[Steps*2];
	float FloatSteps = Steps;
    
	for ( int idx = 0; idx < Steps; idx++ ) {
		Verts[(idx*2)+0] = Center.x + (Real::Cos(idx / FloatSteps) * Radius);
		Verts[(idx*2)+1] = Center.y + (Real::Sin(idx / FloatSteps) * Radius);
	}
    
    glVertexPointer( 2, GL_FLOAT, 0, Verts );
    glDrawArrays( GL_LINE_LOOP, 0, Steps );

	gfxRestoreColor( Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawCircle( const Vector2D& Center, const Vector2D& Radius, const ColorType Color = CurrentColor, const int Steps = 16 ) {
	gfxSetColor( Color );

	float Verts[Steps*2];
	float FloatSteps = Steps;
    
	for ( int idx = 0; idx < Steps; idx++ ) {
		Verts[(idx*2)+0] = Center.x + (Real::Cos(idx / FloatSteps) * Radius.x);
		Verts[(idx*2)+1] = Center.y + (Real::Sin(idx / FloatSteps) * Radius.y);
	}
    
    glVertexPointer( 2, GL_FLOAT, 0, Verts );
    glDrawArrays( GL_LINE_LOOP, 0, Steps );

	gfxRestoreColor( Color );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawCircleFill( const Vector2D& Center, const Real& Radius, const ColorType Color = CurrentColor, const int Steps = 16 ) {
	gfxSetColor( Color );

	float Verts[Steps*2];
	float FloatSteps = Steps;
    
	for ( int idx = 0; idx < Steps; idx++ ) {
		Verts[(idx*2)+0] = Center.x + (Real::Cos(idx / FloatSteps) * Radius);
		Verts[(idx*2)+1] = Center.y + (Real::Sin(idx / FloatSteps) * Radius);
	}
    
    glVertexPointer( 2, GL_FLOAT, 0, Verts );
    glDrawArrays( GL_TRIANGLE_FAN, 0, Steps );

	gfxRestoreColor( Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawCircleFill( const Vector2D& Center, const Vector2D& Radius, const ColorType Color = CurrentColor, const int Steps = 16 ) {
	gfxSetColor( Color );

	float Verts[Steps*2];
	float FloatSteps = Steps;
    
	for ( int idx = 0; idx < Steps; idx++ ) {
		Verts[(idx*2)+0] = Center.x + (Real::Cos(idx / FloatSteps) * Radius.x);
		Verts[(idx*2)+1] = Center.y + (Real::Sin(idx / FloatSteps) * Radius.y);
	}
    
    glVertexPointer( 2, GL_FLOAT, 0, Verts );
    glDrawArrays( GL_TRIANGLE_FAN, 0, Steps );

	gfxRestoreColor( Color );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawRadiusBox( const Vector2D& Center, const Real& Radius, const ColorType Color = CurrentColor ) {
	gfxDrawRect( Center.x-Radius, Center.y-Radius, Center.x+Radius, Center.y+Radius, Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawRadiusBox( const Vector2D& Center, const Vector2D& Radius, const ColorType Color = CurrentColor ) {
	gfxDrawRect( Center.x-Radius.x, Center.y-Radius.y, Center.x+Radius.x, Center.y+Radius.y, Color );
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

// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawDiamond( const Vector2D& Center, const Real& Radius, const ColorType Color = CurrentColor ) {
	gfxDrawCircle( Center, Radius, Color, 4 );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawDiamond( const Vector2D& Center, const Vector2D& Radius, const ColorType Color = CurrentColor ) {
	gfxDrawCircle( Center, Radius, Color, 4 );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawDiamondFill( const Vector2D& Center, const Real& Radius, const ColorType Color = CurrentColor ) {
	gfxDrawCircleFill( Center, Radius, Color, 4 );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawDiamondFill( const Vector2D& Center, const Vector2D& Radius, const ColorType Color = CurrentColor ) {
	gfxDrawCircleFill( Center, Radius, Color, 4 );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawRadiusTriangle( const Vector2D& Center, const Real& Radius, const ColorType Color = CurrentColor ) {
	gfxDrawCircle( Center, Radius, Color, 3 );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawRadiusTriangle( const Vector2D& Center, const Vector2D& Radius, const ColorType Color = CurrentColor ) {
	gfxDrawCircle( Center, Radius, Color, 3 );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawRadiusTriangleFill( const Vector2D& Center, const Real& Radius, const ColorType Color = CurrentColor ) {
	gfxDrawCircleFill( Center, Radius, Color, 3 );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawRadiusTriangleFill( const Vector2D& Center, const Vector2D& Radius, const ColorType Color = CurrentColor ) {
	gfxDrawCircleFill( Center, Radius, Color, 3 );
}
// - ------------------------------------------------------------------------------------------ - //

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
inline void gfxDrawCross( const Vector2D& Center, const Vector2D& Radius, const ColorType Color = CurrentColor ) {
	gfxSetColor( Color );
 
    float Verts[] = {
		Center.x-Radius.x, Center.y,
		Center.x+Radius.x, Center.y,
		Center.x, Center.y-Radius.y,
		Center.x, Center.y+Radius.y,
    };
    
    glVertexPointer( 2, GL_FLOAT, 0, Verts );
    glDrawArrays( GL_LINES, 0, 4 );

	gfxRestoreColor( Color );
}
// - ------------------------------------------------------------------------------------------ - //

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
inline void gfxDrawX( const Vector2D& Center, const Vector2D& Radius, const ColorType Color = CurrentColor ) {
	gfxSetColor( Color );

    float Verts[] = {
		Center.x-Radius.x, Center.y-Radius.y,
		Center.x+Radius.x, Center.y+Radius.y,
		Center.x+Radius.x, Center.y-Radius.y,
		Center.x-Radius.x, Center.y+Radius.y,
    };
    
    glVertexPointer( 2, GL_FLOAT, 0, Verts );
    glDrawArrays( GL_LINES, 0, 4 );

	gfxRestoreColor( Color );
}
// - ------------------------------------------------------------------------------------------ - //
