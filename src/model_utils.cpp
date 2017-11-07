#include "model_utils.hpp"

VertexData* sphere(GLfloat r, GLuint n_lats, GLuint n_longs) {
  GLfloat slice_length = (PI / n_lats);
  GLfloat sector_length = (2 * PI / n_longs);

  GLfloat theta, phi, x, y, z;
  std::vector<glm::vec4> vertices;
  std::vector<glm::vec4> colors;
  std::vector<glm::vec2> tex_coords;
  std::vector<glm::vec4> normals;

  glm::vec4 white_color(1.0f, 1.0f, 1.0f, 1.0f);

  for (int i = 0; i < n_lats; ++i) {
    for (int j = 0; j < n_longs; ++j) {
      theta = i * slice_length;
      phi = j * sector_length;

      { // triangle 1
        x = r * cos(phi) * sin(theta);
        y = r * sin(phi) * sin(theta);
        z = r * cos(theta);
        vertices.push_back(glm::vec4(x, y, z, 1.0));
        colors.push_back(white_color);
        tex_coords.push_back(glm::vec2(theta / PI, phi / (2 * PI)));
        normals.push_back(glm::vec4(x, y, z, 0.0));

        theta += slice_length;
        x = r * cos(phi) * sin(theta);
        y = r * sin(phi) * sin(theta);
        z = r * cos(theta);
        vertices.push_back(glm::vec4(x, y, z, 1.0));
        colors.push_back(white_color);
        tex_coords.push_back(glm::vec2(theta / PI, phi / (2 * PI)));
        normals.push_back(glm::vec4(x, y, z, 0.0));


        phi += sector_length;
        x = r * cos(phi) * sin(theta);
        y = r * sin(phi) * sin(theta);
        z = r * cos(theta);
        vertices.push_back(glm::vec4(x, y, z, 1.0));
        colors.push_back(white_color);
        tex_coords.push_back(glm::vec2(theta / PI, phi / (2 * PI)));
        normals.push_back(glm::vec4(x, y, z, 0.0));
      }

      { // triangle 2
        vertices.push_back(glm::vec4(x, y, z, 1.0));
        colors.push_back(white_color);
        tex_coords.push_back(glm::vec2(theta / PI, phi / (2 * PI)));
        normals.push_back(glm::vec4(x, y, z, 0.0));


        theta -= slice_length;
        x = r * cos(phi) * sin(theta);
        y = r * sin(phi) * sin(theta);
        z = r * cos(theta);
        vertices.push_back(glm::vec4(x, y, z, 1.0));
        colors.push_back(white_color);
        tex_coords.push_back(glm::vec2(theta / PI, phi / (2 * PI)));
        normals.push_back(glm::vec4(x, y, z, 0.0));


        phi -= sector_length;
        x = r * cos(phi) * sin(theta);
        y = r * sin(phi) * sin(theta);
        z = r * cos(theta);
        vertices.push_back(glm::vec4(x, y, z, 1.0));
        colors.push_back(white_color);
        tex_coords.push_back(glm::vec2(theta / PI, phi / (2 * PI)));
        normals.push_back(glm::vec4(x, y, z, 0.0));
      }
    }
  }

  VertexData *data = new VertexData;
  data->num_vertices = vertices.size();
  data->vertices = &vertices[0];
  data->colors = &colors[0];
  data->tex_coords = &tex_coords[0];
  data->normals = &normals[0];

  return data;
}

