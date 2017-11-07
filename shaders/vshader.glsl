#version 400

in vec4 vPosition;
in vec4 vColor;
in vec2 vTexture;
in vec4 vNormal;

uniform mat4 uViewMatrix;
uniform mat4 uModelMatrix;
uniform mat4 uNormalMatrix;

out vec4 color;
out vec2 tex_coord;
out vec4 normal;
out vec4 position;

void main () {
	gl_Position = uViewMatrix * uModelMatrix * vPosition;
	color = vColor;
  tex_coord = vTexture;
  normal = uNormalMatrix * normalize(vNormal);
  position = uModelMatrix * vPosition;
}
