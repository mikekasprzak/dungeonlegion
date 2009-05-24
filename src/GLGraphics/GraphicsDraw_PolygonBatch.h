// - ------------------------------------------------------------------------------------------ - //
#ifndef __GLGraphics_PolygonBatch_H__
#define __GLGraphics_PolygonBatch_H__
// - ------------------------------------------------------------------------------------------ - //
// Polygon Batch is a function and class for drawing vertex arrays.  //
// Texturing and specific textures must be enabled/set before calling the batch Drawing functions //
// - ------------------------------------------------------------------------------------------ - //
#include <Rebel/Binary.h>
// - ------------------------------------------------------------------------------------------ - //
#define POLYBATCH_2D				b00000001
#define POLYBATCH_3D				b00000010

#define POLYBATCH_UV_8BIT			b00000100
#define POLYBATCH_UV_16BIT			b00001000
#define POLYBATCH_UV_32BIT			b00001100
#define POLYBATCH_UV_FLOAT			b00010000
#define POLYBATCH_UV_HALFFLOAT		b00010100
//#define POLYBATCH_UV_FIXED			b00011000
#define POLYBATCH_UV_SYSTEM			b00111100

#define POLYBATCH_INDEX_8BIT		b01000000
#define POLYBATCH_INDEX_16BIT		b10000000
#define POLYBATCH_INDEX_32BIT		b11000000

#define POLYBATCH_VERTEX_8BIT		((b00000001)<<8)
#define POLYBATCH_VERTEX_16BIT		((b00000010)<<8)
#define POLYBATCH_VERTEX_32BIT		((b00000011)<<8)
#define POLYBATCH_VERTEX_FLOAT		((b00000100)<<8)
#define POLYBATCH_VERTEX_HALFFLOAT	((b00000101)<<8)
//#define POLYBATCH_VERTEX_FIXED		((b00000110)<<8)
#define POLYBATCH_VERTEX_SYSTEM		((b00001111)<<8)

#define POLYBATCH_NORMAL_8BIT		((b00010000)<<8)
#define POLYBATCH_NORMAL_16BIT		((b00100000)<<8)
#define POLYBATCH_NORMAL_32BIT		((b00110000)<<8)
#define POLYBATCH_NORMAL_FLOAT		((b01000000)<<8)
#define POLYBATCH_NORMAL_HALFFLOAT	((b01010000)<<8)
//#define POLYBATCH_NORMAL_FIXED		((b01100000)<<8)
#define POLYBATCH_NORMAL_SYSTEM		((b11110000)<<8)

