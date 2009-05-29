//precision mediump float;

vec4 Ambient = vec4( 44.0/255.0, 22.0/255.0, 0.0, 1.0 );
uniform sampler2D tex0;

void main() {
	gl_FragColor = /*Ambient +*/ (gl_Color * texture2D(tex0, gl_TexCoord[0]));
}
