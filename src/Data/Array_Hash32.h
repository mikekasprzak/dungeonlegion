// - ------------------------------------------------------------------------------------------ - //
// Array Hash32 - Data Hashing //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_Array_Hash32_H__
#define __Library_Data_Array_Hash32_H__
// - ------------------------------------------------------------------------------------------ - //
#include "Data_Hash32.h"
// - ------------------------------------------------------------------------------------------ - //
//namespace Data {
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline unsigned int hash32_Array( const Array<Type>* Data ) {
	// TODO: Assert zero pointer //
	if (!Data)
		return 0;
		
	return hash32_Data( Data->Data, Data->Size * sizeof(Type) );
}
// - ------------------------------------------------------------------------------------------ - //
//}; // namepsace Data //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_Array_Hash32_H__ //
// - ------------------------------------------------------------------------------------------ - //
