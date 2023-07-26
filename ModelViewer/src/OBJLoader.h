#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <filesystem>

#include "glm/vec3.hpp"
#include "Logger.h"
#include "Mesh.h"
#include <unordered_map>

namespace fs = std::filesystem;

namespace Loading
{
	static Mesh::MeshDataType MapOBJShortcutToMeshDataType(const std::string& shortcut)
	{
		switch(shortcut)
		{
		case "v":
			return Mesh::MeshDataType::Position;
		case "f":
			return Mesh::MeshDataType::Index;
		case "vn":
			return Mesh::MeshDataType::Normal;
		case "vt":
			return Mesh::MeshDataType::UV;
		}
	}



	static bool LoadOBJ(fs::path objFilePath, std::unordered_map<Mesh::MeshDataType, std::vector<float>>& meshData)
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

			Mesh::MeshDataType key = MapOBJShortcutToMeshDataType(split[0]);
			std::vector<float> data = meshData[key];
			switch (key)
			{
			case Mesh::MeshDataType::Position:
				if (split.size() != 4)
				{
					LogError("Obj vertices are not 3 dimensional");
					return false;
				}

				data.push_back(std::stof(split[1]));
				data.push_back(std::stof(split[2]));
				data.push_back(std::stof(split[3]));

				break;
			case Mesh::MeshDataType::Index:

				if (split.size() != 4)
				{
					LogError("Obj has to be triangulated");
					return {};
				}

				for (int i = 1; i < split.size(); i++)
				{
					std::string sIndex;
					std::stringstream fss(split[i]);
					std::getline(fss, sIndex, '/');
					data.push_back(std::stof(sIndex));
				}
				break;
			case Mesh::MeshDataType::Normal:
				if (split.size() != 4)
				{
					LogError("Obj has incorrect normals");
					return false;
				}
				
				data.push_back(std::stof(split[1]));
				data.push_back(std::stof(split[2]));
				data.push_back(std::stof(split[3]));
				
				break;
			case Mesh::MeshDataType::UV:
				break;
			default:
				break;
			}

		}

		file.close();

		return true;

	}
}
