#include "RailCamera.h"
#include "MathUtliltyForText.h"
using namespace KamataEngine;
using namespace MathUtility;

void RailCamera::Initialize(Vector3& pos, Vector3& rotate, Camera& camera) {
	// ワールドトランスフォームの初期設定
	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;
	worldTransform_.rotation_ = rotate;

	// カメラの初期化
	camera_ = &camera;
}

void RailCamera::Update() {

	// ワールドトランスフォームの座標の数値を加算したりする(移動)

	// ワールドトランスフォームの座標の数値を加算したりする(移動)

	// カメラオブジェクトのワールド行列からビュー行列を計算する
	camera_->matView = Inverse(worldTransform_.matWorld_);
}
