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
#include "PVRTexture.h"
#include "PVRTexture_Load.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Data/DataBlock.h>
#include <Data/DataBlock_LZMA.h>
//#include <Data/DataBlock_ZLIB.h>
//#include <Data/DataBlock_BZIP.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
unsigned int LoadGL_PVRTexture( PVRTexture* Texture, cTextureDetail* Detail ) {
	// Texture ID we'll be returning //
	unsigned int TextureID;

	// Generate a GL Texture //
	glGenTextures( 1, &TextureID );
	glBindTexture( GL_TEXTURE_2D, TextureID );
	
	// Default Load Format //
	int LoadFormat = 0;
	int RGBMode = GL_RGBA;

#ifdef IPHONE_BUILD
	int PVRTC = 0;
#endif // IPHONE_BUILD //
	
	// Switch the Load Format found inside the PVR File //
	switch ( Texture->Flags & PVR_TYPE_MASK ) {
		case PVR_RGBA_4444:
			LoadFormat = GL_UNSIGNED_SHORT_4_4_4_4;
			break;
		case PVR_RGBA_5551:
			LoadFormat = GL_UNSIGNED_SHORT_5_5_5_1;
			break;
		case PVR_RGBA_8888:
			LoadFormat = GL_UNSIGNED_BYTE;
			break;
		case PVR_RGB_565:
			LoadFormat = GL_UNSIGNED_SHORT_5_6_5;
			RGBMode = GL_RGB;
			break;
		case PVR_RGB_888:
			LoadFormat = GL_UNSIGNED_BYTE;
			RGBMode = GL_RGB;
			break;
		case PVR_I_8:
			LoadFormat = GL_UNSIGNED_BYTE;
			RGBMode = GL_LUMINANCE;
			break;
		case PVR_AI_88:
			LoadFormat = GL_UNSIGNED_SHORT;
			RGBMode = GL_LUMINANCE_ALPHA;
			break;
#ifdef IPHONE_BUILD
		case PVR_PVRTC2:
			PVRTC = 2;
			if ( (Texture->Flags & PVR_ALPHA) == 0 ) {
				LoadFormat = GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG;
				RGBMode = GL_RGB;
			}
			else {
				LoadFormat = GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG;
			}
			break;
		case PVR_PVRTC4:
			PVRTC = 4;
			if ( (Texture->Flags & PVR_ALPHA) == 0 ) {
				LoadFormat = GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG;
				RGBMode = GL_RGB;
			}
			else {
				LoadFormat = GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG;
			}
			break;
#else
		case PVR_DXT1:
			break;
		case PVR_DXT3:
			break;
		case PVR_DXT5:
			break;			
#endif // IPHONE_BUILD //
		default:
			printf("Error!  Unknown PVR Format!");
			break;
	};
	
	// Remember a few things about this texture //
	if ( Detail ) {
		Detail->Width = Texture->Width;
		Detail->Height = Texture->Height;
	}

	// Various Settings for executing glTexImage //
	int Width = Texture->Width;
	int Height = Texture->Height;
	int SizeOffset = 0;
	int ChunkSize = 0;

	// Load the First (Main) Texture //
	glTexImage2D(GL_TEXTURE_2D, 0, RGBMode, Width, Height, 0, RGBMode, LoadFormat, &Texture->Data[SizeOffset]);

	// Load the MipMaps (Mipmap count don't include the original texture) //
	for ( int MipMap = 0; MipMap < Texture->MipMapCount; MipMap++ ) {		
#ifdef IPHONE_BUILD
		// If a PVRTC compression scheme //
		if ( PVRTC == 2 ) {
			ChunkSize = ( (Width >? 16) * (Height >? 8) * 2 + 7) / 8;
		}
		else if ( PVRTC == 4 ) {
			ChunkSize = ( (Width >? 8) * (Height >? 8) * 4 + 7) / 8;
		}
		else
#else

#endif // IPHONE_BUILD //
		// If an uncompressed scheme //
		{
			ChunkSize = (Width * Height) * (Texture->BitsPerPixel >> 3);
		}
		
		// Offset and reduce the dimensions //
		SizeOffset += ChunkSize;
		Width >>= 1;
		Height >>= 1;
		
		// Load the Mipmap Texture //
		glTexImage2D(GL_TEXTURE_2D, MipMap+1, RGBMode, Width, Height, 0, RGBMode, LoadFormat, &Texture->Data[SizeOffset]);
	}

	// Return the Texture ID //
	return TextureID;
}
// - ------------------------------------------------------------------------------------------ - //
unsigned int LoadGL_PVRTexture( const char* MyFile, cTextureDetail* Detail ) {
	// Loaded Texture Data and a useful pointer for accessing it's members //
	DataBlock* TextureData;
	PVRTexture* Texture;

	// Load the compressed data //
	{
		DataBlock* Compressed = new_DataBlock( MyFile );
		TextureData = unpack_LZMA_DataBlock( Compressed );
		Texture = (PVRTexture*)TextureData->Data;
		delete_DataBlock( Compressed );
	}

	unsigned int TextureID = LoadGL_PVRTexture( Texture, Detail );

	delete_DataBlock( TextureData );

	return TextureID;
}
// - ------------------------------------------------------------------------------------------ - //
