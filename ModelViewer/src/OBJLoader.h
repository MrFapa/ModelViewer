#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <filesystem>

#include "glm/vec3.hpp"
#include "Logger.h"

namespace fs = std::filesystem;

namespace Loading
{
	struct ModelData
	{
		std::string modelName;
		std::vector<glm::vec3> vertexCoord;
		std::vector<int> indices;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec3> texCoord;
	};

	static ModelData LoadOBJ(fs::path objFilePath)
	{
		//LogInfo("Starting to open file at path: {}", objFilePath.c_str());
		// Invalid file
		if (!fs::is_regular_file(objFilePath))
		{
			//LogInfo("Path: {}, seems to be no regular file", objFilePath.c_str());
			return {};
		}
			

		std::ifstream file(objFilePath);
		if(!file.is_open())
		{
			//LogInfo("Problems opening obj at {}", objFilePath.c_str());
			return {};
		}

		ModelData res = {};

		
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

			if (split[0] == "o") {
				res.modelName = line.substr(2, line.length());
			}
			else if (split[0] == "v") {
				if (split.size() == 4)
				{
					float x = std::stof(split[1]);
					float y = std::stof(split[2]);
					float z = std::stof(split[3]);
					res.vertexCoord.push_back({ x, y, z });
				}
				else
				{
					LogError("Obj vertices are not 3 dimensional");
					return {};
				}
			} else if(split[0] == "vn")
			{
				if (split.size() == 4)
				{
					float x = std::stof(split[1]);
					float y = std::stof(split[2]);
					float z = std::stof(split[3]);
					res.normals.push_back({ x, y, z });
				}
				else
				{
					LogError("Obj has incorrect normals");
					return {};
				}
			} else if(split[0] == "f")
			{
				if(split.size() != 4)
				{
					LogError("Obj has to be triangulated");
					return {};
				}

				for(int i = 1; i < split.size(); i++)
				{
					std::string sIndex;
					std::stringstream fss(split[i]);
					std::getline(fss, sIndex, '/');
					res.indices.push_back(std::stoi(sIndex));
				}
			}
		}

		file.close();

		return res;

	}
}
