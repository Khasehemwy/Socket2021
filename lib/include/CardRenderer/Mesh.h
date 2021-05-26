#pragma once
#include"Includes.h"

#ifdef __ASSIMP_NEED


class Mesh
{
public:
	std::vector<vertex_t> vertices;
	std::vector<UINT32> indices;

	Mesh(std::vector<vertex_t> vertices,std::vector<UINT32> indices);
	~Mesh();

	void draw(Renderer& renderer);

private:

};
#endif // __ASSIMP_NEED

