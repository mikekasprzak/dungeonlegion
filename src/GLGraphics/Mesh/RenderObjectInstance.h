// - ------------------------------------------------------------------------------------------ - //
#ifndef __GLGraphics_RenderObjectInstance_H__
#define __GLGraphics_RenderObjectInstance_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>

// - ------------------------------------------------------------------------------------------ - //
#include <Data/Array.h>

#include <Math/Vector.h>
#include <Math/Matrix.h>
#include <Geometry/Rect.h>

#include <Color.h>
// - ------------------------------------------------------------------------------------------ - //
#include "RenderObject.h"
// - ------------------------------------------------------------------------------------------ - //
class cROIMaterial {
public:
	cROMaterial* Material;
};
// - ------------------------------------------------------------------------------------------ - //
class cROIVertex {
public:
	// VBO
	
	cROVertex* Vertex;
	
	// Computed Colors - Software Vertex Lighting Only //
	std::vector<ColorType> Color;
};
// - ------------------------------------------------------------------------------------------ - //
class cROIFaceGroup {
public:
	Rect3D Rect;
	
	cROFaceGroup* FaceGroup;
};
// - ------------------------------------------------------------------------------------------ - //
class cRenderObjectInstance {
public:
	Matrix3x3 Matrix;
	Vector3D Position;
	
	Rect3D Rect;
	
	cROIMaterial Material;
	cROIVertex Vertex;
	Array<cROIFaceGroup>* FaceGroup;
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GLGraphics_RenderObjectInstance_H__ //
// - ------------------------------------------------------------------------------------------ - //
