// - ------------------------------------------------------------------------------------------ - //
#ifndef __Vector2DAllocator_H__
#define __Vector2DAllocator_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector/Vector2D.h>
#include "Allocator.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< const int MaxSize >
class Vector2DAllocator: public Allocator<Vector2D,MaxSize> {
public:
	inline Vector2DAllocator()
	{
	}
	
	inline Vector2DAllocator( const int Start ) :
		Allocator<Vector2D,MaxSize>( Start )
	{
	}
public:
	inline const int AddMany( const int Count ) {
		int OldSize = Allocator<Vector2D,MaxSize>::_Size;
		Allocator<Vector2D,MaxSize>::_Size += Count;

		return OldSize;
	}

	inline const int AddMany( const float* Src, const int Count ) {
		int OldSize = Allocator<Vector2D,MaxSize>::_Size;
		
		// TODO: Use a better copy function //
		for ( int idx = Count; idx--; ) 
		{
			Allocator<Vector2D,MaxSize>::Data[ Allocator<Vector2D,MaxSize>::_Size + idx ].x = Src[(idx<<1)+0];
			Allocator<Vector2D,MaxSize>::Data[ Allocator<Vector2D,MaxSize>::_Size + idx ].y = Src[(idx<<1)+1];
		}

		Allocator<Vector2D,MaxSize>::_Size += Count;

		return OldSize;
	}

	inline const int AddMany( const float* Src, const int Count, const Vector2D& Pos ) {
		int OldSize = Allocator<Vector2D,MaxSize>::_Size;
		
		// TODO: Use a better copy function //
		for ( int idx = Count; idx--; ) 
		{
			Allocator<Vector2D,MaxSize>::Data[ Allocator<Vector2D,MaxSize>::_Size + idx ].x = Src[(idx<<1)+0] + Pos.x;
			Allocator<Vector2D,MaxSize>::Data[ Allocator<Vector2D,MaxSize>::_Size + idx ].y = Src[(idx<<1)+1] + Pos.y;
		}

		Allocator<Vector2D,MaxSize>::_Size += Count;

		return OldSize;
	}

	inline const int AddMany( const float* Src, const int Count, const Vector2D& Pos, const Real Scale ) {
		int OldSize = Allocator<Vector2D,MaxSize>::_Size;
		
		// TODO: Use a better copy function //
		for ( int idx = Count; idx--; ) 
		{
			Allocator<Vector2D,MaxSize>::Data[ Allocator<Vector2D,MaxSize>::_Size + idx ].x = (Src[(idx<<1)+0]*Scale) + Pos.x;
			Allocator<Vector2D,MaxSize>::Data[ Allocator<Vector2D,MaxSize>::_Size + idx ].y = (Src[(idx<<1)+1]*Scale) + Pos.y;
		}

		Allocator<Vector2D,MaxSize>::_Size += Count;

		return OldSize;
	}
	
	inline const int AddMany( const float* Src, const int Count, const Vector2D& Pos, const Vector2D& Scale ) {
		int OldSize = Allocator<Vector2D,MaxSize>::_Size;
		
		// TODO: Use a better copy function //
		for ( int idx = Count; idx--; ) 
		{
			Allocator<Vector2D,MaxSize>::Data[ Allocator<Vector2D,MaxSize>::_Size + idx ].x = (Src[(idx<<1)+0]*Scale.x) + Pos.x;
			Allocator<Vector2D,MaxSize>::Data[ Allocator<Vector2D,MaxSize>::_Size + idx ].y = (Src[(idx<<1)+1]*Scale.y) + Pos.y;
		}

		Allocator<Vector2D,MaxSize>::_Size += Count;

		return OldSize;
	}
	
	inline const int AddMany( const float* Src, const int Count, const Vector2D& Pos, const Matrix2x2& Scale ) {
		int OldSize = Allocator<Vector2D,MaxSize>::_Size;
			
		Vector2D PosVector;
		
		// TODO: Use a better copy function //
		for ( int idx = Count; idx--; ) 
		{
			PosVector = Vector2D( Src[(idx<<1)+0], Src[(idx<<1)+1] );
			PosVector = PosVector.ApplyMatrix( Scale );
			PosVector += Pos;
			
			Allocator<Vector2D,MaxSize>::Data[ Allocator<Vector2D,MaxSize>::_Size + idx ] = PosVector;
		}

		Allocator<Vector2D,MaxSize>::_Size += Count;

		return OldSize;
	}

