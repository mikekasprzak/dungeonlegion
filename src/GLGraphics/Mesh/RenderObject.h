// - ------------------------------------------------------------------------------------------ - //
#ifndef __GLGraphics_RenderObject_H__
#define __GLGraphics_RenderObject_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Data/Array.h>

#include <Set/UVSet.h>
#include <Set/ABCSet.h>
#include <Math/Vector.h>

#include <UV.h>
#include <Color.h>
#include <TextureID.h>
// - ------------------------------------------------------------------------------------------ - //
class cROMaterial {
public:
	TextureID Texture;
};
// - ------------------------------------------------------------------------------------------ - //
class cROVertex {
public:
	typedef UVSet<UVType> tUVType;
	
	Vector3D Pos;
	Vector3D Normal;
	tUVType UV;
	ColorType Color;
};
// - ------------------------------------------------------------------------------------------ - //
class cROFaceGroup {
public:
	typedef int IndexType;
	
	unsigned short MaterialIndex;
	unsigned short Flags;
	Array<IndexType>* Face;

public:
	inline cROFaceGroup() :
		Face(0)
	{
	}
	
//	inline ~cROFaceGroup() 
	inline void Free() {
		if ( Face )
			delete_Array(Face);
	}
};
// - ------------------------------------------------------------------------------------------ - //
class cRenderObject {
public:
	Array<cROMaterial>* Material;
	Array<cROVertex>* Vertex;
	Array<cROFaceGroup>* FaceGroup;

public:
	inline cRenderObject() :
		Material(0),
		Vertex(0),
		FaceGroup(0)
	{
	}

//	inline ~cRenderObject()
	inline void Free() {
		if ( Material )
			delete_Array(Material);
		if ( Vertex )
			delete_Array(Vertex);
		if ( FaceGroup )
			delete_Array(FaceGroup);
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GLGraphics_RenderObject_H__ //
// - ------------------------------------------------------------------------------------------ - //
