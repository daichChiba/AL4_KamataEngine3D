#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;
#include "../DirectXGame/PlayerBullet.h"

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
	void Initialize(Model* model, uint32_t textureHandle, Vector3& pos);

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

	/// <summary>
	/// ワールド座標を取得
	/// </summary>
	Vector3 GetWorldPosition();

	Vector3 GetWorldRotate();


	// 衝突を検知したら呼び出されるコールバック関数
	void OnCollision();

	//弾リストを取得
	const std::list<PlayerBullet*>& GetBullets() const { return bullets_; }

	//半径を取得
	float GetRadius() { return radius_; }


	//setter
	void SetParent(const WorldTransform* parent) { worldTransform_.parent_ = parent; }

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// キーボード入力
	Input* input_ = nullptr;

	// 半径
	float radius_ = 6.0f;


	// 弾
	std::list<PlayerBullet*> bullets_;
};