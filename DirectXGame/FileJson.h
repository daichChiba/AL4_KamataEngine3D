#pragma once
#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"
#include<KamataEngine.h>
using namespace KamataEngine;
namespace FileJson {
	/// <summary>
	/// jsonBoolファイル読み込み
	/// </summary>
	/// <param name="filename_">ファイル名</param>
	/// <param name="DesiredClass">読み込みたい変数群("firstStage"など)</param>
	/// <param name="variablename">変数名("isClear"など)</param>
	/// <param name="classVariable">読み込みたい変数群と変数名("first stage isClear:"など)</param>
	/// <returns></returns>
	static bool Read_BoolSave(const char* filename_, const char* DesiredClass, const char* variablename, const char* classVariable);
	/// <summary>
	/// jsonVector3ファイル読み込み
	/// </summary>
	/// <param name="filename_">ファイル名</param>
	/// <param name="DesiredClass">読み込みたい変数群("firstStage"など)</param>
	/// <param name="variablename">変数名("isClear"など)</param>
	/// <param name="classVariable">読み込みたい変数群と変数名("first stage isClear:"など)</param>
	/// <param name="readVector">読み込むベクトル</param>
	/// <returns></returns>
	Vector3 Read_Vector3Save(const char* filename_, const char* DesiredClass, const char* variablename, const char* classVariable, Vector3 readVector);

	/// <summary>
	/// jsonIntファイル読み込み
	/// </summary>
	/// <param name="filename_">ファイル名</param>
	/// <param name="DesiredClass">読み込みたい変数群("firstStage"など)</param>
	/// <param name="variablename">変数名("isClear"など)</param>
	/// <param name="classVariable">読み込みたい変数群と変数名("first stage isClear:"など)</param>
	/// <param name="readInt">読み込むint型の値</param>
	/// <returns></returns>
	static int Read_IntSave(const char* filename_, const char* DesiredClass, const char* variablename, const char* classVariable, int readInt);

	/// <summary>
	/// jsonBoolファイル書き込み
	/// </summary>
	/// <param name="filename_">ファイル名</param>
	/// <param name="DesiredClass">書き込みたい変数群("firstStage"など)</param>
	/// <param name="variablename">変数名("isClear"など)</param>
	/// <param name="classVariable">書き込みたい変数群と変数名("first stage isClear:"など)</param>
	/// <returns></returns>
	static bool White_BoolSave(const char* filename_, const char* DesiredClass, const char* variablename, const int classVariable);

	/// <summary>
	/// jsonVector3ファイル書き込み
	/// </summary>
	/// <param name="filename_">ファイル名</param>
	/// <param name="DesiredClass">書き込みたい変数群("firstStage"など)</param>
	/// <param name="variablename">変数名("isClear"など)</param>
	/// <param name="whiteVector">書き込むVector3</param>
	/// <returns></returns>
	Vector3 White_Vector3Save(const char* filename_, const char* DesiredClass, const char* variablename, Vector3 whiteVector);

	/// <summary>
	/// jsonIntファイル書き込み
	/// </summary>
	/// <param name="filename_">ファイル名</param>
	/// <param name="DesiredClass">書き込みたい変数群("firstStage"など)</param>
	/// <param name="variablename">変数名("isClear"など)</param>
	/// <param name="whiteInt">読み込むint型の値</param>
	/// <returns></returns>
	static int White_IntSave(const char* filename_, const char* DesiredClass, const char* variablename, int whiteInt);

};
