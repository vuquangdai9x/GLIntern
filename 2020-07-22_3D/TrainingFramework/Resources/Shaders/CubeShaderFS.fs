precision mediump float;

uniform samplerCube u_texture;
varying vec3 v_pos;

void main(void)
{
	gl_FragColor = textureCube(u_texture, v_pos);
}