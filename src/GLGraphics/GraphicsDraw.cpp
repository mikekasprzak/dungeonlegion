// - ------------------------------------------------------------------------------------------ - //
#include <cstdio>
#include <cstdlib>
// - ------------------------------------------------------------------------------------------ - //
#include <PVRTexture_Load.h>
// - ------------------------------------------------------------------------------------------ - //

//// - ------------------------------------------------------------------------------------------ - //
//#ifdef IPHONE_BUILD
//const char* MyAppName = "Smiles.app";
//#endif // IPHONE_BUILD //
//// - ------------------------------------------------------------------------------------------ - //
//
//// - ------------------------------------------------------------------------------------------ - //
//extern unsigned int gfxLoadTexture( const char* MyFile );
//// - ------------------------------------------------------------------------------------------ - //
//unsigned int gfxLoadTexture( const char* MyFile ) {
//	char File[1024];
//
//#ifdef IPHONE_BUILD
//	sprintf(File,"%s/%s/Content/%s", getenv("HOME"), MyAppName, MyFile);
//#else // IPHONE_BUILD //
//	sprintf(File,"Content/%s", MyFile);
//#endif // IPHONE_BUILD //
//
//	const char* DataFile = &File[0];
//	
//	return LoadGL_PVRTexture( DataFile );
//}
//// - ------------------------------------------------------------------------------------------ - //