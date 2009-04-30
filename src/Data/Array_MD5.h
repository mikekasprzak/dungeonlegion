// - ------------------------------------------------------------------------------------------ - //
// Array MD5 Hash - MD5 Hashing code for Array library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_Array_MD5_H__
#define __Library_Data_Array_MD5_H__
// - ------------------------------------------------------------------------------------------ - //
#include "Array_Core.h"
#include "Data_MD5.h"
// - ------------------------------------------------------------------------------------------ - //
//namespace Data {
// - ------------------------------------------------------------------------------------------ - //
// Hash a block of data with an MD5 sum //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const MD5Hash hash_MD5_Array( const Array<Type>* _Src ) {
	return hash_MD5_Data( _Src->Data, _Src->Size * sizeof(Type) );
}
// - ------------------------------------------------------------------------------------------ - //
//}; // namespace Data //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_Array_MD5_H__ //
// - ------------------------------------------------------------------------------------------ - //
