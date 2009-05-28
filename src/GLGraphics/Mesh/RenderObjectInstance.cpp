// - ------------------------------------------------------------------------------------------ - //
#include <GraphicsDraw.h>
#include "RenderObjectInstance.h"

#include <Texture/TexturePool.h>
// - ------------------------------------------------------------------------------------------ - //
cRenderObjectInstance Instantiate( const cRenderObject& Object ) {
	cRenderObjectInstance Instance;
	
	Instance.Object = &Object;
	Instance.Matrix = Matrix4x4::Identity;
		
	// Allocate Rect //
	Instance.FaceGroup = new_Array<cROIFaceGroup>(Instance.Object->FaceGroup->Size);
	Instance.CalculateRect();
	Instance.CalculateFaceGroupRects();
	
	// Software Lighting //
	{
		Instance.Vertex.Color.resize( Object.Vertex->Size );
	}
	
	return Instance;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cRenderObjectInstance::CalculateFaceGroupRect( const size_t Index ) {
}
// - ------------------------------------------------------------------------------------------ - //
void cRenderObjectInstance::CalculateFaceGroupRects() {
	if ( Object ) {
		for ( size_t FG = 0; FG < Object->FaceGroup->Size; FG++ ) {
			Vector3D Point = Object->Vertex->Data[ Object->FaceGroup->Data[FG].Face->Data[0] ].Pos;
			Point = Point.ApplyMatrix( Matrix );
			
			FaceGroup->Data[FG].Rect = PairRect3D( Point, Vector3D::Zero );
			for ( size_t idx = 1; idx < Object->FaceGroup->Data[FG].Face->Size; idx++ ) {
				Point = Object->Vertex->Data[ Object->FaceGroup->Data[FG].Face->Data[idx] ].Pos;
				Point = Point.ApplyMatrix( Matrix );
	
				FaceGroup->Data[FG].Rect.IncludePoint( Point );
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cRenderObjectInstance::CalculateRect() {
	if ( Object ) {
		Vector3D Point = Object->Vertex->Data[0].Pos;
		Point = Point.ApplyMatrix( Matrix );
		
		Rect = PairRect3D( Point, Vector3D::Zero );
		for ( size_t idx = 1; idx < Object->Vertex->Size; idx++ ) {
			Point = Object->Vertex->Data[idx].Pos;
			Point = Point.ApplyMatrix( Matrix );

			Rect.IncludePoint( Point );
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cRenderObjectInstance::_DrawFaceGroup( const size_t Index ) {
	glEnable(GL_TEXTURE_2D);
	//gfxEnableAlphaBlending();
	gfxSetTexture( Object->Material->Data[ Object->FaceGroup->Data[Index].MaterialIndex ].Texture );
	gfxSetSmoothTexturesMipMapped();
	
	
	cPrimitive Primitive;
	Primitive.Count = Object->FaceGroup->Data[Index].Face->Size;
	Primitive.Vertex = &Object->Vertex->Data[0].Pos;
	Primitive.Normal = &Object->Vertex->Data[0].Normal;
	Primitive.UV = &Object->Vertex->Data[0].UV;
	//Primitive.Color = &Object->Vertex->Data[0].Color;
	
	Primitive.Index = &Object->FaceGroup->Data[Index].Face->Data[0];
	Primitive.Stride = sizeof( cROVertex );
	Primitive.Flags = PRIMITIVE_DEFAULT | PRIMITIVE_TRIANGLES;
	
	Primitive.Draw();


	glDisable(GL_TEXTURE_2D);
}
// - ------------------------------------------------------------------------------------------ - //
void cRenderObjectInstance::DrawFaceGroup( const size_t Index ) {
	glPushMatrix();
	glMultMatrixf( (const float*)&Matrix );

	_DrawFaceGroup( Index );

	glPopMatrix();
}
// - ------------------------------------------------------------------------------------------ - //
void cRenderObjectInstance::Draw() {
	gfxDrawRect( Rect.P1(), Rect.P2(), RGB_WHITE );
	
//	gfxDrawCircleFill( Rect.P1(), Real(0.5), RGB_YELLOW );
//	gfxDrawCircleFill( Rect.P2(), Real(0.5), RGB_YELLOW );
	
	glPushMatrix();
	glMultMatrixf( (const float*)&Matrix );
	
	for ( size_t idx = 0; idx < Object->FaceGroup->Size; idx++ ) {
		_DrawFaceGroup( idx );
	}
	
	glPopMatrix();
}
// - ------------------------------------------------------------------------------------------ - //
