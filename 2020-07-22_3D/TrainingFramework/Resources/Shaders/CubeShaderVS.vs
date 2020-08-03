uniform mat4 u_wvp;
attribute vec3 a_posL;
varying vec3 v_pos;

void main()
{
	gl_Position = u_wvp*vec4(a_posL, 1.0);
	v_pos = a_posL;
}
   