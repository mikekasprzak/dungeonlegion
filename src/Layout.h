// - ------------------------------------------------------------------------------------------ - //
#ifndef __Layout_H__
#define __Layout_H__
// - ------------------------------------------------------------------------------------------ - //
#include <string>
#include <vector>

#include "RoomInstance.h"
// - ------------------------------------------------------------------------------------------ - //
class cLayout {
public:
	std::string FileName;
public:
	std::vector< cRoomInstance > Room;

public:
	// Defaults //
	cLayout()
	{
	}
	
	cLayout( const char* _FileName ) :
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
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Layout_H__ //
// - ------------------------------------------------------------------------------------------ - //