VertexData* cylinder(
  GLfloat br,
  GLfloat tr,
  GLfloat h,
  GLuint tesselation,
  bool closed) {
  GLfloat d_theta = (2 * PI / tesselation);

  GLfloat theta, x, y, z, r;
  std::vector<glm::vec4> vertices;
  std::vector<glm::vec4> colors;
  std::vector<glm::vec2> tex_coords;
  std::vector<glm::vec4> normals;

  glm::vec4 white_color(1.0f, 1.0f, 1.0f, 1.0f);

  for (int i = 0; i < tesselation; ++i) {
    theta = i * d_theta;

    r = tr;
    x = r * sin(theta);
    y = h;
    z = r * cos(theta);
    vertices.push_back(glm::vec4(x, y, z, 1.0));
    colors.push_back(white_color);
    tex_coords.push_back(glm::vec2(theta / (2 * PI), 1.0f));
    normals.push_back(glm::vec4(x, 0.0f, z, 0.0));

    r = br;
    x = r * sin(theta);
    y = 0;
    z = r * cos(theta);
    vertices.push_back(glm::vec4(x, y, z, 1.0));
    colors.push_back(white_color);
    tex_coords.push_back(glm::vec2(theta / (2 * PI), 0.0f));
    normals.push_back(glm::vec4(x, 0.0f, z, 0.0));

    theta += d_theta;
    x = r * sin(theta);
    y = 0;
    z = r * cos(theta);
    vertices.push_back(glm::vec4(x, y, z, 1.0));
    colors.push_back(white_color);
    tex_coords.push_back(glm::vec2(theta / (2 * PI), 0.0f));
    normals.push_back(glm::vec4(x, 0.0f, z, 0.0));

    vertices.push_back(glm::vec4(x, y, z, 1.0));
    colors.push_back(white_color);
    tex_coords.push_back(glm::vec2(theta / (2 * PI), 0.0f));
    normals.push_back(glm::vec4(x, 0.0f, z, 0.0));

    r = tr;
    x = r * sin(theta);
    y = h;
    z = r * cos(theta);
    vertices.push_back(glm::vec4(x, y, z, 1.0));
    colors.push_back(white_color);
    tex_coords.push_back(glm::vec2(theta / (2 * PI), 1.0f));
    normals.push_back(glm::vec4(x, 0.0f, z, 0.0));

    theta -= d_theta;
    x = r * sin(theta);
    y = h;
    z = r * cos(theta);
    vertices.push_back(glm::vec4(x, y, z, 1.0));
    colors.push_back(white_color);
    tex_coords.push_back(glm::vec2(theta / (2 * PI), 1.0f));
    normals.push_back(glm::vec4(x, 0.0f, z, 0.0));
  }

  if (closed) {

    for (int i = 0; i < tesselation; ++i) {
      theta = i * d_theta;

      // top cover
      x = 0.0; y = h; z = 0.0;
      vertices.push_back(glm::vec4(x, y, z, 1.0));
      colors.push_back(white_color);
      tex_coords.push_back(glm::vec2(0.0f, 0.0f));
      normals.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0));

      x = tr * sin(theta); y = h; z = tr * cos(theta);
      vertices.push_back(glm::vec4(x, y, z, 1.0));
      colors.push_back(white_color);
      tex_coords.push_back(glm::vec2(0.0f, 0.0f));
      normals.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0));

      theta += d_theta;
      x = tr * sin(theta); y = h; z = tr * cos(theta);
      vertices.push_back(glm::vec4(x, y, z, 1.0));
      colors.push_back(white_color);
      tex_coords.push_back(glm::vec2(0.0f, 0.0f));
      normals.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0));

      // bottom cover
      x = br * sin(theta); y = 0.0; z = br * cos(theta);
      vertices.push_back(glm::vec4(x, y, z, 1.0));
      colors.push_back(white_color);
      tex_coords.push_back(glm::vec2(0.0f, 0.0f));
      normals.push_back(glm::vec4(0.0f, -1.0f, 0.0f, 0.0));

      theta -= d_theta;
      x = br * sin(theta); y = 0.0; z = br * cos(theta);
      vertices.push_back(glm::vec4(x, y, z, 1.0));
      colors.push_back(white_color);
      tex_coords.push_back(glm::vec2(0.0f, 0.0f));
      normals.push_back(glm::vec4(0.0f, -1.0f, 0.0f, 0.0));

      x = 0.0; y = 0.0; z = 0.0;
      vertices.push_back(glm::vec4(x, y, z, 1.0));
      colors.push_back(white_color);
      tex_coords.push_back(glm::vec2(0.0f, 0.0f));
      normals.push_back(glm::vec4(0.0f, -1.0f, 0.0f, 0.0));
    }
  }

  VertexData *data = new VertexData;
  data->num_vertices = vertices.size();
  data->vertices = &vertices[0];
  data->colors = &colors[0];
  data->tex_coords = &tex_coords[0];
  data->normals = &normals[0];

  return data;
}

