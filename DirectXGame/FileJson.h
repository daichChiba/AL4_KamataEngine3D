#pragma once
#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"
#include<KamataEngine.h>
using namespace KamataEngine;
class FileJson {
public:
	/// <summary>
	/// json�t�@�C���ǂݍ���
	/// </summary>
	/// <param name="filename_">�t�@�C����</param>
	/// <param name="DesiredClass">�ǂݍ��݂����ϐ��Q("firstStage"�Ȃ�)</param>
	/// <param name="variablename">�ϐ���("isClear"�Ȃ�)</param>
	/// <param name="classVariable">�ǂݍ��݂����ϐ��Q�ƕϐ���("first stage isClear:"�Ȃ�)</param>
	/// <returns></returns>
	static bool Read_Save(const char* filename_, const char* DesiredClass, const char* variablename, const char* classVariable);
	/// <summary>
	/// json�t�@�C���ǂݍ���
	/// </summary>
	/// <param name="filename_">�t�@�C����</param>
	/// <param name="DesiredClass">�ǂݍ��݂����ϐ��Q("firstStage"�Ȃ�)</param>
	/// <param name="variablename">�ϐ���("isClear"�Ȃ�)</param>
	/// <param name="classVariable">�ǂݍ��݂����ϐ��Q�ƕϐ���("first stage isClear:"�Ȃ�)</param>
	/// <param name="readVector">�ǂݍ��ރx�N�g��</param>
	/// <returns></returns>
	Vector3 Read_Save(const char* filename_, const char* DesiredClass, const char* variablename, const char* classVariable, Vector3 readVector);
};
