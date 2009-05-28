// - ------------------------------------------------------------------------------------------ - //
#ifndef __GLGraphics_TexturePool_H__
#define __GLGraphics_TexturePool_H__
// - ------------------------------------------------------------------------------------------ - //
#include <TextureID.h>
// - ------------------------------------------------------------------------------------------ - //
namespace TexturePool {
	void Init( const char* BaseDirectory );
	void Exit();
	void AddDirectory( const char* Directory );
	
	TextureID FindID( const char* FileName );
	
	TextureID Load( const char* FileName );
	void Set( const TextureID Texture );
	void Free( const TextureID Texture );
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline TextureID gfxLoadTexture( const char* FileName ) {
	// TODO: Remove file extensions from the search string //
	return TexturePool::Load( FileName );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxSetTexture( const TextureID Texture ) {
	TexturePool::Set( Texture );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxFreeTexture( const TextureID Texture ) {
	TexturePool::Free( Texture );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GLGraphics_TexturePool_H__ //
// - ------------------------------------------------------------------------------------------ - //
