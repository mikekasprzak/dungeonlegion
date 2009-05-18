// - ------------------------------------------------------------------------------------------ - //
#ifndef __RoomPolygon_H__
#define __RoomPolygon_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>

#include <Math/Vector.h>
#include <GraphicsDraw.h>
// - ------------------------------------------------------------------------------------------ - //
class cRoomPolygon {
public:
	std::vector< Vector2D > Vertex;
	
public:
	// Defaults //
	cRoomPolygon()
	{
	}
	
public:
	void Draw() {
		// If there are vertices, draw them //
		if ( Vertex.size() ) {
			Real VertexSize(3);
			Real NormalLength(8);
			
			ColorType VertexColor = RGB_RED;
			ColorType EdgeColor = RGB_WHITE;
			ColorType NormalColor = EdgeColor;

			for ( size_t idx = 0; idx < Vertex.size(); idx++ ) {
				// Points //
				gfxDrawCircleFill( Vertex[idx], VertexSize, VertexColor );
			}
	
			for ( size_t idx = 0; idx < Vertex.size() - 1; idx++ ) {			
				// Edges //
				gfxDrawLine( Vertex[idx], Vertex[idx+1], EdgeColor );
				
				// Normals //
				gfxDrawLineNormal( Vertex[idx], Vertex[idx+1], NormalLength, NormalColor );
			}
			if ( Vertex.size() > 1 ) {
				// Edges //
				gfxDrawLine( Vertex.back(), Vertex[0], EdgeColor );
				
				// Normals //
				gfxDrawLineNormal( Vertex.back(), Vertex[0], NormalLength, NormalColor );			
			}
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __RoomPolygon_H__ //
// - ------------------------------------------------------------------------------------------ - //
