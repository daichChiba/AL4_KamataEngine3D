#include "GameScene.h"
#include <cassert>

namespace KamataEngine {
	// インストラクタ
	GameScene::GameScene() {}
	// デストラクタ
	GameScene::~GameScene() {

		//3Dモデルデータの解放
		delete model_;
		//自キャラの開放
	    delete player_;


	}



	void GameScene::Initialize() {

		// ファイル名を指定してテクスチャを読み込む
		textureHandle_ = TextureManager::Load("mario.jpg");


		dxCommon_ = DirectXCommon::GetInstance();
		input_ = Input::GetInstance();
		audio_ = Audio::GetInstance();

		//3Dモデルデータの生成
		model_ = Model::Create();
		//ビュープロジェクションの初期化
	    camera_.Initialize();

		//自キャラの生成
		player_ = new Player();
		//自キャラの初期化	
		player_->Initialize(model_,textureHandle_);

	}

	void GameScene::Update() {
		//自キャラの更新
	    player_->Update();
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

		//自キャラの描画
	    player_->Draw(camera_);

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

}

