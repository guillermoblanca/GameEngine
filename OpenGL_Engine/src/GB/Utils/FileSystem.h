#pragma once
#include "GB/Core.h"
#include "gbpch.h"
#include <filesystem>

namespace fs = std::filesystem;

namespace GB
{

	class FileParser
	{
	public:
		static const std::vector<std::string> GetFilesInDirectory(const char& path)
		{
			std::vector<std::string> paths;
			for (const auto& entry : fs::directory_iterator(&path))
			{
				paths.push_back(entry.path().u8string());
			}
			return paths;
		}
	private:

	};
}