// - ------------------------------------------------------------------------------------------ - //
#include "Game.h"
// - ------------------------------------------------------------------------------------------ - //
cGame::cGame() :
	Layout( "Content/Layout.map" ),
	Scene( "Content/meshes/BorkenBox.pme" )
{	
	// Add Rooms //
	Room.push_back( cRoom( "Content/rooms/0001.room" ) );
	Room.push_back( cRoom( "Content/rooms/0002.room" ) );


//	Room.push_back( cRoom() );
//	Room.back().FileName = "Content/rooms/0002.room";
//	//Room.back().Polygon.Vertex.push_back( Vector2D( 200, 100 ) );
//	Room.back().TextSave();
}
// - ------------------------------------------------------------------------------------------ - //
cGame::~cGame() {
	
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cGame::Step() {

}
// - ------------------------------------------------------------------------------------------ - //
void cGame::Draw() {
	gfxClearBuffer( RGB(44,22,0) );
	gfxEnableAlphaBlending();

	// Game Mode //
	if ( true ) {
		//for ( size_t idx = 0; idx < Room.size(); idx++ )
		for ( size_t idx = 0; idx < Layout.Room.size(); idx++ ) {
			glPushMatrix();
			glTranslatef( Layout.Room[idx].Pos.x, Layout.Room[idx].Pos.y, 0 );
			
			Room[ Layout.Room[idx].Id ].Draw();
			glPopMatrix();
		}
	}
	// Editor Mode //
	else {
		int CurrentRoom = 0;
		Room[CurrentRoom].Draw();
	}

}
// - ------------------------------------------------------------------------------------------ - //
