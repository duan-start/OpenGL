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

//�洢������������ݣ����ڵ���������λ�ã����ߣ����ж�Ӧ���������꣩
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

//����������
struct Texture {
	unsigned int id;
	string type;

	string path;
};


class Mesh {
public:
	//����
	Mesh(vector<Vertex> vertex, vector<Texture> texture, vector<unsigned int> indices);
	void draw(shader &Shader);


private:
//�������ݣ���������֮ǰ�Ķ��㻹������
	vector<Vertex> m_vertex;
	vector<Texture> m_textures;
//����
	vector<unsigned int> m_indices;

	/*  ��Ⱦ����  */
	unsigned int VAO, VBO, EBO;
	/*  ����  */
	void setupMesh();

};


#endif