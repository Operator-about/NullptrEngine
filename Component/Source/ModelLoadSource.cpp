#include<ModelLoadComponent.h>

void ModelLoad::Load(string File) 
{
	Importer Model;
	const aiScene* Scene = Model.ReadFile(File, aiProcess_Triangulate);

	Node(Scene->mRootNode, Scene);
}

void ModelLoad::Node(aiNode* Node, const aiScene* Scene) 
{
	for (;;) 
	{

	}
	for(;;)
	{
	
	}
}