#pragma once
#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"
#include<KamataEngine.h>
using namespace KamataEngine;
class FileJson {
public:
	/// <summary>
	/// jsonファイル読み込み
	/// </summary>
	/// <param name="filename_">ファイル名</param>
	/// <param name="DesiredClass">読み込みたい変数群("firstStage"など)</param>
	/// <param name="variablename">変数名("isClear"など)</param>
	/// <param name="classVariable">読み込みたい変数群と変数名("first stage isClear:"など)</param>
	/// <returns></returns>
	static bool Read_Save(const char* filename_, const char* DesiredClass, const char* variablename, const char* classVariable);
	/// <summary>
	/// jsonファイル読み込み
	/// </summary>
	/// <param name="filename_">ファイル名</param>
	/// <param name="DesiredClass">読み込みたい変数群("firstStage"など)</param>
	/// <param name="variablename">変数名("isClear"など)</param>
	/// <param name="classVariable">読み込みたい変数群と変数名("first stage isClear:"など)</param>
	/// <param name="readVector">読み込むベクトル</param>
	/// <returns></returns>
	Vector3 Read_Save(const char* filename_, const char* DesiredClass, const char* variablename, const char* classVariable, Vector3 readVector);
};
