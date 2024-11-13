#include "SkyDome.h"

void SkyDome::Initialize(Model* model) {
	// NULLポインタチェック
	assert(model);
	// モデルの情報を参照する
	model_ = model;

	// ワールド座標の初期化
	worldTransform_.Initialize();
}

void SkyDome::Update() {
	worldTransform_.UpdateMatrix();
}

void SkyDome::Draw(Camera& camera) {
	// 3Dモデルの描画
	model_->Draw(worldTransform_, camera);
}
