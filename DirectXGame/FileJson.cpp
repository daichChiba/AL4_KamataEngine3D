#include "FileJson.h"
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
