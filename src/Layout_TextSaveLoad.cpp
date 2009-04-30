// - ------------------------------------------------------------------------------------------ - //
#include <fstream>
#include <WhitespaceTokenizer/WhitespaceTokenizer.h>

using namespace std;
// - ------------------------------------------------------------------------------------------ - //
#include "Layout.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cLayout::TextLoad() {
	// TODO: Support compressed reading //
	cWhitespaceTokenizer File( FileName.c_str() );
	
	do {
		if ( File.IsStringToken( "Room" ) ) {
			File.NextToken();
			// TODO: Skip token for now... eventually use this token (string) to lookup the room //
			File.NextToken();
			
			int RoomId = Room.size();
			
			Vector2D Pos;
			Pos.x = File.StepFloatToken();
			Pos.y = File.StepFloatToken();
			
			Room.push_back( cRoomInstance( RoomId, Pos ) );
		}
		else {
			printf( "%s (%s): Unknown Command\n", __func__, __FILE__ );
		}
	} while ( File.NextLine() );	
}
// - ------------------------------------------------------------------------------------------ - //
void cLayout::TextSave() {
	ofstream File( FileName.c_str(), ios::out );
	File << "// Room Layout //" << endl;
	{
		for ( size_t idx = 0; idx < Room.size(); idx++ ) {
			File << "Room \"\" " << Room[idx].Pos.x << " " << Room[idx].Pos.y << endl;
		}
	}
	File << endl;
}
// - ------------------------------------------------------------------------------------------ - //
