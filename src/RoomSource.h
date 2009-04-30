// - ------------------------------------------------------------------------------------------ - //
#ifndef __RoomSource_H__
#define __RoomSource_H__
// - ------------------------------------------------------------------------------------------ - //
#include <string>
#include <vector>

#include "RoomPolygon.h"
#include "ItemInstance.h"
// - ------------------------------------------------------------------------------------------ - //
class cRoomSource {
public:
	std::string FileName;
public:
	cRoomPolygon Polygon;
	std::vector< cItemInstance > Item;

public:
	// Defaults //
	cRoomSource()
	{
	}
	
	cRoomSource( const char* _FileName ) :
		FileName( _FileName )
	{
		// TODO: Do test to determine input file type (binary or text) //
		TextLoad();	
	}

public:
	void TextLoad();
	void TextSave();
	
	void BinaryLoad();
	void BinarySave();

public:
	void Draw() {
		Polygon.Draw();
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __RoomSource_H__ //
// - ------------------------------------------------------------------------------------------ - //
