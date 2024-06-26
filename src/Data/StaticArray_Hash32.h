// - ------------------------------------------------------------------------------------------ - //
// StaticArray Hash32 - Data Hashing //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_StaticArray_Hash32_H__
#define __Library_Data_StaticArray_Hash32_H__
// - ------------------------------------------------------------------------------------------ - //
#include "Data_Hash32.h"
// - ------------------------------------------------------------------------------------------ - //
//namespace Data {
// - ------------------------------------------------------------------------------------------ - //
template< class Type, size_t MaxSize >
inline unsigned int hash32_StaticArray( const StaticArray<Type,MaxSize>* Data ) {
	// TODO: Assert zero pointer //
	if (!Data)
		return 0;
		
	return hash32_Data( Data->Data, Data->Size * sizeof(Type) );
}
// - ------------------------------------------------------------------------------------------ - //
//}; // namepsace Data //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_StaticArray_Hash32_H__ //
// - ------------------------------------------------------------------------------------------ - //
