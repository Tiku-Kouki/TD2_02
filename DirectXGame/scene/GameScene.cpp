#include "GameScene.h"
#include "AxisIndicator.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete debugCamera_;
	delete modelSkydome_;
	delete ModelPlayer_;
}

void GameScene::Initialize() {
	Vector3 playerPosition(0, 0, 15);
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	textureHandle_ = TextureManager::Load("mario.png");

	ModelPlayer_ = Model::CreateFromOBJ("Player", true);
	model_.reset(Model::Create());

	viewProjection_.Initialize();

	railCamera_ = new RailCamera();
	railCamera_->Initalize();


	player_ = std::make_unique<Player>();
	player_->Initalize(ModelPlayer_, textureHandle_, playerPosition);

	railCamera_->SetTarget(&player_->GetWorldTransform());

	player_->SetViewProjection(&railCamera_->GetViewProjection());
	enemyModel_.reset(Model::Create());
	enemy_ = std::make_unique<Enemy>();
	enemy_->Initialize(enemyModel_.get(), textureHandle_, {0, 0, 50});
	enemy_->SetPlayer(player_.get());

	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	// Skydome
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);
	skydome_ = new Skydome();
	skydome_->Initialize(modelSkydome_);
	skydome_->Update();
}

void GameScene::Update() {

	enemy_->Update();

	player_->Update();

	player_->SetEnemyPosition(enemy_->GetWorldPosition());

#ifdef _DEBUG

	if (input_->PushKey(DIK_SPACE)) {
		isDebugCameraActive_ = true;
	}

#endif // DEBUG

	railCamera_->Update();
	viewProjection_.matView = railCamera_->GetViewProjection().matView;
	viewProjection_.matProjection = railCamera_->GetViewProjection().matProjection;

	viewProjection_.TransferMatrix();
	

	//viewProjection_.UpdateMatrix();
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

	player_->Draw(viewProjection_);

	enemy_->Draw(viewProjection_);

	skydome_->Draw(viewProjection_);

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
