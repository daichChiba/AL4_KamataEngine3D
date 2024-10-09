#include "Player.h"


using namespace KamataEngine;
void Player::Initialize(Model* model, uint32_t textureHandle) {
	//NULLポインタチェック
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;

	worldTransform_.Initialize();

	}

	void Player::Update() {

		//ワールド行列を更新させる
		worldTransform_.TransferMatrix();
	}

	void Player::Draw(Camera& camera) {
		//3Dモデルの描画
	    model_->Draw(worldTransform_, camera, textureHandle_);
	}


