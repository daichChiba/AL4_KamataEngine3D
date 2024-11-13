#include "GameScene.h"
#include "MathUtliltyForText.h"
#include <cassert>

using namespace KamataEngine;

// インストラクタ
GameScene::GameScene() {}
// デストラクタ
GameScene::~GameScene() {

	// 3Dモデルデータの解放
	delete model_;
	// 自キャラの開放
	delete player_;

	// デバックカメラの開放
	delete debugCamera_;

	// 敵キャラの開放
	delete enemy_;

	// 天球の開放
	delete skyDome_;

	// 天球モデルの開放
	delete modelSkydome_;
}

void GameScene::Initialize() {

	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("mario.jpg");
	enemyTextureHandle_ = TextureManager::Load("enemy.png");

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// 3Dモデルデータの生成
	model_ = Model::Create();
	// カメラの初期化
	camera_.farZ = 1500.0f;
	camera_.Initialize();

	// 自キャラの生成
	player_ = new Player();
	// 自キャラの初期化
	player_->Initialize(model_, textureHandle_);

	// 敵キャラの生成
	Vector3 enemyPos = {5.0f, 5.0f, 100.0f};
	enemy_ = new Enemy();
	// 　敵キャラの初期化
	enemy_->Initialize(model_, enemyTextureHandle_, enemyPos);
	enemy_->SetPlayer(player_);
	debugCamera_ = new DebugCamera(640, 360);

	//天球モデルの生成
	modelSkydome_ = Model::CreateFromOBJ("SkyDome", true);

	//天球の生成
	skyDome_ = new SkyDome();
	// 天球の初期化
	skyDome_->Initialize(modelSkydome_);


	// 軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するカメラを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetCamera(&camera_);
}

void GameScene::Update() {
	// 自キャラの更新
	player_->Update();
	// 敵キャラの更新
	enemy_->Update();
	// デバックカメラの更新
	debugCamera_->Update();
	// 天球の更新
	skyDome_->Update();

	// 当たり判定
	CheckAllCollisions();
#ifdef _DEBUG
	if (input_->TriggerKey(DIK_0)) {
		isDebugCameraActive_ = !isDebugCameraActive_;
	}
#endif // DEBUG
	if (isDebugCameraActive_) {
		debugCamera_->Update();

		// デバックカメラのビュー行列
		camera_.matView = debugCamera_->GetCamera().matView;
		// デバックカメラのプロジェクション行列
		camera_.matProjection = debugCamera_->GetCamera().matProjection;
		// ビュープロジェクション行列のと転送
		camera_.TransferMatrix();
	} else {
		// ビュープロジェクション行列の更新と転送
		camera_.UpdateMatrix();
	}
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 自キャラの描画
	player_->Draw(camera_);
	// 敵キャラの描画
	enemy_->Draw(camera_);
	// 天球の描画
	skyDome_->Draw(camera_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::CheckAllCollisions() {
	// 判定対象AとBの座標
	Vector3 posA, posB;

	// 自弾リストの取得
	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();
	// 敵弾リストの取得
	const std::list<EnemyBullet*>& enemybullets = enemy_->GetBullets();

#pragma region 自キャラと敵弾の当たり判定
	// 自キャラの座標
	posA = player_->GetWorldPosition();
	// 自キャラの敵弾すべての当たり判定
	for (EnemyBullet* bullet : enemybullets) {
		// 敵の座標
		posB = bullet->GetWorldPosition();

		Vector3 A2B = Sphere(posA, posB);
		float len = Length(A2B);
		float radius = bullet->GetRadius() + player_->GetRadius();

		if (len <= sqrt(radius * radius)) {
			// 自キャラの衝突時コールバックを呼び出す
			player_->OnCollision();
			// 自弾の衝突時コールバックを呼び出す
			bullet->OnCollision();
		}
	}

#pragma endregion

#pragma region 自弾と敵キャラの当たり判定
	// 自キャラの座標
	posA = enemy_->GetWorldPosition();
	// 自キャラの敵弾すべての当たり判定
	for (PlayerBullet* bullet : playerBullets) {
		// 敵の座標
		posB = bullet->GetWorldPosition();

		Vector3 A2B = Sphere(posA, posB);
		float len = Length(A2B);
		float radius = bullet->GetRadius() + enemy_->GetRadius();

		if (len <= sqrt(radius * radius)) {
			// 敵キャラの衝突時コールバックを呼び出す
			enemy_->OnCollision();
			// 自弾の衝突時コールバックを呼び出す
			bullet->OnCollision();
		}
	}
#pragma endregion

#pragma region 自弾と敵弾の当たり判定
	for (PlayerBullet* bullet : playerBullets) {
		for (EnemyBullet* bullet_ : enemybullets) {
			// 自弾の座標
			posA = bullet->GetWorldPosition();
			// 敵弾の座標
			posB = bullet_->GetWorldPosition();
			Vector3 A2B = Sphere(posA, posB);
			float len = Length(A2B);
			float radius = bullet->GetRadius() + bullet_->GetRadius();

			if (len <= sqrt(radius * radius)) {
				// 自弾の衝突時コールバックを呼び出す
				bullet->OnCollision();
				// 敵弾の衝突時コールバックを呼び出す
				bullet_->OnCollision();
			}
		}
	}
#pragma endregion
}
