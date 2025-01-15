#include "TitleScene.h"

TitleScene::TitleScene() {
}

TitleScene::~TitleScene() {
	delete sprite;
}


void TitleScene::Initialize() {
	textureHandle_ = TextureManager::Load("title.png");
	sprite = Sprite::Create(textureHandle_, {0, 0});
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// サウンドデータの読み込み
	soundDataHandle_ = audio_->LoadWave("title.wav");
	// 音声再生
	audio_->PauseWave(soundDataHandle_);
	// 第2引数でループ再生を指定
	voiceHandle_ = audio_->PlayWave(soundDataHandle_, true);
}

void TitleScene::Update() {
	if (Input::GetInstance()->ReleseKey(DIK_SPACE)) {
		finished_ = true;
		// 音声停止
		audio_->StopWave(voiceHandle_);
	}
}

void TitleScene::Draw() {
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
	///
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	sprite->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();
}
