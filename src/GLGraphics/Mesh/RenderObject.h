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
};
// - ------------------------------------------------------------------------------------------ - //
class cRenderObject {
public:
	Array<cROMaterial>* Material;
	Array<cROVertex>* Vertex;
	Array<cROFaceGroup>* FaceGroup;
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GLGraphics_RenderObject_H__ //
// - ------------------------------------------------------------------------------------------ - //
