#include "IOManager.h"

#include <fstream>

bool IOManager::ReadFileToBuffer(std::string Path, std::vector<unsigned char>& Buffer)
{
	std::ifstream file(Path, std::ios::binary);
	if (file.fail()) {
		perror(Path.c_str());

		return false;
	}

	file.seekg(0, std::ios::end);

	int fileSize = file.tellg();
	file.seekg(0, std::ios::beg);

	fileSize -= file.tellg();

	Buffer.resize(fileSize);
	file.read((char*)&(Buffer[0]), fileSize);
	file.close();

	return true;
}

bool IOManager::ReadFileToString(std::string Path, std::string& String)
{
	String = "";

	std::ifstream file(Path);

	if (file.fail()) {
		perror(Path.c_str());

		return false;
	}

	std::string line;

	while (std::getline(file, line)) {
		String += line + "\n";
	}

	file.close();

	return true;
}

bool IOManager::ReadFileToStringVector(std::string Path, std::vector<std::string>& StringVector)
{
	StringVector.clear();

	std::ifstream file(Path);

	if (file.fail()) {
		perror(Path.c_str());

		return false;
	}

	std::string line;

	while (std::getline(file, line)) {
		StringVector.push_back(line);
	}

	file.close();

	return true;
}

void IOManager::WriteStringVectorToFile(std::string Path, std::vector<std::string> StringVector)
{
	std::ofstream file;

	file.open(Path);

	for (int i = 0; i < StringVector.size(); i++) {
		file << StringVector[i];
	}

	file.close();
}