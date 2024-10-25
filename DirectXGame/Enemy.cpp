#include "Enemy.h"

void Enemy::Initialize(Model* model, uint32_t textureHandle, const Vector3& pos) {
	// NULLポインタチェック
	assert(model);
	// モデルの情報を参照する
	model_ = model;
	textureHandle_ = textureHandle;

	// ワールド座標の初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;
}

void Enemy::Update() {
	// ワールド行列を更新させる
	worldTransform_.TransferMatrix();
}

void Enemy::Draw(Camera& camera) {
	//3Dモデルを描画させる
	model_->Draw(worldTransform_, camera, textureHandle_);
}
