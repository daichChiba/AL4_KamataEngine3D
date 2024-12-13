#include "FileJson.h"
 // nlohmann::jsonライブラリのヘッダファイルをインクルード
using json = nlohmann::json;
using namespace std;
/// <summary>
/// jsonファイル読み込み
/// </summary>
/// <param name="filename_">ファイル名</param>
/// <param name="DesiredClass">読み込みたい変数群("firstStage"など)</param>
/// <param name="variablename">変数名("isClear"など)</param>
/// <param name="classVariable">読み込みたい変数群と変数名("first stage isClear:"など)</param>
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
		// 変数の値を出力
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
