// - ------------------------------------------------------------------------------------------ - //
#ifndef __Game_H__
#define __Game_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Integer.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics.h>
#include <GraphicsDraw.h>
//#include <Sound/SoundPlayer.h>

#include <Geometry/Rect.h>
#include <AdvancedGeometry/2D/Point/PointVsPairRect2D.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Rebel/Sequence.h>
#include <Grid/Grid2D.h>
#include <View/PairView.h>
#include <Data/String.h>

#include <Allocator/Vector2DAllocator.h>
#include <Allocator/UVAllocator.h>
// - ------------------------------------------------------------------------------------------ - //
#include "Room.h"
#include "Layout.h"
// - ------------------------------------------------------------------------------------------ - //
extern void SkipTime();
// - ------------------------------------------------------------------------------------------ - //
#include <Mesh/PMEFile.h>
#include <Mesh/RenderObject.h>
#include <Mesh/RenderObject_Load.h>
#include <Mesh/RenderObjectInstance.h>

// - ------------------------------------------------------------------------------------------ - //
class cGame {
public:
	// - -------------------------------------------------------------------------------------- - //
	//cLayout Layout;
	//std::vector<cRoom> Room;
	
	//cPMEFile Scene;
	
	cPMEFaceGroup Decal;
	Vector2D DecalPos;
	std::vector<cPMEVertex> DecalVertex;
	TextureID HeartTexture;
	
	cRenderObject Object;
	cRenderObjectInstance Instance, Instance2;
	
public:
	// - -------------------------------------------------------------------------------------- - //
	cGame();
	~cGame();

	void Step();
	void Draw();

	// - -------------------------------------------------------------------------------------- - //
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Game_H__ //
// - ------------------------------------------------------------------------------------------ - //
