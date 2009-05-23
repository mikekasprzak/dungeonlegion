// - ------------------------------------------------------------------------------------------ - //
#ifndef __GLGraphics_PMEFile_H__
#define __GLGraphics_PMEFile_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
#include <string>

#include <Set/UVSet.h>
#include <Set/ABCSet.h>
#include <Math/Vector.h>

#include <Color.h>
// - ------------------------------------------------------------------------------------------ - //
class cPMEMaterial {
public:
	// Material Name //
	std::string Name;
	
	// Image FileName of our material - TODO: Array //
	std::string ImageFileName;
};
// - ------------------------------------------------------------------------------------------ - //
class cPMEVertex {
public:
	Vector3D Pos;
	Vector3D Normal;
	UVSet<short> UV;
	ColorType Color;
};
// - ------------------------------------------------------------------------------------------ - //
class cPMEFaceGroup {
public:
	typedef ABCSet<int> FaceType;
	
	int Material;
	std::vector< FaceType > Face;
};
// - ------------------------------------------------------------------------------------------ - //
class cPMEMesh {
public:
	// Mesh Name //
	std::string Name;
	
	// Materials //
	std::vector<cPMEMaterial> Material;

	std::vector<cPMEVertex> Vertex;
	std::vector<cPMEFaceGroup> FaceGroup;
};
// - ------------------------------------------------------------------------------------------ - //
class cPMEFile {
public:
	std::string FileName;

	std::vector<cPMEMesh> Mesh;
public:
	cPMEFile()
	{
	}
	
	cPMEFile( const char* _FileName ) :
		FileName( _FileName )
	{
		TextLoad();
	}

public:	
	void TextLoad();
	void TextSave();
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GLGraphics_PMEFile_H__ //
// - ------------------------------------------------------------------------------------------ - //
