// - ------------------------------------------------------------------------------------------ - //
#include <GraphicsDraw.h>
#include "RenderObjectInstance.h"

//#include <Texture/TexturePool.h>
// - ------------------------------------------------------------------------------------------ - //
cRenderObjectInstance Instantiate( const cRenderObject& Object ) {
	cRenderObjectInstance Instance;
	
	Instance.Object = &Object;
	Instance.Matrix = Matrix4x4::Identity;
		
	// Calculate Rect //
	
	// Software Lighting //
	{
		Instance.Vertex.Color.resize( Object.Vertex->Size );
	}
	
	return Instance;
}
// - ------------------------------------------------------------------------------------------ - //
void cRenderObjectInstance::DrawFaceGroup( const size_t Index ) {
	glPushMatrix();
	glMultMatrixf( (const float*)&Matrix );
	_DrawFaceGroup( Index );
	glPopMatrix();
}
// - ------------------------------------------------------------------------------------------ - //
void cRenderObjectInstance::_DrawFaceGroup( const size_t Index ) {
	gfxDrawPrimitive( 
		Object->FaceGroup->Data[Index].Face->Size,
		
		&Object->Vertex->Data[0].Pos, 
		0,
		0,
		&Object->Vertex->Data[0].Color, 
		
		&Object->FaceGroup->Data[Index].Face->Data[0], 
		
		sizeof( cROVertex ),
		PRIMITIVE_DEFAULT | PRIMITIVE_TRIANGLES
		);
}
// - ------------------------------------------------------------------------------------------ - //
void cRenderObjectInstance::Draw() {
	glPushMatrix();
	glMultMatrixf( (const float*)&Matrix );
	
	for ( size_t idx = 0; idx < Object->FaceGroup->Size; idx++ ) {
		_DrawFaceGroup( idx );
	}
	
	glPopMatrix();
}
// - ------------------------------------------------------------------------------------------ - //
