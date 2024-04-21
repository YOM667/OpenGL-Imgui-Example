#version 330 core
out vec4 FragColor;
uniform vec3 color;
uniform float time;
void main()
{
   // Time varying pixel color
   float red = cos(time) + color.x;
   float green = cos(time) + color.y;
   float blue = cos(time) + color.z;
   vec3 col = vec3(red,green,blue);

   // Output to screen
   FragColor = vec4(col,1.0);
}