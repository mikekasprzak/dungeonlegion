// - ------------------------------------------------------------------------------------------ - //
#include "Game.h"
// - ------------------------------------------------------------------------------------------ - //
cGame::cGame() :
	Layout( "Content/Layout.map" ),
	Scene( "Content/meshes/MultiRoom.pme" )
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
//	gfxEnableAlphaBlending();
	
//	glEnable( GL_CULL_FACE );
//	glCullFace( GL_BACK );
	
	glPushMatrix();
	static int a = 0;
	a++;
	glRotatef( a/40.0f, 1, 1, 1 );
	glScalef( 25, 25, 25 );
	glTranslatef( 0, 0, 0 );

	{
		cPMEMesh& Mesh = Scene.Mesh.back();

		gfxEnableDepthTest();
		glDepthFunc( GL_LESS );
		for ( size_t idx = 0; idx < Mesh.FaceGroup.size(); idx++ ) {		
			gfxDrawPrimitive( 
				Mesh.FaceGroup[idx].Face.size()*3,
				
				&Mesh.Vertex[0].Pos, 
				0,
				0,
				&Mesh.Vertex[0].Color, 
				
				&Mesh.FaceGroup[idx].Face[0], 
				
				sizeof( cPMEVertex ),
				PRIMITIVE_DEFAULT | PRIMITIVE_TRIANGLES
				);
		}
//		glDepthFunc( GL_LEQUAL );
//		for ( size_t idx = 0; idx < Mesh.FaceGroup.size(); idx++ ) {		
//			gfxDrawPrimitive( 
//				Mesh.FaceGroup[idx].Face.size()*3,
//				
//				&Mesh.Vertex[0].Pos, 
//				0,
//				0,
//				0,//&Mesh.Vertex[0].Color, 
//				
//				&Mesh.FaceGroup[idx].Face[0], 
//				
//				sizeof( cPMEVertex ),
//				PRIMITIVE_DEFAULT | PRIMITIVE_TRIANGLES
//				);
//		}
		gfxDisableDepthTest();

		
		for ( size_t idx = 0; idx < Mesh.FaceGroup.size(); idx++ ) {		
			gfxDrawPrimitive(
				Mesh.Vertex.size(),
				&Mesh.Vertex[0].Pos, 0, 0, 0, 
				0,
				sizeof( cPMEVertex ),
				PRIMITIVE_DEFAULT | PRIMITIVE_POINTS
				);
		}
	}
		
	glPopMatrix();

	
//	// Game Mode //
//	if ( true ) {
//		//for ( size_t idx = 0; idx < Room.size(); idx++ )
//		for ( size_t idx = 0; idx < Layout.Room.size(); idx++ ) {
//			glPushMatrix();
//			glTranslatef( Layout.Room[idx].Pos.x, Layout.Room[idx].Pos.y, 0 );
//
//			
//			Room[ Layout.Room[idx].Id ].Draw();
//			glPopMatrix();
//		}
//	}
//	// Editor Mode //
//	else {
//		int CurrentRoom = 0;
//		Room[CurrentRoom].Draw();
//	}

}
// - ------------------------------------------------------------------------------------------ - //
