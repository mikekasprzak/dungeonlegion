// - ------------------------------------------------------------------------------------------ - //
// Bits //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Rebel_Bits_H__
#define __Rebel_Bits_H__
// - ------------------------------------------------------------------------------------------ - //
//#define bitSet(_var, _bit)				_var = (_var) | (1<<(_bit))
//#define bitReset(_var, _bit)			_var = (_var) & ~(1<<(_bit))
//#define bitGet(_var, _bit)				((_var) & (1<<(_bit)))
// - ------------------------------------------------------------------------------------------ - //
static const unsigned int bit0				=	0x1;
static const unsigned int bit1				=	0x2;
static const unsigned int bit2				=	0x4;
static const unsigned int bit3				=	0x8;
static const unsigned int bit4				=	0x10;
static const unsigned int bit5				=	0x20;
static const unsigned int bit6				=	0x40;
static const unsigned int bit7				=	0x80;
static const unsigned int bit8				=	0x100;
static const unsigned int bit9				=	0x200;
static const unsigned int bit10				=	0x400;
static const unsigned int bit11				=	0x800;
static const unsigned int bit12				=	0x1000;
static const unsigned int bit13				=	0x2000;
static const unsigned int bit14				=	0x4000;
static const unsigned int bit15				=	0x8000;
static const unsigned int bit16				=	0x10000;
static const unsigned int bit17				=	0x20000;
static const unsigned int bit18				=	0x40000;
static const unsigned int bit19				=	0x80000;
static const unsigned int bit20				=	0x100000;
static const unsigned int bit21				=	0x200000;
static const unsigned int bit22				=	0x400000;
static const unsigned int bit23				=	0x800000;
static const unsigned int bit24				=	0x1000000;
static const unsigned int bit25				=	0x2000000;
static const unsigned int bit26				=	0x4000000;
static const unsigned int bit27				=	0x8000000;
static const unsigned int bit28				=	0x10000000;
static const unsigned int bit29				=	0x20000000;
static const unsigned int bit30				=	0x40000000;
static const unsigned int bit31				=	0x80000000;
static const unsigned long long int bit32	=	(0x1ull << 32);
static const unsigned long long int bit33	=	(0x2ull << 32);
static const unsigned long long int bit34	=	(0x4ull << 32);
static const unsigned long long int bit35	=	(0x8ull << 32);
static const unsigned long long int bit36	=	(0x10ull << 32);
static const unsigned long long int bit37	=	(0x20ull << 32);
static const unsigned long long int bit38	=	(0x40ull << 32);
static const unsigned long long int bit39	=	(0x80ull << 32);
static const unsigned long long int bit40	=	(0x100ull << 32);
static const unsigned long long int bit41	=	(0x200ull << 32);
static const unsigned long long int bit42	=	(0x400ull << 32);
static const unsigned long long int bit43	=	(0x800ull << 32);
static const unsigned long long int bit44	=	(0x1000ull << 32);
static const unsigned long long int bit45	=	(0x2000ull << 32);
static const unsigned long long int bit46	=	(0x4000ull << 32);
static const unsigned long long int bit47	=	(0x8000ull << 32);
static const unsigned long long int bit48	=	(0x10000ull << 32);
static const unsigned long long int bit49	=	(0x20000ull << 32);
static const unsigned long long int bit50	=	(0x40000ull << 32);
static const unsigned long long int bit51	=	(0x80000ull << 32);
static const unsigned long long int bit52	=	(0x100000ull << 32);
static const unsigned long long int bit53	=	(0x200000ull << 32);
static const unsigned long long int bit54	=	(0x400000ull << 32);
static const unsigned long long int bit55	=	(0x800000ull << 32);
static const unsigned long long int bit56	=	(0x1000000ull << 32);
static const unsigned long long int bit57	=	(0x2000000ull << 32);
static const unsigned long long int bit58	=	(0x4000000ull << 32);
static const unsigned long long int bit59	=	(0x8000000ull << 32);
static const unsigned long long int bit60	=	(0x10000000ull << 32);
static const unsigned long long int bit61	=	(0x20000000ull << 32);
static const unsigned long long int bit62	=	(0x40000000ull << 32);
static const unsigned long long int bit63	=	(0x80000000ull << 32);
// - ------------------------------------------------------------------------------------------ - //
//#define bit0					0x1
//#define bit1					0x2
//#define bit2					0x4
//#define bit3					0x8
//#define bit4					0x10
//#define bit5					0x20
//#define bit6					0x40
//#define bit7					0x80
//#define bit8					0x100
//#define bit9					0x200
//#define bit10					0x400
//#define bit11					0x800
//#define bit12					0x1000
//#define bit13					0x2000
//#define bit14					0x4000
//#define bit15					0x8000
//#define bit16					0x10000
//#define bit17					0x20000
//#define bit18					0x40000
//#define bit19					0x80000
//#define bit20					0x100000
//#define bit21					0x200000
//#define bit22					0x400000
//#define bit23					0x800000
//#define bit24					0x1000000
//#define bit25					0x2000000
//#define bit26					0x4000000
//#define bit27					0x8000000
//#define bit28					0x10000000
//#define bit29					0x20000000
//#define bit30					0x40000000
//#define bit31					0x80000000
//#define bit32					(0x1 << 32)
//#define bit33					(0x2 << 32)
//#define bit34					(0x4 << 32)
//#define bit35					(0x8 << 32)
//#define bit36					(0x10 << 32)
//#define bit37					(0x20 << 32)
//#define bit38					(0x40 << 32)
//#define bit39					(0x80 << 32)
//#define bit40					(0x100 << 32)
//#define bit41					(0x200 << 32)
//#define bit42					(0x400 << 32)
//#define bit43					(0x800 << 32)
//#define bit44					(0x1000 << 32)
//#define bit45					(0x2000 << 32)
//#define bit46					(0x4000 << 32)
//#define bit47					(0x8000 << 32)
//#define bit48					(0x10000 << 32)
//#define bit49					(0x20000 << 32)
//#define bit50					(0x40000 << 32)
//#define bit51					(0x80000 << 32)
//#define bit52					(0x100000 << 32)
//#define bit53					(0x200000 << 32)
//#define bit54					(0x400000 << 32)
//#define bit55					(0x800000 << 32)
//#define bit56					(0x1000000 << 32)
//#define bit57					(0x2000000 << 32)
//#define bit58					(0x4000000 << 32)
//#define bit59					(0x8000000 << 32)
//#define bit60					(0x10000000 << 32)
//#define bit61					(0x20000000 << 32)
//#define bit62					(0x40000000 << 32)
//#define bit63					(0x80000000 << 32)
// - ------------------------------------------------------------------------------------------ - //
#endif // __Rebel_Bits_H__ //
// - ------------------------------------------------------------------------------------------ - //
