#pragma once
#include"Includes.h"

#ifdef __ASSIMP_NEED

class Model
{
public:
	Model(const char* path);
	void draw(Renderer& renderer);

private:
	std::vector<Mesh> meshes;
	std::string directory;

	void load_model(std::string path);
	void process_node(aiNode* node, const aiScene* scene);
	Mesh process_mesh(aiMesh* mesh, const aiScene* scene);

};
#endif // __ASSIMP_NEED