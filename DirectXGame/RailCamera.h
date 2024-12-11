#pragma once
#include"KamataEngine.h"
using namespace KamataEngine;
/// <summary>
/// レールカメラ
/// </summary>
class RailCamera {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Vector3& pos, Vector3& rotate, Camera& camera);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// カメラ
	Camera* camera_;

};
