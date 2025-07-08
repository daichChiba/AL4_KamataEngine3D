#include <KamataEngine.h>

using namespace KamataEngine;
#include"scene/GameScene.h"
#include "scene/TitleScene.h"
#include "scene/ClearScene.h"
#include"scene/OverScene.h"


// シーン（型）
enum class Scene {
	kUnknown = 0,
	kTitle,
	kGame,
	kClear,
	kOver,
};
// 現在シーン（型）
Scene scene = Scene::kUnknown;
void ChangeScene();
void UpdateScene();
void DrawScene();
// ゲームシーンの作成
GameScene* gameScene = nullptr;
TitleScene* titleScene = nullptr;
ClearScene* clearScene = nullptr;
OverScene* overScene = nullptr;
//gameScene = new GameScene;
//gameScene->Initialize();
//gameScene->Update();
//gameScene->Draw();

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	WinApp* win = nullptr;
	DirectXCommon* dxCommon = nullptr;
	// 汎用機能
	Input* input = nullptr;
	Audio* audio = nullptr;
	AxisIndicator* axisIndicator = nullptr;
	PrimitiveDrawer* primitiveDrawer = nullptr;

	// ゲームウィンドウの作成
	win = WinApp::GetInstance();
	win->CreateGameWindow(L"空中戦");

	// DirectX初期化処理
	dxCommon = DirectXCommon::GetInstance();
	dxCommon->Initialize(win);

#pragma region 汎用機能初期化
	// ImGuiの初期化
	ImGuiManager* imguiManager = ImGuiManager::GetInstance();
	imguiManager->Initialize(win, dxCommon);

	// 入力の初期化
	input = Input::GetInstance();
	input->Initialize();

	// オーディオの初期化
	audio = Audio::GetInstance();
	audio->Initialize();

	// テクスチャマネージャの初期化
	TextureManager::GetInstance()->Initialize(dxCommon->GetDevice());
	TextureManager::Load("white1x1.png");

	// スプライト静的初期化
	Sprite::StaticInitialize(dxCommon->GetDevice(), WinApp::kWindowWidth, WinApp::kWindowHeight);

	// 3Dモデル静的初期化
	Model::StaticInitialize();

	// 軸方向表示初期化
	axisIndicator = AxisIndicator::GetInstance();
	axisIndicator->Initialize();

	primitiveDrawer = PrimitiveDrawer::GetInstance();
	primitiveDrawer->Initialize();
#pragma endregion
	// ゲームシーンの初期化
	titleScene = new TitleScene();
	titleScene->Initialize();
	scene = Scene::kTitle;


	// メインループ
	while (true) {
		// メッセージ処理
		if (win->ProcessMessage()) {
			break;
		}

		// ImGui受付開始
		imguiManager->Begin();
		// 入力関連の毎フレーム処理
		input->Update();
		// ゲームシーンの毎フレーム処理
		ChangeScene();
		UpdateScene();
		// 軸表示の更新
		axisIndicator->Update();
		// ImGui受付終了
		imguiManager->End();

		// 描画開始
		dxCommon->PreDraw();
		DrawScene();
		// 軸表示の描画
		axisIndicator->Draw();
		// プリミティブ描画のリセット
		primitiveDrawer->Reset();
		// ImGui描画
		imguiManager->Draw();
		// 描画終了
		dxCommon->PostDraw();
	}

	delete gameScene;
	delete clearScene;
	delete overScene;
	delete titleScene;

	// 3Dモデル解放
	Model::StaticFinalize();
	audio->Finalize();
	// ImGui解放
	imguiManager->Finalize();

	// ゲームウィンドウの破棄
	win->TerminateGameWindow();

	return 0;
}

void ChangeScene() {
	switch (scene) {
	case Scene::kTitle:
		if (titleScene->IsFinished()==true) {
			// シーン変更
			scene = Scene::kGame;
			// 旧シーンの開放
			delete titleScene;
			titleScene = nullptr;
			// 新シーンの生成と初期化
			gameScene = new GameScene;
			gameScene->Initialize();
		}
		break;
	case Scene::kGame:
		if (gameScene->IsClear()==true) {
			if (gameScene->IsFinished() == true) {
				// シーン変更
				scene = Scene::kClear;
				// 旧シーンの開放
				delete gameScene;
				gameScene = nullptr;
				// 新シーンの生成と初期化
				clearScene = new ClearScene;
				clearScene->Initialize();
			}
		} else {
			if (gameScene->IsFinished() == true) {
				// シーン変更
				scene = Scene::kOver;
				// 旧シーンの開放
				delete gameScene;
				gameScene = nullptr;
				// 新シーンの生成と初期化
				overScene = new OverScene;
				overScene->Initialize();
			}
		}

		break;
	case Scene::kClear:
		if (clearScene->IsFinished() == true) {
			// シーン変更
			scene = Scene::kTitle;
			// 旧シーンの開放
			delete clearScene;
			clearScene = nullptr;
			// 新シーンの生成と初期化
			titleScene = new TitleScene;
			titleScene->Initialize();
		}
		break;

	case Scene::kOver:
		if (overScene->IsFinished() == true) {
			// シーン変更
			scene = Scene::kTitle;
			// 旧シーンの開放
			delete overScene;
			overScene = nullptr;
			// 新シーンの生成と初期化
			titleScene = new TitleScene;
			titleScene->Initialize();
		}
		break;
	}
}

void UpdateScene() {
	switch (scene) {
	case Scene::kTitle:
		titleScene->Update();
		break;
	case Scene::kGame:
		gameScene->Update();
		break;
	case Scene::kClear:
		clearScene->Update();
		break;
	case Scene::kOver:
		overScene->Update();
		break;
	}
}

void DrawScene() {
	switch (scene) {
	case Scene::kTitle:
		titleScene->Draw();
		break;
	case Scene::kGame:
		gameScene->Draw();
		break;
	case Scene::kClear:
		clearScene->Draw();
		break;
	case Scene::kOver:
		overScene->Draw();
		break;
	}
}