#define POLYBATCH_POINTS			((b00010000)<<24)	// Not Supported by DS //
#define POLYBATCH_LINES				((b00100000)<<24)	// Not Supported by DS //
#define POLYBATCH_LINE_STRIP		((b00110000)<<24)	// Not Supported by PS1, DS //
#define POLYBATCH_LINE_LOOP			((b01000000)<<24)	// Not Supported by PS1, PS2, Cube, DS, Xbox, DirectX //
#define POLYBATCH_TRIANGLES			((b01010000)<<24)
#define POLYBATCH_TRIANGLE_STRIP	((b01100000)<<24)
#define POLYBATCH_TRIANGLE_FAN		((b01110000)<<24)	// Not Supported by PS1, DS //
#define POLYBATCH_QUADS				((b10000000)<<24)	// Not Supported by GL ES, PS2, DirectX //
#define POLYBATCH_QUAD_STRIP		((b10010000)<<24)	// Not Supported by GL ES, PS1, PS2, DirectX, Cube //
#define POLYBATCH_SPRITE			((b11000000)<<24)	// Only Supported by PS1, PS2 //
#define POLYBATCH_POLYGON			((b11010000)<<24)	// Only Supported by GL, Xbox //
// - ------------------------------------------------------------------------------------------ - //
#define POLYBATCH_DEFAULT		(POLYBATCH_3D|POLYBATCH_UV_SYSTEM|POLYBATCH_INDEX_32BIT|POLYBATCH_TRIANGLES)
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gfxDrawPolygonBatch( 
	const size_t Count,
	const void* Vertex, const void* Normal = 0, const void* UV = 0, const void* Color = 0,
	const void* Index = 0, const int Stride = 0, const unsigned Flags = POLYBATCH_DEFAULT
	)
{
	int VertexDimensions = 0;
	if ( Flags & POLYBATCH_2D )
		VertexDimensions = 2;
	else if ( Flags & POLYBATCH_3D )
		VertexDimensions = 3;
	else
		return;
	
	if ( Vertex ) {
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(VertexDimensions, GL_FLOAT, Stride, Vertex);
	}
	else {
		return;
	}
		
	if ( Normal ) {
		glEnableClientState(GL_NORMAL_ARRAY);
		glVertexPointer(VertexDimensions, GL_FLOAT, Stride, Normal);
	}
	else {
		glDisableClientState(GL_NORMAL_ARRAY);		
	}
	
	if ( UV ) {
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		if ( Flags & POLYBATCH_UV_SYSTEM )
			glTexCoordPointer(2, GL_UVType, Stride, UV);
		else if ( Flags & POLYBATCH_UV_8BIT )
			glTexCoordPointer(2, GL_BYTE, Stride, UV);
		else if ( Flags & POLYBATCH_UV_16BIT )
			glTexCoordPointer(2, GL_SHORT, Stride, UV);
		else if ( Flags & POLYBATCH_UV_32BIT )
			glTexCoordPointer(2, GL_INT, Stride, UV);
		else if ( Flags & POLYBATCH_UV_FLOAT )
			glTexCoordPointer(2, GL_FLOAT, Stride, UV);
		else
			return;

		//glEnable(GL_TEXTURE_2D);
	}
	else {
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
	
	if ( Color ) {
		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(4, GL_UNSIGNED_BYTE, Stride, Color);
	}
	else {
		glDisableClientState(GL_COLOR_ARRAY);
	}

	int RenderMode = 0;
	if ( Flags & POLYBATCH_POINTS )
		RenderMode = GL_POINTS;
	else if ( Flags & POLYBATCH_LINES )
		RenderMode = GL_LINES;
	else if ( Flags & POLYBATCH_LINE_STRIP )
		RenderMode = GL_LINE_STRIP;
	else if ( Flags & POLYBATCH_LINE_LOOP )
		RenderMode = GL_LINE_LOOP;
	else if ( Flags & POLYBATCH_TRIANGLES )
		RenderMode = GL_TRIANGLES;
	else if ( Flags & POLYBATCH_TRIANGLE_STRIP )
		RenderMode = GL_TRIANGLE_STRIP;
	else if ( Flags & POLYBATCH_TRIANGLE_FAN )
		RenderMode = GL_TRIANGLE_FAN;
	else
		return;
		
	if ( Index ) {
		int IndexFormat = 0;
		if ( Flags & POLYBATCH_INDEX_8BIT )
			IndexFormat = GL_UNSIGNED_BYTE;
		else if ( Flags & POLYBATCH_INDEX_16BIT )
			IndexFormat = GL_UNSIGNED_SHORT;
		else if ( Flags & POLYBATCH_INDEX_32BIT )
			IndexFormat = GL_UNSIGNED_INT;
		else
			return;

		glDrawElements(RenderMode, Count, IndexFormat, Index);
	}
	else {
		glDrawArrays(RenderMode, 0, Count);
	}
	
//	if ( UV ) {
//		glDisable(GL_TEXTURE_2D);
//	}

	gfxApplyColor( CurrentColor );
}
// - ------------------------------------------------------------------------------------------ - //
class cPolygonBatch {
public:
	// If there's Indexes, then this is an index count.  Otherwise it's a vert count. //
	size_t Count;
	
	const void* Vertex;
	const void* Normal;
	const void* UV;
	const void* Color;

	const void* Index;
	
	int Stride;
	
	unsigned Flags; // 2D versus 3D?, 16bit versus 32bit Indexes?, "shorts" for UVs? //
public:
	cPolygonBatch( 
		const size_t _Count = 0,
		const void* _Vertex = 0, const void* _Normal = 0, const void* _UV = 0, const void* _Color = 0,
		const void* _Index = 0, const int _Stride = 0, const unsigned _Flags = POLYBATCH_DEFAULT
		) :
		Count( _Count ),
		Vertex( _Vertex ),
		Normal( _Normal ),
		UV( _UV ),
		Color( _Color ),
		Index( _Index ),
		Stride( _Stride ),
		Flags( _Flags )
	{
	}
	
	inline void Draw() {
		gfxDrawPolygonBatch( Count, Vertex, Normal, UV, Color, Index, Stride, Flags );
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GLGraphics_PolygonBatch_H__ //
// - ------------------------------------------------------------------------------------------ - //
