#include "PlayerBullet.h"

void PlayerBullet::Initialize(Model* model, const Vector3& pos) {
	// NULLポインタチェック
	assert(model);
	// モデルの情報を参照する
	model_ = model;
	textureHandle_ = TextureManager::Load("black1x1.png");

	// ワールド座標の初期化
	worldTransform_.Initialize();
	// 引数で受け取った初期座標をセット
	worldTransform_.translation_ = pos;
}

void PlayerBullet::Update() {

	worldTransform_.UpdateMatrix();
}

void PlayerBullet::Draw(const Camera& camera) {
	// 3Dモデルの描画
	model_->Draw(worldTransform_, camera, textureHandle_);
}
