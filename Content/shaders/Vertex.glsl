
void main() {
//	gl_Position = gl_Vertex;
	
//	vec4 ecPosition;
//	vec3 ecPosition3;
//	
//	//if (NeedEyePosition)
//	{
//		ecPosition = gl_ModelViewMatrix * gl_Vertex;
//		ecPosition3 = (vec3 (ecPosition)) / ecPosition.w;
//	}
//	
//	normal = gl_NormalMatrix * gl_Normal;
	
	//gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	gl_Position = ftransform();
}
