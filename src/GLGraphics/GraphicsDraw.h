// - ------------------------------------------------------------------------------------------ - //
#ifndef __SDLGraphics_GraphicsDraw_H__
#define __SDLGraphics_GraphicsDraw_H__
// - ------------------------------------------------------------------------------------------ - //
#include "Graphics.h"
#include "UV.h"
#include "Font.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
extern const Font* CurrentFont;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define gfxPrintf(p,c,_Format,_Args...) \
	gfxPrintfLeft(p,c,_Format, ## _Args)
// - ------------------------------------------------------------------------------------------ - //
#define gfxPrintfLeft(p,c,_Format,_Args...) \
{ \
	char StrBuff[1024]; \
	sprintf( StrBuff, _Format, ## _Args ); \
	gfxPrint(p,c,StrBuff); \
}
// - ------------------------------------------------------------------------------------------ - //
#define gfxPrintfCenter(p,c,_Format,_Args...) \
{ \
	char StrBuff[1024]; \
	sprintf( StrBuff, _Format, ## _Args ); \
	Vector2D Offset( gfxTextWidth(StrBuff) * 0.5, 0 ); \
	gfxPrint((p)-Offset,c,StrBuff); \
}
// - ------------------------------------------------------------------------------------------ - //
#define gfxPrintfRight(p,c,_Format,_Args...) \
{ \
	char StrBuff[1024]; \
	sprintf( StrBuff, _Format, ## _Args ); \
	Vector2D Offset( gfxTextWidth(StrBuff), 0 ); \
	gfxPrint((p)-Offset,c,StrBuff); \
}
// - ------------------------------------------------------------------------------------------ - //
#define gfxPrintfLeftCenter(p,c,_Format,_Args...) \
{ \
	char StrBuff[1024]; \
	sprintf( StrBuff, _Format, ## _Args ); \
	Vector2D Offset( 0, gfxTextHeight(StrBuff) * 0.5 ); \
	gfxPrint((p)-Offset,c,StrBuff); \
}
// - ------------------------------------------------------------------------------------------ - //
#define gfxPrintfCenterCenter(p,c,_Format,_Args...) \
{ \
	char StrBuff[1024]; \
	sprintf( StrBuff, _Format, ## _Args ); \
	Vector2D Offset( gfxTextWidth(StrBuff) * 0.5, gfxTextHeight(StrBuff) * 0.5 ); \
	gfxPrint((p)-Offset,c,StrBuff); \
}
// - ------------------------------------------------------------------------------------------ - //
#define gfxPrintfRightCenter(p,c,_Format,_Args...) \
{ \
	char StrBuff[1024]; \
	sprintf( StrBuff, _Format, ## _Args ); \
	Vector2D Offset( gfxTextWidth(StrBuff), gfxTextHeight(StrBuff) * 0.5 ); \
	gfxPrint((p)-Offset,c,StrBuff); \
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define gfxXPrintf(p,c,s,_Format,_Args...) \
	gfxPrintfLeft(p,c,s,_Format, ## _Args)
// - ------------------------------------------------------------------------------------------ - //
#define gfxXPrintfLeft(p,c,s,_Format,_Args...) \
{ \
	char StrBuff[1024]; \
	sprintf( StrBuff, _Format, ## _Args ); \
	gfxPrint(p,c,StrBuff,s); \
}
// - ------------------------------------------------------------------------------------------ - //
#define gfxXPrintfCenter(p,c,s,_Format,_Args...) \
{ \
	char StrBuff[1024]; \
	sprintf( StrBuff, _Format, ## _Args ); \
	Vector2D Offset( gfxTextWidth(StrBuff,s) * 0.5, 0 ); \
	gfxPrint((p)-Offset,c,StrBuff,s); \
}
// - ------------------------------------------------------------------------------------------ - //
#define gfxXPrintfRight(p,c,s,_Format,_Args...) \
{ \
	char StrBuff[1024]; \
	sprintf( StrBuff, _Format, ## _Args ); \
	Vector2D Offset( gfxTextWidth(StrBuff,s), 0 ); \
	gfxPrint((p)-Offset,c,StrBuff,s); \
}
// - ------------------------------------------------------------------------------------------ - //
#define gfxXPrintfLeftCenter(p,c,s,_Format,_Args...) \
{ \
	char StrBuff[1024]; \
	sprintf( StrBuff, _Format, ## _Args ); \
	Vector2D Offset( 0, gfxTextHeight(StrBuff,s) * 0.5 ); \
	gfxPrint((p)-Offset,c,StrBuff,s); \
}
// - ------------------------------------------------------------------------------------------ - //
#define gfxXPrintfCenterCenter(p,c,s,_Format,_Args...) \
{ \
	char StrBuff[1024]; \
	sprintf( StrBuff, _Format, ## _Args ); \
	Vector2D Offset( gfxTextWidth(StrBuff,s) * 0.5, gfxTextHeight(StrBuff,s) * 0.5 ); \
	gfxPrint((p)-Offset,c,StrBuff,s); \
}
// - ------------------------------------------------------------------------------------------ - //
#define gfxXPrintfRightCenter(p,c,s,_Format,_Args...) \
{ \
	char StrBuff[1024]; \
	sprintf( StrBuff, _Format, ## _Args ); \
	Vector2D Offset( gfxTextWidth(StrBuff,s), gfxTextHeight(StrBuff,s) * 0.5 ); \
	gfxPrint((p)-Offset,c,StrBuff,s); \
}
// - ------------------------------------------------------------------------------------------ - //

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
inline void gfxDrawLineNormal( const Vector2D& P1, const Vector2D& P2, const Real Length = Real(8), const ColorType Color = CurrentColor) {
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


// - ------------------------------------------------------------------------------------------ - //
inline void gfxEnableAlphaBlending() {
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
//	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxEnableAddativeBlending() {
	glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDisableBlending() {
	glDisable( GL_BLEND );
}
// - ------------------------------------------------------------------------------------------ - //


//// - ------------------------------------------------------------------------------------------ - //
//inline void gfxSetTexture( unsigned int TextureId ) {
//	glBindTexture( GL_TEXTURE_2D, TextureId );
//}
//// - ------------------------------------------------------------------------------------------ - //
//extern unsigned int gfxLoadTexture( const char* MyFile );
//// - ------------------------------------------------------------------------------------------ - //
//inline void gfxFreeTexture( unsigned int& MyTexture ) {
//	glDeleteTextures( 1, &MyTexture );
//}
//// - ------------------------------------------------------------------------------------------ - //



// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawTexturedPolygon( const float* Vertex, const UVType* UV, const size_t VertexCount, const Vector2D& Offset ) {
    glEnable(GL_TEXTURE_2D);
    //glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	{
		float Verts[ VertexCount << 1 ];
		
		for ( int idx = 0; idx < VertexCount; idx++ ) {
			Verts[0+(idx<<1)] = (float)Offset.x + Vertex[0+(idx<<1)];
			Verts[1+(idx<<1)] = (float)Offset.y + Vertex[1+(idx<<1)];
		}
		
		glVertexPointer(2, GL_FLOAT, 0, Verts);
		glTexCoordPointer(2, GL_UVType, 0, UV);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, VertexCount);
	}
	
	glDisable(GL_TEXTURE_2D);	
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawTexturedPolygon( const Vector2D* Vertex, const UVType* UV, const size_t VertexCount, const Vector2D& Offset ) {
	gfxDrawTexturedPolygon( (const float*)Vertex, UV, VertexCount, Offset );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawScaledTexturedPolygon( const float* Vertex, const UVType* UV, const size_t VertexCount, const Vector2D& Offset, const float Scale ) {
    glEnable(GL_TEXTURE_2D);
    //glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	{
		float Verts[ VertexCount << 1 ];
		
		for ( int idx = 0; idx < VertexCount; idx++ ) {
			Verts[0+(idx<<1)] = (float)Offset.x + (Vertex[0+(idx<<1)] * Scale);
			Verts[1+(idx<<1)] = (float)Offset.y + (Vertex[1+(idx<<1)] * Scale);
		}
		
		glVertexPointer(2, GL_FLOAT, 0, Verts);
		glTexCoordPointer(2, GL_UVType, 0, UV);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, VertexCount);
	}
	
	glDisable(GL_TEXTURE_2D);	
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawScaledTexturedPolygon( const Vector2D* Vertex, const UVType* UV, const size_t VertexCount, const Vector2D& Offset, const float Scale ) {
	gfxDrawScaledTexturedPolygon( (const float*)Vertex, UV, VertexCount, Offset, Scale );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawScaledTexturedPolygon( const float* Vertex, const UVType* UV, const size_t VertexCount, const Vector2D& Offset, const Vector2D& Scale ) {
    glEnable(GL_TEXTURE_2D);
    //glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	{
		float Verts[ VertexCount << 1 ];
		
		for ( int idx = 0; idx < VertexCount; idx++ ) {
			Verts[0+(idx<<1)] = (float)Offset.x + (Vertex[0+(idx<<1)] * Scale.x);
			Verts[1+(idx<<1)] = (float)Offset.y + (Vertex[1+(idx<<1)] * Scale.y);
		}
		
		glVertexPointer(2, GL_FLOAT, 0, Verts);
		glTexCoordPointer(2, GL_UVType, 0, UV);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, VertexCount);
	}
	
	glDisable(GL_TEXTURE_2D);	
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawScaledTexturedPolygon( const Vector2D* Vertex, const UVType* UV, const size_t VertexCount, const Vector2D& Offset, const Vector2D& Scale ) {
	gfxDrawScaledTexturedPolygon( (const float*)Vertex, UV, VertexCount, Offset, Scale );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawTexturedPolygons( const float* Vertex, const UVType* UV, const size_t VertexCount ) {
	glEnable(GL_TEXTURE_2D);
	//glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glVertexPointer(2, GL_FLOAT, 0, Vertex);
	glTexCoordPointer(2, GL_UVType, 0, UV);
	glDrawArrays(GL_TRIANGLES, 0, VertexCount);
	
	glDisable(GL_TEXTURE_2D);	
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawTexturedIndexedPolygons( const float* Vertex, const UVType* UV, const unsigned short* Indexes, const size_t IndexCount ) {
	glEnable(GL_TEXTURE_2D);
	//glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glVertexPointer(2, GL_FLOAT, 0, Vertex);
	glTexCoordPointer(2, GL_UVType, 0, UV);
	glDrawElements(GL_TRIANGLES, IndexCount, GL_UNSIGNED_SHORT, Indexes);
	
	glDisable(GL_TEXTURE_2D);	
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawTexturedIndexedPolygons( const float* Vertex, const UVType* UV, const unsigned int* Colors, const unsigned short* Indexes, const size_t IndexCount ) {
	glEnable(GL_TEXTURE_2D);
	//glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	
	glVertexPointer(2, GL_FLOAT, 0, Vertex);
	glTexCoordPointer(2, GL_UVType, 0, UV);
	glColorPointer(4, GL_UNSIGNED_BYTE, 0, Colors);
	glDrawElements(GL_TRIANGLES, IndexCount, GL_UNSIGNED_SHORT, Indexes);
	
	glDisableClientState(GL_COLOR_ARRAY);
	
	glDisable(GL_TEXTURE_2D);
	gfxApplyColor( CurrentColor );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawColoredPolygons( const float* Vertex, const unsigned int* Colors, const size_t VertexCount ) {
	glEnableClientState(GL_COLOR_ARRAY);
	
	glVertexPointer(2, GL_FLOAT, 0, Vertex);
	glColorPointer(4, GL_UNSIGNED_BYTE, 0, Colors);
	glDrawArrays(GL_TRIANGLES, 0, VertexCount);
	
	glDisableClientState(GL_COLOR_ARRAY);
	
	gfxApplyColor( CurrentColor );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawPolygons( const float* Vertex, const size_t VertexCount ) {
	glVertexPointer(2, GL_FLOAT, 0, Vertex);
	glDrawArrays(GL_TRIANGLES, 0, VertexCount);
}
// - ------------------------------------------------------------------------------------------ - //


#include <Allocator/Allocator.h>
#include <Allocator/Vector2DAllocator.h>
#include <Allocator/UVAllocator.h>

// - ------------------------------------------------------------------------------------------ - //
inline void gfxSetFont( const Font& FontName ) {
	CurrentFont = &FontName;
}
// - ------------------------------------------------------------------------------------------ - //
inline const float gfxTextWidth( const char* Msg, const float Scale = 1.0f ) {
	float Pos = 0;
	
	// For every Character in the string //
	for ( int CurrentChar = 0; Msg[CurrentChar] != 0; CurrentChar++ ) {
		char ch = Msg[CurrentChar]-' ';
		Pos += CurrentFont->PixelWidth[ch];
	}

	return Pos * Scale;
}
// - ------------------------------------------------------------------------------------------ - //
inline const float gfxTextHeight( const char*, const float Scale = 1.0f ) {
	return *(CurrentFont->PixelHeight) * Scale;
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxPrint( const Vector2D& _Pos, const ColorType Color, const char* Msg ) {
	//const int _Length = strlen( Msg );
	const int Length = 128;
	
	Vector2DAllocator< Length * 4 > Vert;
	UVAllocator< Length * 4 > UV;
	Allocator< unsigned short, Length * 6 > Indexes;
	
	int PolygonIndex = 0;
	
	Vector2D Pos = _Pos;
	
	// For every Character in the string //
	for ( int CurrentChar = 0; Msg[CurrentChar] != 0; CurrentChar++ ) {
		char ch = Msg[CurrentChar]-' ';
		
		if ( ch != 0 ) {
			Vert.AddQuad4( CurrentFont->TriStripTable[ CurrentFont->BlockWidth[ch] - 1 ], Pos );
			UV.AddQuad4( &CurrentFont->UVStrip[8*ch] );
			
			int StartIndex = Indexes.AddMany( 6 );
			// TODO: Optimize this in to a single write operation per pair //
			Indexes[StartIndex+0] = (PolygonIndex)+0;
			Indexes[StartIndex+1] = (PolygonIndex)+1;
			Indexes[StartIndex+2] = (PolygonIndex)+2;
			Indexes[StartIndex+3] = (PolygonIndex)+2;
			Indexes[StartIndex+4] = (PolygonIndex)+1;
			Indexes[StartIndex+5] = (PolygonIndex)+3;
			
			PolygonIndex += 4;
		}
		Pos += Vector2D( CurrentFont->PixelWidth[ch], 0 );
		
	}
	
	ColorType BackupColor = CurrentColor;
	gfxSetColor( Color );
	
	// Draw the string //
	gfxDrawTexturedIndexedPolygons(
		(float*)Vert.Data,
		(UVType*)UV.Data,
		Indexes.Data,
		Indexes.Size()
		);
	
	gfxSetColor( BackupColor );
} 
// - ------------------------------------------------------------------------------------------ - //
inline void gfxPrint( const Vector2D& _Pos, const ColorType Color, const char* Msg, Real Scale ) {
	//const int _Length = strlen( Msg );
	const int Length = 128;
	
	Vector2DAllocator< Length * 4 > Vert;
	UVAllocator< Length * 4 > UV;
	Allocator< unsigned short, Length * 6 > Indexes;
	
	int PolygonIndex = 0;
	
	Vector2D Pos = _Pos;
	
	// For every Character in the string //
	for ( int CurrentChar = 0; Msg[CurrentChar] != 0; CurrentChar++ ) {
		char ch = Msg[CurrentChar]-' ';
		
		if ( ch != 0 ) {
			Vert.AddQuad4( CurrentFont->TriStripTable[ CurrentFont->BlockWidth[ch] - 1 ], Pos, Scale );
			UV.AddQuad4( &CurrentFont->UVStrip[8*ch] );
			
			int StartIndex = Indexes.AddMany( 6 );
			// TODO: Optimize this in to a single write operation per pair //
			Indexes[StartIndex+0] = (PolygonIndex)+0;
			Indexes[StartIndex+1] = (PolygonIndex)+1;
			Indexes[StartIndex+2] = (PolygonIndex)+2;
			Indexes[StartIndex+3] = (PolygonIndex)+2;
			Indexes[StartIndex+4] = (PolygonIndex)+1;
			Indexes[StartIndex+5] = (PolygonIndex)+3;
			
			PolygonIndex += 4;
		}
		Pos += Vector2D( CurrentFont->PixelWidth[ch], 0 ) * Scale;
		
	}
	
	ColorType BackupColor = CurrentColor;
	gfxSetColor( Color );
	
	// Draw the string //
	gfxDrawTexturedIndexedPolygons(
		(float*)Vert.Data,
		(UVType*)UV.Data,
		Indexes.Data,
		Indexes.Size()
		);
	
	gfxSetColor( BackupColor );
} 
// - ------------------------------------------------------------------------------------------ - //
inline void gfxPrint( const Vector2D& _Pos, const ColorType Color, const char* Msg, const Vector2D& Scale ) {
	//const int _Length = strlen( Msg );
	const int Length = 128;
	
	Vector2DAllocator< Length * 4 > Vert;
	UVAllocator< Length * 4 > UV;
	Allocator< unsigned short, Length * 6 > Indexes;
	
	int PolygonIndex = 0;
	
	Vector2D Pos = _Pos;
	
	// For every Character in the string //
	for ( int CurrentChar = 0; Msg[CurrentChar] != 0; CurrentChar++ ) {
		char ch = Msg[CurrentChar]-' ';
		
		if ( ch != 0 ) {
			Vert.AddQuad4( CurrentFont->TriStripTable[ CurrentFont->BlockWidth[ch] - 1 ], Pos, Scale );
			UV.AddQuad4( &CurrentFont->UVStrip[8*ch] );
			
			int StartIndex = Indexes.AddMany( 6 );
			// TODO: Optimize this in to a single write operation per pair //
			Indexes[StartIndex+0] = (PolygonIndex)+0;
			Indexes[StartIndex+1] = (PolygonIndex)+1;
			Indexes[StartIndex+2] = (PolygonIndex)+2;
			Indexes[StartIndex+3] = (PolygonIndex)+2;
			Indexes[StartIndex+4] = (PolygonIndex)+1;
			Indexes[StartIndex+5] = (PolygonIndex)+3;
			
			PolygonIndex += 4;
		}
		Pos += Vector2D( CurrentFont->PixelWidth[ch], 0 );
		
	}
	
	ColorType BackupColor = CurrentColor;
	gfxSetColor( Color );
	
	// Draw the string //
	gfxDrawTexturedIndexedPolygons(
		(float*)Vert.Data,
		(UVType*)UV.Data,
		Indexes.Data,
		Indexes.Size()
		);
	
	gfxSetColor( BackupColor );
} 
// - ------------------------------------------------------------------------------------------ - //
inline void gfxPrint( const Vector2D& _Pos, const ColorType Color, const char* Msg, const Matrix2x2& Scale ) {
	//const int _Length = strlen( Msg );
	const int Length = 128;
	
	Vector2DAllocator< Length * 4 > Vert;
	UVAllocator< Length * 4 > UV;
	Allocator< unsigned short, Length * 6 > Indexes;
	
	int PolygonIndex = 0;
	
	Vector2D Pos = _Pos;
	
	// For every Character in the string //
	for ( int CurrentChar = 0; Msg[CurrentChar] != 0; CurrentChar++ ) {
		char ch = Msg[CurrentChar]-' ';
		
		if ( ch != 0 ) {
			Vert.AddQuad4( CurrentFont->TriStripTable[ CurrentFont->BlockWidth[ch] - 1 ], Pos, Scale );
			UV.AddQuad4( &CurrentFont->UVStrip[8*ch] );
			
			int StartIndex = Indexes.AddMany( 6 );
			// TODO: Optimize this in to a single write operation per pair //
			Indexes[StartIndex+0] = (PolygonIndex)+0;
			Indexes[StartIndex+1] = (PolygonIndex)+1;
			Indexes[StartIndex+2] = (PolygonIndex)+2;
			Indexes[StartIndex+3] = (PolygonIndex)+2;
			Indexes[StartIndex+4] = (PolygonIndex)+1;
			Indexes[StartIndex+5] = (PolygonIndex)+3;
			
			PolygonIndex += 4;
		}
		Pos += Vector2D( CurrentFont->PixelWidth[ch], 0 );
		
	}
	
	ColorType BackupColor = CurrentColor;
	gfxSetColor( Color );
	
	// Draw the string //
	gfxDrawTexturedIndexedPolygons(
		(float*)Vert.Data,
		(UVType*)UV.Data,
		Indexes.Data,
		Indexes.Size()
		);
	
	gfxSetColor( BackupColor );
} 
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __SDLGraphics_GraphicsDraw_H__ //
// - ------------------------------------------------------------------------------------------ - //
