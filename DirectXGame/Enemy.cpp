#include "Enemy.h"
using namespace KamataEngine;
#include "MathUtliltyForText.h"
#include "Player.h"
#include "GameScene.h"
int const Enemy::kFireInterval;
using namespace MathUtility;

Enemy::~Enemy() {
	gameScene_->AddEnemyBulletRelese();
}

void Enemy::Initialize(Model* model, uint32_t textureHandle, const Vector3& pos) {
	// NULLポインタチェック
	assert(model);
	// モデルの情報を参照する
	model_ = model;
	textureHandle_ = textureHandle;

	// ワールド座標の初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;

	ApproachInitialize();

}

void Enemy::Update() {

	#ifdef DEBUG
	//// キャラクターの座標を画面表示する処理
	// ImGui::Begin("Debug2");
	//// ImGui::DragFloat3("player", &worldTransform_.translation_.x, 0.01f);
	// ImGui::InputFloat3("Inputfloat", &worldTransform_.translation_.x);
	// ImGui::SliderFloat3("SliderFloat", &worldTransform_.translation_.x, -10.0f, 10.0f);
	// ImGui::End();


	#endif // DEBUG





	switch (phase_) {
	case Enemy::Phase::Approach:
		ApproachUpdate();

		break;
	case Enemy::Phase::Leave:
		LeaveUpdate();
		break;
	}





	// 球更新


	// アフィン変換行列の作成
	worldTransform_.matWorld_ = MathUtliltyForText::MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);


	// ワールド行列を更新させる
	worldTransform_.TransferMatrix();
}

void Enemy::Draw(Camera& camera) {
	// 3Dモデルの描画
	model_->Draw(worldTransform_, camera, textureHandle_);
	// 弾描画
	gameScene_->AddEnemyBulletDraw();
}

void Enemy::Fire() {
	// 弾の速度
	const float kBulletSpeed = 0.05f;
	Vector3 velocity(0, 0, 0);

	//自キャラのワールド座標を取得する
	Vector3 playerPos = player_->GetWorldPosition();
	//敵キャラのワールド座標を取得する
	Vector3 enemyPos = GetWorldPosition();
	//敵キャラから自キャラへの差分ベクトルを作成する
	Vector3 enemy2player = playerPos - enemyPos;
	//ベクトルの正規化
	MathUtliltyForText::Normalize(enemy2player);
	//ベクトルの長さを早さに合わせる
	velocity = enemy2player * kBulletSpeed;

	// 速度ベクトルを敵の向きに合わせて回転させる
	velocity = MathUtliltyForText::Transform(velocity, worldTransform_.matWorld_);

	// 弾を生成し、初期化
	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);

	//bullet_ = newBullet;
	// 弾を登録する
	gameScene_->AddEnemyBullet(newBullet);
}

void Enemy::ApproachInitialize() {
	//発射タイマーを初期化
	FireTimer = kFireInterval;
}

void Enemy::ApproachUpdate() {
	// キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};
	// 接近
	const float kApproachSpeed = 0.2f;

	move.z -= kApproachSpeed;

	// 移動(ベクトルの加算)
	worldTransform_.translation_ += move;

	//発射タイマーカウントダウン
	--FireTimer;
	//指定時間に達した
	if (FireTimer<=0) {
		//弾を発射
		Fire();
		//発射タイマーを初期化
		FireTimer = kFireInterval;
	}

	if (worldTransform_.translation_.z < 10.0f) {
		phase_ = Phase::Leave;
	}
}

void Enemy::LeaveUpdate() {
	// キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};
	//　離脱
	const float kLeaveSpeed = 0.1f;


	move.x -= kLeaveSpeed;
	move.y += kLeaveSpeed;

	// 移動(ベクトルの加算)
	worldTransform_.translation_ += move;
}

Vector3 Enemy::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}

void Enemy::OnCollision() {
}
