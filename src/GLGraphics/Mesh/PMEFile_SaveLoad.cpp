// - ------------------------------------------------------------------------------------------ - //
#include <fstream>
#include <WhitespaceTokenizer/WhitespaceTokenizer.h>

using namespace std;
// - ------------------------------------------------------------------------------------------ - //
#include <UV.h>
#include "PMEFile.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cPMEFile::TextLoad() {
	// TODO: Support compressed reading //
	cWhitespaceTokenizer File( FileName.c_str() );
	
	do {
		if ( File.IsStringToken( "Mesh" ) ) {
			File.NextToken();
			
			// A mesh found, so add one //
			Mesh.push_back( cPMEMesh() );
			Mesh.back().Name = File.StringToken();
		}
		else if ( File.IsStringToken( "Materials" ) ) {
			// Ignored //
		}
		else if ( File.IsStringToken( "Material" ) ) {
			File.NextToken();
			
			// Ignore "Index" Token //
			File.NextToken();
			
			// Name //
			Mesh.back().Material.push_back( cPMEMaterial() );
			Mesh.back().Material.back().Name = File.StringToken();
		}
		else if ( File.IsStringToken( "Image" ) ) {
			File.NextToken();
			
			Mesh.back().Material.back().ImageFileName = File.StringToken();
		}
		else if ( File.IsStringToken( "Vertices" ) ) {
			// Ignored //
		}
		else if ( File.IsStringToken( "Vertex" ) ) {
			File.NextToken();
			
			Mesh.back().Vertex.push_back( cPMEVertex() );
			Mesh.back().Vertex.back().Pos.x = File.StepFloatToken();
			Mesh.back().Vertex.back().Pos.y = File.StepFloatToken();
			Mesh.back().Vertex.back().Pos.z = File.StepFloatToken();
		}
		else if ( File.IsStringToken( "VertexNorm" ) ) {
			File.NextToken();
			
			Mesh.back().Vertex.push_back( cPMEVertex() );
			Mesh.back().Vertex.back().Pos.x = File.StepFloatToken();
			Mesh.back().Vertex.back().Pos.y = File.StepFloatToken();
			Mesh.back().Vertex.back().Pos.z = File.StepFloatToken();
			Mesh.back().Vertex.back().Normal.x = File.StepFloatToken();
			Mesh.back().Vertex.back().Normal.y = File.StepFloatToken();
			Mesh.back().Vertex.back().Normal.z = File.StepFloatToken();
		}
		else if ( File.IsStringToken( "VertexNormUV" ) ) {
			File.NextToken();
			
			Mesh.back().Vertex.push_back( cPMEVertex() );
			Mesh.back().Vertex.back().Pos.x = File.StepFloatToken();
			Mesh.back().Vertex.back().Pos.y = File.StepFloatToken();
			Mesh.back().Vertex.back().Pos.z = File.StepFloatToken();
			Mesh.back().Vertex.back().Normal.x = File.StepFloatToken();
			Mesh.back().Vertex.back().Normal.y = File.StepFloatToken();
			Mesh.back().Vertex.back().Normal.z = File.StepFloatToken();
			Mesh.back().Vertex.back().UV.u = File.StepFloatToken() * UV_ONE_F;
			Mesh.back().Vertex.back().UV.v = File.StepFloatToken() * UV_ONE_F;
		}
		else if ( File.IsStringToken( "VertexNormUVColor" ) ) {
			File.NextToken();
			
			Mesh.back().Vertex.push_back( cPMEVertex() );
			Mesh.back().Vertex.back().Pos.x = File.StepFloatToken();
			Mesh.back().Vertex.back().Pos.y = File.StepFloatToken();
			Mesh.back().Vertex.back().Pos.z = File.StepFloatToken();
			Mesh.back().Vertex.back().Normal.x = File.StepFloatToken();
			Mesh.back().Vertex.back().Normal.y = File.StepFloatToken();
			Mesh.back().Vertex.back().Normal.z = File.StepFloatToken();
			Mesh.back().Vertex.back().UV.u = File.StepFloatToken() * UV_ONE_F;
			Mesh.back().Vertex.back().UV.v = File.StepFloatToken() * UV_ONE_F;
			int r = File.StepIntegerToken();
			int g = File.StepIntegerToken();
			int b = File.StepIntegerToken();
			int a = File.StepIntegerToken();
			Mesh.back().Vertex.back().Color = RGBA(r,g,b,a);
		}
		else if ( File.IsStringToken( "VertexNormColor" ) ) {
			File.NextToken();
			
			Mesh.back().Vertex.push_back( cPMEVertex() );
			Mesh.back().Vertex.back().Pos.x = File.StepFloatToken();
			Mesh.back().Vertex.back().Pos.y = File.StepFloatToken();
			Mesh.back().Vertex.back().Pos.z = File.StepFloatToken();
			Mesh.back().Vertex.back().Normal.x = File.StepFloatToken();
			Mesh.back().Vertex.back().Normal.y = File.StepFloatToken();
			Mesh.back().Vertex.back().Normal.z = File.StepFloatToken();
			int r = File.StepIntegerToken();
			int g = File.StepIntegerToken();
			int b = File.StepIntegerToken();
			int a = File.StepIntegerToken();
			Mesh.back().Vertex.back().Color = RGBA(r,g,b,a);
		}
		else if ( File.IsStringToken( "VertexUV" ) ) {
			File.NextToken();
			
			Mesh.back().Vertex.push_back( cPMEVertex() );
			Mesh.back().Vertex.back().Pos.x = File.StepFloatToken();
			Mesh.back().Vertex.back().Pos.y = File.StepFloatToken();
			Mesh.back().Vertex.back().Pos.z = File.StepFloatToken();
			Mesh.back().Vertex.back().UV.u = File.StepFloatToken() * UV_ONE_F;
			Mesh.back().Vertex.back().UV.v = File.StepFloatToken() * UV_ONE_F;
		}
		else if ( File.IsStringToken( "VertexUVColor" ) ) {
			File.NextToken();
			
			Mesh.back().Vertex.push_back( cPMEVertex() );
			Mesh.back().Vertex.back().Pos.x = File.StepFloatToken();
			Mesh.back().Vertex.back().Pos.y = File.StepFloatToken();
			Mesh.back().Vertex.back().Pos.z = File.StepFloatToken();
			Mesh.back().Vertex.back().UV.u = File.StepFloatToken() * UV_ONE_F;
			Mesh.back().Vertex.back().UV.v = File.StepFloatToken() * UV_ONE_F;
			int r = File.StepIntegerToken();
			int g = File.StepIntegerToken();
			int b = File.StepIntegerToken();
			int a = File.StepIntegerToken();
			Mesh.back().Vertex.back().Color = RGBA(r,g,b,a);
		}
		else if ( File.IsStringToken( "VertexColor" ) ) {
			File.NextToken();
			
			Mesh.back().Vertex.push_back( cPMEVertex() );
			Mesh.back().Vertex.back().Pos.x = File.StepFloatToken();
			Mesh.back().Vertex.back().Pos.y = File.StepFloatToken();
			Mesh.back().Vertex.back().Pos.z = File.StepFloatToken();
			int r = File.StepIntegerToken();
			int g = File.StepIntegerToken();
			int b = File.StepIntegerToken();
			int a = File.StepIntegerToken();
			Mesh.back().Vertex.back().Color = RGBA(r,g,b,a);
		}
		else if ( File.IsStringToken( "Faces" ) ) {
			// Ignored //
		}
		else if ( File.IsStringToken( "FaceGroup" ) ) {
			File.NextToken();
			
			Mesh.back().FaceGroup.push_back( cPMEFaceGroup() );
		}
		else if ( File.IsStringToken( "UseMaterial" ) ) {
			File.NextToken();
			
			Mesh.back().FaceGroup.back().Material = File.IntegerToken();
		}
		else if ( File.IsStringToken( "Face" ) ) {
			File.NextToken();
			
			Mesh.back().FaceGroup.back().Face.push_back( cPMEFaceGroup::FaceType() );
			Mesh.back().FaceGroup.back().Face.back().a = File.StepIntegerToken();
			Mesh.back().FaceGroup.back().Face.back().b = File.StepIntegerToken();
			Mesh.back().FaceGroup.back().Face.back().c = File.StepIntegerToken();
		}
		else if ( File.IsStringToken( "Properties" ) ) {
			// Ignored //
		}
		else if ( File.IsStringToken( "Property" ) ) {
			// TODO: Property decoding and noting //
		}
		else {
			printf( "%s (%s): Unknown Command\n", __func__, __FILE__ );
		}
	} while ( File.NextLine() );
}
// - ------------------------------------------------------------------------------------------ - //
void cPMEFile::TextSave() {
}
// - ------------------------------------------------------------------------------------------ - //
