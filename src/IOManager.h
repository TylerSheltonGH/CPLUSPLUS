#pragma once
#include <vector>
#include <string>

class IOManager
{
public:
	static bool ReadFileToBuffer(std::string Path, std::vector<unsigned char>& Buffer);

	static bool ReadFileToString(std::string Path, std::string& String);

	static bool ReadFileToStringVector(std::string Path, std::vector<std::string>& StringVector);

	static void WriteStringVectorToFile(std::string Path, std::vector<std::string> StringVector);
};