#pragma once

#include "../MeshData/MeshData.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//using namespace std;

class Model
{
public:
    Model(string const& path, bool gamma = false) : gammaCorrection(gamma) {
   loadModel(path);
     }

    vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    bool gammaCorrection;
    void Draw(shader& Shader);
private:
    /*  模型数据  */
    vector<Mesh> meshes;
    string directory;
    /*  函数   */
    void loadModel(string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
        string typeName);
    unsigned int TextureFromFile(const char* path, const string& directory, bool gamma);
}
;
