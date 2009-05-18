// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawLine( const Vector3D& P1, const Vector3D& P2, const ColorType Color = CurrentColor) {
	gfxSetColor( Color );

    float Verts[] = {
		P1.x, P1.y, P1.z,
		P2.x, P2.y, P2.z,
    };
    
    glVertexPointer( 3, GL_FLOAT, 0, Verts );
    glDrawArrays( GL_LINES, 0, 2 );

	gfxRestoreColor( Color );
}
// - ------------------------------------------------------------------------------------------ - //

//// - ------------------------------------------------------------------------------------------ - //
//inline void gfxDrawLineNormal( const Vector3D& P1, const Vector3D& P2, const Real Length = CurrentNormalLength, const ColorType Color = CurrentColor) {
//	gfxSetColor( Color );
//	
//	Vector3D Ray = (P2-P1);
//	Vector3D Normal = Ray.Tangent().Normal();
//	
//	Vector3D Center = P1 + (Ray * Real::Half);
//	Vector3D NormalPos = Center + (Normal * Length);
//
//    float Verts[] = {
//		Center.x, Center.y, Center.z,
//		NormalPos.x, NormalPos.y, NormalPos.z,
//    };
//    
//    glVertexPointer( 3, GL_FLOAT, 0, Verts );
//    glDrawArrays( GL_LINES, 0, 2 );
//
//	gfxRestoreColor( Color );
//}
//// - ------------------------------------------------------------------------------------------ - //
//inline void gfxDrawArrow( const Vector3D& P1, const Vector3D& P2, const ColorType Color = CurrentColor, const Real HeadLength = CurrentNormalLength ) {
//	gfxSetColor( Color );
//
//	Vector3D HeadPoint = P2 - P1;
//	HeadPoint.Normalize();
//	HeadPoint *= HeadLength;
//
//    float Verts[] = {
//		(float)P1.x, (float)P1.y, (float)P1.z,
//		(float)P2.x, (float)P2.y, (float)P2.z,
//		
//		
//		(float)P2.x, (float)P2.y, (float)P2.z,
//		(float)-HeadPoint.Rotate45().x+P2.x, (float)-HeadPoint.Rotate45().y+P2.y, (float)-HeadPoint.Rotate45().y+P2.z,
//
//		(float)P2.x, (float)P2.y, (float)P2.z,
//		(float)-HeadPoint.RotateNegative45().x+P2.x, (float)-HeadPoint.RotateNegative45().y+P2.y, (float)-HeadPoint.RotateNegative45().z+P2.z,
//		
//		(float)P2.x, (float)P2.y, (float)P2.z,
//		(float)-HeadPoint.Rotate45().x+P2.x, (float)-HeadPoint.Rotate45().y+P2.y, (float)-HeadPoint.RotateNegative45().z+P2.z,
//
//		(float)P2.x, (float)P2.y, (float)P2.z,
//		(float)-HeadPoint.RotateNegative45().x+P2.x, (float)-HeadPoint.RotateNegative45().y+P2.y, (float)-HeadPoint.Rotate45().z+P2.z,
//    };
//    
//    glVertexPointer( 3, GL_FLOAT, 0, Verts );
//    glDrawArrays( GL_LINES, 0, 10 );
//
//	gfxRestoreColor( Color );
//}
//// - ------------------------------------------------------------------------------------------ - //
//inline void gfxDrawArrow2( const Vector3D& P1, const Vector3D& P2, const ColorType Color = CurrentColor, const Real HeadLength = CurrentNormalLength ) {
//	gfxSetColor( Color );
//
//	Vector3D HeadPoint = P2 - P1;
//	HeadPoint.Normalize();
//	HeadPoint *= HeadLength;
//
//    float Verts[] = {
//		(float)P1.x, (float)P1.y, (float)P1.z,
//		(float)P2.x, (float)P2.y, (float)P2.z,
//
//		
//		(float)P1.x, (float)P1.y, (float)P1.z,
//		(float)HeadPoint.Rotate45().x+P1.x, (float)HeadPoint.Rotate45().y+P1.y, (float)HeadPoint.Rotate45().z+P1.z,
//
//		(float)P1.x, (float)P1.y, (float)P1.z,
//		(float)HeadPoint.RotateNegative45().x+P1.x, (float)HeadPoint.RotateNegative45().y+P1.y, (float)HeadPoint.RotateNegative45().z+P1.z,
//
//		(float)P2.x, (float)P2.y, (float)P2.z,
//		(float)-HeadPoint.Rotate45().x+P2.x, (float)-HeadPoint.Rotate45().y+P2.y, (float)-HeadPoint.Rotate45().z+P2.z,
//
//		(float)P2.x, (float)P2.y, (float)P2.z,
//		(float)-HeadPoint.RotateNegative45().x+P2.x, (float)-HeadPoint.RotateNegative45().y+P2.y, (float)-HeadPoint.RotateNegative45().z+P2.z,
//
//		
//		(float)P1.x, (float)P1.y, (float)P1.z,
//		(float)HeadPoint.Rotate45().x+P1.x, (float)HeadPoint.Rotate45().y+P1.y, (float)HeadPoint.RotateNegative45().z+P1.z,
//
//		(float)P1.x, (float)P1.y, (float)P1.z,
//		(float)HeadPoint.RotateNegative45().x+P1.x, (float)HeadPoint.RotateNegative45().y+P1.y, (float)HeadPoint.Rotate45().z+P1.z,
//
//		(float)P2.x, (float)P2.y, (float)P2.z,
//		(float)-HeadPoint.Rotate45().x+P2.x, (float)-HeadPoint.Rotate45().y+P2.y, (float)-HeadPoint.RotateNegative45().z+P2.z,
//
//		(float)P2.x, (float)P2.y, (float)P2.z,
//		(float)-HeadPoint.RotateNegative45().x+P2.x, (float)-HeadPoint.RotateNegative45().y+P2.y, (float)-HeadPoint.Rotate45().z+P2.z,
//    };
//    
//    glVertexPointer( 3, GL_FLOAT, 0, Verts );
//    glDrawArrays( GL_LINES, 0, 18 );
//
//	gfxRestoreColor( Color );
//}
//// - ------------------------------------------------------------------------------------------ - //
