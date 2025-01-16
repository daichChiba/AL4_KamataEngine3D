#include "FileJson.h"
#include <nlohmann/json.hpp>
 // nlohmann::json���C�u�����̃w�b�_�t�@�C�����C���N���[�h
using json = nlohmann::json;
using namespace std;
/// <summary>
/// json�t�@�C���ǂݍ���
/// </summary>
/// <param name="filename_">�t�@�C����</param>
/// <param name="DesiredClass">�ǂݍ��݂����ϐ��Q("firstStage"�Ȃ�)</param>
/// <param name="variablename">�ϐ���("isClear"�Ȃ�)</param>
/// <param name="classVariable">�ǂݍ��݂����ϐ��Q�ƕϐ���("first stage isClear:"�Ȃ�)</param>
/// <returns></returns>
bool FileJson::Read_Save(const char* filename_, const char* DesiredClass, const char* variablename, const char* classVariable) {
	string fileName = filename_;

	ifstream reading_file(fileName);
	if (!reading_file.is_open()) {
		cerr << "Cannot open file: " << fileName << endl;
		return true;
	}

	json m_json;
	try {
		reading_file >> m_json;
	} catch (nlohmann::json::parse_error& e) {
		cerr << "JSON parse error: " << e.what() << endl;
		reading_file.close();
		return true;
	}
	reading_file.close();

	string DesiredClass_ = DesiredClass;
	string variableName_ = variablename;
	string classVariable_ = classVariable;

	try {
		bool StageClear = m_json.at(DesiredClass_).at(variableName_).get<int>() == 1;
		// �ϐ��̒l���o��
		cout << classVariable_ << (StageClear ? "Yes" : "No") << endl;
		return StageClear;
	} catch (nlohmann::json::type_error& e) {
		cerr << "Type error: " << e.what() << endl;
		return 1;
	} catch (nlohmann::json::out_of_range& e) {
		cerr << "Out of range error: " << e.what() << endl;
		return 1;
	}

	return false;
}
/// <summary>
/// json�t�@�C���ǂݍ���
/// </summary>
/// <param name="filename_">�t�@�C����</param>
/// <param name="DesiredClass">�ǂݍ��݂����ϐ��Q("firstStage"�Ȃ�)</param>
/// <param name="variablename">�ϐ���("isClear"�Ȃ�)</param>
/// <param name="classVariable">�ǂݍ��݂����ϐ��Q�ƕϐ���("first stage isClear:"�Ȃ�)</param>
/// <param name="readVector">�ǂݍ��ރx�N�g��</param>
/// <returns></returns>
Vector3 FileJson::Read_Save(const char* filename_, const char* DesiredClass, const char* variablename, const char* classVariable, Vector3 readVector) {
	try {
		// �t�@�C�����J��
		std::ifstream file(filename_);
		if (!file.is_open()) {
			std::cerr << "Error: Cannot open file " << filename_ << std::endl;
			return readVector;
		}

		// JSON���p�[�X
		nlohmann::json jsonData;
		file >> jsonData;

		// �w�肳�ꂽ�N���X������
		if (jsonData.contains(DesiredClass)) {
			auto& classData = jsonData[DesiredClass];

			// �N���X���̕ϐ�������
			if (classData.contains(classVariable)) {
				auto& variableData = classData[classVariable];

				// �ϐ������m�F���AVector3�f�[�^���擾
				if (variableData.contains(variablename)) {
					auto vectorData = variableData[variablename];
					if (vectorData.contains("x") && vectorData.contains("y") && vectorData.contains("z")) {
						return Vector3(vectorData["x"].get<float>(), vectorData["y"].get<float>(), vectorData["z"].get<float>());
					}
				}
			}
		}
	} catch (const std::exception& e) {
		std::cerr << "Error: Exception while reading JSON: " << e.what() << std::endl;
	}

	// �G���[���̓f�t�H���g�l��Ԃ�
	return readVector;
}

/// <summary>
/// jsonBool�t�@�C����������
/// </summary>
/// <param name="filename_">�t�@�C����</param>
/// <param name="DesiredClass">�ǂݍ��݂����ϐ��Q("firstStage"�Ȃ�)</param>
/// <param name="variablename">�ϐ���("isClear"�Ȃ�)</param>
/// <param name="classVariable">�ǂݍ��݂����ϐ��Q�ƕϐ���("first stage isClear:"�Ȃ�)</param>
/// <returns></returns>
bool FileJson::White_Save(const char* filename_, const char* DesiredClass, const char* variablename, const int classVariable) {
	// JSON�I�u�W�F�N�g�̍쐬
	json m_json;

	// �t�@�C�������݂���ꍇ�͊����̃f�[�^��ǂݍ���
	ifstream input_file(filename_);
	if (input_file.is_open()) {
		try {
			input_file >> m_json;
		} catch (nlohmann::json::parse_error& e) {
			cerr << "JSON parse error: " << e.what() << endl;
		}
		input_file.close();
	}

	m_json[DesiredClass] = {
	    {variablename, classVariable}
    };

	// JSON�f�[�^���t�@�C���ɏ�������
	ofstream writing_file(filename_, ios::out);
	if (!writing_file.is_open()) {
		cerr << "Cannot open file: " << filename_ << endl;
		return true;
	}

	writing_file << m_json.dump(4) << endl; // 4�X�y�[�X�̃C���f���g�Ő��`
	writing_file.close();

	return false;
}
