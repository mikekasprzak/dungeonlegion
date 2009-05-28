//// - ------------------------------------------------------------------------------------------ - //
//inline void gfxDrawRect( const Vector3D& P1, const Vector3D& P2, const ColorType Color = CurrentColor ) {
//	gfxSetColor( Color );
//
//	float Diff = P1.z + ((P2.z - P1.z) * Real::Half);
//
//	float Verts[] = {
//		(float)P1.x, (float)P1.y, (float)P1.z,
//		(float)P1.x, (float)P2.y, Diff,
//		(float)P2.x, (float)P2.y, (float)P2.z,
//		(float)P2.x, (float)P1.y, Diff,
//	};
//    
//    glVertexPointer( 3, GL_FLOAT, 0, Verts );
//    glDrawArrays( GL_LINE_LOOP, 0, 4 );
//
//	gfxRestoreColor( Color );
//}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawRect( const Vector3D& P1, const Vector3D& P2, const ColorType Color = CurrentColor ) {
	gfxSetColor( Color );

	Vector3D Diff = P2-P1;
	Vector3D XDiff(Diff.x,0,0);
	Vector3D YDiff(0,Diff.y,0);
	Vector3D ZDiff(0,0,Diff.z);

	Vector3D Verts[] = {
		P1, P1+XDiff,
		P1, P1+YDiff,
		P1, P1+ZDiff,

		P1+ZDiff, P1+ZDiff+XDiff,
		P1+ZDiff, P1+ZDiff+YDiff,

		P2, P2-XDiff,
		P2, P2-YDiff,
		P2, P2-ZDiff,

		P2-ZDiff, P2-ZDiff-XDiff,
		P2-ZDiff, P2-ZDiff-YDiff,

		P1+XDiff, P1+ZDiff+XDiff,
		P1+YDiff, P1+ZDiff+YDiff,
	};
    
    glVertexPointer( 3, GL_FLOAT, 0, Verts );
    glDrawArrays( GL_LINES, 0, 24 );

	gfxRestoreColor( Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawRect( const Real P1x, const Real P1y, const Real P1z, const Real P2x, const Real P2y, const Real P2z, const ColorType Color = CurrentColor ) {
	gfxSetColor( Color );
	
	float Diff = P1z + ((P2z - P1z) * Real::Half);

	float Verts[] = {
		(float)P1x, (float)P1y, (float)P1z,
		(float)P1x, (float)P2y, Diff,
		(float)P2x, (float)P2y, (float)P2z,
		(float)P2x, (float)P1y, Diff,
	};
    
    glVertexPointer( 3, GL_FLOAT, 0, Verts );
    glDrawArrays( GL_LINE_LOOP, 0, 4 );

	gfxRestoreColor( Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawRectFill( const Vector3D& P1, const Vector3D& P2, const ColorType Color = CurrentColor ) {
	gfxSetColor( Color );

	float Diff = P1.z + ((P2.z - P1.z) * Real::Half);

    float Verts[] = {
		(float)P1.x, (float)P1.y, (float)P1.z,
		(float)P1.x, (float)P2.y, Diff,
		(float)P2.x, (float)P1.y, Diff,
		(float)P2.x, (float)P2.y, (float)P2.z,
    };
    
    glVertexPointer( 3, GL_FLOAT, 0, Verts );
    glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );

	gfxRestoreColor( Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawRectFill( const Real P1x, const Real P1y, const Real P1z, const Real P2x, const Real P2y, const Real P2z, const ColorType Color = CurrentColor ) {
	gfxSetColor( Color );

	float Diff = P1z + ((P2z - P1z) * Real::Half);

    float Verts[] = {
		(float)P1x, (float)P1y, (float)P1z,
		(float)P1x, (float)P2y, Diff,
		(float)P2x, (float)P1y, Diff,
		(float)P2x, (float)P2y, (float)P2z,
	};
        
    glVertexPointer( 3, GL_FLOAT, 0, Verts );
    glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );

	gfxRestoreColor( Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawRectNormals( const Vector3D& P1, const Vector3D& P2, const Real NormalLength = CurrentNormalLength, const ColorType NormalColor = CurrentNormalColor ) {
//	MatrixRectNormals( Buffer, Matrix, Rect2D::Pair( P1, P2 ), NormalLength, NormalColor );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawRectWithNormals( const Vector3D& P1, const Vector3D& P2, const ColorType Color = CurrentColor, const Real NormalLength = CurrentNormalLength, const ColorType NormalColor = CurrentNormalColor ) {
	gfxDrawRect( P1, P2, Color );
	gfxDrawRectNormals( P1, P2, NormalLength, NormalColor );
}
// - ------------------------------------------------------------------------------------------ - //
