// ADS Point lighting Shader
// Fragment Shader
// Richard S. Wright Jr.
// OpenGL SuperBible
#version 130

out vec4 vFragColor;
smooth in vec4 vVaryingColor;
smooth in vec2 vTexCoords;
void main(void)
   { 
   vFragColor = vVaryingColor;
   }