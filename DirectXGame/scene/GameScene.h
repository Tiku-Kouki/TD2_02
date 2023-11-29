#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Player.h"
#include "Enemy.h"
#include"DebugCamera.h"
#include <Skydome.h>
#include "RailCamera.h"
#include "scene.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void CheckAllCollisions();

	void Reset();

	bool isSceneEnd = false;
	bool IsSceneEnd() { return isSceneEnd; }

	bool isGameOver = false;
	bool IsGameOver() { return isGameOver; }

	SceneType NextScene() {

		if (isSceneEnd == true) {
			return SceneType::kClearGame;
		} else if (isGameOver == true) {
			return SceneType::kGameOver;
		}
		return SceneType::kGamePlay;
	}




private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	uint32_t textureHandle_ = 0;

	
	ViewProjection viewProjection_;
	WorldTransform worldTransform_;
	Skydome* skydome_ = nullptr;
	std::unique_ptr<Model> modelSkydome_ = nullptr;
	std::unique_ptr<Model> ModelPlayer_ = nullptr;
	std::unique_ptr<Model> ModelPlayerBullet_ = nullptr;
	std::unique_ptr<Model> model_ = nullptr;
	std::unique_ptr<Model> enemyModel_ = nullptr;
	
	std::unique_ptr<Enemy> enemy_ = nullptr;
	std::unique_ptr<Player> player_ = nullptr;
	
	std::list<EnemyBullet*> enemyBullets_;


	bool isDebugCameraActive_ = false;
	DebugCamera* debugCamera_ = nullptr;

	 // ライフ
	uint32_t LifeHandle_;

	int playerLife = 3;

	int EnemyLife = 40;

	Sprite* sprite0 = nullptr;
	Sprite* sprite1 = nullptr;
	Sprite* sprite2 = nullptr;

	RailCamera* railCamera_ = nullptr;

	// サウンドハンドル
	uint32_t soundDataHandle_ = 0;

	uint32_t voiceHandle_ = 0;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
