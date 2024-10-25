#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;
#include"../DirectXGame/PlayerBullet.h"

/// <summary>
/// 自キャラ
/// </summary>
class Player {
public:
	~Player();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model>モデル</param>
	/// <param name="textureHandle>テクスチャハンドル</param>
	void Initialize(Model* model, uint32_t textureHandle);


	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 旋回(回転)
	/// </summary>
	void Rotate();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="camera>camera(参照渡し)</param>
	void Draw(Camera& camera);

	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack();

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// キーボード入力
	Input* input_ = nullptr;

	//弾
	std::list<PlayerBullet*> bullets_ ;
};
