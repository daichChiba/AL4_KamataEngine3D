#include "FileJson.h"
#include <nlohmann/json.hpp>
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
bool FileJson::Read_BoolSave(const char* filename_, const char* DesiredClass, const char* variablename, const char* classVariable) {
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
/// <summary>
/// jsonファイル読み込み
/// </summary>
/// <param name="filename_">ファイル名</param>
/// <param name="DesiredClass">読み込みたい変数群("firstStage"など)</param>
/// <param name="variablename">変数名("isClear"など)</param>
/// <param name="classVariable">読み込みたい変数群と変数名("first stage isClear:"など)</param>
/// <param name="readVector">読み込むベクトル</param>
/// <returns></returns>
Vector3 FileJson::Read_Vector3Save(const char* filename_, const char* DesiredClass, const char* variablename, const char* classVariable, Vector3 readVector) {
	try {
		// ファイルを開く
		std::ifstream file(filename_);
		if (!file.is_open()) {
			std::cerr << "Error: Cannot open file " << filename_ << std::endl;
			return readVector;
		}

		// JSONをパース
		nlohmann::json jsonData;
		file >> jsonData;

		// 指定されたクラスを検索
		if (jsonData.contains(DesiredClass)) {
			auto& classData = jsonData[DesiredClass];

			// クラス内の変数を検索
			if (classData.contains(classVariable)) {
				auto& variableData = classData[classVariable];

				// 変数名を確認し、Vector3データを取得
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

	// エラー時はデフォルト値を返す
	return readVector;
}

/// <summary>
/// jsonIntファイル読み込み
/// </summary>
/// <param name="filename_">ファイル名</param>
/// <param name="DesiredClass">読み込みたい変数群("firstStage"など)</param>
/// <param name="variablename">変数名("isClear"など)</param>
/// <param name="classVariable">読み込みたい変数群と変数名("first stage isClear:"など)</param>
/// <param name="readInt">読み込むint型の値</param>
/// <returns></returns>
int FileJson::Read_IntSave(const char* filename_, const char* DesiredClass, const char* variablename, const char* classVariable, int readInt) {
	// JSONオブジェクトの作成
	json m_json;

	// ファイルが存在する場合は既存のデータを読み込む
	ifstream input_file(filename_);
	if (input_file.is_open()) {
		try {
			input_file >> m_json;
		} catch (nlohmann::json::parse_error& e) {
			cerr << "JSON parse error: " << e.what() << endl;
			input_file.close();
			return 0; // デフォルト値を返す
		}
		input_file.close();
	}

	// 指定されたクラスと変数名にintデータを保存
	m_json[DesiredClass][classVariable][variablename] = readInt;

	// JSONデータをファイルに書き込む
	ofstream writing_file(filename_, ios::out);
	if (!writing_file.is_open()) {
		cerr << "Cannot open file: " << filename_ << endl;
		return 0; // デフォルト値を返す
	}

	writing_file << m_json.dump(4) << endl; // 4スペースのインデントで整形
	writing_file.close();

	// 保存したintデータを返す
	return readInt;
}

/// <summary>
/// jsonBoolファイル書き込み
/// </summary>
/// <param name="filename_">ファイル名</param>
/// <param name="DesiredClass">読み込みたい変数群("firstStage"など)</param>
/// <param name="variablename">変数名("isClear"など)</param>
/// <param name="classVariable">読み込みたい変数群と変数名("first stage isClear:"など)</param>
/// <returns></returns>
bool FileJson::White_BoolSave(const char* filename_, const char* DesiredClass, const char* variablename, const int classVariable) {
	// JSONオブジェクトの作成
	json m_json;

	// ファイルが存在する場合は既存のデータを読み込む
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

	// JSONデータをファイルに書き込む
	ofstream writing_file(filename_, ios::out);
	if (!writing_file.is_open()) {
		cerr << "Cannot open file: " << filename_ << endl;
		return true;
	}

	writing_file << m_json.dump(4) << endl; // 4スペースのインデントで整形
	writing_file.close();

	return false;
}
/// <summary>
/// jsonVector3ファイル書き込み
/// </summary>
/// <param name="filename_">ファイル名</param>
/// <param name="DesiredClass">書き込みたい変数群("firstStage"など)</param>
/// <param name="variablename">変数名("isClear"など)</param>
/// <param name="whiteVector">書き込むVector3</param>
/// <returns></returns>
Vector3 FileJson::White_Vector3Save(const char* filename_, const char* DesiredClass, const char* variablename, Vector3 whiteVector) {
	// JSONオブジェクトの作成
	json m_json;

	// ファイルが存在する場合は既存のデータを読み込む
	ifstream input_file(filename_);
	if (input_file.is_open()) {
		try {
			input_file >> m_json;
		} catch (nlohmann::json::parse_error& e) {
			cerr << "JSON parse error: " << e.what() << endl;
			input_file.close();
			return Vector3(); // デフォルト値を返す
		}
		input_file.close();
	}

	// 指定されたクラスと変数名にVector3データを保存
	m_json[DesiredClass][variablename] = {whiteVector.x, whiteVector.y, whiteVector.z};

	// JSONデータをファイルに書き込む
	ofstream writing_file(filename_, ios::out);
	if (!writing_file.is_open()) {
		cerr << "Cannot open file: " << filename_ << endl;
		return Vector3(); // デフォルト値を返す
	}

	writing_file << m_json.dump(4) << endl; // 4スペースのインデントで整形
	writing_file.close();

	// 保存したVector3データを返す
	return whiteVector;
}

/// <summary>
/// jsonIntファイル書き込み
/// </summary>
/// <param name="filename_">ファイル名</param>
/// <param name="DesiredClass">書き込みたい変数群("firstStage"など)</param>
/// <param name="variablename">変数名("isClear"など)</param>
/// <param name="whiteInt">読み込むint型の値</param>
/// <returns></returns>
int FileJson::White_IntSave(const char* filename_, const char* DesiredClass, const char* variablename, int whiteInt) {
	// JSONオブジェクトの作成
	json m_json;

	// ファイルが存在する場合は既存のデータを読み込む
	ifstream input_file(filename_);
	if (input_file.is_open()) {
		try {
			input_file >> m_json;
		} catch (nlohmann::json::parse_error& e) {
			cerr << "JSON parse error: " << e.what() << endl;
			input_file.close();
			return int(); // デフォルト値を返す
		}
		input_file.close();
	}

	// 指定されたクラスと変数名にVector3データを保存
	m_json[DesiredClass][variablename] = {whiteInt};

	// JSONデータをファイルに書き込む
	ofstream writing_file(filename_, ios::out);
	if (!writing_file.is_open()) {
		cerr << "Cannot open file: " << filename_ << endl;
		return int(); // デフォルト値を返す
	}

	writing_file << m_json.dump(4) << endl; // 4スペースのインデントで整形
	writing_file.close();

	return whiteInt;
}
