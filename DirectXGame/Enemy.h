#pragma once
#include<KamataEngine.h>
using namespace KamataEngine;
class Enemy {
public:
	
	//行動フェーズ
	enum class Phase {
		Approach,	//接近する
		Leave,		//離脱する
	};

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


private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	//フェーズ
	Phase phase_ = Phase::Approach;

	// 接近フェーズの更新関数
	void ApproachUpdate();
	// 離脱フェーズの更新関数
	void LeaveUpdate();

};
