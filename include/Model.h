#pragma once

#include <vector>
#include <string>
#include <memory>

#include <Shader.h>
#include <Mesh.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
public:
	Model (const char* path);
	virtual ~Model ();

	void draw(std::unique_ptr<Shader> const& shader);
private:
	/* Model data */
	std::vector<Mesh> meshes;
	std::string directory;
	std::vector<Texture> textures_loaded;

	void load_model(const std::string& path);
	void process_node(aiNode *node, const aiScene *scene);
	Mesh process_mesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> load_material_textures(aiMaterial *mat, aiTextureType type, std::string typeName);
};
