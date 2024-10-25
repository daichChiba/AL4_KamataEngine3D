#include "PlayerBullet.h"
#include "MathUtliltyForText.h"


int32_t const PlayerBullet::kLifeTime;
void PlayerBullet::Initialize(Model* model, const Vector3& pos, const Vector3& velocity) {
	// NULLポインタチェック
	assert(model);
	// モデルの情報を参照する
	model_ = model;
	textureHandle_ = TextureManager::Load("black1x1.png");

	// ワールド座標の初期化
	worldTransform_.Initialize();
	// 引数で受け取った初期座標をセット
	worldTransform_.translation_ = pos;
	// 引数で受け取った速度をメンバ変数にセット
	velocity_ = velocity;
}

void PlayerBullet::Update() {


	//座標を移動させる(1フレーム分の移動量を足し込む)
	worldTransform_.translation_ += velocity_;

	//時間経過でデス
	if (--deathTimer_<=0) {
		isDead_ = true;
	}

	worldTransform_.UpdateMatrix();
}

void PlayerBullet::Draw(const Camera& camera) {
	// 3Dモデルの描画
	model_->Draw(worldTransform_, camera, textureHandle_);
}
