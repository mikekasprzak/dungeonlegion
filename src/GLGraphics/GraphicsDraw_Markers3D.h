
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawCircle( const Vector3D& Center, const Vector3D& Radius, const ColorType Color = CurrentColor, const int Steps = 16 ) {
	gfxSetColor( Color );

	float Verts[Steps*3];
	float FloatSteps = Steps;
    
	for ( int idx = 0; idx < Steps; idx++ ) {
		Verts[(idx*3)+0] = Center.x + (Real::Cos(idx / FloatSteps) * Radius.x);
		Verts[(idx*3)+1] = Center.y + (Real::Sin(idx / FloatSteps) * Radius.y);
		Verts[(idx*3)+2] = Center.z;
	}
    
    glVertexPointer( 3, GL_FLOAT, 0, Verts );
    glDrawArrays( GL_LINE_LOOP, 0, Steps );

	gfxRestoreColor( Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawCircle( const Vector3D& Center, const Vector2D& Radius, const ColorType Color = CurrentColor, const int Steps = 16 ) {
	gfxDrawCircle( Center, Radius.ToVector3D(), Color, Steps );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawCircle( const Vector3D& Center, const Real& Radius, const ColorType Color = CurrentColor, const int Steps = 16 ) {
	gfxDrawCircle( Center, Vector3D(Radius,Radius,0), Color, Steps );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawCircleFill( const Vector3D& Center, const Vector3D& Radius, const ColorType Color = CurrentColor, const int Steps = 16 ) {
	gfxSetColor( Color );

	float Verts[Steps*3];
	float FloatSteps = Steps;
    
	for ( int idx = 0; idx < Steps; idx++ ) {
		Verts[(idx*3)+0] = Center.x + (Real::Cos(idx / FloatSteps) * Radius.x);
		Verts[(idx*3)+1] = Center.y + (Real::Sin(idx / FloatSteps) * Radius.y);
		Verts[(idx*3)+2] = Center.z;
	}
    
    glVertexPointer( 3, GL_FLOAT, 0, Verts );
    glDrawArrays( GL_TRIANGLE_FAN, 0, Steps );

	gfxRestoreColor( Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawCircleFill( const Vector3D& Center, const Vector2D& Radius, const ColorType Color = CurrentColor, const int Steps = 16 ) {
	gfxDrawCircleFill( Center, Radius.ToVector3D(), Color, Steps );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawCircleFill( const Vector3D& Center, const Real& Radius, const ColorType Color = CurrentColor, const int Steps = 16 ) {
	gfxDrawCircleFill( Center, Vector3D(Radius,Radius,0), Color, Steps );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawSquare( const Vector3D& Center, const Real& Radius, const ColorType Color = CurrentColor ) {
	gfxDrawRect( Vector3D( Center.x-Radius, Center.y-Radius, Center.z ), Vector3D( Center.x+Radius, Center.y+Radius, Center.z ), Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawSquare( const Vector3D& Center, const Vector3D& Radius, const ColorType Color = CurrentColor ) {
	gfxDrawRect( Center-Radius, Center+Radius, Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawSquare( const Vector3D& Center, const Vector2D& Radius, const ColorType Color = CurrentColor ) {
	gfxDrawSquare( Center, Radius.ToVector3D(), Color );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawSquareFill( const Vector3D& Center, const Real& Radius, const ColorType Color = CurrentColor ) {
	gfxDrawRectFill( Vector3D( Center.x-Radius, Center.y-Radius, Center.z ), Vector3D( Center.x+Radius, Center.y+Radius, Center.z ), Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawSquareFill( const Vector3D& Center, const Vector3D& Radius, const ColorType Color = CurrentColor ) {
	gfxDrawRectFill( Center-Radius, Center+Radius, Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawSquareFill( const Vector3D& Center, const Vector2D& Radius, const ColorType Color = CurrentColor ) {
	gfxDrawSquareFill( Center, Radius.ToVector3D(), Color );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawDiamond( const Vector3D& Center, const Real& Radius, const ColorType Color = CurrentColor ) {
	gfxDrawCircle( Center, Radius, Color, 4 );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawDiamond( const Vector3D& Center, const Vector3D& Radius, const ColorType Color = CurrentColor ) {
	gfxDrawCircle( Center, Radius, Color, 4 );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawDiamond( const Vector3D& Center, const Vector2D& Radius, const ColorType Color = CurrentColor ) {
	gfxDrawDiamond( Center, Radius.ToVector3D(), Color );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawDiamondFill( const Vector3D& Center, const Real& Radius, const ColorType Color = CurrentColor ) {
	gfxDrawCircleFill( Center, Radius, Color, 4 );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawDiamondFill( const Vector3D& Center, const Vector3D& Radius, const ColorType Color = CurrentColor ) {
	gfxDrawCircleFill( Center, Radius, Color, 4 );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawDiamondFill( const Vector3D& Center, const Vector2D& Radius, const ColorType Color = CurrentColor ) {
	gfxDrawDiamondFill( Center, Radius.ToVector3D(), Color );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawRadiusTriangle( const Vector3D& Center, const Real& Radius, const ColorType Color = CurrentColor ) {
	gfxDrawCircle( Center, Radius, Color, 3 );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawRadiusTriangle( const Vector3D& Center, const Vector3D& Radius, const ColorType Color = CurrentColor ) {
	gfxDrawCircle( Center, Radius, Color, 3 );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawRadiusTriangle( const Vector3D& Center, const Vector2D& Radius, const ColorType Color = CurrentColor ) {
	gfxDrawRadiusTriangle( Center, Radius.ToVector3D(), Color );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawRadiusTriangleFill( const Vector3D& Center, const Real& Radius, const ColorType Color = CurrentColor ) {
	gfxDrawCircleFill( Center, Radius, Color, 3 );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawRadiusTriangleFill( const Vector3D& Center, const Vector3D& Radius, const ColorType Color = CurrentColor ) {
	gfxDrawCircleFill( Center, Radius, Color, 3 );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawRadiusTriangleFill( const Vector3D& Center, const Vector2D& Radius, const ColorType Color = CurrentColor ) {
	gfxDrawRadiusTriangleFill( Center, Radius.ToVector3D(), Color );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawCross( const Vector3D& Center, const Vector3D& Radius, const ColorType Color = CurrentColor ) {
	gfxSetColor( Color );
 
    float Verts[] = {
		Center.x-Radius.x, Center.y, Center.z,
		Center.x+Radius.x, Center.y, Center.z,
		Center.x, Center.y-Radius.y, Center.z,
		Center.x, Center.y+Radius.y, Center.z,
    };
    
    glVertexPointer( 3, GL_FLOAT, 0, Verts );
    glDrawArrays( GL_LINES, 0, 4 );

	gfxRestoreColor( Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawCross( const Vector3D& Center, const Vector2D& Radius, const ColorType Color = CurrentColor ) {
	gfxDrawCross( Center, Radius.ToVector3D(), Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawCross( const Vector3D& Center, const Real& Radius, const ColorType Color = CurrentColor ) {
	gfxDrawCross( Center, Vector3D(Radius,Radius,0), Color );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawX( const Vector3D& Center, const Vector3D& Radius, const ColorType Color = CurrentColor ) {
	gfxSetColor( Color );

    float Verts[] = {
		Center.x-Radius.x, Center.y-Radius.y, Center.z,
		Center.x+Radius.x, Center.y+Radius.y, Center.z,
		Center.x+Radius.x, Center.y-Radius.y, Center.z,
		Center.x-Radius.x, Center.y+Radius.y, Center.z,
    };
    
    glVertexPointer( 3, GL_FLOAT, 0, Verts );
    glDrawArrays( GL_LINES, 0, 4 );

	gfxRestoreColor( Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawX( const Vector3D& Center, const Vector2D& Radius, const ColorType Color = CurrentColor ) {
	gfxDrawX( Center, Radius.ToVector3D(), Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawX( const Vector3D& Center, const Real& Radius, const ColorType Color = CurrentColor ) {
	gfxDrawX( Center, Vector3D(Radius,Radius,0), Color );
}
// - ------------------------------------------------------------------------------------------ - //
