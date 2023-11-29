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
	
	bool isDebugCameraActive_ = false;
	DebugCamera* debugCamera_ = nullptr;

	 // ライフ
	uint32_t LifeHandle_;

	Sprite* sprite0 = nullptr;
	Sprite* sprite1 = nullptr;
	Sprite* sprite2 = nullptr;

	RailCamera* railCamera_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
