// - ------------------------------------------------------------------------------------------ - //
#ifndef __ItemInstance_H__
#define __ItemInstance_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Real.h>
#include <Math/Vector.h>
// - ------------------------------------------------------------------------------------------ - //
class cItemInstance {
public:
	// TODO: Add some way of referencing an item //
	int ItemId;
	
	Vector2D Pos;
	Real Radius;
	
public:
	// Defaults //
	cItemInstance()
	{
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __ItemInstance_H__ //
// - ------------------------------------------------------------------------------------------ - //
