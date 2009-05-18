// - ------------------------------------------------------------------------------------------ - //
#ifndef __UVAllocator_H__
#define __UVAllocator_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Set/UVSet.h>
#include <UV.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< const int MaxSize >
class UVAllocator: public Allocator<UVSet<UVType>,MaxSize> {
public:
	inline UVAllocator()
	{
	}
	
	inline UVAllocator( const int Start ) :
		Allocator<UVSet<UVType>,MaxSize>( Start )
	{
	}
public:
	inline const int AddMany( const UVType* Src, const int Count ) {
		int OldSize = Allocator<UVSet<UVType>,MaxSize>::_Size;
		
		// TODO: Use a better copy function //
		for ( int idx = Count; idx--; ) 
		{
			Allocator<UVSet<UVType>,MaxSize>::Data[ Allocator<UVSet<UVType>,MaxSize>::_Size + idx ].u = Src[(idx<<1)+0];
			Allocator<UVSet<UVType>,MaxSize>::Data[ Allocator<UVSet<UVType>,MaxSize>::_Size + idx ].v = Src[(idx<<1)+1];
		}

		Allocator<UVSet<UVType>,MaxSize>::_Size += Count;

		return OldSize;
	}


	inline const int AddRect6( UVType U1, UVType V1, UVType U2, UVType V2 ) {
		UVSet<UVType>* VP = &Allocator<UVSet<UVType>,MaxSize>::Data[ Allocator<UVSet<UVType>,MaxSize>::_Size ];
		
		VP[0] = UVSet<UVType>( U1, V1 );
		VP[1] = UVSet<UVType>( U2, V1 );
		VP[2] = UVSet<UVType>( U1, V2 );
		VP[3] = UVSet<UVType>( U2, V1 );
		VP[4] = UVSet<UVType>( U1, V2 );
		VP[5] = UVSet<UVType>( U2, V2 );		
		
		Allocator<UVSet<UVType>,MaxSize>::_Size += 6;
	}


	inline const int AddQuad6( const UVType* Src ) {
		AddMany( &Src[0], 3 );
		AddMany( &Src[2], 3 );
	}

	inline const int AddQuad6( const UVSet<UVType>* Src ) {
		AddMany( &Src[0], 3 );
		AddMany( &Src[1], 3 );
	}


	inline const int AddQuad4( const UVType* Src ) {
		AddMany( &Src[0], 4 );
	}

	inline const int AddQuad4( const UVSet<UVType>* Src ) {
		AddMany( &Src[0], 4 );
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __UVAllocator_H__ //
// - ------------------------------------------------------------------------------------------ - //
