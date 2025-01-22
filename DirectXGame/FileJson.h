#pragma once
#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"
#include<KamataEngine.h>
using namespace KamataEngine;
class FileJson {
public:
	/// <summary>
	/// jsonBool�t�@�C���ǂݍ���
	/// </summary>
	/// <param name="filename_">�t�@�C����</param>
	/// <param name="DesiredClass">�ǂݍ��݂����ϐ��Q("firstStage"�Ȃ�)</param>
	/// <param name="variablename">�ϐ���("isClear"�Ȃ�)</param>
	/// <param name="classVariable">�ǂݍ��݂����ϐ��Q�ƕϐ���("first stage isClear:"�Ȃ�)</param>
	/// <returns></returns>
	static bool Read_BoolSave(const char* filename_, const char* DesiredClass, const char* variablename, const char* classVariable);
	/// <summary>
	/// jsonVector3�t�@�C���ǂݍ���
	/// </summary>
	/// <param name="filename_">�t�@�C����</param>
	/// <param name="DesiredClass">�ǂݍ��݂����ϐ��Q("firstStage"�Ȃ�)</param>
	/// <param name="variablename">�ϐ���("isClear"�Ȃ�)</param>
	/// <param name="classVariable">�ǂݍ��݂����ϐ��Q�ƕϐ���("first stage isClear:"�Ȃ�)</param>
	/// <param name="readVector">�ǂݍ��ރx�N�g��</param>
	/// <returns></returns>
	Vector3 Read_Vector3Save(const char* filename_, const char* DesiredClass, const char* variablename, const char* classVariable, Vector3 readVector);

	/// <summary>
	/// jsonInt�t�@�C���ǂݍ���
	/// </summary>
	/// <param name="filename_">�t�@�C����</param>
	/// <param name="DesiredClass">�ǂݍ��݂����ϐ��Q("firstStage"�Ȃ�)</param>
	/// <param name="variablename">�ϐ���("isClear"�Ȃ�)</param>
	/// <param name="classVariable">�ǂݍ��݂����ϐ��Q�ƕϐ���("first stage isClear:"�Ȃ�)</param>
	/// <param name="readInt">�ǂݍ���int�^�̒l</param>
	/// <returns></returns>
	static int Read_IntSave(const char* filename_, const char* DesiredClass, const char* variablename, const char* classVariable, int readInt);

	/// <summary>
	/// jsonBool�t�@�C����������
	/// </summary>
	/// <param name="filename_">�t�@�C����</param>
	/// <param name="DesiredClass">�������݂����ϐ��Q("firstStage"�Ȃ�)</param>
	/// <param name="variablename">�ϐ���("isClear"�Ȃ�)</param>
	/// <param name="classVariable">�������݂����ϐ��Q�ƕϐ���("first stage isClear:"�Ȃ�)</param>
	/// <returns></returns>
	static bool White_BoolSave(const char* filename_, const char* DesiredClass, const char* variablename, const int classVariable);

	/// <summary>
	/// jsonVector3�t�@�C����������
	/// </summary>
	/// <param name="filename_">�t�@�C����</param>
	/// <param name="DesiredClass">�������݂����ϐ��Q("firstStage"�Ȃ�)</param>
	/// <param name="variablename">�ϐ���("isClear"�Ȃ�)</param>
	/// <param name="whiteVector">��������Vector3</param>
	/// <returns></returns>
	Vector3 White_Vector3Save(const char* filename_, const char* DesiredClass, const char* variablename, Vector3 whiteVector);

	/// <summary>
	/// jsonInt�t�@�C����������
	/// </summary>
	/// <param name="filename_">�t�@�C����</param>
	/// <param name="DesiredClass">�������݂����ϐ��Q("firstStage"�Ȃ�)</param>
	/// <param name="variablename">�ϐ���("isClear"�Ȃ�)</param>
	/// <param name="whiteInt">�ǂݍ���int�^�̒l</param>
	/// <returns></returns>
	static int White_IntSave(const char* filename_, const char* DesiredClass, const char* variablename, int whiteInt);

};
