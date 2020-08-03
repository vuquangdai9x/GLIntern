precision mediump float;

uniform samplerCube u_texture;
uniform vec4 u_fogColor;

varying vec3 v_pos;
varying float v_fogDensity;

void main(void)
{
	vec4 color = textureCube(u_texture, v_pos);
	gl_FragColor = u_fogColor * v_fogDensity + color * (1.0 - v_fogDensity);
}