#pragma once
#ifndef MESHDATA_H
#define MESHDATA_H

#include <glad/glad.h>
#include "../inner/shader.h"

#include <vector>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

#define MAX_BONE_INFLUENCE 4

//存储顶点里面的数据（对于单个来讲，位置，法线，还有对应的纹理坐标）
struct Vertex {
	glm::vec3	Position;
	glm::vec3   Normal;
	glm::vec2   TexCoords;

	glm::vec3 Tangent;
	// bitangent
	glm::vec3 Bitangent;
	//bone indexes which will influence this vertex
	int m_BoneIDs[MAX_BONE_INFLUENCE];
	//weights from each bone
	float m_Weights[MAX_BONE_INFLUENCE];
};

//索引，类型
struct Texture {
	unsigned int id;
	string type;

	string path;
};


class Mesh {
public:
	//函数
	Mesh(vector<Vertex> vertex, vector<Texture> texture, vector<unsigned int> indices);
	void draw(shader &Shader);


private:
//网格数据（包括我们之前的顶点还有纹理）
	vector<Vertex> m_vertex;
	vector<Texture> m_textures;
//索引
	vector<unsigned int> m_indices;

	/*  渲染数据  */
	unsigned int VAO, VBO, EBO;
	/*  函数  */
	void setupMesh();

};


#endif