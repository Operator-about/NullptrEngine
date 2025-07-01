#include<assimp/config.h>
#include<assimp/scene.h>
#include<assimp/postprocess.h>
#include<assimp/Importer.hpp>
#include<glm/gtx/transform.hpp>
#include<iostream>
#include<string>
using namespace std;
using namespace glm;
using namespace Assimp;

class ModelLoad
{

public:

	ModelLoad(string File)
	{
		Load(File);
	}

private:
	void Load(string File);
	void Node(aiNode* Node, const aiScene* Scene);
};