	inline const int AddRect6( Vector2D& P1, Vector2D P2 ) {
		Vector2D* VP = &Allocator<Vector2D,MaxSize>::Data[ Allocator<Vector2D,MaxSize>::_Size ];
		
		VP[0] = Vector2D( P1.x, P1.y );
		VP[1] = Vector2D( P2.x, P1.y );
		VP[2] = Vector2D( P1.x, P2.y );
		VP[3] = Vector2D( P2.x, P1.y );
		VP[4] = Vector2D( P1.x, P2.y );
		VP[5] = Vector2D( P2.x, P2.y );
		
		Allocator<Vector2D,MaxSize>::_Size += 6;
	}

	

	inline const int AddQuad6( const float* Src, const Vector2D& Pos ) {
		AddMany( &Src[0], 3, Pos );
		AddMany( &Src[2], 3, Pos );
	}

	inline const int AddQuad6( const Vector2D* Src, const Vector2D& Pos ) {
		AddMany( &Src[0], 3, Pos );
		AddMany( &Src[1], 3, Pos );
	}

	inline const int AddQuad6( const float* Src, const Vector2D& Pos, const Real Scale ) {
		AddMany( &Src[0], 3, Pos, Scale );
		AddMany( &Src[2], 3, Pos, Scale );
	}

	inline const int AddQuad6( const Vector2D* Src, const Vector2D& Pos, const Real Scale ) {
		AddMany( &Src[0], 3, Pos, Scale );
		AddMany( &Src[1], 3, Pos, Scale );
	}

	inline const int AddQuad6( const float* Src, const Vector2D& Pos, const Vector2D& Scale ) {
		AddMany( &Src[0], 3, Pos, Scale );
		AddMany( &Src[2], 3, Pos, Scale );
	}

	inline const int AddQuad6( const Vector2D* Src, const Vector2D& Pos, const Vector2D& Scale ) {
		AddMany( &Src[0], 3, Pos, Scale );
		AddMany( &Src[1], 3, Pos, Scale );
	}

	inline const int AddQuad6( const float* Src, const Vector2D& Pos, const Matrix2x2& Scale ) {
		AddMany( &Src[0], 3, Pos, Scale );
		AddMany( &Src[2], 3, Pos, Scale );
	}

	inline const int AddQuad6( const Vector2D* Src, const Vector2D& Pos, const Matrix2x2& Scale ) {
		AddMany( &Src[0], 3, Pos, Scale );
		AddMany( &Src[1], 3, Pos, Scale );
	}


	inline const int AddQuad4( const float* Src, const Vector2D& Pos ) {
		AddMany( &Src[0], 4, Pos );
	}

	inline const int AddQuad4( const Vector2D* Src, const Vector2D& Pos ) {
		AddMany( &Src[0], 4, Pos );
	}

	inline const int AddQuad4( const float* Src, const Vector2D& Pos, const Real Scale ) {
		AddMany( &Src[0], 4, Pos, Scale );
	}

	inline const int AddQuad4( const Vector2D* Src, const Vector2D& Pos, const Real Scale ) {
		AddMany( &Src[0], 4, Pos, Scale );
	}

	inline const int AddQuad4( const float* Src, const Vector2D& Pos, const Vector2D& Scale ) {
		AddMany( &Src[0], 4, Pos, Scale );
	}

	inline const int AddQuad4( const Vector2D* Src, const Vector2D& Pos, const Vector2D& Scale ) {
		AddMany( &Src[0], 4, Pos, Scale );
	}

	inline const int AddQuad4( const float* Src, const Vector2D& Pos, const Matrix2x2& Scale ) {
		AddMany( &Src[0], 4, Pos, Scale );
	}

	inline const int AddQuad4( const Vector2D* Src, const Vector2D& Pos, const Matrix2x2& Scale ) {
		AddMany( &Src[0], 4, Pos, Scale );
	}

};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Vector2DAllocator_H__ //
// - ------------------------------------------------------------------------------------------ - //
