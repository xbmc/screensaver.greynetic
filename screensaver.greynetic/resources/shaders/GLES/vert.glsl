#version 100

uniform mat4 u_projModelMat;

attribute vec4 a_position;
attribute vec4 a_color;

varying vec4 v_color;

void main ()
{
  gl_Position = u_projModelMat * a_position;
  v_color = a_color;
}
