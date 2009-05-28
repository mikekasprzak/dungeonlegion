// - ------------------------------------------------------------------------------------------ - //
#ifndef __GLGraphics_RenderObject_H__
#define __GLGraphics_RenderObject_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
#include <string>

#include <Set/UVSet.h>
#include <Set/ABCSet.h>
#include <Math/Vector.h>

#include <Color.h>
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
	typedef ABCSet<int> FaceType;
	
	int MaterialIndex;
	std::vector< FaceType > Face;
};
// - ------------------------------------------------------------------------------------------ - //
class cRenderObject {
public:
	std::vector<cROMaterial> Material;

	std::vector<cROVertex> Vertex;
	std::vector<cROFaceGroup> FaceGroup;
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GLGraphics_RenderObject_H__ //
// - ------------------------------------------------------------------------------------------ - //
