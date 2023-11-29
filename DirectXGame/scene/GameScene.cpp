#include "GameScene.h"
#include "AxisIndicator.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete debugCamera_;
	delete railCamera_;
	
	
}

void GameScene::Initialize() {
	Vector3 playerPosition(0, 0, 15);
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	textureHandle_ = TextureManager::Load("mario.png");

	ModelPlayer_.reset(Model::CreateFromOBJ("Player", true));
	ModelPlayerBullet_.reset(Model::CreateFromOBJ("PlayerBullet", true));
	model_.reset(Model::Create());

	viewProjection_.Initialize();

	railCamera_ = new RailCamera();
	railCamera_->Initalize();


	player_ = std::make_unique<Player>();
	player_->Initalize(ModelPlayer_.get(), ModelPlayerBullet_.get(), textureHandle_, playerPosition);

	railCamera_->SetTarget(&player_->GetWorldTransform());

	player_->SetViewProjection(&railCamera_->GetViewProjection());
	enemyModel_.reset(Model::CreateFromOBJ("Enemybody", true));
	enemy_ = std::make_unique<Enemy>();
	enemy_->Initialize(enemyModel_.get(), textureHandle_);
	enemy_->SetPlayer(player_.get());

	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	// Skydome
	modelSkydome_.reset (Model::CreateFromOBJ("skydome", true));
	skydome_ = new Skydome();
	skydome_->Initialize(modelSkydome_.get());
	skydome_->Update();

	// 時機ライフ
	LifeHandle_ = TextureManager::Load("UI/HP.png");

	sprite0 = Sprite::Create(LifeHandle_, {10.0f, 50.0f});
	sprite1 = Sprite::Create(LifeHandle_, {70.0f, 50.0f});
	sprite2 = Sprite::Create(LifeHandle_, {130.0f, 50.0f});

	
	 soundDataHandle_ = audio_->LoadWave("Shooting_Zone.wav");


}

void GameScene::Update() {

	if (!audio_->IsPlaying(voiceHandle_)) {

		 voiceHandle_ = audio_->PlayWave(soundDataHandle_, true, 0.5);
	 }
	audio_->ResumeWave(voiceHandle_);
	
	if (playerLife==0) {
		isGameOver = true;
	} else {
		isGameOver = false;
	}

	if (EnemyLife == 0) {
		isSceneEnd = true;
	} else {
		isSceneEnd = false;
	}

	

	// デスフラグの立った弾を削除
	enemyBullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;

			return true;
		}
		return false;
	});

	enemy_->Update();

	player_->Update();

	player_->SetEnemyPosition(enemy_->GetWorldPosition());

	CheckAllCollisions();

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
void GameScene::CheckAllCollisions() {
	Vector3 posA, posB;

	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();

#pragma region // 自キャラと敵弾の当たり判定
	posA = player_->GetWorldPosition();

	for (EnemyBullet* bullet : enemyBullets_) {
		posB = bullet->GetWorldPosition();

		float X = (posB.x - posA.x);
		float Y = (posB.y - posA.y);
		float Z = (posB.z - posA.z);

		float center = X * X + Y * Y + Z * Z;
		float R1 = 3.0f; // 自分で決める
		float R2 = 1.0f; // 自分で決める
		float RR = (R1 + R2);

		if (center <= (RR * RR)) {
			// 自キャラの衝突時コールバックを呼び出す
			player_->OnCollision();
			// 敵弾の衝突時コールバックを呼び出す
			bullet->OnCollision();
			playerLife--;
		}
	}
#pragma endregion

#pragma region // 自弾と敵キャラの当たり判定

	posA = enemy_->GetWorldPosition();

	for (PlayerBullet* bullet : playerBullets) {
			
			posB = bullet->GetWorldPosition();

			float X = (posB.x - posA.x);
			float Y = (posB.y - posA.y);
			float Z = (posB.z - posA.z);

			float center = sqrtf(X * X + Y * Y + Z * Z);
			float R1 = 1.5f; // 自分で決める
			float R2 = 0.5f; // 自分で決める
			float RR = (R1 + R2);

			if (center <= (RR * RR)) {
				// 敵キャラの衝突時コールバックを呼び出す
			enemy_->OnCollision();
				// 自弾の衝突時コールバックを呼び出す
			bullet->OnCollision();

				EnemyLife --;
			}

	}
	

#pragma endregion


}

void GameScene::Reset() {

	

	for (EnemyBullet* bullet : enemyBullets_) {
		    bullet->OnCollision();
	}

playerLife = 3;

EnemyLife = 40;

audio_->PauseWave(voiceHandle_);

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


	if (playerLife >= 3) {
		    sprite2->Draw();
	}
	if (playerLife >= 2 ) {
		    sprite1->Draw();
	}
	if (playerLife >= 1) {
		sprite0->Draw();
	}

	
	


	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
