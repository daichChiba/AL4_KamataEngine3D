#pragma once
#include<KamataEngine.h>
using namespace KamataEngine;
#include "EnemyBullet.h"

//自機クラスの前方宣言
class Player;

class Enemy {
public:
	
	//行動フェーズ
	enum class Phase {
		Approach,	//接近する
		Leave,		//離脱する
	};

	//デストラクタ
	~Enemy();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model>モデル</param>
	/// <param name="textureHandle>テクスチャハンドル</param>
	void Initialize(Model* model, uint32_t textureHandle,const Vector3& pos);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="camera>camera(参照渡し)</param>
	void Draw(Camera& camera);

	/// <summary>
	/// 弾発射
	/// </summary>
	void Fire();

	// 発射間隔
	static const int kFireInterval = 60;

	//接近フェーズ初期化
	void ApproachInitialize();

	// 接近フェーズの更新関数
	void ApproachUpdate();
	// 離脱フェーズの更新関数
	void LeaveUpdate();

	//Player設定
	void SetPlayer(Player* player) { player_ = player; }

	/// <summary>
	/// ワールド座標を取得
	/// </summary>
	Vector3 GetWorldPosition();


private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	//フェーズ
	Phase phase_ = Phase::Approach;


	// 弾
	std::list<EnemyBullet*> bullets_;

	//発射タイマー
	int32_t FireTimer = 0;

	//自キャラ
	Player* player_ = nullptr;

};
