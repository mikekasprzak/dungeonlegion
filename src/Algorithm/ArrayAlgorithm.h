// - ------------------------------------------------------------------------------------------ - //
#ifndef __ALGORITHM_ARRAYALGORITHM_H__
#define __ALGORITHM_ARRAYALGORITHM_H__
// - ------------------------------------------------------------------------------------------ - //
// Dimensionality - Biggest or Smallest value in an array //
// - ------------------------------------------------------------------------------------------ - //
template<class Type>
inline Type GetLargest( Type* Data, size_t Size ) {
	if ( Size > 0 ) {
		Type Value = Data[Size-1];
		for ( size_t idx = Size-1; idx--; ) {
			if ( Data[idx] > Value )
				Value = Data[idx];
		}
		return Value;
	}
	return Type();
}
// - ------------------------------------------------------------------------------------------ - //
template<class Type>
inline Type GetSmallest( Type* Data, size_t Size ) {
	if ( Size > 0 ) {
		Type Value = Data[Size-1];
		for ( size_t idx = Size-1; idx--; ) {
			if ( Data[idx] < Value )
				Value = Data[idx];
		}
		return Value;
	}
	return Type();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Arithmetic - Apply values to an array //
// - ------------------------------------------------------------------------------------------ - //
template<class Type>
inline void Add( Type Value, Type* Data, size_t Size ) {
	for ( size_t idx = Size; idx--; ) {
		Data[idx] += Value;
	}
}
// - ------------------------------------------------------------------------------------------ - //
template<class Type>
inline void Subtract( Type Value, Type* Data, size_t Size ) {
	for ( size_t idx = Size; idx--; ) {
		Data[idx] -= Value;
	}
}
// - ------------------------------------------------------------------------------------------ - //
template<class Type>
inline void Multiply( Type Value, Type* Data, size_t Size ) {
	for ( size_t idx = Size; idx--; ) {
		Data[idx] *= Value;
	}
}
// - ------------------------------------------------------------------------------------------ - //
template<class Type>
inline void Divide( Type Value, Type* Data, size_t Size ) {
	for ( size_t idx = Size; idx--; ) {
		Data[idx] /= Value;
	}
}
// - ------------------------------------------------------------------------------------------ - //
template<class Type>
inline void Mod( Type Value, Type* Data, size_t Size ) {
	for ( size_t idx = Size; idx--; ) {
		Data[idx] %= Value;
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template<class Type>
inline void And( Type Value, Type* Data, size_t Size ) {
	for ( size_t idx = Size; idx--; ) {
		Data[idx] &= Value;
	}
}
// - ------------------------------------------------------------------------------------------ - //
template<class Type>
inline void Or( Type Value, Type* Data, size_t Size ) {
	for ( size_t idx = Size; idx--; ) {
		Data[idx] |= Value;
	}
}
// - ------------------------------------------------------------------------------------------ - //
template<class Type>
inline void Xor( Type Value, Type* Data, size_t Size ) {
	for ( size_t idx = Size; idx--; ) {
		Data[idx] ^= Value;
	}
}
// - ------------------------------------------------------------------------------------------ - //
template<class Type>
inline void LeftShift( Type Value, Type* Data, size_t Size ) {
	for ( size_t idx = Size; idx--; ) {
		Data[idx] <<= Value;
	}
}
// - ------------------------------------------------------------------------------------------ - //
template<class Type>
inline void RightShift( Type Value, Type* Data, size_t Size ) {
	for ( size_t idx = Size; idx--; ) {
		Data[idx] >>= Value;
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __ALGORITHM_ARRAYALGORITHM_H__ //
// - ------------------------------------------------------------------------------------------ - //
