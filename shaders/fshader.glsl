#version 400

in vec4 color;
in vec2 tex_coord;
in vec4 normal;
in vec4 position;

uniform sampler2D textureSampler;
uniform vec4 uCameraPosition;
uniform vec4 uLightPositions[2];
uniform vec4 uSpotLightPosition[2];
uniform bool uLightsState[3];

out vec4 out_color;

void main () {
  vec4 base_color = texture(textureSampler, tex_coord);
  vec4 intensity = vec4(0.0);

  // Defining material properties
  vec4 diffuse = vec4(1.0, 1.0, 1.0, 1.0);
  vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
  vec4 specular = vec4(1.0, 1.0, 1.0, 1.0);
  float shininess = 5.0;
  vec4 spec = vec4(0.0);

  vec3 norm = normalize(normal.xyz);

  // ---------------------------

  // Light 1
  if (uLightsState[0]) {
    // float intensity = 0;
    float diffuseIntensity = 0;
    float specularIntensity = 0;

    vec4 lightPosition = uLightPositions[0];
    vec3 lightVector = lightPosition.xyz - position.xyz;
    // optional: attenuation
    float dist = length(lightVector);
    float attenuation = 1.0 / (1.0 + 0.00001 * dist + 0.00000001 * dist * dist);
    // float attenuation = 1.0;

    lightVector = normalize(lightVector);

    diffuseIntensity = max(0.0, dot(norm, lightVector));
    // out_color += base_color * diffuse * nxDir;

    vec4 cameraPosition = uCameraPosition;

    if (diffuseIntensity > 0.0) {
      vec3 cameraVector = normalize(cameraPosition.xyz - position.xyz);
      vec3 halfVector = normalize(lightVector + cameraVector);
      specularIntensity = pow(max(0.0, dot(norm, halfVector)), shininess);
    }

    intensity += (diffuse * diffuseIntensity + specular * specularIntensity) * attenuation;
  }

  // Light 2
  if (uLightsState[1]) {
    // float intensity = 0;
    float diffuseIntensity = 0;
    float specularIntensity = 0;

    vec4 lightPosition = uLightPositions[1];
    vec3 lightVector = lightPosition.xyz - position.xyz;
    // optional: attenuation
    float dist = length(lightVector);
    float attenuation = 1.0 / (1.0 + 0.00001 * dist + 0.0000001 * dist * dist);
    // float attenuation = 1.0;

    lightVector = normalize(lightVector);

    diffuseIntensity = max(0.0, dot(norm, lightVector));
    // out_color += base_color * diffuse * nxDir;

    vec4 cameraPosition = uCameraPosition;

    if (diffuseIntensity > 0.0) {
      vec3 cameraVector = normalize(cameraPosition.xyz - position.xyz);
      vec3 halfVector = normalize(lightVector + cameraVector);
      specularIntensity = pow(max(0.0, dot(norm, halfVector)), shininess);
    }

    intensity += (diffuse * diffuseIntensity + specular * specularIntensity) * attenuation;
  }

  // SpotLight
  if (uLightsState[2]) {
    // float intensity = 0;
    float diffuseIntensity = 0;
    float specularIntensity = 0;

    vec4 lightPosition = uSpotLightPosition[0];
    vec3 lightVector = lightPosition.xyz - position.xyz;
    // optional: attenuation
    float dist = length(lightVector);

    if (dist < 100) {
      // part of spotlight
      intensity = vec4(1.0f);
      base_color = vec4(1.0f);
    } else {
      float attenuation = 1.0 / (1.0 + 0.0000001 * dist);

      lightVector = normalize(lightVector);

      diffuseIntensity = max(0.0, dot(norm, lightVector));
      // out_color += base_color * diffuse * nxDir;

      vec4 cameraPosition = uCameraPosition;

      if (diffuseIntensity > 0.0) {
        vec3 cameraVector = normalize(cameraPosition.xyz - position.xyz);
        vec3 halfVector = normalize(lightVector + cameraVector);
        specularIntensity = pow(max(0.0, dot(norm, halfVector)), shininess);
      }

      vec3 spotlightDir = normalize(uSpotLightPosition[0].xyz - uSpotLightPosition[1].xyz);
      float cos_theta = dot(spotlightDir, lightVector);

      if (cos_theta > 0.9)
        intensity += (diffuse * diffuseIntensity + specular * specularIntensity) * attenuation;
    }
  }

  intensity += ambient;
  out_color = base_color * intensity;
}
