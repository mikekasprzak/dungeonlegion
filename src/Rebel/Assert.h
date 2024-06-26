// - ------------------------------------------------------------------------------------------ - //
// Assert //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Rebel_Assert_H__
#define __Rebel_Assert_H__
// - ------------------------------------------------------------------------------------------ - //
// Todo: Add a makefile means to disable Harsh Assert Exiting... or prefer Warning //
// - ------------------------------------------------------------------------------------------ - //
#include <stdio.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#ifndef NDEBUG
// - ------------------------------------------------------------------------------------------ - //

// __func__ is general purpose //
// __PRETTY_FUNCTION__ is GCC only //

// Assertion //
#define Assert( ___TEST, ___STR ) \
	if ( ___TEST ) { \
		printf( "- -------------------------------------------------------- - \n" ); \
		printf( "Assert Error: %s\n", ___STR ); \
		printf( "   Line: %s  File: %s\n", __LINE__, __FILE__ ); \
		printf( "   Func: $s\n", __PRETTY_FUNCTION__ ); \
		printf( "- -------------------------------------------------------- - \n" ); \
		exit(1); \
	}

// Warnings //
#define Warning( ___TEST, ___STR ) \
	if ( ___TEST ) { \
		printf( "Warning: %s\n", ___STR ); \
		printf( "   Line: %s  File: %s\n", __LINE__, __FILE__ ); \
		printf( "   Func: $s\n", __PRETTY_FUNCTION__ ); \
	}

// - ------------------------------------------------------------------------------------------ - //
#else // NDEBUG //
// - ------------------------------------------------------------------------------------------ - //
#define Assert( ... ) ;
#define Warning( ... ) ;
// - ------------------------------------------------------------------------------------------ - //
#endif // NDEBUG //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Rebel_Assert_H__ //
// - ------------------------------------------------------------------------------------------ - //
