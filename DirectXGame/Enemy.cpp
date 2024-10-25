#include "Enemy.h"
using namespace KamataEngine;
#include "MathUtliltyForText.h"

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

	//// キャラクターの座標を画面表示する処理
	//ImGui::Begin("Debug2");
	//// ImGui::DragFloat3("player", &worldTransform_.translation_.x, 0.01f);
	//ImGui::InputFloat3("Inputfloat", &worldTransform_.translation_.x);
	//ImGui::SliderFloat3("SliderFloat", &worldTransform_.translation_.x, -10.0f, 10.0f);
	//ImGui::End();

	// キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};
	// キャラクターの移動速度
	const float kCharacterSpeed = 0.2f;

	move.z -= kCharacterSpeed;

	// 座標移動(ベクトルの加算)
	worldTransform_.translation_ += move;


	// アフィン変換行列の作成
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);


	// ワールド行列を更新させる
	worldTransform_.TransferMatrix();
}

void Enemy::Draw(Camera& camera) {
	// 3Dモデルの描画
	model_->Draw(worldTransform_, camera, textureHandle_);
}
