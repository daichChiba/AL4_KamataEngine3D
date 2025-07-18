#pragma once
#include<KamataEngine.h>
#include "../Shooting/player/Player.h"
#include "../Shooting/enemy/Enemy.h"
#include <vector>
#include "../Shooting/SkyDome.h"
#include "../Shooting/RailCamera.h"

using namespace KamataEngine;

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 衝突判定と応答
	/// </summary>
	void CheckAllCollisions();

	bool IsFinished() const { return finished_; }
	bool IsClear() const { return isClear; }

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;
	// 敵キャラのテクスチャハンドル
	uint32_t enemyTextureHandle_ = 0;

	// 3Dモデルデータ
	Model* model_ = nullptr;

	// カメラ
	Camera camera_;

	// デバックカメラ有効
	bool isDebugCameraActive_ = false;

	// デバックカメラ
	DebugCamera* debugCamera_ = nullptr;

	// 自キャラ
	Player* player_ = nullptr;

	// 敵キャラ
	Enemy* enemy_ = nullptr;

	// 天球
	SkyDome* skyDome_ = nullptr;

	// 天球モデル
	Model* modelSkydome_ = nullptr;

	// レールカメラ
	RailCamera* railCamera_ = nullptr;

	// 終了フラグ
	bool finished_ = false;

	bool isClear = false;
	// サウンドデータハンドル
	uint32_t soundDataHandle_ = 0;
	// 音声再生ハンドル
	uint32_t voiceHandle_ = 0;
};
