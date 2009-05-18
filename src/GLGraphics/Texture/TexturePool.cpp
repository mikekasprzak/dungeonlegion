// - ------------------------------------------------------------------------------------------ - //
#ifdef SDL_BUILD
// - ------------------------------------------------------------------------------------------ - //
#include <SDL/SDL.h>
// ---------------------------------------------------------------------------------------------- //
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
// - ------------------------------------------------------------------------------------------ - //
#else // NOT SDL_BUILD //
// - ------------------------------------------------------------------------------------------ - //
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
// - ------------------------------------------------------------------------------------------ - //
#endif // SDL_BUILD //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <Rebel/Log.h>
// - ------------------------------------------------------------------------------------------ - //
#include "TexturePool.h"
// - ------------------------------------------------------------------------------------------ - //
#include <map>
#include <vector>
#include <string>
// - ------------------------------------------------------------------------------------------ - //
#include "Pool_String.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Data/Data.h>
#include <Data/Directory.h>
// - ------------------------------------------------------------------------------------------ - //
#include "FileFormats/PVRTexture_Load.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
namespace TexturePool {
// - ------------------------------------------------------------------------------------------ - //
	class cTextureInfo {
	public:
		// The different levels of texture usability status //
		unsigned int GLTexture;		// Texture is in VRAM //
//		DataBlock* Uncompressed;	// Uncompressed Data Ready to be Transfered //
//		DataBlock* Compressed;		// Compressed Data is Loaded, ready to be decompressed //
		std::string FileName;		// All we have is a filename //
	
		cTextureDetail Detail;
	public:
		cTextureInfo() :
			GLTexture( 0 )
		{
		}
		cTextureInfo( const char* _FileName ) :
			GLTexture( 0 ),
			FileName( _FileName )
		{
		}
		cTextureInfo( std::string _FileName ) :
			GLTexture( 0 ),
			FileName( _FileName )
		{
		}
	};
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Members //
	std::string FilePrefix;	
	std::vector< cTextureInfo > TextureInfo;
	std::map<std::string, TextureID> TextureLookup;
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	void Set( const TextureID Texture ) {
		glBindTexture( GL_TEXTURE_2D, TextureInfo[ Texture ].GLTexture );
	}
	// - -------------------------------------------------------------------------------------- - //
	void Free( const TextureID Texture ) {
		if ( TextureInfo[ Texture ].GLTexture ) {
			glDeleteTextures( 1, &TextureInfo[ Texture ].GLTexture );
			TextureInfo[ Texture ].GLTexture = 0;
		}
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	void Init( const char* BaseDirectory ) {
		// Create a string containing the base filename directory //
		{
			char _FilePrefix[1024];

#ifdef IPHONE_BUILD
			// If an empty string (i.e. first character is terminator) //
			if ( BaseDirectory[0] == 0 )
				sprintf(_FilePrefix,"%s/%s", getenv("HOME"), MY_APP_NAME );
			else
				sprintf(_FilePrefix,"%s/%s/%s", getenv("HOME"), MY_APP_NAME, BaseDirectory );
#else // IPHONE_BUILD //
			sprintf(_FilePrefix,"%s", BaseDirectory );
#endif // IPHONE_BUILD //

			// Store the prefix (without trailing slash.  Slash will be part of search strings) //
			FilePrefix = _FilePrefix;
		}
		
		{
			// Initalize the TextureInfo //
			TextureInfo.clear();
			TextureInfo.push_back( cTextureInfo() );	// Dummy //
			
			// Initalize the TextureLookup //
			TextureLookup.clear();
		}
	}
	// - -------------------------------------------------------------------------------------- - //
	void Exit() {
		for ( size_t idx = 0; idx < TextureInfo.size(); idx++ ) {
			Free( TextureInfo[ idx ].GLTexture );
		}
	}
	// - -------------------------------------------------------------------------------------- - //
	void AddDirectory( const char* Directory ) {
		// TODO: Be sure to include a beginning "/" in the populated filenames //
		// TODO: Be sure to remove file extensions in the search query //
		std::string ReadDir = FilePrefix;
		if ( Directory[0] != 0 ) {
			ReadDir += "/";
			ReadDir += Directory;
		}
		ReadDir += "/";
		
		DIRECTORY* Dir = new_Directory( ReadDir.c_str() );
		
		for( int idx = 0; idx < size_Directory( Dir ); idx++ ) {
			std::string SlashString = "/";
			SlashString += index_Directory( Dir, idx );
			TextureInfo.push_back( cTextureInfo( SlashString ) );
			
			std::string NoExt = NoExtensions( SlashString );
			TextureLookup[ NoExt.c_str() ] = TextureInfo.size() - 1;
			
//			printf( "%s\n", SlashString.c_str() );
//			printf( "%s\n", NoExt.c_str() );
		}
		
		delete_Directory( Dir );
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	TextureID FindID( const char* FileName ) {
		// Search the map for the specific pattern //
		std::map<std::string, TextureID>::iterator SearchIterator = TextureLookup.find( FileName );
		
		// If it was found, return the Id //
		if ( SearchIterator != TextureLookup.end() ) {
//			printf( "- %s found in lookup cache!\n", FileName );
			return SearchIterator->second;
		}

		// Linear pattern matching search (if it contains the pattern, instead of exact match) //
		for ( size_t idx = 0; idx < TextureInfo.size(); idx++ ) {
			// Linear test strings if they contain the pattern passed //
			if ( TextureInfo[idx].FileName.find( FileName ) != std::string::npos ) {
				return idx;
			}
		}
		
		// Otherwise, no file was found.  Return the dummy Id (0). //
		return 0;
	}
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
	void LoadTexture( const TextureID Texture ) {
		// Bail if the dummy texture //
		if ( Texture == 0 )
			return;
		
		// If GL Texture is set, activate it //
		if ( TextureInfo[ Texture ].GLTexture ) {
			Set( Texture );		
			return;
		}
		
		// TODO: If there is uncompressed data, load it in to memory //
		// TODO: If there is compressed data, decompress it, then load in to memory //
		
		// If there is only a filename, load it //
		{
			std::string File = FilePrefix;
			File += TextureInfo[ Texture ].FileName;
			
			Log( "Caching %s...\n", File.c_str() );

			// TODO: Figure out what kind of image this file is //
			TextureInfo[ Texture ].GLTexture = LoadGL_PVRTexture( File.c_str(), &TextureInfo[ Texture ].Detail );
		}
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	TextureID Load( const char* FileName ) {
		TextureID Texture = FindID( FileName );
		
		// Loaded, so cache the texture in memory //
		LoadTexture( Texture );
		
		// Return the Id //
		return Texture;	
	}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace TexturePool //
// - ------------------------------------------------------------------------------------------ - //
