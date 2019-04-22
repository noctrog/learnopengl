#pragma once

#include <string>
#include <vector>
#include <memory>
#include <inttypes.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Shader.h>

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture {
	uint32_t id;
	std::string type;
	std::string path;
};

class Mesh
{
public:
	Mesh (std::vector<Vertex> vertices, std::vector<uint32_t> indices, std::vector<Texture> textures);
	virtual ~Mesh ();

	void draw(std::unique_ptr<Shader> const& shader);

private:
	uint32_t VAO, VBO, EBO;

	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	std::vector<Texture> textures;

	void setup_mesh();
};
