// FileJson.h
#pragma once
#include "nlohmann/json.hpp"
#include <KamataEngine.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

using json = nlohmann::json;
using namespace KamataEngine;

namespace FileJson {

class FileAccessor {
public:
	FileAccessor(const std::string& filename);
	~FileAccessor();

	// JSONから値を読み込むための汎用的な関数
	template<typename T> T Read(const std::string& desiredClass, const std::string& variableName, const T& defaultValue) const;

	// JSONに値を書き込むための汎用的な関数
	template<typename T> void Write(const std::string& desiredClass, const std::string& variableName, const T& value);

	// Vector3を読み書きするための特殊化
	Vector3 ReadVector3(const std::string& desiredClass, const std::string& variableName, const Vector3& defaultValue) const;
	void WriteVector3(const std::string& desiredClass, const std::string& variableName, const Vector3& value);

	// ファイルからJSONデータをロードする
	void LoadJsonFromFile();

	// JSONデータをファイルに保存する
	void SaveJsonToFile();

private:
	std::string filename_;
	std::ifstream inputFile_;
	std::ofstream outputFile_;
	json jsonData_;
};

} // namespace FileJson