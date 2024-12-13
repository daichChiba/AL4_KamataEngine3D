#define NOMINMAX
#define NOMINMIN
#include "Player.h"
using namespace KamataEngine;
#include "MathUtliltyForText.h"

Player::~Player() {
	for (PlayerBullet* bullet : bullets_) {
		delete bullet;
	}
}

void Player::Initialize(Model* model, uint32_t textureHandle,Vector3& pos) {
	// NULLポインタチェック
	assert(model);
	// モデルの情報を参照する
	model_ = model;
	textureHandle_ = textureHandle;

	// ワールド座標の初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;
}

void Player::Update() {
	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();

	// キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};

	// キャラクターの移動速度
	const float kCharacterSpeed = 0.2f;

	// 押したところに移動ベクトルの変更(左右)
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}

	// 押したところに移動ベクトルの変更(上下)
	if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	}

	Rotate();

	// 座標移動(ベクトルの加算)
	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;

	// キャラクター攻撃処理
	Attack();

	// 球更新
	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	// 球更新
	for (PlayerBullet* bullet : bullets_) {
		bullet->Update();
	}

	#ifdef DEBUG
	// キャラクターの座標を画面表示する処理
	ImGui::Begin("Debug1");
	// ImGui::DragFloat3("player", &worldTransform_.translation_.x, 0.01f);
	ImGui::InputFloat3("Inputfloat3", &worldTransform_.translation_.x);
	ImGui::SliderFloat3("SliderFloat3", &worldTransform_.translation_.x, -10.0f, 10.0f);
	ImGui::End();

	#endif // DEBUG


	// 移動限界座標
	const float kMoveLimitX = 6;
	const float kMoveLimitY = 3;

	// 範囲を超えない処理
	worldTransform_.translation_.x = std::max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = std::min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = std::max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = std::min(worldTransform_.translation_.y, +kMoveLimitY);


	// ワールド行列を更新させる
	worldTransform_.UpdateMatrix();
}

void Player::Rotate() {
	// 回転の速さ[ラジアン/frame]
	const float kRotSpeed = 0.02f;

	// 押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.y -= kRotSpeed;
	} else if (input_->PushKey(DIK_D)) {
		worldTransform_.rotation_.y += kRotSpeed;
	}
}

void Player::Draw(Camera& camera) {
	// 3Dモデルの描画
	model_->Draw(worldTransform_, camera, textureHandle_);

	// 弾描画
	for (PlayerBullet* bullet : bullets_) {
		bullet->Draw(camera);
	}
}

void Player::Attack() {
	if (input_->TriggerKey(DIK_SPACE)) {
		// 弾の速度
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);

		// 速度ベクトルを自機の向きに合わせて回転させる
		velocity = MathUtliltyForText::Transform(velocity, worldTransform_.matWorld_);

		// 弾を生成し、初期化
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, GetWorldPosition(), velocity);

		// 弾を登録する
		bullets_.push_back(newBullet);
	}
}

Vector3 Player::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

Vector3 Player::GetWorldRotate() {

	// ワールド座標を入れる変数
	Vector3 worldRotate;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldRotate.x = worldTransform_.rotation_.x;
	worldRotate.y = worldTransform_.rotation_.y;
	worldRotate.z = worldTransform_.rotation_.z;

	return worldRotate;
}

void Player::OnCollision() {}
