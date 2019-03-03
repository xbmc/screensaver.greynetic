#ifndef GL_ES
#define lowp
#endif

varying lowp vec4 v_color;

void main ()
{
  gl_FragColor = v_color;
}
