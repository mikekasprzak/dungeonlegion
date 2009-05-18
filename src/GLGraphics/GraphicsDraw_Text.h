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