VertexData* cuboid(GLfloat a, GLfloat b, GLfloat c) {
  std::vector<glm::vec4> vertices;
  std::vector<glm::vec4> colors;
  std::vector<glm::vec2> tex_coords;
  std::vector<glm::vec4> normals;

  glm::vec4 white_color(1.0f, 1.0f, 1.0f, 1.0f);

  /*
   (7)____(6)
    |     |
    |(3)__|__(2) ____ y = c
    |__|__|  |
  (4)  | (5) |
       |_____|
      (0)    (1) ---- y = 0

  */

  glm::vec4 positions[8] = {
    glm::vec4(-a, 0.0f, b, 1.0f),
    glm::vec4(a, 0.0f, b, 1.0f),
    glm::vec4(a, c, b, 1.0f),
    glm::vec4(-a, c, b, 1.0f),

    glm::vec4(-a, 0.0f, -b, 1.0f),
    glm::vec4(a, 0.0f, -b, 1.0f),
    glm::vec4(a, c, -b, 1.0f),
    glm::vec4(-a, c, -b, 1.0f)
  };

  glm::vec2 t_coords[4] = {
    glm::vec2(0.0f, 0.0f),
    glm::vec2(0.0f, 1.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(1.0f, 0.0f)
  };

  glm::vec4 nx(1.0f, 0.0f, 0.0f, 1.0f),
            ny(0.0f, 1.0f, 0.0f, 1.0f),
            nz(0.0f, 0.0f, 1.0f, 1.0f);

  {
    // front
    vertices.push_back(positions[0]);
    vertices.push_back(positions[1]);
    vertices.push_back(positions[3]);

    vertices.push_back(positions[3]);
    vertices.push_back(positions[1]);
    vertices.push_back(positions[2]);

    for (int i = 0; i < 6; ++i) {
      normals.push_back(nz);
      colors.push_back(white_color);
    }
  }

  {
    // top
    vertices.push_back(positions[3]);
    vertices.push_back(positions[2]);
    vertices.push_back(positions[7]);

    vertices.push_back(positions[7]);
    vertices.push_back(positions[2]);
    vertices.push_back(positions[6]);

    for (int i = 0; i < 6; ++i) {
      normals.push_back(ny);
      colors.push_back(white_color);
    }
  }

  {
    // right side
    vertices.push_back(positions[1]);
    vertices.push_back(positions[5]);
    vertices.push_back(positions[2]);

    vertices.push_back(positions[2]);
    vertices.push_back(positions[5]);
    vertices.push_back(positions[6]);

    for (int i = 0; i < 6; ++i) {
      normals.push_back(nx);
      colors.push_back(white_color);
    }
  }

  {
    // left side
    vertices.push_back(positions[4]);
    vertices.push_back(positions[0]);
    vertices.push_back(positions[7]);

    vertices.push_back(positions[7]);
    vertices.push_back(positions[0]);
    vertices.push_back(positions[3]);

    for (int i = 0; i < 6; ++i) {
      normals.push_back(-nx);
      colors.push_back(white_color);
    }
  }

  {
    // bottom side
    vertices.push_back(positions[4]);
    vertices.push_back(positions[5]);
    vertices.push_back(positions[0]);

    vertices.push_back(positions[0]);
    vertices.push_back(positions[5]);
    vertices.push_back(positions[1]);

    for (int i = 0; i < 6; ++i) {
      normals.push_back(-ny);
      colors.push_back(white_color);
    }
  }

  {
    // back side
    vertices.push_back(positions[5]);
    vertices.push_back(positions[4]);
    vertices.push_back(positions[6]);

    vertices.push_back(positions[6]);
    vertices.push_back(positions[4]);
    vertices.push_back(positions[7]);

    for (int i = 0; i < 6; ++i) {
      normals.push_back(-nz);
      colors.push_back(white_color);
    }
  }


  for (int i = 0; i < 6; ++i) {
    tex_coords.push_back(t_coords[0]);
    tex_coords.push_back(t_coords[1]);
    tex_coords.push_back(t_coords[3]);
    tex_coords.push_back(t_coords[3]);
    tex_coords.push_back(t_coords[1]);
    tex_coords.push_back(t_coords[2]);
  }

  VertexData *data = new VertexData;
  data->num_vertices = vertices.size();
  data->vertices = &vertices[0];
  data->colors = &colors[0];
  data->tex_coords = &tex_coords[0];
  data->normals = &normals[0];

  return data;
}