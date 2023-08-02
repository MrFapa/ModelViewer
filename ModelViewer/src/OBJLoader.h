#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <unordered_map>

#include "glm/vec3.hpp"
#include "Logger.h"
#include "Mesh.h"
#include "MeshDataType.h"

namespace fs = std::filesystem;

namespace Loading
{
	static MeshDataType MapOBJShortcutToEnum(const std::string& shortcut)
	{
		if (shortcut == "v")
			return MeshDataType::Position;
		else if (shortcut == "f")
			return MeshDataType::Index;
		else if (shortcut == "vn")
			return MeshDataType::Normal;
		else if (shortcut == "vt")
			return MeshDataType::UV;
		else
			return MeshDataType::Invalid;
	}



	static bool LoadOBJ(const std::string& objFilePath, Mesh& mesh)
	{
		//LogInfo("Starting to open file at path: {}", objFilePath.c_str());
		// Invalid file
		if (!fs::is_regular_file(objFilePath))
		{
			//LogInfo("Path: {}, seems to be no regular file", objFilePath.c_str());
			return false;
		}
			

		std::ifstream file(objFilePath);
		if(!file.is_open())
		{
			//LogInfo("Problems opening obj at {}", objFilePath.c_str());
			return false;
		}

		// ref
		std::string name = "nameless";
		std::vector<glm::vec3> positions;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> uvs;
		std::vector<unsigned int> pIndices;
		std::vector<unsigned int> nIndices;
		std::vector<unsigned int> uIndices;


		std::string line;
		
		while(std::getline(file, line))
		{
			if (line.empty())
				continue;

			std::vector<std::string> split;
			std::stringstream ss(line);
			std::string s;
			while(std::getline(ss, s, ' '))
			{
				split.push_back(s);
			}

			MeshDataType key = MapOBJShortcutToEnum(split[0]);
			switch (key)
			{
			case MeshDataType::Position:
				if (split.size() != 4)
				{
					LogError("Obj vertices are not 3 dimensional");
					return false;
				}
				positions.push_back({ std::stof(split[1]) , std::stof(split[2]) , std::stof(split[3]) });

				break;
			case MeshDataType::Index:

				if (split.size() != 4)
				{
					LogError("Obj has to be triangulated");
					return {};
				}

				for (int i = 1; i < split.size(); i++)
				{
					std::string pIndex;
					std::string uIndex;
					std::string nIndex;
					std::stringstream fss(split[i]);
					std::getline(fss, pIndex, '/');
					std::getline(fss, uIndex, '/');
					std::getline(fss, nIndex, '/');
					pIndices.push_back(std::stoi(pIndex));
					uIndices.push_back(std::stoi(uIndex));
					nIndices.push_back(std::stoi(nIndex));
				}
				break;
			case MeshDataType::Normal:
				if (split.size() != 4)
				{
					LogError("Obj has incorrect normals");
					return false;
				}
				normals.push_back({ std::stof(split[1]) , std::stof(split[2]) , std::stof(split[3]) });
				break;
			case MeshDataType::UV:
				if (split.size() != 3)
				{
					LogError("Obj has incorrect normals");
					return false;
				}
				uvs.push_back({ std::stof(split[1]) , std::stof(split[2])});
				break;
			default:
				break;
			}

		}

		mesh.SetName(name);
		mesh.SetPositions(positions);
		mesh.SetNormals(normals);
		mesh.SetUVs(uvs);

		std::vector<Vertex> vertices;
		for(int i = 0; i < pIndices.size(); i++)
		{
			Vertex currentVertex = { positions[pIndices[i] - 1], normals[nIndices[i] - 1], uvs[uIndices[i] - 1] };
			vertices.push_back(currentVertex);
		}
		mesh.SetVertices(vertices);
		//mesh.SetIndices(indices);
		LogInfo("Loading the Model was successful");
		file.close();

		return true;

	}
}
