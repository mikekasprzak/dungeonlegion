// - ------------------------------------------------------------------------------------------ - //
#include <fstream>
#include <WhitespaceTokenizer/WhitespaceTokenizer.h>

using namespace std;
// - ------------------------------------------------------------------------------------------ - //
#include "RoomSource.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cRoomSource::TextLoad() {
	// TODO: Support compressed reading //
	cWhitespaceTokenizer File( FileName.c_str() );
	
	do {
		if ( File.IsStringToken( "Polygon" ) ) {
			// Currently only 1 polygon per file //
		}
		else if ( File.IsStringToken( "Vertex" ) ) {
			File.NextToken();
			
			Vector2D Pos;
			Pos.x = File.StepFloatToken();
			Pos.y = File.StepFloatToken();

			Polygon.Vertex.push_back( Pos );
		}
		else {
			printf( "%s (%s): Unknown Command\n", __func__, __FILE__ );
		}
	} while ( File.NextLine() );
}
// - ------------------------------------------------------------------------------------------ - //
void cRoomSource::TextSave() {
	ofstream File( FileName.c_str(), ios::out );
	File << "// Room //" << endl;
	{
		// Currently only 1 polygon per file //
		cRoomPolygon& Poly = Polygon;
	
		File << "Polygon" << endl;
		for ( size_t idx = 0; idx < Poly.Vertex.size(); idx++ ) {
			File << "Vertex " << Poly.Vertex[idx].x << " " << Poly.Vertex[idx].y << endl;
		}
	}
	File << endl;
	
	File << "// Models //" << endl;
	File << endl;

	File << "// Items //" << endl;
	File << endl;

	File << "// Entities //" << endl;
	File << endl;
}
// - ------------------------------------------------------------------------------------------ - //
