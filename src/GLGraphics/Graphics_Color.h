// - ------------------------------------------------------------------------------------------ - //
#ifndef __GLGraphics_Color_H__
#define __GLGraphics_Color_H__
// - ------------------------------------------------------------------------------------------ - //
typedef int ColorType;

#define RGB(_r,_g,_b)		((_r)|((_g)<<8)|((_b)<<16)|((255)<<24))
#define RGBA(_r,_g,_b,_a)	((_r)|((_g)<<8)|((_b)<<16)|((_a)<<24))

#define GET_R(c)	(((c))&255)
#define GET_G(c)	(((c)>>8)&255)
#define GET_B(c)	(((c)>>16)&255)
#define GET_A(c)	(((c)>>24)&255)


#define RGB_BLACK	RGB(0,0,0)
#define RGB_GREY	RGB(127,127,127)
#define RGB_WHITE	RGB(255,255,255)

#define RGB_RED		RGB(255,0,0)
#define RGB_GREEN	RGB(0,255,0)
#define RGB_BLUE	RGB(0,0,255)

#define RGB_MAGENTA	RGB(255,0,255)
#define RGB_YELLOW	RGB(255,255,0)
#define RGB_CYAN	RGB(0,255,255)

#define RGB_ORANGE	RGB(255,127,0)
#define RGB_PINK	RGB(255,0,127)
#define RGB_PURPLE	RGB(127,0,255)
#define RGB_PUKE	RGB(127,255,0)
#define RGB_MINT	RGB(0,255,127)
#define RGB_SKY		RGB(0,127,255)
// - ------------------------------------------------------------------------------------------ - //
inline ColorType HSV( float Hue, float Sat, float Val ) {
	float r,g,b;

	while (Hue < 0)
		Hue += 360;
	while (Hue > 360)
		Hue -= 360;
		
	if ( Sat > 1.0f ) 
		Sat = 1.0f;
	else if ( Sat < 0.0f )
		Sat = 0.0f;
		
	if ( Val > 1.0f ) 
		Val = 1.0f;
	else if ( Val < 0.0f )
		Val = 0.0f;

	if (Hue < 120) {
		r = (120 - Hue) / 60.0f;
		g = Hue / 60.0f;
		b = 0;
	}
	else if (Hue < 240) {
		r = 0;
		g = (240 - Hue) / 60.0f;
		b = (Hue - 120) / 60.0f;
	}
	else {
		r = (Hue - 240) / 60.0f;
		g = 0;
		b = (360 - Hue) / 60.0f;
	}
	
	r = (r > 1)?1:r;
	g = (g > 1)?1:g;
	b = (b > 1)?1:b;

	r = (1 - Sat + Sat * r) * Val;
	g = (1 - Sat + Sat * g) * Val;
	b = (1 - Sat + Sat * b) * Val;

	return RGB( (int)(r * 255.0f), (int)(g * 255.0f), (int)(b * 255.0f) );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxEnableAlphaBlending() {
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
//	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxEnableAddativeBlending() {
	glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gfxDisableBlending() {
	glDisable( GL_BLEND );
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GLGraphics_Color_H__ //
// - ------------------------------------------------------------------------------------------ - //
