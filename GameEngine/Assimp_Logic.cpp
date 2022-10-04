#include "Assimp_Logic.h"

void Assimp_Logic::LoadFile(string file_path)
{
	const aiScene* scene = aiImportFile(file_path.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr && scene->HasMeshes())
	{
		//Iterate scene meshes
		for (int i = 0; i < scene->mNumMeshes; i++) {
			Mesh mesh;
			//Copy fbx mesh info to Mesh struct
			mesh.num_vertices = scene->mMeshes[i]->mNumVertices;
			mesh.vertices = new float[mesh.num_vertices * 3];
			memcpy(mesh.vertices, scene->mMeshes[i]->mVertices, sizeof(float) * mesh.num_vertices * 3);
			LOG("New mesh with %d vertices", mesh.num_vertices);

			//Load Faces
			if (scene->mMeshes[i]->HasFaces())
			{
				//Copy fbx mesh indices info to Mesh struct
				mesh.num_indices = scene->mMeshes[i]->mNumFaces * 3;
				mesh.indices = new uint[mesh.num_indices]; // assume each face is a triangle
				
				//Iterate mesh faces
				for (uint j = 0; j < scene->mMeshes[i]->mNumFaces; ++j)
				{
					//Check that faces are triangles
					if (scene->mMeshes[i]->mFaces[j].mNumIndices != 3) {
						LOG("WARNING, geometry face with != 3 indices!");
					}
					else {
						memcpy(&mesh.indices[i * 3], scene->mMeshes[i]->mFaces[j].mIndices, 3 * sizeof(uint));
					}
				}
			}

			//Add mesh to array
			meshes.push_back(mesh);
		}

		aiReleaseImport(scene);
	}
	else
		LOG("Error loading scene % s", file_path);
}

void Assimp_Logic::Init()
{
	// Stream log messages to Debug window
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);

}

void Assimp_Logic::CleanUp()
{
	// detach log stream
	aiDetachAllLogStreams();
}