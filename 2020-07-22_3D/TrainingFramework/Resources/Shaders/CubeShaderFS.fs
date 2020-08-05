precision mediump float;

uniform samplerCube u_mainTexture;
uniform vec4 u_fogColor;

varying vec3 v_pos;
varying float v_fogDensity;

void main(void)
{
	vec4 color = textureCube(u_mainTexture, v_pos);
	//gl_FragColor = u_fogColor * v_fogDensity + color * (1.0 - v_fogDensity);
	gl_FragColor = color;
}