// - ------------------------------------------------------------------------------------------ - //
#ifndef __ALGORITHM_ALIGN_H__
#define __ALGORITHM_ALIGN_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template<class Type>
inline Type AlignA( Type A, Type B = 0, Type C = 0, Type D = 0, Type E = 0 ) {
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
template<class Type>
inline Type AlignB( Type A, Type B, Type C = 0, Type D = 0, Type E = 0 ) {
	Type Total = A + B + C + D + E;
	return A / Total;
}
// - ------------------------------------------------------------------------------------------ - //
template<class Type>
inline Type AlignC( Type A, Type B, Type C, Type D = 0, Type E = 0 ) {
	Type Total = A + B + C + D + E;
	return (A+B) / Total;
}
// - ------------------------------------------------------------------------------------------ - //
template<class Type>
inline Type AlignD( Type A, Type B, Type C, Type D, Type E = 0 ) {
	Type Total = A + B + C + D + E;
	return (A+B+C) / Total;
}
// - ------------------------------------------------------------------------------------------ - //
template<class Type>
inline Type AlignE( Type A, Type B, Type C, Type D, Type E ) {
	Type Total = A + B + C + D + E;
	//return (A+B+C+D) / Total;
	return (1 - E) / Total;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __ALGORITHM_ALIGN_H__ //
// - ------------------------------------------------------------------------------------------ - //
