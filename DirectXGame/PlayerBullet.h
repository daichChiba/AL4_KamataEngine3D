#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;

/// <summary>
/// 自キャラの弾
/// </summary>
class PlayerBullet {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model>モデル</param>
	/// <param name="textureHandle>テクスチャハンドル</param>
	void Initialize(Model* model, const Vector3& pos,const Vector3& velocity);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="camera>camera(参照渡し)</param>
	void Draw(const Camera& camera);

	// 寿命<frm>
	static const int32_t kLifeTime = 60 * 3;

	bool IsDead() const { return isDead_; }

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	//速度
	Vector3 velocity_;

	//デスタイマー
	int32_t deathTimer_ = kLifeTime;
	//デスフラグ
	bool isDead_ = false;
};
