// - ------------------------------------------------------------------------------------------ - //
#include "Game.h"
#include <Geometry/Rect.h>
// - ------------------------------------------------------------------------------------------ - //
cGame::cGame() :
//	Layout( "Content/Layout.map" ),
//	Scene( "Content/meshes/MultiRoom.pme" ),
	DecalPos( 0, 0 )
{	
	// Add Rooms //
//	Room.push_back( cRoom( "Content/rooms/0001.room" ) );
//	Room.push_back( cRoom( "Content/rooms/0002.room" ) );

	{
		cPMEFile PME( "Content/meshes/MultiRoom.pme" );
		Object = LoadPME( PME );
		Instance = Instantiate( Object );
		Instance2 = Instantiate( Object );
	}
	
//	cPMEMesh& Mesh = Scene.Mesh.back();
//	DecalVertex = Mesh.Vertex;

	HeartTexture = gfxLoadTexture( "/Heart" );
}
// - ------------------------------------------------------------------------------------------ - //
cGame::~cGame() {
	Object.Free();
	Instance.Free();
	Instance2.Free();
}
// - ------------------------------------------------------------------------------------------ - //
int Tweak;
// - ------------------------------------------------------------------------------------------ - //
void cGame::Step() {
	// Test using 2D Shapes //
	PairRect2D DecalVolume( -4,-4, 8,8 );
	
	DecalPos += Vector2D( System::StickX, System::StickY ) * Real(0.1f);
	Tweak++;
	
/*
	cPMEMesh& Mesh = Scene.Mesh.back();
	Decal.Face.clear();
	
	// Determine what faces lie within Volume //
	for ( size_t Group = 0; Group < Mesh.FaceGroup.size(); Group++ ) {
		cPMEFaceGroup& FaceGroup = Mesh.FaceGroup[Group];
		for ( size_t idx = 0; idx < FaceGroup.Face.size(); idx++ ) {
			PairRect2D TriangleVolume( 
				Mesh.Vertex[ FaceGroup.Face[idx].a ].Pos.ToVector2D() - DecalPos, 
				Vector2D::Zero
				);
			TriangleVolume.IncludePoint( Mesh.Vertex[ FaceGroup.Face[idx].b ].Pos.ToVector2D() - DecalPos );
			TriangleVolume.IncludePoint( Mesh.Vertex[ FaceGroup.Face[idx].c ].Pos.ToVector2D() - DecalPos );
			
			if ( DecalVolume == TriangleVolume ) {
				Decal.Face.push_back( FaceGroup.Face[idx] );
			}
		}
	}

	// Calculate UVs //
	for ( size_t idx = 0; idx < Decal.Face.size(); idx++ ) {
		Vector2D Across = DecalVolume.P2() - DecalVolume.P1();

		{
			size_t Index = Decal.Face[idx].a;
			Vector2D a = Mesh.Vertex[ Index ].Pos.ToVector2D() - DecalPos;
			DecalVertex[ Index ].UV.u = ((a.x - DecalVolume.P1().x) / Across.x) * Real(UV_ONE);
			DecalVertex[ Index ].UV.v = ((a.y - DecalVolume.P1().y) / Across.y) * Real(UV_ONE);
		}

		{
			size_t Index = Decal.Face[idx].b;
			Vector2D a = Mesh.Vertex[ Index ].Pos.ToVector2D() - DecalPos;
			DecalVertex[ Index ].UV.u = ((a.x - DecalVolume.P1().x) / Across.x) * Real(UV_ONE);
			DecalVertex[ Index ].UV.v = ((a.y - DecalVolume.P1().y) / Across.y) * Real(UV_ONE);
		}

		{
			size_t Index = Decal.Face[idx].c;
			Vector2D a = Mesh.Vertex[ Index ].Pos.ToVector2D() - DecalPos;
			DecalVertex[ Index ].UV.u = ((a.x - DecalVolume.P1().x) / Across.x) * Real(UV_ONE);
			DecalVertex[ Index ].UV.v = ((a.y - DecalVolume.P1().y) / Across.y) * Real(UV_ONE);
		}
	}
*/	
}
// - ------------------------------------------------------------------------------------------ - //
void cGame::Draw() {
	gfxClearBuffer( RGB(44,22,0) );
//	gfxEnableAlphaBlending();
	
//	glEnable( GL_CULL_FACE );
//	glCullFace( GL_BACK );
	
	glPushMatrix();
	//glRotatef( Tweak, 1, 1, 1 );
	//glScalef( 25, 25, 25 );
	glScalef( 15, 15, 15 );
	glTranslatef( 0, 0, 0 );

	Real Slide = Real::Sin(Tweak * Real(0.002)) * Real(8);

	Instance.Matrix(0,3) = Real(-10) + Slide;
	Instance.CalculateRect();
	//Instance.CalculateFaceGroupRects();

	Instance2.Matrix(0,0) = Real::Zero;
	Instance2.Matrix(0,1) = Real::One;
	Instance2.Matrix(1,0) = -Real::One;
	Instance2.Matrix(1,1) = Real::Zero;

	Instance2.Matrix(0,3) = Real(10) + Slide;
	Instance2.Matrix(1,3) = -Real(2);
	Instance2.CalculateRect();
	
	{
//		cPMEMesh& Mesh = Scene.Mesh.back();

		gfxEnableDepthTest();
		glDepthFunc( GL_LESS );
//		for ( size_t idx = 0; idx < Mesh.FaceGroup.size(); idx++ ) {
//			gfxDrawPrimitive( 
//				Mesh.FaceGroup[idx].Face.size()*3,
//				
//				&Mesh.Vertex[0].Pos, 
//				0,
//				0,
//				&Mesh.Vertex[0].Color, 
//				
//				&Mesh.FaceGroup[idx].Face[0], 
//				
//				sizeof( cPMEVertex ),
//				PRIMITIVE_DEFAULT | PRIMITIVE_TRIANGLES
//				);
//		}

		Instance.Draw();
		Instance2.Draw();

//		for ( size_t idx = 0; idx < Object.FaceGroup->Size; idx++ ) {
//			gfxDrawPrimitive( 
//				Object.FaceGroup->Data[idx].Face->Size,
//				
//				&Object.Vertex->Data[0].Pos, 
//				0,
//				0,
//				&Object.Vertex->Data[0].Color, 
//				
//				&Object.FaceGroup->Data[idx].Face->Data[0], 
//				
//				sizeof( cROVertex ),
//				PRIMITIVE_DEFAULT | PRIMITIVE_TRIANGLES
//				);
//		}
		
//		glEnable(GL_TEXTURE_2D);
//		gfxEnableAlphaBlending();
//		gfxSetTexture( HeartTexture );
//		gfxSetSmoothTexturesMipMapped();
//		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
//		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
//		
//		// Draw Decal //
//		glDepthFunc( GL_LEQUAL );
//		for ( size_t idx = 0; idx < Mesh.FaceGroup.size(); idx++ ) {
//			gfxDrawPrimitive( 
//				Decal.Face.size()*3,
//				
//				&Mesh.Vertex[0].Pos, 
//				0,
//				&DecalVertex[0].UV,
//				0,//&Mesh.Vertex[0].Color, 
//				
//				&Decal.Face[0],
//				
//				sizeof( cPMEVertex ),
//				PRIMITIVE_DEFAULT | PRIMITIVE_TRIANGLES
//				);
//		}
//		
//		gfxDisableDepthTest();
//		gfxDisableBlending();
//		glDisable(GL_TEXTURE_2D);

		
//		for ( size_t idx = 0; idx < Mesh.FaceGroup.size(); idx++ ) {		
//			gfxDrawPrimitive(
//				Mesh.Vertex.size(),
//				&Mesh.Vertex[0].Pos, 0, 0, 0, 
//				0,
//				sizeof( cPMEVertex ),
//				PRIMITIVE_DEFAULT | PRIMITIVE_POINTS
//				);
//		}
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
